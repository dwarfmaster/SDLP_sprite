#include "spriteedit.hpp"

namespace sdl
{
	SpriteEditor::SpriteEditor()
	{
		this->clear();
	}

	SpriteEditor::SpriteEditor(const ASprite& sprite)
	{
		this->set(sprite);
	}

	SpriteEditor::SpriteEditor(const SpriteEditor& cp)
	{
		this->set(cp);
	}

	SpriteEditor& SpriteEditor::set(const SpriteEditor& cp)
	{
		m_edit = cp.m_edit;
		m_current = cp.m_current;
		m_idxCur = cp.m_idxCur;
		m_path = cp.m_path;
		return *this;
	}

	SpriteEditor& SpriteEditor::set(const ASprite& sprite)
	{
		this->clear();
		m_edit = sprite;
		m_path = sprite.m_imgPath;
		return *this;
	}

	SpriteEditor& SpriteEditor::clear()
	{
		m_current = "";
		m_idxCur = 0;
		m_path = "";
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

		m_edit[m_current][m_idxCur]=nvalue;
		return true;
	}

	bool SpriteEditor::modifie(std::string str, size_t idx, const AABB& nvalue)
	{
		if( !m_edit.exist(str)
				|| m_idxCur >= m_edit[str].size() )
			return false;

		m_edit[str][idx]=nvalue;
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
		file << "<image path=\"" << m_path.string() << "\" />\n";
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
		for(size_t i=0; i<groups.size(); ++i)
			sprite.m_groups[groups[i]].global.englobe(sprite.m_groups[groups[i]].aabbs);

		sprite.m_hotPoint = m_edit.m_hotPoint;
		sprite.m_imgPath = m_path;

		if( !m_path.empty()
				&& boost::filesystem::exists(m_path) 
				&& !boost::filesystem::is_empty(m_path)
				&& !boost::filesystem::is_directory(m_path) )
		{
			SDL_Surface* tmp = IMG_Load(m_path.string().c_str());
			if( tmp == NULL )
				return sprite;
			Liberator lib;
			sprite.m_img.reset(tmp, lib);
		}
		else if(m_edit.m_img)
			sprite.m_img = m_edit.m_img;

		return sprite;
	}

};
