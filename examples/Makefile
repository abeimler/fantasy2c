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

install: Release
	@echo
	@echo Makefile finished
	@echo OS: $(OS)
	@echo Compiler: $(CXX)
	@echo Fantasy2C Example compile has been successfully.
