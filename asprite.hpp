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
	class ASprite
	{
		public:
			typedef boost::filesystem::path path_t;

			ASprite();
			ASprite(path_t path); // charge un fichier .sprite
			ASprite(const ASprite& cp);

			void set(const ASprite& cp);
			bool load(path_t path);
			void clear();

			ASprite& operator=(const ASprite& cp);
			operator SDL_Surface() const;
			operator boost::shared_ptr<SDL_Surface>();

			boost::shared_ptr<SDL_Surface> get() const;
			SDL_Surface* getPtr() const; // Dangereux

			Pointsi hotPoint() const;

			std::vector<AABB> saabb(std::string id) const;
			AABB globalSAABB(std::string id) const;
			std::vector<AABB> operator[](std::string id) const;
			bool exist(std::string id) const;
			std::vector<std::string> groups() const;
			std::vector<std::string> inGroup(const Pointsi& p) const;
			std::string inUniqueGroup(const Pointsi& p) const;

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

			Pointsi m_hotPoint;

			boost::shared_ptr<SDL_Surface> m_img;

			void parseGAABB(TiXmlElement* gaabb);
	};
};

#endif//DEF_SDLP_SPRITE
