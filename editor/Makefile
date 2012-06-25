OBJS=main.o editor.o mybutton.o groupModel.o saabbModel.o slistener.o
PROG=spriteCreator

CXXFLAGS=-Wall -Wextra `pkg-config --cflags SDLP_sprite guichan-0.8 guichan_sdl-0.8` `sdl-config --cflags`
LDFLAGS=`pkg-config --libs SDLP_sprite guichan-0.8 guichan_sdl-0.8` `sdl-config --libs`

all : $(OBJS)
	g++ $(CXXFLAGS)    -o $(PROG)	$^ $(LDFLAGS)

main.o : main.cpp
	g++ $(CXXFLAGS) -c -o $@		$<

%.o : %.cpp %.hpp
	g++ $(CXXFLAGS) -c -o $@		$<

clean :
	@touch $(OBJS) $(PROG)
	@rm -v $(OBJS) $(PROG)

rec : clean all

