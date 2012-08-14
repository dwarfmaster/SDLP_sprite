#ifndef DEF_SDLP_SPRITEFILE
#define DEF_SDLP_SPRITEFILE

#include "asprite.hpp"

#include <vector>
#include <map>
#include <string>
#include <limits>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <tinyxml.h>
#include <SDL/SDL_image.h>

#include <SDLP_position.hpp>
#include <SDLP_tools.hpp>

namespace sdl
{
	class SpriteFile
	{
		struct sprite;

		public:
			typedef boost::filesystem::path path_t;
			typedef std::map<std::string, sprite>::iterator sprite_iterator;
			typedef std::map<std::string, sprite>::const_iterator csprite_iterator;

			SpriteFile();
			SpriteFile(const path_t& path);
			SpriteFile(const SpriteFile& cp);

			void clear();
			bool load(const path_t& path);
			void set(const SpriteFile& cp);
			SpriteFile& operator=(const SpriteFile& cp);

			ASprite getSprite(std::string id);
			AABB getRect(std::string id) const;
			ASprite operator[](std::string id);
			bool exist(std::string id) const;

			std::vector<std::string> listIds() const;

			bool changeSprite(std::string id, const std::map<std::string, gaabb>& groups, const Pointsi& hotp, const AABB& rect);
			bool changeSprite(std::string id, const std::map<std::string, gaabb>& groups, const Pointsi& hotp); // Utilise le rect enregistré
			bool addSprite(std::string id, const std::map<std::string, gaabb>& groups, const Pointsi& hotp, const AABB& rect);
			bool deleteSprite(std::string id);
			bool save(path_t path) const;
			bool save() const; // Sauvegarde avec le chemin enregistré

			static std::string xmlSprite(const ASprite& sprite, const std::string& id, const AABB& rect, const std::string& toadd="", const std::string& begin="");
			static ASprite* spriteXml(TiXmlElement* sprite, const path_t& img, AABB* rect = NULL);
			static ASprite* spriteXml(TiXmlElement* sprite, SDL_Surface* img, AABB* arect = NULL); // La surface ne sera pas modifiée

		private:
			path_t m_path;
			boost::shared_ptr<SDL_Surface> m_img;

			struct sprite
			{
				AABB rect;
				Pointsi hotp;

				std::map<std::string, gaabb> gaabbs;
			};
			std::map<std::string, sprite> m_sprites;

			static bool parseSprite(TiXmlElement* spriten, sprite* p, const SDL_Surface* img); // Ces trois fonctions peuvent être utlisées par spriteXml
			static void parseRect(TiXmlElement* spriten, AABB* p, const SDL_Surface* img);
			static bool parseGAABB(TiXmlElement* gaabbn, gaabb* p);
	};
};

#endif//DEF_SDLP_SPRITEFILE
