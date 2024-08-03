BDIR = build
IDIR = include
LDIR = lib
ODIR = obj
SDIR = src

vpath %.cpp $(SDIR)

CC = clang++
TARGET = $(BDIR)/sdl.exe

CFLAGS = -I $(IDIR) -Wall -Wextra -Wno-missing-braces -Wconversion \
		 -fsanitize=address -pedantic -ggdb -std=c++17 -D UNI_DEBUG
LIBS = -L $(LDIR) -lSDL2main -lSDL2 -lSDL2_ttf

__OBJS = test game window util 
OBJS = $(patsubst %,$(ODIR)/uni_%.o,$(__OBJS))

all: $(TARGET)
	echo Build Complete!

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
