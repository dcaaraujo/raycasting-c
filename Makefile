CC = clang
CFLAGS = -std=c99 -Wall -Wpedantic -Wextra
RAYLIB_CFLAGS = $(shell pkg-config --cflags raylib)
RAYLIB_LIBS   = $(shell pkg-config --libs raylib)
SRC_DIR = src
BUILD_DIR = build
OBJS = $(BUILD_DIR)/map.o $(BUILD_DIR)/player.o $(BUILD_DIR)/ray.o $(BUILD_DIR)/render.o $(BUILD_DIR)/main.o

all: build

build: raycast

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(RAYLIB_CFLAGS) -c $< -o $@

raycast: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(RAYLIB_LIBS) -o raycast

clean:
	rm -rf $(BUILD_DIR) raycast

fmt:
	clang-format -i --style Microsoft src/*
