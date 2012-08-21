include param.mk

DEST=/home/luc/libs
VERSION=1.0

INCLUDES=/home/luc/includes
INCFILE=$(NAME).hpp
INCSDIR=$(INCLUDES)/$(NAME)

PCFILE=$(NAME).pc
PCDIR=/usr/lib/pkgconfig

all :
	cd src && make

clean :
	cd src && make clean

rec : clean all

install : $(LIB)
	@cp -v $(LIB) $(DEST)
	@mkdir $(INCSDIR)
	@cp -v $(INCFILE) $(INCLUDES)
	@cp -v `ls src/*.hpp` $(INCSDIR)
	@cp -v $(PCFILE) $(PCDIR)

uninstall : $(LIBS)
	@touch $(DEST)/$(LIB) $(INCLUDES)/$(INCFILE) $(PCDIR)/$(PCFILE) $(INCSDIR)
	@rm -v $(DEST)/$(LIB) $(INCLUDES)/$(INCFILE)
	@rm -rv $(INCSDIR)
	@rm -v $(PCDIR)/$(PCFILE)

mr-proper : uninstall clean

reinstall : uninstall rec install

tools :
	cd tools && make

clean-all : clean
	cd tools && make clean

install-all : install
	@echo -e "\t***** TOOLS *****"
	cd tools && make install

uninstall-all : uninstall
	@echo -e "\t***** TOOLS *****"
	cd tools && make uninstall

reinstall-all : reinstall
	@echo -e "\t***** TOOLS *****"
	cd tools && make reinstall

doc :
	cd doc && doxygen Doxyfile
	firefox doc/html/index.html > /dev/null 2>&1 &

clear-doc :
	rm -rf doc/html
	rm -rf doc/man
	rm -rf doc/latex

.PHONY: doc clear-doc reinstall-all uninstall-all install-all clean-all reinstall mr-proper uninstall install rec clean all tools

