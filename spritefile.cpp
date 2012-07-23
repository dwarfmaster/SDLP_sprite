#include "spritefile.hpp"

namespace sdl
{
	SpriteFile::SpriteFile()
	{
		clear();
	}

	SpriteFile::SpriteFile(const path_t& path)
	{
		load(path);
	}

	SpriteFile::SpriteFile(const SpriteFile& cp)
	{
		set(cp);
	}

	void SpriteFile::clear()
	{
		m_path.clear();
		m_img.reset();
		m_sprites.clear();
	}

	bool SpriteFile::load(const path_t& path)
	{
		// On ouvre le fichier
		TiXmlDocument file(path.string());
		if(!file.LoadFile())
			return false;

		// On trouve l'élément image
		TiXmlElement* elem = file.FirstChildElement("image");
		if(elem == NULL )
			return false;

		// On récupère le chemin
		path_t imgpath = elem->Attribute("path");
		if(imgpath.empty()
				|| !boost::filesystem::exists(imgpath)
				|| boost::filesystem::is_directory(imgpath) )
			return false;
		m_path = imgpath;

		// On charge l'image
		SDL_Surface* surf = IMG_Load(m_path.string().c_str());
		if(surf == NULL)
			return false;
		Liberator lib;
		m_img.reset(surf, lib);

		// On charge les sprites
		elem = file.FirstChildElement("sprite");
		while(elem)
		{
			std::string id = elem->Attribute("id");
			if(!id.empty())
				parseSprite(elem, &m_sprites[id]);

			elem = elem->NextSiblingElement("sprite");
		}

		return true;
	}

	void SpriteFile::set(const SpriteFile& cp)
	{
		m_path = cp.m_path;
		m_img = cp.m_img;
		m_sprites = cp.m_sprites;
	}

	SpriteFile& SpriteFile::operator=(const SpriteFile& cp)
	{
		set(cp);
		return *this;
	}

	ASprite SpriteFile::getSprite(std::string id)
	{
		ASprite err;
		if(!exist(id))
			return err;

		boost::shared_ptr<SDL_Surface> img;
		SDL_Surface* surf = SDL_CreateRGBSurface(SDL_HWSURFACE, m_sprites[id].rect->w, m_sprites[id].rect->h, 24, 0, 0, 0, 0);
		if(SDL_GetVideoSurface() != NULL)
		{
			SDL_Surface* tmp = SDL_DisplayFormatAlpha(surf);
			if(tmp == NULL)
				return err;
			else
				SDL_FreeSurface(surf);
			surf=tmp;
		}

		SDL_Rect clip = m_sprites[id].rect.rect();
		SDL_BlitSurface(m_img.get(), &clip, surf, NULL);
		Liberator lib;
		img.reset(surf, lib);

		return ASprite( m_sprites[id].gaabbs, m_sprites[id].hotp, img);
	}

	ASprite SpriteFile::operator[](std::string id)
	{
		return getSprite(id);
	}

	std::vector<std::string> SpriteFile::listIds() const
	{
		std::vector<std::string> ids;

		for(csprite_iterator it = m_sprites.begin(); it != m_sprites.end(); ++it)
			ids.push_back(it->first);

		return ids;
	}

	bool SpriteFile::parseSprite(TiXmlElement* spriten, SpriteFile::sprite* p)
	{
		// On récupère le clip rect
		parseRect(spriten, &p->rect);

		// On récupère le node hotpoint
		TiXmlElement* elem = spriten->FirstChildElement("hotpoint");
		if(elem == NULL) 
			return false;

		// On en récupère la position
		std::string str(elem->Attribute("x"));
		if(str.empty())
			return false;
		p->hotp.x = sdl::atoi(str);

		str = elem->Attribute("y");
		if(str.empty())
			return false;
		p->hotp.y = sdl::atoi(str);

		// On récupère les SAABBs
		elem = spriten->FirstChildElement("gaabb");
		while(elem)
		{
			std::string id = elem->Attribute("id");
			if(!id.empty())
				this->parseGAABB(elem, &p->gaabbs[id]);
			elem = elem->NextSiblingElement("gaabb");
		}

		return true;
	}

	void SpriteFile::parseRect(TiXmlElement* spriten, AABB* p)
	{
		int x=0, y=0, w=10, h=10;

		std::string str = spriten->Attribute("x");
		if(!str.empty())
			x=atoi(str);
		if(x < 0)
			x=0;
		else if( x > m_img->w-10 )
			x = m_img->w - 10;

		str = spriten->Attribute("y");
		if(!str.empty())
			y=atoi(str);
		if(y < 0)
			y=0;
		else if( y > m_img->h-10 )
			y = m_img->h - 10;

		str = spriten->Attribute("w");
		if(!str.empty())
			w=atoi(str);
		if(w < 10)
			w=10;
		else if( x+w > m_img->w )
			w = m_img->w - x;

		str = spriten->Attribute("h");
		if(!str.empty())
			h=atoi(str);
		if(h < 10)
			h=10;
		else if( y+h > m_img->h )
			h = m_img->h - y;

		p->set(makeRect(x, y, w, h));
	}

	bool SpriteFile::parseGAABB(TiXmlElement* gaabbn, gaabb* p)
	{
		// On récupère la priorité
		std::string prio = gaabbn->Attribute("priority");
		if(prio.empty())
			return false;
		p->priority = atoi(prio);

		// On récupère les saabbs
		TiXmlElement* saabb = gaabbn->FirstChildElement("saabb");
		while(saabb)
		{
			SDL_Rect saabbr;

			std::string str = saabb->Attribute("x");
			if(str.empty())
				break;
			saabbr.x = atoi(str);
			str = saabb->Attribute("y");
			if(str.empty())
				break;
			saabbr.y = atoi(str);
			str = saabb->Attribute("w");
			if(str.empty())
				break;
			saabbr.w = atoi(str);
			str = saabb->Attribute("h");
			if(str.empty())
				break;
			saabbr.h = atoi(str);

			p->saabbs.push_back(saabbr);

			saabb = saabb->NextSiblingElement("saabb");
		}

		return true;
	}

	bool SpriteFile::exist(std::string id) const
	{
		if(m_sprites.find(id) != m_sprites.end())
			return true;
		else
			return false;
	}

	bool SpriteFile::changeSprite(std::string id, const std::map<std::string, gaabb>& groups, const Pointsi& hotp, const AABB& rect)
	{
		if(!exist(id))
			return false;

		m_sprites[id].gaabbs = groups;
		m_sprites[id].hotp = hotp;
		m_sprites[id].rect = rect;

		return true;
	}

	bool SpriteFile::changeSprite(std::string id, const std::map<std::string, gaabb>& groups, const Pointsi& hotp)
	{
		if(!exist(id))
			return false;

		return changeSprite(id, groups, hotp, m_sprites[id].rect);
	}

	bool SpriteFile::addSprite(std::string id, const std::map<std::string, gaabb>& groups, const Pointsi& hotp, const AABB& rect)
	{
		if(exist(id))
			return false;

		m_sprites[id].gaabbs = groups;
		m_sprites[id].hotp = hotp;
		m_sprites[id].rect = rect;

		return true;
	}

	bool SpriteFile::deleteSprite(std::string id)
	{
		if(!exist(id))
			return false;

		m_sprites.erase(id);

		return true;
	}

	bool SpriteFile::save(path_t path) const
	{
		boost::filesystem::ofstream file(path);
		if(!file)
			return false;

		file << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n\n";
		file << "<image path=\"" << m_path.string() << "\" />\n\n";

		for(csprite_iterator it = m_sprites.begin(); it != m_sprites.end(); ++it)
		{
			file << "<sprite id=\"" << it->first 
				<< "\" x=\"" << itoa(it->second.rect->x)
				<< "\" y=\"" << itoa(it->second.rect->y)
				<< "\" w=\"" << itoa(it->second.rect->w)
				<< "\" h=\"" << itoa(it->second.rect->h)
				<< "\" >\n";
			file << "\t<hotpoint x=\"" << itoa(it->second.hotp.x) << "\" y=\"" << itoa(it->second.hotp.y) << "\" />\n\n";

			for(std::map<std::string,gaabb>::const_iterator git = it->second.gaabbs.begin(); git != it->second.gaabbs.end(); ++git)
			{
				file << "\t<gaabb id=\"" << git->first << "\" priority=\"" << itoa(git->second.priority) << "\" >\n";

				for(size_t i=0; i < git->second.saabbs.size(); ++i)
				{
					file << "\t\t<saabb x=\"" << itoa(git->second.saabbs[i]->x)
						<< "\" y=\"" << itoa(git->second.saabbs[i]->y)
						<< "\" w=\"" << itoa(git->second.saabbs[i]->w)
						<< "\" h=\"" << itoa(git->second.saabbs[i]->h)
						<< "\" />\n";
				}

				file << "\t</gaabb>\n\n";
			}

			file << "</sprite>\n\n";
		}

		return true;
	}

	bool SpriteFile::save() const
	{
		return save(m_path);
	}

};

