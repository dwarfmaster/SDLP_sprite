#ifndef DEF_SDLP_ANIM
#define DEF_SDLP_ANIM

#include "asprite.hpp"

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
			size_t idFromName(const std::string& name) const;
			std::string nameFromId(size_t id) const;
			ASprite* sprite(const std::string& frame) const;
			ASprite* operator[](const std::string& frame) const;
			unsigned int time(const std::string& frame) const;
			unsigned int time() const; // Retourne la durée totale de l'animation
			unsigned int defaultTime() const;

			void changeSprite(const std::string& frame, ASprite* nsprite, bool tofree=false);
			void changeTime(const std::string& frame, unsigned int ntime);
			void reorder(const std::vector<std::string>& norder); // Change l'ordre selon le vector, une entrée non existante sera ignorée et les entrées non précisées seront mises à la fin
			void addFrame(unsigned int pos, const std::string& id, ASprite* sprite, unsigned int time=0, bool tofree=false); // Si time = 0, alors la valeur par défaut sera appliquée; les frames suivantes seront décalées
			void deleteFrame(const std::string& name);

			bool exist(const std::string& frame) const;

			ASprite* update(); // Va mettre à jour m_lastTime, m_act et m_timeStay
			ASprite* getSprite() const;
			operator ASprite*() const;
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
				std::string id;
				ASprite* sprite;
				bool toFree;
				unsigned int time; // Durée de la frame
			};
			std::list<frame> m_frames;
			bool m_loaded;
			unsigned int m_default; // Time

			typedef std::list<frame>::iterator frame_iterator;
			typedef std::list<frame>::const_iterator cframe_iterator;
	};
};

#endif//DEF_SDLP_ANIM
