# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -I./mock -I./unit_tests -g
LDFLAGS =

# Directories
SRC_DIR = src
INCLUDE_DIR = include
MOCK_DIR = mock
TEST_DIR = unit_tests

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
MOCK_FILES = $(wildcard $(MOCK_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)

# Output directories and files
OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) \
            $(MOCK_FILES:$(MOCK_DIR)/%.c=$(OBJ_DIR)/%.o) \
            $(TEST_FILES:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

EXEC = test_app

# Targets

# Default target to compile and run tests
all: $(EXEC)
	./$(EXEC)

# Compile the main executable and link the object files
$(EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC) $(LDFLAGS)

# Compile the object files from the source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(MOCK_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure object directory exists before compiling
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up object files and the executable
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC) $(OBJ_DIR)

# Phony targets
.PHONY: all clean
