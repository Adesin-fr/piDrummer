CC=g++
CXXFLAGS=-g3 -W -Wall -ansi -pedantic -std=c++11 -D__GXX_EXPERIMENTAL_CXX0X__ -DWITH_ALSA -pthread
LDFLAGS=-DWITH_ALSA
LDLIBS=-lpthread -lasound -lsndfile -lSDL -lSDL_image -lSDL_ttf -lconfig++
EXEC=piDrummer
SRC= $(wildcard *.cpp) soloud/stb_vorbis.c $(wildcard soloud/*.cpp)
HDR= $(wildcard *.h)
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

piDrummer: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(CFLAGS)

piDrummer.o: $(HDR)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm *.o soloud/*.o

mrproper: clean
	rm -rf piDrummer
