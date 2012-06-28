#ifndef DEF_EDITOR
#define DEF_EDITOR

#include <SDL/SDL.h>
#include <SDLP_sprite.hpp>
#include <SDLP_position.hpp>
#include <SDLP_event.hpp>

#include <guichan.hpp>
#include <guichan/sdl.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/bind.hpp>

#include "mybutton.hpp"
#include "groupModel.hpp"
#include "saabbModel.hpp"
#include "slistener.hpp"
#include "editorArea.hpp"

class Editor
{
	public:
		typedef sdl::ASprite::path_t path_t;

		Editor();
		void load(path_t path);
		void loop();
		void free();

		void update();

	protected:
		void calculatePos(SDL_Rect nsize); // Calcule la position des Widgets
		void colors(); // Colore les widgets

		// Basic functions
		bool save();
		void changeGroup(std::string name);
		void changeIdx(int idx);
		void hotPoint();
		void drawSAABBS();
		void drawAABB(sdl::AABB aabb, gcn::Color* c=NULL); // Dessine une aabb
		void drawPrincAABB(sdl::AABB aabb, gcn::Color* c=NULL); // Dessine l'aabb en édition
		void drawHotPoint(const sdl::Pointsi& pos); // Dessine l'hotpoint
		void changeP();

		void addGroup();
		void deleteGroup();
		void addSAABB();
		void deleteSAABB();

		sdl::SpriteEditor* m_editor;
		void loadSpriteEditor(path_t path);

		void loadImage(path_t path);
		void putPixel(int x, int y, gcn::Color* c=NULL);
		SDL_Rect maxSizeScreen() const;
		void setColor(gcn::Widget* wid, const gcn::Color& bs, const gcn::Color& bg, const gcn::Color& fg, const gcn::Color& sl);

		// General Elements
		path_t m_firstPath;
		sdl::AnEvent* m_U;
		sdl::AnEvent* m_space;
		SDL_Surface* m_icon;

		// Obligatory Elements
		SDL_Surface* ecran;
		gcn::SDLInput* m_input;
		gcn::SDLGraphics* m_graph;
		gcn::SDLImageLoader* m_loader;
		gcn::Gui* m_gui;
		gcn::Container* m_top;
		gcn::ImageFont* m_font;

		// GUI Elements
		SDL_Surface* m_savedsurf;
		SDL_Surface* m_usedsurf;
		gcn::Image* m_image;
		gcn::Icon* m_img;
		gcn::ScrollArea* m_scroll;

		MyButton* m_save;

		gcn::ListBox* m_groups;
		GroupModel* m_groupModel;
		SListener* m_groupListener;
		gcn::ScrollArea* m_scrollGroups;
		gcn::TextField* m_nameNGroup;
		MyButton* m_addGroup;
		MyButton* m_deleteGroup;

		gcn::TextField* m_priority;
		gcn::CheckBox* m_showAll;

		gcn::TextField* m_hotX;
		gcn::TextField* m_hotY;
		MyButton* m_hotP;

		gcn::ListBox* m_saabbs;
		SaabbModel* m_saabbModel;
		SListener* m_saabbListener;
		gcn::ScrollArea* m_scrollSaabb;
		MyButton* m_addSaabb;
		MyButton* m_deleteSaabb;
};

#endif//DEF_EDITOR
