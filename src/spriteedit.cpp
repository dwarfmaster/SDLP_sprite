
/*!
 * \file spriteedit.cpp
 * \brief Implémente la classe sdl::SpriteEditor.
 */

#include "spriteedit.hpp"

namespace sdl
{
	SpriteEditor::SpriteEditor()
	{
		this->clear();
	}

	SpriteEditor::SpriteEditor(const SpriteEditor& cp)
	{
		this->set(cp);
	}

	SpriteEditor::SpriteEditor(SpriteFile* file, std::string id)
	{
		this->set(file, id);
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
		m_file = cp.m_file;
		m_id = cp.m_id;

		return *this;
	}

	SpriteEditor& SpriteEditor::set(SpriteFile* file, std::string id)
	{
		this->clear();
		m_file = file;
		m_id = id;
		m_edit = m_file->getSprite(m_id);

		return *this;
	}

	SpriteEditor& SpriteEditor::clear()
	{
		m_current = "";
		m_idxCur = 0;
		m_file = NULL;
		m_id.clear();

		return *this;
	}

	SpriteEditor& SpriteEditor::operator=(const SpriteEditor& cp)
	{
		this->set(cp);
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

	SDL_Surface* SpriteEditor::getReal()
	{
		return m_edit.getPtr();
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
		std::map<std::string, gaabb> groups;
		for(ASprite::c_group_iterator it = m_edit.m_groups.begin(); it != m_edit.m_groups.end(); ++it)
		{
			groups[it->first].saabbs = it->second.aabbs;
			groups[it->first].priority = it->second.priority;
		}

		m_file->changeSprite(m_id, groups, m_edit.m_hotPoint);
		return m_file->save(path);
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

	bool SpriteEditor::check() const
	{
		return m_file != NULL;
	}

	SpriteEditor::operator bool() const
	{
		return check();
	}

	bool SpriteEditor::operator!() const
	{
		return !check();
	}

};
