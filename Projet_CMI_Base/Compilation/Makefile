all: toto


toto: main.o Animation.o Button.o Collider.o Fading.o Ground.o Hitbox.o Map.o Player.o TextBox.o
	g++ main.o Animation.o Button.o Collider.o Fading.o Ground.o Hitbox.o Map.o Player.o TextBox.o

Animation.o : ../src/Animation.cpp ../include/Animation.h
	g++ -c ../src/Animation.cpp

Button.o : ../src/Button.cpp ../include/Button.h
	g++ -c ../src/Button.cpp

Collider.o : ../src/Collider.cpp ../include/Collider.h
	g++ -c ../src/Collider.cpp

Fading.o : ../src/Fading.cpp ../include/Fading.h
	g++ -c ../src/Fading.cpp

Ground.o : ../src/Ground.cpp ../include/Ground.h
	g++ -c ../src/Ground.cpp

Hitbox.o : ../src/Hitbox.cpp ../include/Hitbox.h
	g++ -c ../src/Hitbox.cpp

Map.o : ../src/Map.cpp ../include/Map.h
	g++ -c ../src/Map.cpp

Player.o : ../src/Player.cpp ../include/Player.h
	g++ -c ../src/Player.cpp

TextBox.o : ../src/TextBox.cpp ../include/TextBox.h
	g++ -c ../src/TextBox.cpp


main.o : ../main.cpp  ../include/TextBox.h ../include/Player.h ../include/Map.h ../include/Hitbox.h ../include/Animation.h ../include/Button.h ../include/Collider.h ../include/Fading.h ../include/Ground.h
	g++ -c ../main.cpp

