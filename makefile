CC=g++
CXXFLAGS=-W -Wall -ansi -pedantic -std=c++11 -D__GXX_EXPERIMENTAL_CXX0X__ 
LDFLAGS=
LDLIBS=-lpthread -lasound -lsndfile -lsoloud -lSDL -lSDL_image -lSDL_ttf -lconfig++
EXEC=urDrummer
SRC= $(wildcard *.cpp)
HDR= $(wildcard *.h)
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

urDrummer: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(CFLAGS)

urDrummer.o: $(HDR)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm *.o

mrproper:
	rm -rf urDrummer