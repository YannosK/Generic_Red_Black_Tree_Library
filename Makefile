.PHONY: all clean

# Set the executable name
EXECUTABLE := executable

# Compiler flags
CFLAGS := -g 
# CFLAGS := -g -Wall -Wextra

# Set the compiler
CC := gcc

# BUILD_DIR is a variable which has the string build
# the following line creates a directory to put the exe and the objects
BUILD_DIR := build
$(shell mkdir -p $(BUILD_DIR))

SRC := main.c RedBlackTree.c IntegerNodes.c StringNodes.c
OBJ := $(BUILD_DIR)/main.o $(BUILD_DIR)/RedBlackTree.o $(BUILD_DIR)/IntegerNodes.o $(BUILD_DIR)/StringNodes.o
HEADER := RedBlackTree.h IntegerNodes.h StringNodes.h

all: $(EXECUTABLE)
	@echo "Finished!"

# The following creates the object files and then compiles
# $(HEADER) is to update changes in the header files
$(BUILD_DIR)/%.o : %.c $(HEADER)
	$(CC) -c $< -o $@ $(CFLAGS)

# The following creates the executable.
# $(OBJ) is expanding on our list of strings that are our objects
$(EXECUTABLE): $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS)

# this removes the entire build folder
clean:
	rm -rf build/