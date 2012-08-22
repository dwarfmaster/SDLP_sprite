
/*!
 * \file spriteedit.hpp
 * \brief Définit la classe sdl::SpriteEditor.
 */

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
			SpriteEditor(const SpriteEditor& cp);
			SpriteEditor(SpriteFile* file, std::string id);
			~SpriteEditor();

			SpriteEditor& set(const SpriteEditor& cp);
			SpriteEditor& set(SpriteFile* file, std::string id);
			SpriteEditor& clear();

			SpriteEditor& operator=(const SpriteEditor& cp);

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

			void setHotPoint(const Pointsi& hp);
			bool addGroup(std::string gr);
			bool deleteGroup(std::string str);
			bool addSAABB(const AABB& saabb);
			bool deleteSAABB(size_t idx);
			Pointsi hotpoint() const;

			SDL_Surface* getReal();

			ASprite tmpSprite() const; // Retourne la Sprite en construction : non utilisable mais permet d'avoir des infos
			ASprite* operator->(); // Idem, permet un accès plus rapide

			bool save(const ASprite::path_t& path) const;
			ASprite create() const;

			bool check() const; // Teste si la classe peut être utilisée (dans le cas contraire, elle peut déclencher des segfaults)
			operator bool() const; // idem
			bool operator!() const; // idem

		protected:
			ASprite m_edit; /*!< Contient une version temporaire du sprite en édition. */

			std::string m_current; /*!< Indique le groupe de sous AABBs en édition. */
			size_t m_idxCur; /*!< Indique la sous AABB en édition. */

			SpriteFile* m_file; /*!< Le sdl::SpriteFile contenant la sdl::ASprite en édition. */
			std::string m_id; /*!< Le nom de la sdl::ASprite en édition. */
	};
};

#endif//DEF_SDLP_SPRITEEDIT
