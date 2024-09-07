CC = clang++

CFLAGS = -I include -Wall -Wextra -Wno-missing-braces -Wconversion -std=c++17 -pedantic \
		 -D __UNI_DEBUG -ggdb -fsanitize=address
LIBS = -L lib -lSDL2main -lSDL2

build/test.exe: obj/uni_test.o
	clang++ -o $@ $< $(CFLAGS) $(LIBS)
