#ifndef DEF_CREATOR
#define DEF_CREATOR

#include <SDL.h>
#include <guichan.hpp>
#include <guichan/sdl.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/bind.hpp>

#include <SDLP_tools.hpp>
#include <SDLP_sprite.hpp>
#include <SDLP_event.hpp>

#include <map>
#include <string>

#include "slistener.hpp"
#include "spriteModel.hpp"
#include "mybutton.hpp"
#include "creatorArea.hpp"

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
		void update();

	private:
		void loadImage();

		// Gui functions
		void calculatePos(SDL_Rect nsize); // Calcule la position des Widgets
		void colors(); // Colore les widgets
		void setColor(gcn::Widget* wid, const gcn::Color& bs, const gcn::Color& bg, const gcn::Color& fg, const gcn::Color& sl);

		// Basic functions
		bool save();
		void drawSubSprites();
		void drawRect(sdl::AABB aabb, gcn::Color* c=NULL);
		void drawEditRect(sdl::AABB aabb, gcn::Color* c=NULL);
		void putPixel(int x, int y, gcn::Color* c);

		void updateAllSprites();
		void changeAct(const std::string& nact);
		void addSprite();
		void deleteSprite();
		bool exists(std::string sprite);
		void set();

		// Basic members
		path_t m_path; // Chemin vers l'image
		std::map<std::string, sdl::AABB> m_sprites;
		std::string m_act;
		std::vector<std::string> m_allsprites;
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
		SDL_Surface* m_usedSurf;
		gcn::Image* m_image;
		gcn::Icon* m_print;
		gcn::ScrollArea* m_creator;

		gcn::ListBox* m_spritesList;
		SpriteModel* m_spritesModel;
		SListener* m_spritesListener;
		gcn::ScrollArea* m_spritesScroll;
		gcn::TextField* m_nameNSprite;
		MyButton* m_add;
		MyButton* m_del;

		gcn::Label* m_x;
		gcn::TextField* m_xfield;
		gcn::Label* m_y;
		gcn::TextField* m_yfield;
		gcn::Label* m_w;
		gcn::TextField* m_wfield;
		gcn::Label* m_h;
		gcn::TextField* m_hfield;
		MyButton* m_set;

		MyButton* m_save;

};

#endif//DEF_CREATOR
