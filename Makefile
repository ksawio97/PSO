BIN_DIR=bin
BUILD_DIR=build
SRC_DIR=src

CFLAGS := -Wall -Wextra -g 
TARGET=$(BIN_DIR)/pso

# all .c files in src
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
# .o files to generate from SRC_FILES
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

build: $(TARGET)

# create executable
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(dir $@)
	cc $(OBJ_FILES) -o $@

# build .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	cc $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BIN_DIR)/* $(BUILD_DIR)/*
