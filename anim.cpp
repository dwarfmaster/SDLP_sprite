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
	}

	bool Anim::load(const path_t& path ) // TODO
	{
	}

	bool Anim::save(const path_t& path) // TODO
	{
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
		return 0;
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

	unsigned int Anim::time(const std::string& frame) const
	{
		return m_frames.at( idFromName(frame) ).time;
	}

	unsigned int Anim::time() const
	{
		unsigned int ttime = 0;
		for(size_t i=0; i < m_frames.size(); ++i)
			ttime += m_frames[i].time;
		return ttime;
	}

	unsigned int Anim::defaultTime() const
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

	bool Anim::changeTime(const std::string& frame, unsigned int ntime)
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

	bool Anim::addFrame(unsigned int pos, const std::string& name, ASprite* sprite, unsigned int time, bool tofree)
	{
		if( exist(name) )
			return false;
		
		// TODO
		return true;
	}

	bool Anim::deleteFrame(const std::string& name)
	{
		// TODO
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

	ASprite* Anim::update()
	{
		// TODO
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

	void Anim::reset()
	{
		// TODO
	}

	void Anim::set(const std::string& frame)
	{
		// TODO
	}

	void Anim::set(size_t id)
	{
		// TODO
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
		// TODO
	}

	void Anim::prev()
	{
		// TODO
	}

	void Anim::forward(Uint32 time)
	{
		// TODO
	}

	void Anim::backward(Uint32 time)
	{
		// TODO
	}

	void Anim::speed(float nspeed)
	{
		m_speed = nspeed;
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

};

