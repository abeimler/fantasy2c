include ./configure

OUTDIR		        := lib
OBJDIR		        := obj

DEBUGDIR	        := $(BUILDDIR)/Debug
RELEASEDIR	        := $(BUILDDIR)/Release

override BUILDDIR   	:= $(strip $(BUILDDIR))
SOURCES             	:= $(wildcard $(SRCDIR)/*.$(SRCSUF))
OBJECTSDEBUG	    	:= $(patsubst $(SRCDIR)/%.$(SRCSUF), $(DEBUGDIR)/$(OBJDIR)/%.$(OBJSUF), $(SOURCES))
OBJECTSRELEASE     	:= $(patsubst $(SRCDIR)/%.$(SRCSUF), $(RELEASEDIR)/$(OBJDIR)/%.$(OBJSUF), $(SOURCES))

install: Debug Release
	@echo
	@echo Makefile finished
	@echo OS: $(OS)
	@echo Compiler: $(CXX)
	@echo Install in $(BUILDDIR)
	@echo Fantasy2C Debug and Release has been successfully compiled.

debugdirs:
	mkdir -p $(DEBUGDIR)/$(OBJDIR)
	mkdir -p $(DEBUGDIR)/$(OUTDIR)
                
releasedirs:
	mkdir -p $(RELEASEDIR)/$(OBJDIR)
	mkdir -p $(RELEASEDIR)/$(OUTDIR)

Debug : debugdirs $(OBJECTSDEBUG)
	$(LD) $(DEBUGFLAGS) $(LDFLAGS) $(DEFAULTFLAGS) $(SOFLAGS) -I$(HEADERSDIR) $(OUTFLAG)$(DEBUGDIR)/$(OUTDIR)/$(OUTLIB).$(OUTLIBSUF) $(OBJECTSDEBUG) $(LIBFLAGS)
 
Release : releasedirs $(OBJECTSRELEASE)
	$(LD) $(RELEASEFLAGS) $(LDFLAGS) $(DEFAULTFLAGS) $(SOFLAGS) -I$(HEADERSDIR) $(OUTFLAG)$(RELEASEDIR)/$(OUTDIR)/$(OUTLIB).$(OUTLIBSUF) $(OBJECTSRELEASE) $(LIBFLAGS)

$(OBJECTSDEBUG): $(DEBUGDIR)/$(OBJDIR)/%.$(OBJSUF): $(SRCDIR)/%.$(SRCSUF) $(DEBUGDIR)/$(OBJDIR)/.tag
	$(CXX) $(DEBUGFLAGS) $(CXXFLAGS) $(DEFAULTFLAGS) -I$(HEADERSDIR) -c $< $(OUTFLAG) $@ 


$(OBJECTSRELEASE): $(RELEASEDIR)/$(OBJDIR)/%.$(OBJSUF): $(SRCDIR)/%.$(SRCSUF) $(RELEASEDIR)/$(OBJDIR)/.tag
	$(CXX) $(RELEASEFLAGS) $(CXXFLAGS) $(DEFAULTFLAGS) -I$(HEADERSDIR) -c $< $(OUTFLAG) $@ 

%.tag:
	mkdir -p $(dir $(@))
	touch $@


clean: cleanDebug cleanRelease


cleanDebug:
	rm -rf $(DEBUGDIR)/$(OBJDIR)

cleanRelease:
	rm -rf $(RELEASEDIR)/$(OBJDIR)

