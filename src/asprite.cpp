#include "asprite.hpp"

namespace sdl
{
	ASprite::ASprite()
	{}

	ASprite::ASprite(const ASprite& cp)
	{
		this->set(cp);
	}

	ASprite::ASprite(const std::map<std::string, gaabb>& groups, const Pointsi& hotp, const boost::shared_ptr<SDL_Surface>& img)
	{
		this->set(groups, hotp, img);
	}

	void ASprite::set(const ASprite& cp)
	{
		m_groups = cp.m_groups;
		m_hotPoint = cp.m_hotPoint;
		m_img = cp.m_img;
		m_global = cp.m_global;
	}

	void ASprite::set(const std::map<std::string, gaabb>& groups, const Pointsi& hotp, const boost::shared_ptr<SDL_Surface>& img)
	{
		std::vector<AABB> globals;
		for(std::map<std::string, gaabb>::const_iterator it = groups.begin(); it != groups.end(); ++it)
		{
			m_groups[it->first] = fromGaabb(it->second);
			globals.push_back(m_groups[it->first].global);
		}
		m_global.englobe(globals);

		m_hotPoint = hotp;
		m_img = img;
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

	Vector2f ASprite::decale() const
	{
		return Vector2f(-m_hotPoint.x, -m_hotPoint.y);
	}

	AABB ASprite::global() const
	{
		return m_global;
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

	unsigned int ASprite::priority(std::string id) const
	{
		if( !exist(id) )
			return 0;
		else
			return m_groups.find(id)->second.priority;
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
					{
						col = i->first;
						high = i->second.priority;
					}
		}

		return col;
	}

	std::vector< std::pair<std::string, std::string> > ASprite::colision(Pointsi pos1, const ASprite& other, Pointsi pos2) const
	{
		std::vector< std::pair<std::string, std::string> > vec;

		pos1 += decale();
		pos2 += other.decale();

		AABB global1 = global();
		global1.move(pos1);
		AABB global2 = other.global();
		global2.move(pos2);

		if(!global1.colision(global2))
			return vec;

		std::vector<std::string> g1 = groups();
		std::vector<std::string> g2 = other.groups();

		for(size_t i=0; i<g1.size(); ++i)
		{
			for(size_t j=0; j<g2.size(); ++j)
			{
				AABB gl1 = globalSAABB(g1[i]);
				gl1.move(pos1);
				AABB gl2 = other.globalSAABB(g2[j]);
				gl2.move(pos2);

				if(gl1.colision(gl2))
				{
					std::vector<AABB> saabb1 = saabb(g1[i]);
					std::vector<AABB> saabb2 = other.saabb(g2[j]);

					for(size_t k=0; k<saabb1.size(); ++k)
					{
						saabb1[k].move(pos1);
						for(size_t l=0; l<saabb2.size(); ++l)
						{
							saabb2[l].move(pos2);
							if(saabb1[k].colision(saabb2[l]))
							{
								std::pair<std::string, std::string> p(g1[i], g2[j]);
								vec.push_back(p);
								// On met fin aux boucles
								k = saabb1.size();
								l = saabb2.size();
							}
						}
					}
				}
			}
		}

		return vec;
	}

	ASprite::GAABB ASprite::fromGaabb(const gaabb& cp)
	{
		GAABB gaabb;
		gaabb.priority = cp.priority;
		gaabb.aabbs = cp.saabbs;
		gaabb.global.englobe( gaabb.aabbs );

		return gaabb;
	}
};

