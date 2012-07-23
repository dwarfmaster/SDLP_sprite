#ifndef DEF_SDLP_SPRITEEDIT
#define DEF_SDLP_SPRITEEDIT

#include <boost/filesystem/fstream.hpp>

#include "asprite.hpp"
#include "spritefile.hpp"

namespace sdl
{
	class SpriteEditor
	{
		public:
			typedef std::vector<AABB>::iterator saabbs_it;

			SpriteEditor();
			SpriteEditor(const ASprite& sprite); // TODO à supprimer
			SpriteEditor(const SpriteEditor& cp);
			SpriteEditor(const SpriteFile& file, std::string id); // TODO à faire
			~SpriteEditor();

			SpriteEditor& set(const SpriteEditor& cp);
			SpriteEditor& set(const ASprite& sprite); // TODO à supprimer
			SpriteEditor& set(const SpriteFile& file, std::string id); // TODO à faire
			SpriteEditor& clear();

			SpriteEditor& operator=(const SpriteEditor& cp);
			SpriteEditor& operator=(const ASprite& sprite); // TODO à supprimer

			std::vector<std::string> groups() const;
			size_t nbGroups() const;

			bool setCurrent(std::string cur, size_t idx=0);
			std::string current() const;
			size_t currentIdx() const;
			bool deleteCurrent(); // supprime la SAABB courante
			bool deleteCurrentGroup();
			AABB get() const;
			std::vector<AABB> getGroup() const;

			bool setPriority(int newp);
			int getPriority();
			saabbs_it SAABBbegin();
			saabbs_it SAABBend();
			bool modifie(const AABB& nvalue); // Modifie la SAABB courante
			bool modifie(std::string str, size_t idx, const AABB& nvalue); // En modifie une précisément
			size_t nbSAABBS() const;
			std::vector<AABB> SAABBS() const;

			AABB& operator[](size_t idx); // Stoppe le programme en cas d'erreur d'index : à utiliser avec précaution
			std::vector<AABB>& operator[](std::string str); // Idem

			void setPath(const ASprite::path_t& path);
			void setHotPoint(const Pointsi& hp);
			bool addGroup(std::string gr);
			bool deleteGroup(std::string str);
			bool addSAABB(const AABB& saabb);
			bool deleteSAABB(size_t idx);
			Pointsi hotpoint() const;
			ASprite::path_t getPath() const;

			SDL_Surface* getTotal();
			SDL_Surface* getReal();
			AABB getSubRect();
			void setSubRect(AABB rect); // À utiliser avec précaution : les saabbs à l'extérieures seront supprimées et celles dépassant raccoucies // TODO à supprimer

			ASprite tmpSprite() const; // Retourne la Sprite en construction : non utilisable mais permet d'avoir des infos
			ASprite* operator->(); // Idem, permet un accès plus rapide

			bool save(const ASprite::path_t& path) const; // TODO à modifier
			ASprite create() const;

		private:
			ASprite m_edit;

			std::string m_current; // GAABB actuel
			size_t m_idxCur; // SAABB actuel

			ASprite::path_t m_path;
			AABB m_rect;
			SDL_Surface* m_total;
			bool toFree;
	};
};

#endif//DEF_SDLP_SPRITEEDIT
