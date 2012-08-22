
/*
 * Copyright (C) 2012 Chabassier Luc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*!
 * \file spritefile.hpp
 * \brief Définit la classe sdl::SpriteFile.
 */

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

		protected:
			path_t m_path; /*!< Le chemin du fichier chargé. */
			path_t m_imgPath; /*!< Le chemin de l'image. */
			boost::shared_ptr<SDL_Surface> m_img; /*!< L'image utilisée. */

			struct sprite
			{
				AABB rect; /*!< La partie de l'image à utiliser. */
				Pointsi hotp; /*!< Le point chaud. */

				std::map<std::string, gaabb> gaabbs; /*!< Le groupes de sous AABBs. */
			};
			std::map<std::string, sprite> m_sprites; /*!< Le sprites. */

			static bool parseSprite(TiXmlElement* spriten, sprite* p, const SDL_Surface* img); // Ces trois fonctions peuvent être utlisées par spriteXml
			static void parseRect(TiXmlElement* spriten, AABB* p, const SDL_Surface* img);
			static bool parseGAABB(TiXmlElement* gaabbn, gaabb* p);
	};
};

#endif//DEF_SDLP_SPRITEFILE
