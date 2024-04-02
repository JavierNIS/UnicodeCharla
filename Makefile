#@Brief: Basic makefile
#@Author: Javier Niño Sánchez
#@Date: 18/03/2024

#Options and directories
CXXFLAGS = -std=c17 -pedantic -Wall -g -Ofast
PROJECT_DIR = /home/javier/Documents/Projects/C++/UnicodeCharla/.
SRC_DIR = ./source/
HEADER_DIR = ./include/
OBJ_DIR = ./objects/

#Globals
NAME = UTF-Conversion
SOURCES := $(wildcard $(SRC_DIR)*.cpp)
HEADERS := $(wildcard $(HEADER_DIR)*.h)
OBJECTS := $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SOURCES))

#Globals for .c files
SOURCESC := $(wildcard $(SRC_DIR)*.c)
HEADERS := $(wildcard $(HEADER_DIR)*.h)
OBJECTSC := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SOURCESC))

all: obj $(NAME)
#Make the directory for the objects
obj:
	@mkdir -p $(OBJ_DIR)

#Link it all together
$(NAME): $(OBJECTS) $(OBJECTSC) $(HEADERS)
	gcc $(CXXFLAGS) $(OBJECTS) $(OBJECTSC) -o $(NAME)

#Compile source code into objects, first C++
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(HEADERS)
	gcc -c $(CXXFLAGS) -I$(HEADER_DIR) -o $@ $<
#Now every C
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	gcc -c $(CXXFLAGS) -I$(HEADER_DIR) -o $@ $<
#Clean everything
clean:
	@rm -rf $(OBJ_DIR) $(NAME)
.PHONY: all clean
