OBJECTS = src/main.cpp src/Ground.cpp src/Map.cpp src/Animation.cpp src/Player.cpp src/Collider.cpp src/Fading.cpp src/MainMenu.cpp
RECOMPILABLE = compilation/main.o compilation/main.o compilation/Map.o compilation/Ground.o compilation/Animation.o compilation/Player.o compilation/Collider.o compilation/Fading.o compilation/MainMenu.o
RECOMPILABLE_FOR_ENTITY = compilation/main_entityEditor.o compilation/TextBox.o compilation/Button.o

CC=g++
CFLAGS= -Wall -g -o
GAME=The_game
ENTITY = Entity_Editor
ADDSFML = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

all: $(GAME) $(ENTITY)

$(GAME) : $(RECOMPILABLE) $(ADDSFML)
	$(CC) $(CFLAGS) $@ $^

$(ENTITY) : $(RECOMPILABLE_FOR_ENTITY) $(ADDSFML)
	$(CC) $(CFLAGS) $@ $^


compilation/%.o : src/%.cpp
	$(CC) -c $(CFLAGS) $@ $^

clean :
	rm $(RECOMPILABLE) $(RECOMPILABLE_FOR_ENTITY)
