#!/usr/bin/make
include ./configure

override BUILDDIR   	:= $(strip $(BUILDDIR))
SOURCES             	:= $(wildcard $(SRCDIR)/*.$(SRCSUF))
OBJECTSDEBUG	    	:= $(patsubst $(SRCDIR)/%.$(SRCSUF), $(DEBUGDIR)/$(OBJDIR)/%.$(OBJSUF), $(SOURCES))
OBJECTSRELEASE     	:= $(patsubst $(SRCDIR)/%.$(SRCSUF), $(RELEASEDIR)/$(OBJDIR)/%.$(OBJSUF), $(SOURCES))
HEADERFILES		:= $(wildcard $(HEADERSDIR)/*)

ifeq ($(OS),win32vc++)
	include ./make-win32
else
	ifeq ($(OS),win32)
		include ./make-win32
	else
		include ./make-linux
	endif
endif

.PHONY: clean all

all: Debug Release
	@echo
	@echo Makefile finished
	@echo OS: $(OS)
	@echo Compiler: $(CXX)
	@echo Fantasy2C Debug and Release compiling has been successfully.

install: Release
	cp -R -f $(RELEASEDIR)/$(OUTDIR)/$(OUTLIB).$(OUTLIBSUF) /usr/lib/
	cp -R -f $(HEADERSDIR)/* /usr/include/
	@echo
	@echo Makefile finished
	@echo OS: $(OS)
	@echo Compiler: $(CXX)
	@echo copy $(RELEASEDIR)/$(OUTDIR)/$(OUTLIB).$(OUTLIBSUF) into  /usr/lib
	@echo copy $(HEADERSDIR)/ into /usr/include/
	@echo Fantasy2C install has been successfully.
uninstall: $(HEADERFILES)
	rm -f /usr/lib/$(OUTLIB).$(OUTLIBSUF)
	rm -f /usr/include/$<

