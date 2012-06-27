OBJS=main.o editor.o mybutton.o groupModel.o saabbModel.o slistener.o editorArea.o
PROG=spriteCreator

CXXFLAGS=-Wall -Wextra `pkg-config --cflags guichan-0.8 guichan_sdl-0.8` `sdl-config --cflags` -I/home/luc/includes -g
LDFLAGS=`pkg-config --libs SDLP_sprite SDLP_event guichan-0.8 guichan_sdl-0.8` `sdl-config --libs`

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

