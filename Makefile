CXX       = g++
LD        = g++
DEBFLAGS  = -fsanitize=address
CXXFLAGS  = -Wall -pedantic -std=c++17
LIBFLAGS  = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
_OBJ      = functions.o scene/About.o scene/Start.o scene/SoloGame/SoloGame1v1.o scene/SoloGame/SoloGame.o scene/SoloGame/SoloGameLoadPC.o scene/SoloGame/SoloGameLoad1v1.o scene/SoloGame/SoloGame1vPC.o scene/Stop.o scene/Menu/MenuButtonWithSelector.o scene/Menu/GameMenu.o scene/Menu/MenuSelector.o scene/Menu/MenuButton.o scene/Menu/SaveMenu.o scene/Menu/MainMenu.o scene/Menu/Menu.o scene/Scene.o scene/SceneManager.o scene/Background.o game/GameButton.o game/GraphicObject.o game/Text.o game/Inventory.o game/HandCards.o game/cards/CurseCard.o game/cards/CardDeck.o game/cards/BoostCard.o game/cards/MonsterBoostCard.o game/cards/LevelUpCard.o game/cards/ItemCard.o game/cards/MonsterCard.o game/cards/Card.o game/GameObject.o game/PileCard.o game/Human.o game/Bot.o game/Player.o main.o
OBJDIR    = obj
SRCDIR    = src

OBJ       = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

all: munchkin doc

compile: munchkin

#TODO
#debug:

munchkin: $(OBJ)
	$(LD) -o $@ $^ $(LIBFLAGS) $(CXXFLAGS)

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
