CXX       = g++
LD        = g++
CXXFLAGS  = -Wall -pedantic -O2 -std=c++17
LIBFLAGS  = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
_OBJ      = game/GameObject.o game/cards/Card.o game/Player.o scene/Stop.o scene/Start.o scene/Menu/MenuButtonWithSelector.o scene/Menu/MenuButton.o scene/Menu/MenuSelector.o scene/Menu/Menu.o scene/Menu/MainMenu.o scene/Menu/GameMenu.o scene/SDLResources.o scene/SoloGame/SoloGame.o scene/SceneManager.o scene/About.o scene/Scene.o scene/Background.o main.o
OBJDIR    = obj
SRCDIR    = src

OBJ       = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

all: munchkin doc

compile: munchkin

munchkin: $(OBJ)
	$(LD) -o $@ $^ $(LIBFLAGS)

$(OBJDIR):
	mkdir $(OBJDIR)
	mkdir -p $(OBJDIR)/game/cards
	mkdir -p $(OBJDIR)/scene/SoloGame
	mkdir $(OBJDIR)/scene/Menu

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

doc:
	doxygen

clean:
	rm -rf munchkin doc $(OBJDIR) &>/dev/null

run: munchkin
	./munchkin