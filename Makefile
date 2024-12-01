# Compiler and Flags
CC = gcc
#CFLAGS = -Wall -Wextra -ggdb -Iinclude $(shell pkg-config --cflags libmongoc-1.0)
CFLAGS = -Wall -Wextra -ggdb -Iinclude

# you need to add libmongoc path to the ld linker
#LDFLAGS = $(shell pkg-config --libs libmongoc-1.0)

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Source and Object Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Target
TARGET = $(BUILD_DIR)/my-http-server

all: $(TARGET)
	@echo "Build complete"

run: all
	@echo "Running $(TARGET) ..."
	$(TARGET)
	
debug: all
	@echo "Debugging $(TARGET) with gdb..."
	gdb --args $(TARGET)

# Build Rules
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean
