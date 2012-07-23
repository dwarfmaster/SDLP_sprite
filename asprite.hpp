#ifndef DEF_SDLP_ASPRITE
#define DEF_SDLP_ASPRITE

#include <vector>
#include <map>
#include <string>
#include <limits>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <tinyxml.h>
#include <SDL/SDL_image.h>

#include <SDLP_position.hpp>
#include <SDLP_tools.hpp>

namespace sdl
{
	struct gaabb
	{
		std::vector<sdl::AABB> saabbs;
		unsigned int priority;
	};

	class SpriteEditor;

	class ASprite
	{
		struct GAABB;

		public:
			typedef boost::filesystem::path path_t;
			friend SpriteEditor;

			ASprite();
			ASprite(path_t path); // charge un fichier .sprite // TODO à supprimer
			ASprite(const ASprite& cp);
			ASprite(const std::map<std::string, gaabb>& groups, const Pointsi& hotp, const boost::shared_ptr<SDL_Surface>& img);

			void set(const ASprite& cp);
			void set(const std::map<std::string, gaabb>& groups, const Pointsi& hotp, const boost::shared_ptr<SDL_Surface>& img);
			bool load(path_t path); // TODO à supprimer
			void clear();

			ASprite& operator=(const ASprite& cp);
			operator SDL_Surface() const;
			operator boost::shared_ptr<SDL_Surface>();

			boost::shared_ptr<SDL_Surface> get() const;
			SDL_Surface* getPtr() const; // Dangereux

			Pointsi hotPoint() const;
			Vector2f decale() const; // retourne le décalage nécessaire à partir du hotPoint.

			AABB global() const;
			std::vector<AABB> saabb(std::string id) const;
			AABB globalSAABB(std::string id) const;
			std::vector<AABB> operator[](std::string id) const;
			bool exist(std::string id) const;
			std::vector<std::string> groups() const;
			std::vector<std::string> inGroup(const Pointsi& p) const;
			std::string inUniqueGroup(const Pointsi& p) const;

			// Les groupes du premiers qui sont en colision avec le second
			std::vector< std::pair<std::string, std::string> > colision(Pointsi pos1, const ASprite& other, Pointsi pos2) const;

		private:
			struct GAABB // Groupe de SAABB
			{
				AABB global;
				std::vector<AABB> aabbs;
				unsigned int priority; // 0 = max level
			};
			std::map<std::string, GAABB> m_groups;
			typedef std::map<std::string,GAABB>::iterator group_iterator;
			typedef std::map<std::string,GAABB>::const_iterator c_group_iterator;

			AABB m_global;

			Pointsi m_hotPoint;

			boost::shared_ptr<SDL_Surface> m_img;

			path_t m_imgPath; // Variable interne pour SpriteEditor // TODO à supprimer
			AABB m_rect; // Idem // TODO à supprimer

			bool parseImage(TiXmlElement* image); // TODO à supprimer
			void parseGAABB(TiXmlElement* gaabb); // TODO à supprimer
			GAABB fromGaabb(const gaabb& cp);
	};
};

#endif//DEF_SDLP_SPRITE
