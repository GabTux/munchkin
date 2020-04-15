CXX       = g++
CXXFLAGS  = -Wall -pedantic -O2 -std=c++17
LIBFLAGS  = -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
_DEPS     =        game/Card.h constants.h scene/Stop.h scene/Start.h scene/SceneManager.h scene/Background.h scene/SoloGame/SoloGame.h scene/Menu/MenuItem.h scene/Menu/MenuButton.h scene/SDLResources.h scene/Menu/MenuSelector.h scene/Scene.h scene/Menu/MainMenu.h scene/Menu/Menu.h game/GameObject.h
_OBJ      = main.o game/Card.o             scene/Stop.o scene/Start.o scene/SceneManager.o scene/Background.o scene/SoloGame/SoloGame.o scene/Menu/MenuItem.o scene/Menu/MenuButton.o scene/SDLResources.o scene/Menu/MenuSelector.o scene/Scene.o scene/Menu/MainMenu.o scene/Menu/Menu.o game/GameObject.o
OBJDIR    = obj
SRCDIR    = src

DEPS      = $(patsubst %,$(SRCDIR)/%,$(_DEPS))
OBJ       = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

all: munchkin doc

compile: munchkin

$(OBJDIR):
	mkdir $(OBJDIR)
	mkdir $(OBJDIR)/game
	mkdir $(OBJDIR)/scene
	mkdir $(OBJDIR)/scene/SoloGame
	mkdir $(OBJDIR)/scene/Menu

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS) $(OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

munchkin: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBFLAGS)

doc:
	doxygen

clean:
	rm -rf munchkin doc $(OBJDIR) &>/dev/null

run: munchkin
	./munchkin
