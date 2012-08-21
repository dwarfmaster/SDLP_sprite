include ../param.mk

DEST=../$(LIB)

OBJS=asprite.o spriteedit.o spritefile.o anim.o
CXXFLAGS=-Wall -Wextra `sdl-config --cflags` `pkg-config --cflags SDLP_position SDLP_tools SDL_image` -fPIC -fsigned-bitfields -std=gnu++0x -g
LDFLAGS=-shared

all : $(OBJS)
	g++ $(CXXFLAGS)    -o $(DEST)	$^ $(LDFLAGS)
	chmod -x $(DEST)

%.o : %.cpp %.hpp
	g++ $(CXXFLAGS) -c -o $@	$<

clean :
	@touch $(OBJS) $(DEST)
	@rm -v $(OBJS) $(DEST)

rec : clean all

