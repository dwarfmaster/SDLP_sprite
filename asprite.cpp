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
		// À compléter
		return false;
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
						cols.push_back(i->first);
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
};

