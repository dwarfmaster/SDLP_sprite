#include "asprite.hpp"

namespace sdl
{
	ASprite::ASprite()
	{}

	ASprite::ASprite(ASprite::path_t path)
	{
		this->load(path);
	}

	ASprite::ASprite(const ASprite& cp)
	{
		this->set(cp);
	}

	void ASprite::set(const ASprite& cp)
	{
		m_groups = cp.m_groups;
		m_hotPoint = cp.m_hotPoint;
		m_img = cp.m_img;
	}

	bool ASprite::load(ASprite::path_t path)
	{
		TiXmlDocument file(path.string());
		if(!file.LoadFile())
			return false;

		// On récupère le node image
		TiXmlElement* elem = file.FirstChildElement("image");
		if(elem == NULL )
			return false;

		// On récupère le chemin vers l'image
		std::string img(elem->Attribute("path"));
		if(img.empty()
				|| !boost::filesystem::exists(img))
			return false;

		// On charge l'image
		SDL_Surface* tmp = IMG_Load(img.c_str());
		if(tmp == NULL)
			return false;
		Liberator lib;
		m_img.reset(tmp, lib);

		// On récupère le node hotpoint
		elem = file.FirstChildElement("hotpoint");
		if(elem == NULL) 
			return false;

		// On en récupère la position
		std::string str(elem->Attribute("x"));
		if(str.empty())
			return false;
		m_hotPoint.x = sdl::atoi(str);
		str = elem->Attribute("y");
		if(str.empty())
			return false;
		m_hotPoint.y = sdl::atoi(str);

		// On récupère les SAABBs
		elem = file.FirstChildElement("gaabb");
		while(elem)
		{
			this->parseGAABB(elem);
			elem = elem->NextSiblingElement("gaabb");
		}

		return true;
	}

	void ASprite::clear()
	{
		m_groups.clear();
		m_hotPoint.clear();
		m_img.reset();
	}

	ASprite& ASprite::operator=(const ASprite& cp)
	{
		this->set(cp);
		return *this;
	}

	ASprite::operator SDL_Surface() const
	{
		return *m_img;
	}

	ASprite::operator boost::shared_ptr<SDL_Surface>()
	{
		return this->get();
	}

	boost::shared_ptr<SDL_Surface> ASprite::get() const
	{
		return m_img;
	}

	SDL_Surface* ASprite::getPtr() const
	{
		return m_img.get();
	}

	Pointsi ASprite::hotPoint() const
	{
		return m_hotPoint;
	}

	std::vector<AABB> ASprite::saabb(std::string id) const
	{
		if(!exist(id))
			return std::vector<AABB>(0);
		else
			return m_groups.find(id)->second.aabbs;
	}

	AABB ASprite::globalSAABB(std::string id) const
	{
		if(!exist(id))
			return AABB( makeRect(0,0) );
		else
			return m_groups.find(id)->second.global;
	}

	std::vector<AABB> ASprite::operator[](std::string id) const
	{
		return this->saabb(id);
	}

	bool ASprite::exist(std::string id) const
	{
		return m_groups.find(id) != m_groups.end();
	}

	std::vector<std::string> ASprite::groups() const
	{
		std::vector<std::string> strs;
		for(c_group_iterator i=m_groups.begin(); i!=m_groups.end(); ++i)
			strs.push_back(i->first);
		return strs;
	}

	std::vector<std::string> ASprite::inGroup(const Pointsi& p) const
	{
		std::vector<std::string> cols;

		for(c_group_iterator i=m_groups.begin(); i!=m_groups.end(); ++i)
		{
			if(i->second.global.contain(p))
				for(size_t j=0; j<i->second.aabbs.size(); ++j)
					if(i->second.aabbs[j].contain(p))
					{
						cols.push_back(i->first);
						break;
					}
		}

		return cols;
	}

	std::string ASprite::inUniqueGroup(const Pointsi& p) const
	{
		std::string col;
		unsigned int high = std::numeric_limits<unsigned int>::max();

		for(c_group_iterator i=m_groups.begin(); i!=m_groups.end(); ++i)
		{
			if(i->second.global.contain(p))
				for(size_t j=0; j<i->second.aabbs.size(); ++j)
					if(i->second.aabbs[j].contain(p)
							&& i->second.priority < high)
						col = i->first;
		}

		return col;
	}

	void ASprite::parseGAABB(TiXmlElement* gaabb)
	{
		GAABB group;
		std::string name;

		name = gaabb->Attribute("id");
		if(name.empty()
				|| this->exist(name) )
			return;

		std::string str = gaabb->Attribute("priority");
		if(str.empty())
			return;
		group.priority = sdl::atoi(str);

		TiXmlElement* child = gaabb->FirstChildElement("saabb");
		while(child)
		{
			SDL_Rect saabb;

			str = child->Attribute("x");
			if(str.empty())
				break;
			saabb.x = atoi(str);
			str = child->Attribute("y");
			if(str.empty())
				break;
			saabb.y = atoi(str);
			str = child->Attribute("w");
			if(str.empty())
				break;
			saabb.w = atoi(str);
			str = child->Attribute("h");
			if(str.empty())
				break;
			saabb.h = atoi(str);

			group.aabbs.push_back(saabb);

			child = child->NextSiblingElement("saabb");
		}

		if(group.aabbs.empty())
			return;

		group.global.englobe(group.aabbs);
		m_groups[name]=group;
	}
};

