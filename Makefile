#Created 24/11/2024

#Directories
SRC_D = ./source/
TEST_D = ./tests/
HEADER_D = ./include/
OBJ_D = ./objects/

#Compiler options
COMP = gcc
CXXFLAGS = -g -std=c11 -Wall -pedantic -I$(HEADER_D)

#Tests
T1 = InputCharacter
T2 = UTF32conversionsTo
T3 = UTF8ToUTF16

#Source files for the tests
SRC := $(wildcard $(SRC_D)*.c)
TESTS := $(wildcard $(TEST_D)*.c)
#Header files for the tests
HEADERS := $(wildcard $(HEADER_D)*.h)
#.o for the tests
SRC_OBJ := $(patsubst $(SRC_D)%.c, $(OBJ_D)%.o, $(SRC))
TEST_OBJ := $(patsubst $(TEST_D)%.c, $(OBJ_D)%.o, $(TESTS))

all: $(T1) $(T2) $(T3)

$(T1): $(OBJ_D)$(T1).o $(SRC_OBJ)
	$(COMP) $(CXXFLAGS) $^ -o $(T1)

$(T2): $(OBJ_D)$(T2).o $(SRC_OBJ)
	$(COMP) $(CXXFLAGS) $^ -o $(T2)

$(T3): $(OBJ_D)$(T3).o $(SRC_OBJ)
	$(COMP) $(CXXFLAGS) $^ -o $(T3)

$(OBJ_D)%.o: $(SRC_D)%.c $(HEADERS)
	$(COMP) -c $(CXXFLAGS) -I$(HEADER_D) -o $@ $<

$(OBJ_D)%.o: $(TEST_D)%.c $(HEADERS)
	$(COMP) -c $(CXXFLAGS) -I$(HEADER_D) -o $@ $<

clean:
	rm $(OBJ_D)* $(T1) $(T2) $(T3)
.PHONY: all clean
