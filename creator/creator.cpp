#include "creator.hpp"

Creator::Creator()
	: m_img(NULL),
	ecran(NULL), m_input(NULL), m_graph(NULL), m_loader(NULL), m_gui(NULL), m_top(NULL), m_font(NULL),
	m_usedSurf(NULL), m_image(NULL), m_print(NULL), m_creator(NULL),
	m_spritesList(NULL), m_spritesModel(NULL), m_spritesListener(NULL), m_spritesScroll(NULL),
	m_nameNSprite(NULL), m_add(NULL), m_del(NULL),
	m_x(NULL), m_xfield(NULL), m_y(NULL), m_yfield(NULL), m_w(NULL), m_wfield(NULL), m_h(NULL), m_hfield(NULL),
	m_set(NULL), m_save(NULL)
{
}

void Creator::loop()
{
	bool continuer=true;
	sdl::Event event;

	event.addQuitKey(SDLK_ESCAPE);
	event.setOnCaptedEventCallback( boost::bind(&gcn::SDLInput::pushInput, m_input, _1) );

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

void Creator::load(const path_t& img)
{
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
		throw std::string("Erreur au chargement de la lib SDL.");

	SDL_WM_SetCaption("SDLP_Sprite Creator", NULL);
	ecran = SDL_SetVideoMode(800, 600, 24, SDL_HWSURFACE | SDL_DOUBLEBUF);
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
	m_top->setOpaque(true);
	m_top->setDimension(gcn::Rectangle(0, 0, ecran->w, ecran->h));
	m_gui->setTop(m_top);

	path_t path = std::string(RCDIR) + "/font.png";
	m_font = new gcn::ImageFont(path.string(), " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\"");
	gcn::Widget::setGlobalFont(m_font);

	m_path = img;
	loadImage();
	m_image = new gcn::SDLImage(m_usedSurf, false);
	m_print = new gcn::Icon(m_image);
	m_creator = new CreatorArea(this, m_print);

	updateAllSprites();
	m_spritesModel = new SpriteModel(m_allsprites);
	m_spritesListener = new SListener( boost::bind(&Creator::changeAct, this, _2) );
	m_spritesList = new gcn::ListBox(m_spritesModel);
	m_spritesList->addSelectionListener(m_spritesListener);
	m_spritesList->setWrappingEnabled(true);
	m_spritesList->setWidth(200);
	m_spritesScroll = new gcn::ScrollArea(m_spritesList);

	m_nameNSprite = new gcn::TextField;
	m_add = new MyButton("Add");
	m_add->setClicCallback( boost::bind(&Creator::addSprite, this) );
	m_del = new MyButton("Delete");
	m_del->setClicCallback( boost::bind(&Creator::deleteSprite, this) );

	m_x = new gcn::Label("X:");
	m_xfield = new gcn::TextField;
	m_y = new gcn::Label("Y:");
	m_yfield = new gcn::TextField;
	m_w = new gcn::Label("W:");
	m_wfield = new gcn::TextField;
	m_h = new gcn::Label("H:");
	m_hfield = new gcn::TextField;

	m_set = new MyButton("Set");
	m_set->setClicCallback( boost::bind(&Creator::set, this) );
	m_save = new MyButton("Save");
	m_save->setClicCallback( boost::bind(&Creator::save, this) );

	calculatePos( sdl::makeRect(0, 0, ecran->w, ecran->h) );
	colors();

	m_top->add(m_spritesScroll);
	m_top->add(m_nameNSprite);
	m_top->add(m_add);
	m_top->add(m_del);
	m_top->add(m_x);
	m_top->add(m_xfield);
	m_top->add(m_y);
	m_top->add(m_yfield);
	m_top->add(m_w);
	m_top->add(m_wfield);
	m_top->add(m_h);
	m_top->add(m_hfield);
	m_top->add(m_set);
	m_top->add(m_save);
	m_top->add(m_creator);
}

void Creator::free()
{
	delete m_spritesScroll;
	delete m_spritesModel;
	delete m_spritesListener;
	delete m_spritesList;

	delete m_nameNSprite;
	delete m_add;
	delete m_del;

	delete m_x;
	delete m_xfield;
	delete m_y;
	delete m_yfield;
	delete m_w;
	delete m_wfield;
	delete m_h;
	delete m_hfield;

	delete m_set;
	delete m_save;

	SDL_FreeSurface(m_img);
	SDL_FreeSurface(m_usedSurf);
	delete m_print;

	delete m_top;
	delete m_font;
	delete m_gui;
	delete m_graph;
	delete m_input;
	delete m_loader;

	SDL_Quit();
}

void Creator::loadImage()
{
	m_img = IMG_Load(m_path.string().c_str());
	if(m_img == NULL)
		throw std::string("Erreur au chargement de l'image.");

	SDL_Surface* tmp = SDL_DisplayFormat(m_img);
	if(tmp != NULL)
	{
		SDL_FreeSurface(m_img);
		m_img = tmp;
	}

	m_usedSurf = SDL_CreateRGBSurface(SDL_HWSURFACE, m_img->w, m_img->h, 24, 0, 0, 0, 0);
	if(m_usedSurf == NULL)
		throw std::string("Erreur à la création de la surface de dessin.");

	tmp = SDL_DisplayFormat(m_usedSurf);
	if(tmp != NULL)
	{
		SDL_FreeSurface(m_usedSurf);
		m_usedSurf = tmp;
	}

	SDL_BlitSurface(m_img, NULL, m_usedSurf, NULL);
}

void Creator::changeSprite(sdl::AABB naabb)
{
	if( !exists(m_act) )
		return;

	if(naabb->x < 0)
		naabb->x = 0;
	else if(naabb->x > m_img->w - 10)
		naabb->x = m_img->w-10;

	if(naabb->y < 0)
		naabb->y = 0;
	else if(naabb->y > m_img->h - 10)
		naabb->y = m_img->h-10;

	if(naabb->w < 10)
		naabb->w = 10;
	else if(naabb->w + naabb->x > m_img->w)
		naabb->w = m_img->w-naabb->x;

	if(naabb->h < 10)
		naabb->h = 10;
	else if(naabb->h + naabb->y > m_img->h)
		naabb->h = m_img->h-naabb->y;

	m_sprites[m_act] = naabb;
	update();
}

sdl::AABB Creator::getSprite()
{
	if( !exists(m_act) )
		return sdl::AABB( sdl::makeRect(0, 0, m_img->w, m_img->h) );
	else
		return m_sprites[m_act];
}

void Creator::calculatePos(SDL_Rect nsize)
{
	unsigned int x = 150 - m_save->getWidth() - 6;
	unsigned int y = nsize.h - m_save->getHeight() - 6;
	m_save->setSpacing(2);
	m_save->setPosition(x, y);

	y -= m_set->getHeight() + 20;
	x = 150 - m_set->getWidth() - 4;
	m_set->setSpacing(2);
	m_set->setPosition(x, y);

	y -= m_w->getHeight() + 4;
	m_w->setPosition(2, y);
	x = m_w->getWidth() + 3;
	m_wfield->setDimension( gcn::Rectangle(x, y, 150/2-x, m_w->getHeight()) ); 
	x += m_wfield->getWidth() + 2;
	m_h->setPosition(x, y);
	x += m_h->getWidth() + 1;
	m_hfield->setDimension( gcn::Rectangle(x, y, 148-x, m_h->getHeight()) );

	y -= m_x->getHeight() + 6;
	m_x->setPosition(2, y);
	x = m_x->getWidth() + 3;
	m_xfield->setDimension( gcn::Rectangle(x, y, 150/2-x, m_x->getHeight()) ); 
	x += m_xfield->getWidth() + 2;
	m_y->setPosition(x, y);
	x += m_y->getWidth() + 1;
	m_yfield->setDimension( gcn::Rectangle(x, y, 148-x, m_y->getHeight()) );

	y -= m_add->getHeight() + 20;
	x = 150 - m_add->getWidth() - 4;
	m_add->setPosition(x, y);
	m_add->setSpacing(2);
	x = 2;
	m_del->setPosition(x, y);
	m_del->setSpacing(2);
	y -= m_font->getHeight() + 6;
	m_nameNSprite->setDimension( gcn::Rectangle(x, y, 146, m_font->getHeight()+2) );

	y -= 10;
	m_spritesScroll->setDimension( gcn::Rectangle(2, 2, 146, y) );

	m_creator->setDimension( gcn::Rectangle(150, 2, nsize.w-152, nsize.h-4) );
}

void Creator::colors()
{
	gcn::Color bs(100, 100, 0);
	gcn::Color bg(0, 0, 0);
	gcn::Color fg(255, 165, 0);
	gcn::Color sl(255, 165, 0);

	setColor(m_top, bs, bg, fg, sl);
	setColor(m_save, bs, bg, fg, sl);
	setColor(m_set, bs, bg, fg, sl);
	setColor(m_x, bs, bg, fg, sl);
	setColor(m_xfield, bs, bg, fg, sl);
	setColor(m_y, bs, bg, fg, sl);
	setColor(m_yfield, bs, bg, fg, sl);
	setColor(m_w, bs, bg, fg, sl);
	setColor(m_wfield, bs, bg, fg, sl);
	setColor(m_h, bs, bg, fg, sl);
	setColor(m_hfield, bs, bg, fg, sl);
	setColor(m_add, bs, bg, fg, sl);
	setColor(m_del, bs, bg, fg, sl);
	setColor(m_nameNSprite, bs, bg, fg, sl);
	setColor(m_spritesScroll, bs, bg, fg, sl);
	setColor(m_spritesList, bs, bg, fg, sl);
	setColor(m_creator, bs, bg, fg, sl);
}

bool Creator::save()
{
	path_t spath = boost::filesystem::change_extension(m_path, ".sprite");

	boost::filesystem::ofstream file(spath);
	if(!file)
		return false;

	file << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n\n";
	file << "<image path=\"" << m_path.string() << "\" />\n\n";

	for(std::map<std::string,sdl::AABB>::iterator it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		file << "<sprite id=\"" << it->first
			<< "\" x=\"" << sdl::itoa(it->second->x)
			<< "\" y=\"" << sdl::itoa(it->second->y)
			<< "\" w=\"" << sdl::itoa(it->second->w)
			<< "\" h=\"" << sdl::itoa(it->second->h)
			<< "\" >" << std::endl;
		file << "</sprite>\n" << std::endl;
	}

	return true;
}

void Creator::drawSubSprites()
{
	for(std::map<std::string, sdl::AABB>::iterator it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		if(it->first == m_act)
			drawEditRect(it->second);
		else
			drawRect(it->second);
	}
}

void Creator::drawRect(sdl::AABB aabb, gcn::Color* c)
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

void Creator::drawEditRect(sdl::AABB aabb, gcn::Color* c)
{
	drawRect(aabb, c);
	aabb->x+=2;
	aabb->y+=2;
	aabb->w-=4;
	aabb->h-=4;
	drawRect(aabb, c);
}

void Creator::update()
{
	updateAllSprites();
	SDL_BlitSurface(m_img, NULL, m_usedSurf, NULL);
	drawSubSprites();

	if( exists(m_act) )
	{
		m_xfield->setText( sdl::itoa(m_sprites[m_act]->x) );
		m_yfield->setText( sdl::itoa(m_sprites[m_act]->y) );
		m_wfield->setText( sdl::itoa(m_sprites[m_act]->w) );
		m_hfield->setText( sdl::itoa(m_sprites[m_act]->h) );

		if(m_spritesList->getSelected() != m_spritesModel->getIndexOf(m_act))
			m_spritesList->setSelected( m_spritesModel->getIndexOf(m_act) );
	}
	else
	{
		m_xfield->setText("");
		m_yfield->setText("");
		m_wfield->setText("");
		m_hfield->setText("");
	}
}

void Creator::updateAllSprites()
{
	std::vector<std::string> sprites;

	for(std::map<std::string, sdl::AABB>::iterator it = m_sprites.begin(); it != m_sprites.end(); ++it)
		sprites.push_back(it->first);

	m_allsprites = sprites;
}

void Creator::changeAct(const std::string& nact)
{
	m_act = nact;
	update();
}

void Creator::addSprite()
{
	std::string name = m_nameNSprite->getText();
	if(name.empty())
		return;

	m_nameNSprite->setText("");
	if( exists(name) )
		return;

	sdl::AABB aabb( sdl::makeRect(0, 0, m_img->w, m_img->h) );
	m_sprites[name] = aabb;
	m_act = m_spritesModel->getElementAt(0);
	update();
}

void Creator::deleteSprite()
{
	if( !exists(m_act) )
		return;

	m_sprites.erase(m_act);
	update();
}

bool Creator::exists(std::string sprite)
{
	return m_sprites.find(sprite) != m_sprites.end();
}

void Creator::set()
{
	changeSprite(sdl::makeRect( sdl::atoi(m_xfield->getText()),
				sdl::atoi(m_yfield->getText()),
				sdl::atoi(m_wfield->getText()),
				sdl::atoi(m_hfield->getText()) ));
}

void Creator::setColor(gcn::Widget* wid, const gcn::Color& bs, const gcn::Color& bg, const gcn::Color& fg, const gcn::Color& sl)
{
	wid->setBaseColor(bs);
	wid->setBackgroundColor(bg);
	wid->setForegroundColor(fg);
	wid->setSelectionColor(sl);
}

void Creator::putPixel(int x, int y, gcn::Color* c)
{
	if( x >= m_usedSurf->w
			|| x < 0 
			|| y >= m_usedSurf->h
			|| y < 0 )
		return;

	int bpp = m_usedSurf->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)m_usedSurf->pixels + y * m_usedSurf->pitch + x * bpp;

	Uint32 pixel = 0;
	if(c == NULL)
		pixel = SDL_MapRGB(m_usedSurf->format, 0, 0, 0);
	else
		pixel = SDL_MapRGB(m_usedSurf->format, c->r, c->g, c->b);

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

