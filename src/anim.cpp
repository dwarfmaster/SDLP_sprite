
/*!
 * \file anim.cpp
 * \brief Implémente la classe sdl::Anim.
 */

#include "anim.hpp"

namespace sdl
{
	Anim::Anim()
	{
		clear();
	}

	Anim::Anim(const Anim& cp)
	{
		set(cp);
	}

	Anim::Anim(const path_t& path)
	{
		load(path);
	}

	void Anim::clear()
	{
		m_lastTime = 0;
		m_act = 0;
		m_pause = true;
		m_timeStay = 0;
		m_speed = 1.0;

		for(size_t i=0; i < m_frames.size(); ++i)
		{
			if(m_frames[i].toFree)
				delete m_frames[i].sprite;
		}
		m_frames.clear();
		m_default = 0;
		m_loaded = false;
	}

	void Anim::set(const Anim& cp)
	{
		m_lastTime = cp.m_lastTime;
		m_act = cp.m_act;
		m_pause = cp.m_pause;
		m_timeStay = cp.m_timeStay;
		m_speed = cp.m_speed;

		m_frames = cp.m_frames;
		for(size_t i=0; i < m_frames.size(); ++i)
		{
			if(m_frames[i].toFree) // On fait une copie de ce qui devait être libéré
			{
				ASprite* tmp = m_frames[i].sprite;
				m_frames[i].sprite = new ASprite(*tmp);
			}
		}
		m_default = cp.m_default;
		m_loaded = cp.m_loaded;
	}

	Anim& Anim::operator=(const Anim& cp)
	{
		set(cp);
		return *this;
	}

	bool Anim::load(const path_t& path )
	{
		clear();
		path_t basepath = path.parent_path();
		if( basepath.empty() )
			basepath = "./";
		else
			basepath += "/";

		// On ouvre le document
		TiXmlDocument doc(path.string());
		if(!doc.LoadFile())
			return false;

		// On trouve l'anim
		TiXmlElement* elem = doc.FirstChildElement("anim");
		if(elem == NULL)
			return false;

		// On trouve le temps par défaut
		if( elem->Attribute("time") == NULL )
			m_default = 1000;
		else
		{
			std::string time = elem->Attribute("time");
			if(time.empty())
				m_default = 1000;
			else
			{
				m_default = atoi(time);
				if(m_default == 0)
					m_default = 1000;
			}
		}

		// On charge les sprites
		std::vector<frame> sprites;
		parseSprites(&sprites, elem, basepath);
		m_frames = sprites;

		return true;
	}

	bool Anim::save(const path_t& path)
	{
		boost::filesystem::ofstream file(path);

		if( !file )
			return false;

		file << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n" << std::endl;

		file << "<anim time=\"" << m_default << "\">" << std::endl;
		size_t nb = 0;
		for(cframe_iterator it = m_frames.begin(); it != m_frames.end(); ++it)
		{
			++nb;
			if( !it->id.empty() )
			{
				file << "\t<sprite nb=\"" << nb 
					<< "\" id=\"" << it->name << "\" ";
				if( it->time != m_default )
					file << "time=\"" << it->time << "\" ";
				file << "path=\"" << it->path << ":" << it->id << "\" />" << std::endl;
			}
			else
			{
				std::string toadd("");
				toadd += "nb=\"";
				toadd += itoa(nb);
				toadd += "\" path=\"";
				toadd += it->path;
				toadd += "\"";
				if( it->time != m_default )
				{
					toadd += " time=\"";
					toadd += itoa(it->time);
					toadd += "\" ";
				}

				file << SpriteFile::xmlSprite(*it->sprite, it->name, it->rect, toadd, "\t") << std::endl;
			}
		}
		file << "</anim>\n" << std::endl;

		return true;
	}

	bool Anim::isLoaded() const
	{
		return m_loaded;
	}

	Anim::operator bool() const
	{
		return isLoaded();
	}

	bool Anim::operator!() const
	{
		return !isLoaded();
	}

	std::vector<std::string> Anim::frames() const
	{
		std::vector<std::string> names;
		for(size_t i=0; i < m_frames.size(); ++i)
			names.push_back( m_frames[i].name );
		return names;
	}

	size_t Anim::nbFrames() const
	{
		return m_frames.size();
	}

	size_t Anim::idFromName(const std::string& name) const
	{
		size_t nb = 0;
		for(cframe_iterator it = m_frames.begin(); it != m_frames.end(); ++it)
		{
			if( it->name == name )
				return nb;
			++nb;
		}

		return m_frames.size();
	}

	std::string Anim::nameFromId(size_t id) const
	{
		return m_frames.at(id).name;
	}

	ASprite* Anim::sprite(const std::string& frame) const
	{
		return m_frames.at( idFromName(frame) ).sprite;
	}

	ASprite* Anim::operator[](const std::string& frame) const
	{
		return sprite(frame);
	}

	Uint32 Anim::time(const std::string& frame) const
	{
		return m_frames.at( idFromName(frame) ).time;
	}

	Uint32 Anim::time() const
	{
		Uint32 ttime = 0;
		for(size_t i=0; i < m_frames.size(); ++i)
			ttime += m_frames[i].time;
		return ttime;
	}

	Uint32 Anim::defaultTime() const
	{
		return m_default;
	}

	bool Anim::changeSprite(const std::string& frame, ASprite* nsprite, bool tofree)
	{
		if( !exist(frame) )
			return false;

		size_t id = idFromName(frame);
		m_frames[id].sprite = nsprite;
		m_frames[id].toFree = tofree;

		return true;
	}

	bool Anim::changeTime(const std::string& frame, Uint32 ntime)
	{
		if( !exist(frame) )
			return false;

		size_t id = idFromName(frame);
		m_frames[id].time = ntime;

		return true;
	}

	bool Anim::reorder(const std::vector<std::string>& norder)
	{
		if(norder.size() != m_frames.size())
			return false;

		std::vector<frame> frames;
		for(size_t i=0; i < norder.size(); ++i)
		{
			if( !exist(norder[i]) )
				return false;
			frames.push_back( m_frames[ idFromName(norder[i]) ] );
		}

		m_frames = frames;
		return true;
	}

	bool Anim::addFrame(size_t pos, const std::string& name, ASprite* sprite, Uint32 time, bool tofree, AABB rect, path_t path)
	{
		if( exist(name) )
			return false;

		frame fr;
		fr.name = name;
		fr.sprite = sprite;
		fr.time = (time == 0) ? m_default : time;
		fr.toFree = tofree;

		fr.rect = (rect->w == 0) ? fr.sprite->global() : rect;
		fr.path = path.string();
		fr.id.clear();

		size_t nb = 0;
		for(frame_iterator it = m_frames.begin(); it != m_frames.end(); ++it)
		{
			if(pos <= nb)
			{
				m_frames.insert(it, fr);
				return true;
			}
			++nb;
		}
		m_frames.insert(m_frames.end(), fr);

		return true;
	}

	bool Anim::deleteFrame(const std::string& name)
	{
		for(frame_iterator it = m_frames.begin(); it != m_frames.end(); ++it)
		{
			if(it->name == name)
			{
				m_frames.erase(it);
				return true;
			}
		}

		return false;
	}

	bool Anim::exist(const std::string& frame) const
	{
		for(size_t i=0; i < m_frames.size(); ++i)
		{
			if(m_frames[i].name == frame)
				return true;
		}
		return false;
	}

	ASprite* Anim::getSprite()
	{
		return m_frames[m_act].sprite;
	}

	const ASprite* Anim::getSprite() const
	{
		return m_frames[m_act].sprite;
	}

	Anim::operator ASprite*()
	{
		return getSprite();
	}

	Anim::operator const ASprite*() const
	{
		return getSprite();
	}

	Anim::operator ASprite() const
	{
		return *getSprite();
	}

	ASprite* Anim::operator->()
	{
		return getSprite();
	}

	const ASprite* Anim::operator->() const
	{
		return getSprite();
	}

	SDL_Surface* Anim::getImg() const
	{
		return getSprite()->getPtr();
	}

	Anim::operator SDL_Surface*() const
	{
		return getImg();
	}

	ASprite* Anim::update()
	{
		if(m_pause)
			return m_frames[m_act].sprite;

		Uint32 ntime = SDL_GetTicks();
		Uint32 timeLapsed = ntime - m_lastTime;

		while(timeLapsed >= m_timeStay)
		{
			++m_act;
			if(m_act >= nbFrames())
				m_act=0;

			timeLapsed -= m_timeStay;
			m_timeStay = static_cast<Uint32>( (float)m_frames[m_act].time * m_speed );
		}

		m_timeStay -= timeLapsed;
		m_lastTime = ntime;

		return m_frames[m_act].sprite;
	}

	void Anim::reset()
	{
		set(0);
	}

	void Anim::set(const std::string& frame)
	{
		set( idFromName(frame) );
	}

	void Anim::set(size_t id)
	{
		m_lastTime = SDL_GetTicks();
		m_act = id;
		if(m_act >= nbFrames())
			m_act = nbFrames()-1;
		m_timeStay = static_cast<Uint32>( (float)m_frames[m_act].time * m_speed );
	}

	void Anim::pause()
	{
		m_pause = true;
	}

	void Anim::play()
	{
		m_pause = false;
	}

	void Anim::next()
	{
		if(m_act == nbFrames()-1)
			set(0);
		else
			set(m_act + 1);
	}

	void Anim::prev()
	{
		if(m_act == 0)
			set(nbFrames() - 1);
		else
			set(m_act - 1);
	}

	void Anim::forward(Uint32 time)
	{
		while(time >= m_timeStay)
		{
			++m_act;
			if(m_act >= nbFrames())
				m_act=0;

			time -= m_timeStay;
			m_timeStay = static_cast<Uint32>( (float)m_frames[m_act].time * m_speed );
		}
		m_timeStay -= time;
	}

	void Anim::backward(Uint32 time)
	{
		Uint32 timeSpent = static_cast<Uint32>( (float)m_frames[m_act].time * m_speed ) - m_timeStay;

		while(time >= timeSpent)
		{
			if(m_act == 0)
				m_act = nbFrames() - 1;
			else
				--m_act;

			time -= timeSpent;
			timeSpent = static_cast<Uint32>( (float)m_frames[m_act].time * m_speed );
		}
		m_timeStay = time;
	}

	void Anim::speed(float nspeed)
	{
		m_timeStay = static_cast<Uint32>( (float)m_frames[m_act].time / m_speed );
		m_speed = nspeed;
		m_timeStay = static_cast<Uint32>( (float)m_frames[m_act].time * m_speed );
	}

	std::string Anim::getActName() const
	{
		return nameFromId(m_act);
	}

	size_t Anim::getActId() const
	{
		return m_act;
	}

	sdl::AABB Anim::getMaxSize() const
	{
		int w=0, h=0;

		for(size_t i=0; i < m_frames.size(); ++i)
		{
			if(m_frames[i].sprite->getPtr()->w > w)
				w = m_frames[i].sprite->getPtr()->w;
			if(m_frames[i].sprite->getPtr()->h > h)
				h = m_frames[i].sprite->getPtr()->h;
		}

		return sdl::AABB( makeRect(0, 0, w, h) );
	}

	sdl::AABB Anim::getMaxSizeFloat() const
	{
		unsigned int wl=0, wr=0;
		unsigned int hl=0, hr=0;

		for(size_t i=0; i < m_frames.size(); ++i)
		{
			unsigned int cwl = m_frames[i].sprite->hotPoint().x;
			unsigned int cwr = m_frames[i].sprite->getPtr()->w - cwl;
			if(cwl > wl)
				wl = cwl;
			if(cwr > wr)
				wr = cwr;

			unsigned int chl = m_frames[i].sprite->hotPoint().y;
			unsigned int chr = m_frames[i].sprite->getPtr()->h - chl;
			if(chl > hl)
				hl = chl;
			if(chr > hr)
				hr = chr;
		}

		return sdl::AABB( makeRect(0, 0, wl+wr, hl+hr) );
	}

	/*!
	 * \struct sdl::ParsedFrame
	 * \brief Structure inaccessible pour l'utilisateur servant au chargement du fichier d'animation.
	 */
	struct ParsedFrame // Utilisée uniquement lors du chargement des sprites
	{
		ParsedFrame() : id(""), surf(NULL), elem(NULL), sprite(NULL)
		{}

		inline bool operator==(const ParsedFrame& o) // Pour le tri
		{ return (nb == o.nb); }
		inline bool operator!=(const ParsedFrame& o)
		{ return (nb != o.nb); }
		inline bool operator<(const ParsedFrame& o)
		{ return (nb < o.nb); }
		inline bool operator<=(const ParsedFrame& o)
		{ return (nb <= o.nb); }
		inline bool operator>(const ParsedFrame& o)
		{ return (nb > o.nb); }
		inline bool operator>=(const ParsedFrame& o)
		{ return (nb >= o.nb); }

		size_t nb; // La position
		std::string name;
		AABB rect;

		boost::filesystem::path path;
		std::string id; // vide s'il faut charger le sprite directement

		SDL_Surface* surf; // Valable uniquement avec id vide, NULL sinon
		TiXmlElement* elem; // Idem

		Uint32 time;

		ASprite* sprite;
	};

	void Anim::parseSprites(std::vector<frame>* sprites, TiXmlElement* elem, path_t basepath)
	{
		std::list<ParsedFrame> pf;

		elem = elem->FirstChildElement("sprite"); // On parse l'xml
		while(elem != NULL)
		{
			if( elem->Attribute("path") != NULL )
			{
				std::string str = elem->Attribute("path");
				if( str.empty() )
					goto end;

				ParsedFrame fr;

				if( elem->Attribute("name") == NULL )
					goto end;
				fr.name = elem->Attribute("name");
				if( fr.name.empty() )
					goto end;

				if( elem->Attribute("nb") != NULL )
					fr.nb = atoi( elem->Attribute("nb") );
				else
					fr.nb = 0;

				if( elem->Attribute("time") == NULL)
					fr.time = m_default;
				else
				{
					std::string tmp = elem->Attribute("time");
					if(tmp.empty())
						fr.time = m_default;
					else
					{
						fr.time = atoi(tmp);
						if(fr.time == 0)
							fr.time = m_default;
					}
				}

				size_t pos = str.find_last_of(':');
				if( pos == std::string::npos )
				{
					fr.id.clear(); // id vide
					fr.path = basepath.string() + str;

					fr.surf = IMG_Load( fr.path.c_str() );
					if( fr.surf == NULL )
						goto end;
					fr.elem = elem;
				}
				else
				{
					fr.id = str.substr(pos + 1);
					fr.path = basepath.string() + str.substr(0, pos);
				}

				pf.push_back(fr);
			}

end:
			elem = elem->NextSiblingElement("sprite");
		}

		std::map<std::string, SpriteFile*> files;
		std::list<ParsedFrame>::iterator toera = pf.end();
		for(std::list<ParsedFrame>::iterator it = pf.begin(); it != pf.end(); ++it) // On charge les frames
		{
			if( toera != pf.end() )
			{
				pf.erase(toera);
				toera = pf.end();
			}

			if( it->id.empty() )
			{
				it->sprite = SpriteFile::spriteXml(it->elem, it->surf, &it->rect);
				if( it->sprite == NULL ) // Si on n'arrive pas à le charger, on le supprime
					toera = it;
			}
			else
			{
				SpriteFile* file; // SpriteFile à utiliser

				if( files.find(it->path.string()) == files.end() ) // Chargement du SpriteFile s'il ne l'est pas déjà
				{
					file = new SpriteFile;
					if( !file->load(it->path) )
					{
						delete file;
						file = NULL;
					}
					files[it->path.string()] = file;
				}
				else
					file = files[it->path.string()]; // Utilisation d'un SpriteFile déjà chargé

				if( file == NULL ) // Si le fichier est inchargeable, on supprime la frame
					toera = it;
				else
				{
					if( file->exist(it->id) ) // Si cet id existe, on récupère le sprite, sinon, on le supprime
						it->sprite = new ASprite( file->getSprite(it->id) );
					else
						toera = it;
				}
			}
		}

		if( toera != pf.end() )
			pf.erase( toera );

		for(std::map<std::string, SpriteFile*>::iterator it = files.begin(); it != files.end(); ++it) // On libère les SpriteFile
		{
			if( it->second != NULL )
				delete it->second;
		}

		if( pf.empty() )
			return;

		pf.sort(); // on trie les sprites

		sprites->resize( pf.size() );
		size_t i = 0;
		for(std::list<ParsedFrame>::iterator it = pf.begin(); it != pf.end(); ++it) // On convertit les ParsedFrame en frame
		{
			frame fr;
			fr.name = it->name;
			fr.sprite = it->sprite;
			fr.toFree = true;
			fr.time = it->time;
			fr.path = it->path.string();
			fr.id = it->id;

			sprites->at(i++) = fr;
		}
	}
};

