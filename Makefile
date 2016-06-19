FRAMEWORKS=-F/Users/abed/Library/Frameworks/
MOREFRAMEWORKS=-framework SDL2 -framework SDL2_image
CC=clang++
OBJS=main.o graphics.o game.o input.o sprite.o animatedsprite.o player.o level.o tile.o tinyxml2.o
EXE=main
FLAGS=-Wall

$(EXE): $(OBJS)
	clang++ -o $(EXE) $(OBJS) $(FLAGS) $(FRAMEWORKS) $(MOREFRAMEWORKS)

main.o: main.cpp game.h
	$(CC) -c main.cpp $(FRAMEWORKS)
graphics.o: graphics.cpp graphics.h globals.h
	$(CC) -c graphics.cpp $(FRAMEWORKS)
game.o: game.cpp game.h graphics.h input.h level.h
	$(CC) -c game.cpp $(FRAMEWORKS)
input.o: input.cpp input.h
	$(CC) -c input.cpp $(FRAMEWORKS)
sprite.o: sprite.cpp sprite.h graphics.h globals.h
	$(CC) -c sprite.cpp $(FRAMEWORKS)
animatedsprite.o: animatedsprite.cpp animatedsprite.h sprite.h globals.h graphics.h sprite.h
	$(CC) -c animatedsprite.cpp $(FRAMEWORKS)
player.o: player.cpp player.h graphics.h
	$(CC) -c player.cpp $(FRAMEWORKS)
level.o: level.cpp level.h globals.h
	$(CC) -c level.cpp $(FRAMEWORKS)
tile.o: tile.cpp tile.h globals.h graphics.h
	$(CC) -c tile.cpp $(FRAMEWORKS)
tinyxml2.o: tinyxml2.cpp tinyxml2.h
	$(CC) -c tinyxml2.cpp

clean:
	rm -f $(EXE) $(OBJS)
