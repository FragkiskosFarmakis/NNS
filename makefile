# Compiler settings
CC = g++
CFLAGS = -std=c++11 -Wall -g
LDFLAGS = -lstdc++ -lpthread

# Include directories (add src/ to this list to find functions.h)
INCLUDE_DIRS = -I./src -I./tests  # Add src to search for functions.h

# Directories for source and tests
SRC_DIR = src
TEST_DIR = tests

# Main Program Compilation
MAIN_SRC = $(SRC_DIR)/vamana.cpp
FUNCTIONS_SRC = $(SRC_DIR)/functions.cpp
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
FUNCTIONS_OBJ = $(FUNCTIONS_SRC:.cpp=.o)
MAIN_EXEC = vamana_program

# Test Compilation
TEST_SRC = $(TEST_DIR)/test_vamana.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_EXEC = test_vamana

# Rules for building executables

# Build the main program
$(MAIN_EXEC): $(MAIN_OBJ) $(FUNCTIONS_OBJ)
	$(CC) $(MAIN_OBJ) $(FUNCTIONS_OBJ) -o $(MAIN_EXEC) $(LDFLAGS)

# Build the test program
$(TEST_EXEC): $(TEST_OBJ) $(FUNCTIONS_OBJ)
	$(CC) $(TEST_OBJ) $(FUNCTIONS_OBJ) -o $(TEST_EXEC) $(LDFLAGS)

# General rule to build object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(MAIN_EXEC) $(TEST_EXEC)

.PHONY: all clean


