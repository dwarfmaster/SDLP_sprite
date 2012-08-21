OBJS=main.o editor.o mybutton.o groupModel.o saabbModel.o slistener.o editorArea.o
PROG=spriteEditor

RCDIR=/usr/share/SDLP_sprite/editor/
DEST=/home/luc/Prog
RCS=font.png icon.png

CXXFLAGS=-Wall -Wextra `pkg-config --cflags guichan-0.8 guichan_sdl-0.8 SDLP_sprite` `sdl-config --cflags` -DRCDIR=\"$(RCDIR)\" -g
LDFLAGS=`pkg-config --libs SDLP_sprite SDLP_event guichan-0.8 guichan_sdl-0.8 SDLP_sprite` `sdl-config --libs`

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


