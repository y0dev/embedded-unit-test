# Compiler
CC = gcc

ifeq ($(OS),Windows_NT)
    MKDIR_P = if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
else
    MKDIR_P = mkdir -p $(dir $@)
endif

# Directories
SRC_DIR = src
INC_DIR = 
MOCK_DIR = mock
TEST_MAIN_DIR = unit_tests

# Automatically included subdir.mk files
-include unit_tests/external_communication/subdir.mk
-include unit_tests/gpio/subdir.mk
-include unit_tests/interrupt/subdir.mk
-include unit_tests/mailbox/subdir.mk
-include unit_tests/registers/subdir.mk
-include unit_tests/shared_memory/subdir.mk
-include unit_tests/system_monitor/subdir.mk
-include unit_tests/uart/subdir.mk


# Flags
CFLAGS = -Wall -Werror -I./mock -I./unit_tests $(INC_DIR) -g
LDFLAGS =


# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
MOCK_FILES = $(wildcard $(MOCK_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_MAIN_DIR)/*.c)

# Output directories and files
OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) \
            $(MOCK_FILES:$(MOCK_DIR)/%.c=$(OBJ_DIR)/%.o) \
            $(TEST_FILES:$(TEST_MAIN_DIR)/%.c=$(OBJ_DIR)/%.o) \
			$(OBJS)

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

$(OBJ_DIR)/%.o: $(TEST_MAIN_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Pattern rule
obj/%.o: %.c
	@$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


# Ensure object directory exists before compiling
$(OBJ_DIR)/$(@D):
	@$(MKDIR_P) $@

info:
	@echo "==== Build Configuration ===="
	@echo "Compiler      : $(CC)"
	@echo "CFLAGS        : $(CFLAGS)"
	@echo "LDFLAGS       : $(LDFLAGS)"
	@echo "Source Dir    : $(SRC_DIR)"
	@echo "Include Dir   : $(INC_DIR)"
	@echo "Mock Dir      : $(MOCK_DIR)"
	@echo "Test Dir      : $(TEST_DIR)"
	@echo "Object Dir    : $(OBJ_DIR)"
	@echo "Executable    : $(EXEC)"
	@echo "Source Files  :"
	@printf "  %s\n" $(SRC_FILES)
	@echo "Mock Files    :"
	@printf "  %s\n" $(MOCK_FILES)
	@echo "Test Files    :"
	@printf "  %s\n" $(TEST_FILES)
	@echo "C Source Files    :"
	@printf "  %s\n" $(C_SRCS)
	@echo "Object Files  :"
	@printf "  %s\n" $(OBJ_FILES)

# Clean up object files and the executable
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC) $(OBJ_DIR)

# Phony targets
.PHONY: all clean

