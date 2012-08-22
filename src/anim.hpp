
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
 * \file anim.hpp
 * \brief Définit la classe sdl::Anim.
 */

#ifndef DEF_SDLP_ANIM
#define DEF_SDLP_ANIM

#include "asprite.hpp"
#include "spritefile.hpp"

#include <vector>
#include <string>
#include <boost/filesystem/path.hpp>

#include <SDL/SDL.h>
#include <SDLP_position.hpp>

namespace sdl
{
	class Anim
	{
		public:
			typedef boost::filesystem::path path_t;

			Anim();
			Anim(const Anim& cp);
			Anim(const path_t& path);

			void clear();
			void set(const Anim& cp);
			Anim& operator=(const Anim& cp);
			bool load(const path_t& path);
			bool save(const path_t& path);

			bool isLoaded() const;
			operator bool() const;
			bool operator!() const;

			std::vector<std::string> frames() const;
			size_t nbFrames() const;
			size_t idFromName(const std::string& name) const; // Renvoie nbframes si name n'existe pas
			std::string nameFromId(size_t id) const;
			ASprite* sprite(const std::string& frame) const;
			ASprite* operator[](const std::string& frame) const;
			Uint32 time(const std::string& frame) const;
			Uint32 time() const; // Retourne la durée totale de l'animation
			Uint32 defaultTime() const;

			bool changeSprite(const std::string& frame, ASprite* nsprite, bool tofree=false);
			bool changeTime(const std::string& frame, Uint32 ntime);
			bool reorder(const std::vector<std::string>& norder); // Toutes les frames doivent y être, sans aucune supplémentaire
			bool addFrame(size_t pos, const std::string& name, ASprite* sprite,  Uint32 time=0, bool tofree=false, AABB rect = makeRect(0,0,0,0), path_t path = ""); // Si time = 0, alors la valeur par défaut sera appliquée; les frames suivantes seront décalées, le rect et le path servent juste pour la sauvegarde
			bool deleteFrame(const std::string& name);

			bool exist(const std::string& frame) const;

			ASprite* update(); // Va mettre à jour m_lastTime, m_act et m_timeStay
			ASprite* getSprite();
			const ASprite* getSprite() const;
			operator ASprite*();
			operator const ASprite*() const;
			operator ASprite() const;
			ASprite* operator->();
			const ASprite* operator->() const;
			SDL_Surface* getImg() const;
			operator SDL_Surface*() const;

			void reset(); // Considère que le temps actuel est le début de la première frame
			void set(const std::string& frame); // Idem mais avec la frame précisée
			void set(size_t id); // Idem
			void pause();
			void play();
			void next(); // Amène au début de la frame suivante
			void prev(); // Amène au début de la frame précédente
			void forward(Uint32 time); // Accélère de time
			void backward(Uint32 time); // Idem mais à l'envers
			void speed(float nspeed=1.0);

			std::string getActName() const;
			size_t getActId() const;

			sdl::AABB getMaxSize() const; // Retourne la taille de la frame la plus grande
			sdl::AABB getMaxSizeFloat() const; // Retourne tout l'espace qui pourra être occupé avec un hotpoint fixe

		protected:
			Uint32 m_lastTime; /*!< Le temps retouné par SDL_GetTicks lors du dernier appel à update. */
			size_t m_act; /*!< L'id de la frame actuelle. */
			bool m_pause; /*!< Indique si l'anim est en pause. */
			Uint32 m_timeStay; /*!< Temps restant avant le changement de frame. */
			float m_speed; /*!< Le facteur de vitesse. */

			struct frame
			{
				std::string name; /*!< Le nom de la frame. */
				ASprite* sprite; /*!< La sdl::ASprite de la frame. */
				bool toFree; /*!< S'il faudra libérer la sdl::ASprite de la frame. */
				Uint32 time; /*!< La durée de la frame. */

				std::string path; /*!< Le chemin de l'image originale ou du fichier sprite, utilisé uniquement pour la sauvegarde. */
				std::string id; /*!< L'id de la sprite dans le fichier. S'il est vide, on chargera path comme une image. Est utilisé uniquement pour la sauvegarde. */
				AABB rect; /*!< La portion occupée par le sprite dans l'image originale. N'est utilisé que pour la suavegarde et si l'id est vide. */
			};
			std::vector<frame> m_frames; /*!< La liste de frames. */
			bool m_loaded; /*!< Si l'anim est chargée. */
			Uint32 m_default; /*!< Le temps par défaut. */

			void parseSprites(std::vector<frame>* sprites, TiXmlElement* elem, path_t basepath);

			typedef std::vector<frame>::iterator frame_iterator;
			typedef std::vector<frame>::const_iterator cframe_iterator;
	};
};

#endif//DEF_SDLP_ANIM
