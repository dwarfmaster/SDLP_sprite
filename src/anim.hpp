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
			Uint32 m_lastTime; // Le temps lors du dernier appel à update
			size_t m_act; // L'id de l'actuel
			bool m_pause;
			Uint32 m_timeStay; // Temps restant avant le changement
			float m_speed; // Multiplier de vitesse

			struct frame
			{
				std::string name;
				ASprite* sprite;
				bool toFree;
				Uint32 time; // Durée de la frame

				std::string path; // Utilisé uniquement pour la sauvegarde
				std::string id; // Idem
				AABB rect; // Idem
			};
			std::vector<frame> m_frames; // Il peut y avoir un ajout au milieu, mais l'accès rapide est plus important
			bool m_loaded;
			Uint32 m_default; // Time

			void parseSprites(std::vector<frame>* sprites, TiXmlElement* elem, path_t basepath);

			typedef std::vector<frame>::iterator frame_iterator;
			typedef std::vector<frame>::const_iterator cframe_iterator;
	};
};

#endif//DEF_SDLP_ANIM
