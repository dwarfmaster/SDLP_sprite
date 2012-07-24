#ifndef DEF_CREATOR
#define DEF_CREATOR

#include <SDL.h>
#include <guichan.hpp>
#include <guichan/sdl.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/bind.hpp>

#include <SDLP_tools.hpp>
#include <SDLP_sprite.hpp>
#include <SDLP_event.hpp>

#include <map>
#include <string>

class Creator
{
	public:
		typedef boost::filesystem::path path_t;

		Creator();
		void load(const path_t& img);
		void loop();
		void free();

		void changeSprite(sdl::AABB naabb);
		sdl::AABB getSprite();

	private:
		// Gui functions
		void calculatePos(SDL_Rect nsize); // Calcule la position des Widgets
		void colors(); // Colore les widgets

		// Basic functions
		bool save();
		void drawSubSprites();
		void drawRect(sdl::AABB aabb, gcn::Color* c=NULL);
		void drawEditRect(sdl::AABB aabb, gcn::Color* c=NULL);

		// Basic members
		path_t m_path; // Chemin vers l'image
		std::map<std::string, sdl::AABB> m_sprites;
		SDL_Surface* m_img;

		// Necessary gui members
		SDL_Surface* ecran;
		gcn::SDLInput* m_input;
		gcn::SDLGraphics* m_graph;
		gcn::SDLImageLoader* m_loader;
		gcn::Gui* m_gui;
		gcn::Container* m_top;
		gcn::ImageFont* m_font;

		// Gui elements
		// TODO à remplir

};

#endif//DEF_CREATOR
