#include "editor.hpp"

Editor::Editor()
	: ecran(NULL), m_input(NULL), m_graph(NULL), m_loader(NULL),
	m_gui(NULL), m_top(NULL), m_font(NULL),
	m_groups(NULL), m_groupModel(NULL), m_groupListener(NULL), m_scrollGroups(NULL), m_addGroup(NULL),
	m_hotX(NULL), m_hotY(NULL), m_hotP(NULL),
	m_saabbs(NULL), m_saabbModel(NULL), m_saabbListener(NULL), m_scrollSaabb(NULL), m_addSaabb(NULL),
	m_img(NULL), m_scroll(NULL), m_save(NULL)
{}

void Editor::loop()
{
}

void Editor::free()
{
	delete m_font;
	delete m_top;
	delete m_gui;
	
	delete m_loader;
	delete m_graph;
	delete m_input;

	SDL_Quit();
}

void Editor::load(path_t path)
{
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
		throw std::string("Erreur au chargement de la lib SDL.");

	ecran = SDL_SetVideoMode(640, 480, 24, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if( ecran == NULL )
		throw std::string("Erreur à l'ouverture de la fenêtre.");

	SDL_EnableUNICODE(1);

	m_input = new gcn::SDLInput;
	m_graph = new gcn::SDLGraphics;
	m_graph->setTarget(ecran);
	m_loader = new gcn::SDLImageLoader;
	gcn::Image::setImageLoader(m_loader);

	m_gui = new gcn::Gui;
	m_gui->setGraphics(m_graph);
	m_gui->setInput(m_input);
	m_top = new gcn::Container;
	m_top->setDimension(gcn::Rectangle(0, 0, ecran->w, ecran->h));
	m_top->setOpaque(true);
	m_gui->setTop(m_top);
	m_font = new gcn::ImageFont("font.png", " abcdefghijklmnopqrstuvwxyzABCEDFGHIJKLMNOPQRSTUVWXYZ0123456789"); // À compléter
	gcn::Widget::setGlobalFont(m_font);
}

void Editor::loadSpriteEditor(path_t path)
{
	std::string ext = boost::filesystem::extension(path);
	std::cout<<ext<<std::endl;

	if(ext == "sprite"
			|| ext == "xml")
	{
	}
	else
	{
	}
}

