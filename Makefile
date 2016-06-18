FRAMEWORKS=-F/Users/abed/Library/Frameworks/
OBJS=main.o graphics.o game.o input.o sprite.o animatedsprite.o

main: $(OBJS)
	clang++ -o main $(OBJS) -Wall $(FRAMEWORKS) -framework SDL2 -framework SDL2_image

main.o: main.cpp game.h
	clang++ -c main.cpp $(FRAMEWORKS)
graphics.o: graphics.cpp graphics.h globals.h
	clang++ -c graphics.cpp $(FRAMEWORKS)
game.o: game.cpp game.h graphics.h input.h
	clang++ -c game.cpp $(FRAMEWORKS)
input.o: input.cpp input.h
	clang++ -c input.cpp $(FRAMEWORKS)
sprite.o: sprite.cpp sprite.h graphics.h globals.h
	clang++ -c sprite.cpp $(FRAMEWORKS)
animatedsprite.o: animatedsprite.cpp animatedsprite.h sprite.h globals.h
	clang++ -c animatedsprite.cpp $(FRAMEWORKS)

clean:
	rm -f main $(OBJS)
