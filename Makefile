#!/usr/bin/make
include ./configure

HEADERS		:= $(HEADERSDIR)/*

ifeq ($(OS),win32vc++)
	include ./make-win32
else
	ifeq ($(OS),win32)
		include ./make-win32
	else
		ifeq ($(OS),win64)
			include ./make-win32
		else
			include ./make-linux
		endif
	endif
endif

.PHONY: all

all: Debug Release
	@echo
	@echo "Makefile finished"
	@echo "OS: $(OS)"
	@echo "Compiler: $(CXX)"
	@echo "Fantasy2C Debug and Release compiling has been successfully."

installDebug: Debug
	cp -R -f $(OUTLIBDIR)/$(OUTLIB).$(OUTLIBSUF) /usr/lib/
	cp -R -f $(HEADERS) /usr/include/
	mkdir -p /usr/src/Fantasy2C
	cp -R -f $(SRCDIR)/* /usr/src/Fantasy2C
	@echo
	@echo "Makefile finished"
	@echo "OS: $(OS)"
	@echo "Compiler: $(CXX)"
	@echo "copy $(DEBUGDIR)/$(OUTLIB).$(OUTLIBSUF) into  /usr/lib"
	@echo "copy $(HEADERSDIR) into /usr/include/"
	@echo "Fantasy2C(Debug Version) install has been successfully."

install: Release
	cp -R -f $(OUTLIBDIR)/$(OUTLIB).$(OUTLIBSUF) /usr/lib/
	cp -R -f $(HEADERS) /usr/include/
	@echo
	@echo "Makefile finished"
	@echo "OS: $(OS)"
	@echo "Compiler: $(CXX)"
	@echo "copy $(RELEASEDIR)/$(OUTLIB).$(OUTLIBSUF) into  /usr/lib"
	@echo "copy $(HEADERSDIR) into /usr/include/"
	@echo "Fantasy2C install has been successfully."

