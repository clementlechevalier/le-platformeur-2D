all: toto


Animation.o : ../src/Animation.cpp ../include/Animation.h
	g++ -c ../src/Animation.cpp -lsfml-graphics -lsfml-window -lsfml-system

Button.o : ../src/Button.cpp ../include/Button.h
	g++ -c ../src/Button.cpp -lsfml-graphics -lsfml-window -lsfml-system

Collider.o : ../src/Collider.cpp ../include/Collider.h
	g++ -c ../src/Collider.cpp -lsfml-graphics -lsfml-window -lsfml-system

Fading.o : ../src/Fading.cpp ../include/Fading.h
	g++ -c ../src/Fading.cpp -lsfml-graphics -lsfml-window -lsfml-system

Ground.o : ../src/Ground.cpp ../include/Ground.h
	g++ -c ../src/Ground.cpp -lsfml-graphics -lsfml-window -lsfml-system

Hitbox.o : ../src/Hitbox.cpp ../include/Hitbox.h
	g++ -c ../src/Hitbox.cpp -lsfml-graphics -lsfml-window -lsfml-system

Map.o : ../src/Map.cpp ../include/Map.h
	g++ -c ../src/Map.cpp -lsfml-graphics -lsfml-window -lsfml-system

Player.o : ../src/Player.cpp ../include/Player.h
	g++ -c ../src/Player.cpp -lsfml-graphics -lsfml-window -lsfml-system

TextBox.o : ../src/TextBox.cpp ../include/TextBox.h
	g++ -c ../src/TextBox.cpp -lsfml-graphics -lsfml-window -lsfml-system


main.o : ../main.cpp  ../include/TextBox.h ../include/Player.h ../include/Map.h ../include/Hitbox.h ../include/Animation.h ../include/Button.h ../include/Collider.h ../include/Fading.h ../include/Ground.h
	g++ -c ../main.cpp -lsfml-graphics -lsfml-window -lsfml-system

toto: main.o Animation.o Button.o Collider.o Fading.o Ground.o Hitbox.o Map.o Player.o TextBox.o
	g++ main.o Animation.o Button.o Collider.o Fading.o Ground.o Hitbox.o Map.o Player.o TextBox.o -o toto  -lsfml-graphics -lsfml-window -lsfml-system

