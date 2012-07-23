#include "editor.hpp"

	Editor::Editor()
: m_file(NULL), m_editor(NULL), m_U(NULL), m_space(NULL), m_icon(NULL),
	ecran(NULL), m_input(NULL), m_graph(NULL), m_loader(NULL),
	m_gui(NULL), m_top(NULL), m_font(NULL),
	m_savedsurf(NULL), m_usedsurf(NULL), m_image(NULL), m_img(NULL), m_scroll(NULL), m_save(NULL),
	m_groups(NULL), m_groupModel(NULL), m_groupListener(NULL), m_scrollGroups(NULL),
	m_nameNGroup(NULL), m_addGroup(NULL), m_deleteGroup(NULL), 
	m_priority(NULL), m_showAll(NULL),
	m_hotX(NULL), m_hotY(NULL), m_hotP(NULL),
	m_saabbs(NULL), m_saabbModel(NULL), m_saabbListener(NULL), m_scrollSaabb(NULL),
	m_addSaabb(NULL), m_deleteSaabb(NULL)
{}

void Editor::loop()
{
	bool continuer=true;
	sdl::Event event;

	event.addQuitKey(SDLK_ESCAPE);
	event.setOnCaptedEventCallback( boost::bind(&gcn::SDLInput::pushInput, m_input, _1) );
	// event.setOnResizeWindowCallback( boost::bind(&Editor::calculatePos, this, _1) );
	event.addPEvent("update_u", m_U, boost::bind(&Editor::drawSAABBS, this));
	event.addPEvent("update_space", m_space, boost::bind(&Editor::drawSAABBS, this));

	while(continuer)
	{
		event.update();

		if(event.quit())
			continuer=false;

		m_gui->logic();
		m_gui->draw();
		SDL_Flip(ecran);

		SDL_Delay(1000/60);
	}
}

void Editor::load(path_t path, std::string id)
{
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
		throw std::string("Erreur au chargement de la lib SDL.");

	SDL_WM_SetIcon(m_icon, NULL);
	SDL_WM_SetCaption("SDLP_Sprite Editor", NULL);

	ecran = SDL_SetVideoMode(800, 600, 24, SDL_HWSURFACE | SDL_DOUBLEBUF); // SDL_RESIZABLE
	if( ecran == NULL )
		throw std::string("Erreur à l'ouverture de la fenêtre.");

	m_icon = IMG_Load("./icon.png");
	if(m_icon == NULL)
		throw std::string("Erreur au chargement de l'icone.");

	SDL_Rect msize = maxSizeScreen();
	SDL_EnableUNICODE(1);

	m_U = new sdl::AnEvent("u");
	m_space = new sdl::AnEvent(SDLK_SPACE);

	m_input = new gcn::SDLInput;
	m_graph = new gcn::SDLGraphics;
	m_graph->setTarget(ecran);
	m_loader = new gcn::SDLImageLoader;
	gcn::Image::setImageLoader(m_loader);

	m_gui = new gcn::Gui;
	m_gui->setGraphics(m_graph);
	m_gui->setInput(m_input);
	m_top = new gcn::Container;
	m_top->setOpaque(true);
	// m_top->setDimension(gcn::Rectangle(0, 0, msize.w, msize.h));
	m_top->setDimension(gcn::Rectangle(0, 0, ecran->w, ecran->h));
	m_gui->setTop(m_top);
	m_font = new gcn::ImageFont("font.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\"");
	gcn::Widget::setGlobalFont(m_font);

	loadSpriteEditor(path, id);

	loadImage();
	m_image = new gcn::SDLImage(m_usedsurf, false);
	m_img = new gcn::Icon(m_image);
	m_scroll = new EditorArea(m_editor, this, m_img);

	m_save = new MyButton("Save");
	m_save->setClicCallback(boost::bind(&Editor::save, this));

	m_groupModel = new GroupModel(m_editor);
	m_groupListener = new SListener(boost::bind(&Editor::changeGroup, this, _2));
	m_groups = new gcn::ListBox(m_groupModel);
	m_groups->addSelectionListener(m_groupListener);
	m_groups->setWrappingEnabled(true);
	m_groups->setWidth(200);
	m_scrollGroups = new gcn::ScrollArea(m_groups);
	m_scrollGroups->setScrollbarWidth(5);
	m_nameNGroup = new gcn::TextField;
	m_addGroup = new MyButton("Add");
	m_addGroup->setClicCallback(boost::bind(&Editor::addGroup, this));
	m_deleteGroup = new MyButton("Delete");
	m_deleteGroup->setClicCallback(boost::bind(&Editor::deleteGroup, this));

	m_priority = new gcn::TextField;
	m_showAll = new gcn::CheckBox("Show all", false);

	m_hotX = new gcn::TextField( sdl::itoa(m_editor->hotpoint().x) );
	m_hotY = new gcn::TextField( sdl::itoa(m_editor->hotpoint().y) );
	m_hotP = new MyButton("HotPoint");
	m_hotP->setClicCallback( boost::bind(&Editor::hotPoint, this) );

	m_saabbModel = new SaabbModel(m_editor);
	m_saabbListener = new SListener(boost::bind(&Editor::changeIdx, this, _1));
	m_saabbs = new gcn::ListBox(m_saabbModel);
	m_saabbs->addSelectionListener(m_saabbListener);
	m_saabbs->setWrappingEnabled(true);
	m_saabbs->setWidth(300);
	m_scrollSaabb = new gcn::ScrollArea(m_saabbs);
	m_scrollSaabb->setScrollbarWidth(5);
	m_addSaabb = new MyButton("Add");
	m_addSaabb->setClicCallback(boost::bind(&Editor::addSAABB, this));
	m_deleteSaabb = new MyButton("Delete");
	m_deleteSaabb->setClicCallback(boost::bind(&Editor::deleteSAABB, this));

	calculatePos(sdl::makeRect(0, 0, ecran->w, ecran->h));
	colors();

	m_top->add(m_scroll);
	m_top->add(m_save);
	m_top->add(m_scrollGroups);
	m_top->add(m_nameNGroup);
	m_top->add(m_addGroup);
	m_top->add(m_deleteGroup);
	m_top->add(m_priority);
	m_top->add(m_showAll);
	m_top->add(m_hotX);
	m_top->add(m_hotY);
	m_top->add(m_hotP);
	m_top->add(m_scrollSaabb);
	m_top->add(m_addSaabb);
	m_top->add(m_deleteSaabb);

	drawHotPoint(m_editor->hotpoint());
}

void Editor::calculatePos(SDL_Rect nsize)
{
	int y = nsize.h - m_hotP->getHeight() - 6;
	m_hotP->setSpacing(2);
	m_hotP->setPosition(150 - m_hotP->getWidth() - 4, y);
	y -= m_font->getHeight() + 4;
	m_hotX->setDimension(gcn::Rectangle(2, y, 73, m_font->getHeight() + 2));
	m_hotY->setDimension(gcn::Rectangle(m_hotX->getWidth() + 2, y, 73, m_font->getHeight() + 2));

	y -= m_showAll->getHeight() + 20;
	m_showAll->setPosition(0, y);
	y -= m_font->getHeight() + 6;
	m_priority->setDimension( gcn::Rectangle(0, y, 150, m_font->getHeight() + 4) );
	y -= m_addGroup->getHeight() + 6;
	m_addGroup->setSpacing(2);
	m_addGroup->setPosition(150 - m_addGroup->getWidth() - 4, y);
	m_deleteGroup->setSpacing(2);
	m_deleteGroup->setPosition(0, y);
	y -= m_font->getHeight() + 8;
	m_nameNGroup->setDimension(gcn::Rectangle(2, y, 148, m_font->getHeight() + 4));
	y -= 6;
	m_groups->adjustSize();
	m_scrollGroups->setDimension(gcn::Rectangle(2, 2, 148, y));

	int x = nsize.w - m_save->getWidth() - 4;
	y = nsize.h - m_save->getHeight() - 6;
	m_save->setPosition(x, y);
	m_save->setSpacing(2);

	y -= m_addSaabb->getHeight() + 20;
	x = nsize.w - 150;
	m_addSaabb->setPosition(x, y);
	m_addSaabb->setSpacing(2);
	m_deleteSaabb->setPosition(nsize.w - m_deleteSaabb->getWidth(), y);
	m_deleteSaabb->setSpacing(2);
	m_saabbs->adjustSize();
	m_scrollSaabb->setDimension(gcn::Rectangle(x, 2, 148, y-6));

	x -= 154;
	m_scroll->setDimension(gcn::Rectangle(152, 2, x, nsize.h-4));
}

void Editor::colors()
{
	// gcn::Color bs(125, 125, 125);
	gcn::Color bs(100, 100, 0);
	gcn::Color bg(0, 0, 0);
	gcn::Color fg(255, 165, 0);
	// gcn::Color fg(150, 100, 0);
	gcn::Color sl(255, 165, 0);

	setColor(m_save, bs, bg, fg, sl);
	setColor(m_scroll, bs, bg, fg, sl);
	setColor(m_img, bs, bg, fg, sl);
	setColor(m_scrollGroups, bs, bg, fg, sl);
	setColor(m_groups, bs, bg, fg, sl);
	setColor(m_addGroup, bs, bg, fg, sl);
	setColor(m_deleteGroup, bs, bg, fg, sl);
	setColor(m_nameNGroup, bs, bg, fg, sl);
	setColor(m_priority, bs, bg, fg, sl);
	setColor(m_showAll, bs, bg, fg, sl);
	setColor(m_hotX, bs, bg, fg, sl);
	setColor(m_hotY, bs, bg, fg, sl);
	setColor(m_hotP, bs, bg, fg, sl);
	setColor(m_scrollSaabb, bs, bg, fg, sl);
	setColor(m_saabbs, bs, bg, fg, sl);
	setColor(m_addSaabb, bs, bg, fg, sl);
	setColor(m_deleteSaabb, bs, bg, fg, sl);

	bs = gcn::Color(150, 100, 0);
	setColor(m_top, bs, bg, fg, sl);
}

void Editor::free()
{
	delete m_U;
	delete m_space;

	SDL_FreeSurface(m_savedsurf);
	SDL_FreeSurface(m_usedsurf);
	SDL_FreeSurface(m_icon);

	delete m_save;
	delete m_scroll;
	delete m_image;
	delete m_img;

	delete m_scrollGroups;
	delete m_groups;
	delete m_groupModel;
	delete m_groupListener;
	delete m_addGroup;
	delete m_deleteGroup;
	delete m_nameNGroup;

	delete m_priority;
	delete m_showAll;

	delete m_hotX;
	delete m_hotY;
	delete m_hotP;

	delete m_scrollSaabb;
	delete m_saabbs;
	delete m_saabbModel;
	delete m_saabbListener;
	delete m_addSaabb;
	delete m_deleteSaabb;

	delete m_editor;
	delete m_file;

	delete m_font;
	delete m_top;
	delete m_gui;

	delete m_loader;
	delete m_graph;
	delete m_input;

	SDL_Quit();
}

void Editor::update()
{
	m_hotX->setText( sdl::itoa(m_editor->hotpoint().x) );
	m_hotY->setText( sdl::itoa(m_editor->hotpoint().y) );

	drawSAABBS();
}

void Editor::loadSpriteEditor(path_t path, std::string id)
{
	std::string ext = boost::filesystem::extension(path);

	if(ext == ".sprite"
			|| ext == ".sprites"
			|| ext == ".xml")
	{
		m_file = new sdl::SpriteFile;
		if(!m_file->load(path))
			throw std::string("Erreur au chargement du sprite.");
		m_editor = new sdl::SpriteEditor(m_file, id);
	}
	else
		throw std::string("Le fichier à charger n'est pas un sprite.");

	m_firstPath = path;
}

void Editor::loadImage()
{
	m_savedsurf = m_editor->getReal();
	if(m_savedsurf == NULL)
		throw std::string("Erreur à l'obtention de l'image.");

	SDL_Surface* tmp = m_savedsurf;
	m_savedsurf = SDL_DisplayFormat(tmp);
	// SDL_FreeSurface(tmp); -> tmp sera libéré par le pointeur automatique de boost

	tmp = SDL_CreateRGBSurface(SDL_HWSURFACE, m_savedsurf->w, m_savedsurf->h, 24, 0, 0, 0, 0);
	if(tmp == NULL)
		throw std::string("Erreur à la création de la surface de dession.");
	m_usedsurf = SDL_DisplayFormat(tmp);
	SDL_FreeSurface(tmp);
	SDL_BlitSurface(m_savedsurf, NULL, m_usedsurf, NULL);
}

bool Editor::save()
{
	m_editor->setPriority( sdl::atoi(m_priority->getText()) );
	path_t path = boost::filesystem::change_extension(m_firstPath, ".sprite");
	std::cout << "Save path : " << path << std::endl; // TODO juste pour tester
	m_editor->save(path);
	return true;
}

void Editor::drawSAABBS()
{
	SDL_BlitSurface(m_savedsurf, NULL, m_usedsurf, NULL);

	if(m_showAll->isSelected())
	{
		gcn::Color c(255, 165, 0);
		std::vector<std::string> groups = m_editor->groups();
		for(size_t i=0; i<groups.size(); ++i)
		{
			if(groups[i] != m_editor->current())
			{
				std::vector<sdl::AABB> saabbs = (*m_editor)[groups[i]];
				for(size_t j=0; j<saabbs.size(); ++j)
					drawAABB(saabbs[j], &c);
			}
		}
	}

	std::vector<sdl::AABB> saabbs = m_editor->SAABBS();
	for(size_t i=0; i<saabbs.size(); ++i)
		if((int)i == m_saabbs->getSelected())
			drawPrincAABB(saabbs[i]);
		else
			drawAABB(saabbs[i]);
	drawHotPoint(m_editor->hotpoint());
}

void Editor::drawAABB(sdl::AABB aabb, gcn::Color* c)
{
	gcn::Color col;
	if(c == NULL)
		col.r = col.g = col.b = 0;
	else
		col = *c;

	for(size_t i=0; i<2; ++i)
	{
		for(int x = aabb->x; x < aabb->x + aabb->w; ++x)
		{
			putPixel(x, aabb->y, &col);
			putPixel(x, aabb->y + aabb->h, &col);
		}

		for(int y = aabb->y; y < aabb->y + aabb->h; ++y)
		{
			putPixel(aabb->x, y, &col);
			putPixel(aabb->x + aabb->w, y, &col);
		}

		aabb->x-=1;
		aabb->y-=1;
		aabb->w+=2;
		aabb->h+=2;
	}
}

void Editor::drawPrincAABB(sdl::AABB aabb, gcn::Color* c)
{
	drawAABB(aabb, c);
	aabb->x+=2;
	aabb->y+=2;
	aabb->w-=4;
	aabb->h-=4;
	drawAABB(aabb, c);
}

void Editor::drawHotPoint(const sdl::Pointsi& pos)
{
	gcn::Color c(255, 0, 0);

	for(int x = pos.x - 3; x <= pos.x+3; ++x)
		putPixel(x, pos.y, &c);
	for(int y = pos.y - 3; y <= pos.y+3; ++y)
		putPixel(pos.x, y, &c);
	for(int x = pos.x - 1; x <= pos.x+1; ++x)
		for(int y = pos.y - 1; y <= pos.y+1; ++y)
			putPixel(x, y, &c);
}

void Editor::changeGroup(std::string name)
{
	m_editor->setPriority( sdl::atoi(m_priority->getText()) );

	int i = m_saabbs->getSelected();
	m_editor->setCurrent(name);

	if(i >= m_saabbModel->getNumberOfElements())
		m_saabbs->setSelected( m_saabbModel->getNumberOfElements() - 1 );
	else if(i<0
			&& m_saabbModel->getNumberOfElements() > 0)
		m_saabbs->setSelected( 0 );
	else
		m_saabbs->setSelected( i );

	m_saabbs->adjustSize();
	m_priority->setText( sdl::itoa(m_editor->getPriority()) );
	drawSAABBS();
}

void Editor::changeIdx(int idx)
{
	m_editor->setCurrent(m_editor->current(), idx);
	drawSAABBS();
}

void Editor::addGroup()
{
	std::string name = m_nameNGroup->getText();
	if(name == "")
		return;
	m_nameNGroup->setText("");
	m_editor->addGroup(name);
	m_groups->setSelected( m_groupModel->nbGroup(name) );
	m_groups->adjustSize();
	drawSAABBS();
}

void Editor::deleteGroup()
{
	int i = m_groups->getSelected();
	if(i < 0)
		return;

	m_editor->deleteCurrentGroup();
	m_groups->setSelected(i);
}

void Editor::addSAABB()
{
	sdl::AABB aabb(sdl::makeRect(0, 0, 10, 10));
	m_editor->addSAABB(aabb);
	m_saabbs->setSelected( m_saabbModel->getNumberOfElements() - 1);
	m_saabbs->adjustSize();
	drawSAABBS();
}

void Editor::deleteSAABB()
{
	int i = m_saabbs->getSelected();
	if(i < 0)
		return;

	m_editor->deleteCurrent();
	m_saabbs->setSelected(i);
}

void Editor::hotPoint()
{
	int x = sdl::atoi( m_hotX->getText() );
	int y = sdl::atoi( m_hotY->getText() );

	m_editor->setHotPoint( sdl::Pointsi(x,y) );
	drawSAABBS();
}

void Editor::putPixel(int x, int y, gcn::Color* c)
{
	if( x >= m_usedsurf->w
			|| x < 0 
			|| y >= m_usedsurf->h
			|| y < 0 )
		return;

	int bpp = m_usedsurf->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)m_usedsurf->pixels + y * m_usedsurf->pitch + x * bpp;

	Uint32 pixel = 0;
	if(c == NULL)
		pixel = SDL_MapRGB(m_usedsurf->format, 0, 0, 0);
	else
		pixel = SDL_MapRGB(m_usedsurf->format, c->r, c->g, c->b);

	switch(bpp) {
		case 1:
			*p = pixel;
			break;

		case 2:
			*(Uint16 *)p = pixel;
			break;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32 *)p = pixel;
			break;
	}
}

SDL_Rect Editor::maxSizeScreen() const
{
	SDL_Rect** modes = SDL_ListModes(NULL, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);

	if(modes == (SDL_Rect**)0)
		return sdl::makeRect(0, 0, 0, 0);
	else if(modes == (SDL_Rect**)-1)
		return sdl::makeRect(0, 0, 1600, 900);
	else
		return *modes[0];
}

void Editor::setColor(gcn::Widget* wid, const gcn::Color& bs, const gcn::Color& bg, const gcn::Color& fg, const gcn::Color& sl)
{
	wid->setBaseColor(bs);
	wid->setBackgroundColor(bg);
	wid->setForegroundColor(fg);
	wid->setSelectionColor(sl);
}

void Editor::changeP()
{
}

