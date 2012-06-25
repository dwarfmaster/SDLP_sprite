#ifndef DEF_EDITOR
#define DEF_EDITOR

#include <SDL/SDL.h>
#include <SDLP_sprite.hpp>
#include <SDLP_position.hpp>
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

class Editor
{
	public:
		typedef sdl::ASprite::path_t path_t;

		Editor();
		void load(path_t path);
		void loop();
		void free();

	protected:
		// Basic functions
		bool save();
		void drawAABB(const sdl::Pointsi& ori, const sdl::AABB& aabb); // Dessine une aabb
		void drawPrincAABB(const sdl::Pointsi& ori, const sdl::AABB& aabb); // Dessine l'aabb en édition
		void changeGroup(std::string name);
		void changeIdx(int idx);

		sdl::SpriteEditor* editor;
		void loadSpriteEditor(path_t path);

		// Obligatory Elements
		SDL_Surface* ecran;
		gcn::SDLInput* m_input;
		gcn::SDLGraphics* m_graph;
		gcn::SDLImageLoader* m_loader;
		gcn::Gui* m_gui;
		gcn::Container* m_top;
		gcn::ImageFont* m_font;

		// GUI Elements
		gcn::ListBox* m_groups;
		GroupModel* m_groupModel;
		SListener* m_groupListener;
		gcn::ScrollArea* m_scrollGroups;
		gcn::Button* m_addGroup;

		gcn::TextField* m_hotX;
		gcn::TextField* m_hotY;
		gcn::Button* m_hotP;

		gcn::ListBox* m_saabbs;
		SaabbModel* m_saabbModel;
		SListener* m_saabbListener;
		gcn::ScrollArea* m_scrollSaabb;
		gcn::Button* m_addSaabb;

		gcn::Icon* m_img;
		gcn::ScrollArea* m_scroll;

		gcn::Button* m_save;
};

#endif//DEF_EDITOR
