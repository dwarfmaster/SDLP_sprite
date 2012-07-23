#include "spriteedit.hpp"

namespace sdl
{
	SpriteEditor::SpriteEditor()
	{
		toFree=false;
		this->clear();
	}

	SpriteEditor::SpriteEditor(const ASprite& sprite)
	{
		toFree=false;
		this->set(sprite);
	}

	SpriteEditor::SpriteEditor(const SpriteEditor& cp)
	{
		toFree=false;
		this->set(cp);
	}

	SpriteEditor::~SpriteEditor()
	{
		this->clear();
	}

	SpriteEditor& SpriteEditor::set(const SpriteEditor& cp)
	{
		this->clear();
		m_edit = cp.m_edit;
		m_current = cp.m_current;
		m_idxCur = cp.m_idxCur;
		m_path = cp.m_path;
		m_rect = cp.m_rect;
		m_total = cp.m_total;
		toFree = false;
		return *this;
	}

	SpriteEditor& SpriteEditor::set(const ASprite& sprite)
	{
		this->clear();
		m_edit = sprite;
		m_path = sprite.m_imgPath;
		m_rect = sprite.m_rect;

		SDL_Surface* img = IMG_Load(m_path.string().c_str());
		if(img == NULL)
		{
			m_total = sprite.getPtr();
			toFree=false;
		}
		else
		{
			m_total = img;
			toFree=true;
		}

		return *this;
	}

	SpriteEditor& SpriteEditor::clear()
	{
		m_current = "";
		m_idxCur = 0;
		m_path = "";
		m_rect = makeRect(0, 0, 0, 0);

		if(toFree)
			SDL_FreeSurface(m_total);
		m_total = NULL;
		toFree=false;
		return *this;
	}

	SpriteEditor& SpriteEditor::operator=(const SpriteEditor& cp)
	{
		this->set(cp);
		return *this;
	}

	SpriteEditor& SpriteEditor::operator=(const ASprite& sprite)
	{
		this->set(sprite);
		return *this;
	}

	std::vector<std::string> SpriteEditor::groups() const
	{
		return m_edit.groups();
	}

	size_t SpriteEditor::nbGroups() const
	{
		return m_edit.groups().size();
	}

	bool SpriteEditor::setCurrent(std::string cur, size_t idx)
	{
		if(!m_edit.exist(cur))
			return false;
		m_current=cur;

		if(m_edit[m_current].size() <= idx)
			return false;
		m_idxCur = idx;

		return true;
	}

	std::string SpriteEditor::current() const
	{
		return m_current;
	}

	size_t SpriteEditor::currentIdx() const
	{
		return m_idxCur;
	}

	bool SpriteEditor::deleteCurrent()
	{
		return this->deleteSAABB(m_idxCur);
	}

	bool SpriteEditor::deleteCurrentGroup()
	{
		return this->deleteGroup(m_current);
	}

	AABB SpriteEditor::get() const
	{
		if( !m_edit.exist(m_current)
				|| m_idxCur >= m_edit[m_current].size() )
			return sdl::AABB( sdl::makeRect(0, 0, 0, 0) );
		else
			return getGroup()[m_idxCur];
	}

	std::vector<AABB> SpriteEditor::getGroup() const
	{
		if(m_edit.exist(m_current))
			return m_edit[m_current];
		std::vector<AABB> vec;
		return vec;
	}

	bool SpriteEditor::setPriority(int newp)
	{
		if(!m_edit.exist(m_current))
			return false;

		m_edit.m_groups[m_current].priority = newp;
		return true;
	}

	int SpriteEditor::getPriority()
	{
		if(!m_edit.exist(m_current))
			return -1;

		return m_edit.m_groups[m_current].priority;
	}

	SpriteEditor::saabbs_it SpriteEditor::SAABBbegin()
	{
		if(!m_edit.exist(m_current))
			return this->SAABBend();

		return m_edit.m_groups[m_current].aabbs.begin();
	}

	SpriteEditor::saabbs_it SpriteEditor::SAABBend()
	{
		if(!m_edit.exist(m_current))
		{
			std::vector<AABB> tmp;
			return tmp.end();
		}

		return m_edit.m_groups[m_current].aabbs.end();
	}

	bool SpriteEditor::modifie(const AABB& nvalue)
	{
		if( !m_edit.exist(m_current)
				|| m_idxCur >= m_edit[m_current].size() )
			return false;

		modifie(m_current, m_idxCur, nvalue);
		return true;
	}

	bool SpriteEditor::modifie(std::string str, size_t idx, const AABB& nvalue)
	{
		if( !m_edit.exist(str)
				|| m_idxCur >= m_edit[str].size() )
			return false;

		m_edit.m_groups[str].aabbs[idx]=nvalue;
		return true;
	}

	size_t SpriteEditor::nbSAABBS() const
	{
		return this->SAABBS().size();
	}

	std::vector<AABB> SpriteEditor::SAABBS() const
	{
		if(m_current!="")
			return m_edit[m_current];
		else
			return std::vector<AABB>(0);
	}

	AABB& SpriteEditor::operator[](size_t idx)
	{
		if( !m_edit.exist(m_current)
				|| idx >= m_edit[m_current].size() )
		{
			std::cerr<<"Erreur d'index dans SpriteEditor."<<std::endl;
			exit(EXIT_FAILURE);
		}

		return m_edit[m_current][idx];
	}

	std::vector<AABB>& SpriteEditor::operator[](std::string str)
	{
		if( !m_edit.exist(str) )
		{
			std::cerr<<"Erreur d'index dans SpriteEditor."<<std::endl;
			exit(EXIT_FAILURE);
		}

		return m_edit.m_groups[str].aabbs;
	}

	void SpriteEditor::setPath(const ASprite::path_t& path)
	{
		m_path = path;
		m_edit.m_img.reset();
	}

	void SpriteEditor::setHotPoint(const Pointsi& hp)
	{
		m_edit.m_hotPoint = hp;
	}

	bool SpriteEditor::addGroup(std::string gr)
	{
		if(m_edit.exist(gr))
			return false;

		m_edit.m_groups[gr];
		return true;
	}

	bool SpriteEditor::deleteGroup(std::string str)
	{
		if(!m_edit.exist(str))
			return false;

		m_edit.m_groups.erase(str);
		return true;
	}

	bool SpriteEditor::addSAABB(const AABB& saabb)
	{
		if(!m_edit.exist(m_current))
			return false;
		m_edit.m_groups[m_current].aabbs.push_back(saabb);
		return true;
	}

	bool SpriteEditor::deleteSAABB(size_t idx)
	{
		if( !m_edit.exist(m_current)
				|| idx >= m_edit.m_groups[m_current].aabbs.size() )
			return false;

		m_edit.m_groups[m_current].aabbs.erase( m_edit.m_groups[m_current].aabbs.begin() + idx );
		return true;
	}

	Pointsi SpriteEditor::hotpoint() const
	{
		return m_edit.m_hotPoint;
	}

	ASprite::path_t SpriteEditor::getPath() const
	{
		return m_path;
	}

	SDL_Surface* SpriteEditor::getTotal()
	{
		return m_total;
	}

	SDL_Surface* SpriteEditor::getReal()
	{
		return m_edit.getPtr();
	}

	AABB SpriteEditor::getSubRect()
	{
		AABB rect(m_rect);

		if(rect->w == 0
				|| rect->h == 0)
		{
			rect->w = m_total->w;
			rect->h = m_total->h;
		}

		return rect;
	}

	void SpriteEditor::setSubRect(AABB rect)
	{
		Pointsi lori = m_rect[AABB::TOP_LEFT]; // Last origine

		if(rect->x < 0)
			rect->x = 0;
		else if(rect->x >= m_total->w - 10)
			rect->x = m_total->w - 11;

		if(rect->y < 0)
			rect->y = 0;
		else if(rect->y >= m_total->h - 10)
			rect->y = m_total->h - 11;

		if(rect->w + rect->x >= m_total->w)
			rect->w = m_total->w - rect->x;

		if(rect->h + rect->y >= m_total->h)
			rect->h = m_total->h - rect->y;

		m_rect = rect;
		Pointsi nori = rect[AABB::TOP_LEFT]; // New origine
		Vector2f vec(lori, nori);
		vec = -vec;

		std::vector<std::string> gr = groups();
		for(size_t i=0; i<gr.size(); ++i)
		{
			setCurrent(gr[i]);
			for(saabbs_it it = SAABBbegin(); it != SAABBend(); ++it)
			{
				Pointsi tl = it->location(AABB::TOP_LEFT);
				tl += vec;
				it->move(tl);

				if((*it)->x >= rect->x + rect->w
						|| (*it)->y >= rect->x + rect->w
						|| (*it)->x + (*it)->w <= rect->x
						|| (*it)->y + (*it)->h <= rect->y )
					m_edit.m_groups[m_current].aabbs.erase(it);

				if( (*it)->x + (*it)->w >= rect->x + rect->w )
					(*it)->w = rect->x + rect->w - (*it)->x;

				if( (*it)->y + (*it)->h >= rect->y + rect->h )
					(*it)->h = rect->y + rect->h - (*it)->y;
			}
		}

		if(m_edit.m_hotPoint.x < rect->x)
			m_edit.m_hotPoint.x = rect->x;
		else if(m_edit.m_hotPoint.x >= rect->x + rect->w)
			m_edit.m_hotPoint.x = rect->x + rect->w - 1;

		if(m_edit.m_hotPoint.y < rect->y)
			m_edit.m_hotPoint.y = rect->y;
		else if(m_edit.m_hotPoint.y >= rect->y + rect->h)
			m_edit.m_hotPoint.y = rect->y + rect->h - 1;

		SDL_Surface* img = SDL_CreateRGBSurface(SDL_HWSURFACE, rect->w, rect->h, 24, 0, 0, 0, 0);
		if(img == NULL)
			return;
		SDL_Rect r = rect.rect();
		SDL_BlitSurface(m_total, &r, img, NULL);

		Liberator lib;
		m_edit.m_img.reset(img, lib);
	}

	ASprite SpriteEditor::tmpSprite() const
	{
		return m_edit;
	}

	ASprite* SpriteEditor::operator->()
	{
		return &m_edit;
	}

	bool SpriteEditor::save(const ASprite::path_t& path) const
	{
		boost::filesystem::ofstream file(path);
		if(!file)
			return false;

		file << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n\n";

		if(m_path.empty())
			return false;
		file << "<image>\n";
		file << "\t<path>" << m_path.string() << "</path>\n";
		if(m_rect->w != 0
				&& m_rect->h != 0)
			file << "<aabb x=\"" << itoa(m_rect->x) << "\" y=\"" << itoa(m_rect->y) << "\" w=\"" << itoa(m_rect->w) << "\" h=\"" << itoa(m_rect->h) << "\" />\n";
		file << "</image>\n";

		file << "<hotpoint x=\"" << itoa(m_edit.m_hotPoint.x) << "\" y=\"" << itoa(m_edit.m_hotPoint.y) << "\" />\n\n";

		std::vector<std::string> groups = m_edit.groups();
		for(size_t i=0; i<groups.size(); ++i)
		{
			ASprite::GAABB gaabb = m_edit.m_groups.find(groups[i])->second;
			file << "<gaabb id=\"" << groups[i] << "\" priority=\"" << itoa(gaabb.priority) << "\">\n";

			std::vector<AABB> aabbs = gaabb.aabbs;
			for(size_t j=0; j<aabbs.size(); ++j)
				file << "\t<saabb x=\"" << itoa(aabbs[j]->x) << "\" y=\"" << itoa(aabbs[j]->y) << "\" w=\"" << itoa(aabbs[j]->w) << "\" h=\"" << itoa(aabbs[j]->h) << "\" />\n";

			file << "</gaabb>\n\n";
		}

		return true;
	}

	ASprite SpriteEditor::create() const
	{
		ASprite sprite;

		sprite.m_groups = m_edit.m_groups;
		std::vector<std::string> groups = m_edit.groups();
		std::vector<AABB> globals;
		for(size_t i=0; i<groups.size(); ++i)
		{
			sprite.m_groups[groups[i]].global.englobe(sprite.m_groups[groups[i]].aabbs);
			globals.push_back( sprite.m_groups[groups[i]].global );
		}
		sprite.m_global.englobe(globals);

		sprite.m_hotPoint = m_edit.m_hotPoint;
		sprite.m_img = m_edit.m_img;

		return sprite;
	}

};
