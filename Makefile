#########################################################################

BIN = Unnamed
CYGWIN_DIR=  
SRCS = main.cpp GLEntity.cpp GLPlayer.cpp events.cpp GLMap.cpp gl.cpp

CXX     = g++
CFLAGS  = -g   -Wall  -ansi -DDEBUG
INCLUDE = -I. -Iinclude
LDFLAGS = -Llib -L$(CYGWIN_DIR)/lib -lGL -lGLU `sdl-config --libs`

#############################################################################################
# you should not need to edit anything below this line
#############################################################################################


OBJS		= $(SRCS:.cpp=.o)
HEADERS 	= $(SRCS:.cpp=.h)	



default:
	@echo "+-----------------------------------------------------------------+"
	@echo "|"
	@echo "|            	 Unnamed "
	@echo "|"
	@echo "| Usage: make all      builds the binary"
	@echo "|        make clean    removes the *.o file(s) and executable(s)"
	@echo "|"
	@echo "+-----------------------------------------------------------------+"

all:$(BIN)

$(BIN):$(OBJS)
	@echo "+-----------------------------------------------------------------+"
	@echo "|          Linking these .o files: "$(OBJS)
	@echo "|          and linking libraries to"
	@echo "|          create binary (executable) file: "$(BIN)	
	@echo "+-----------------------------------------------------------------+"
	$(CXX) $(CFLAGS) $(INCLUDE) $^ -o $@   $(LDFLAGS)
	@echo "+-----------------------------------------------------------------+"
	@echo "|    Binary file: "$(BIN)" was successfully created."
	@echo "|    This binary can be executed by running ./"$(BIN)
	@echo "+-----------------------------------------------------------------+"


%.o : %.cpp
	@echo "+-----------------------------------------------------------------+"
	@echo "|          Compiling file: "$?
	@echo "|          to create object file: "$@	
	@echo "+-----------------------------------------------------------------+"
	$(CXX) $(CFLAGS) $(INCLUDE)  -c $<


all:$(ALL)

clean:	
	@echo "+-----------------------------------------------------------------+"
	@echo "|     Removing all  binaries and temp files"
	@echo "+-----------------------------------------------------------------+"
	@ rm -f *.o
	@ rm -f *.dat
	@ rm -f $(ALL)
	@ rm -f $(BIN)
	@ rm -f *.exe






#
# makefile created  by Sean Leonard in '99
# added EE445 specifics in '01


