#########################################################################

BIN = bitstream
CYGWIN_DIR=  
SRCDIR = src
SRCS = src/main.cpp src/GLEntity.cpp src/GLPlayer.cpp src/events.cpp src/GLMap.cpp src/gl.cpp src/Texture.cpp src/BSM.cpp src/BSMPiece.cpp src/GLShot.cpp src/GLEnemy.cpp src/en_cube.cpp src/physics.cpp src/effects.cpp src/hud.cpp src/collision.cpp

CXX     = g++
CFLAGS  = -g   -ggdb -Wall  -ansi -DDEBUG
INCLUDE = -I. -Iinclude
LDFLAGS = -Llib  -lGL -lGLU -lm `sdl-config --libs`

#############################################################################################


OBJS		= $(SRCS:.cpp=.o)
HEADERS 	= $(SRCS:.cpp=.h)	



default:$(BIN)

all:$(BIN)

$(BIN):$(OBJS) 
	$(CXX) $(CFLAGS) $(INCLUDE) $^ -o $@  $(LDFLAGS)
	@echo "|    Binary file: "$(BIN)" was successfully created."


%.o : %.cpp 

	$(CXX) $(CFLAGS) $(INCLUDE)  -o $@ -c $<


all:$(ALL)

clean:	

	@ rm -f src/*.o
	@ rm -f *.dat
	@ rm -f $(ALL)
	@ rm -f $(BIN)
	@ rm -f *.exe
	@ rm -f *.stackdump







