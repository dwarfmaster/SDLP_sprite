#ifndef DEF_SDLP_SPRITEEDIT
#define DEF_SDLP_SPRITEEDIT

#include <boost/filesystem/fstream.hpp>

#include "asprite.hpp"

namespace sdl
{
	class SpriteEditor
	{
		public:
			typedef std::vector<AABB>::iterator saabbs_it;

			SpriteEditor();
			SpriteEditor(const ASprite& sprite);
			SpriteEditor(const SpriteEditor& cp);

			SpriteEditor& set(const SpriteEditor& cp);
			SpriteEditor& set(const ASprite& sprite);
			SpriteEditor& clear();

			SpriteEditor& operator=(const SpriteEditor& cp);
			SpriteEditor& operator=(const ASprite& sprite);

			bool setCurrent(std::string cur, size_t idx=0);
			bool setPriority(int newp);
			saabbs_it SAABBbegin();
			saabbs_it SAABBend();
			bool modifie(const AABB& nvalue); // Modifie la SAABB courante
			bool modifie(std::string str, size_t idx, const AABB& nvalue); // En modifie une précisément
			AABB& operator[](size_t idx); // Stoppe le programme en cas d'erreur d'index : à utiliser avec précaution
			std::vector<AABB>& operator[](std::string str); // Idem

			void setPath(const ASprite::path_t& path);
			void setHotPoint(const Pointsi& hp);
			bool addGroup(std::string gr);
			bool addSAABB(const AABB& saabb);

			ASprite tmpSprite() const; // Retourne la Sprite en construction : non utilisable mais permet d'avoir des infos
			ASprite* operator->(); // Idem, permet un accès plus rapide

			bool save(const ASprite::path_t& path) const;
			ASprite create() const;

		private:
			ASprite m_edit;

			std::string m_current; // GAABB actuel
			size_t m_idxCur; // SAABB actuel
			ASprite::path_t m_path;
	};
};

#endif//DEF_SDLP_SPRITEEDIT
