OBJS=main.o creator.o mybutton.o spriteModel.o creatorArea.o slistener.o
PROG=spriteCreator

RCDIR=/usr/share/SDLP_sprite/creator/
DEST=/home/luc/Prog
RCS=font.png

CXXFLAGS=-Wall -Wextra `pkg-config --cflags guichan-0.8 guichan_sdl-0.8` `sdl-config --cflags` -I/home/luc/includes -DRCDIR=\"$(RCDIR)\"
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

install : all
	@mkdir -p $(RCDIR)
	@cp -v $(RCS) $(RCDIR)
	@cp -v $(PROG) $(DEST)

uninstall :
	@rm -rvf $(RCDIR)
	@rm -v $(DEST)/$(PROG)

reinstall : uninstall rec install


