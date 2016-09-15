CC=g++
CXXFLAGS=-g3 -W -Wall -ansi -pedantic -std=c++11 -D__GXX_EXPERIMENTAL_CXX0X__ 
LDFLAGS=
LDLIBS=-lpthread -lasound -lsndfile -lsoloud -lSDL -lSDL_image -lSDL_ttf -lconfig++
EXEC=piDrummer
SRC= $(wildcard *.cpp)
HDR= $(wildcard *.h)
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

piDrummer: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(CFLAGS)

piDrummer.o: $(HDR)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm *.o

mrproper: clean
	rm -rf piDrummer
