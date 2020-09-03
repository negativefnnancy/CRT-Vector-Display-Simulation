CC         := cc
CFLAGS     := -Wall -Wpedantic -ansi -Og -g
LDFLAGS    := $(shell pkg-config --cflags --libs sdl2) -lm
BIN        := crt
BUILD_DIR  := build
SOURCE_DIR := src

SOURCE     := $(SOURCE_DIR)/*.c
TARGET     := $(BUILD_DIR)/$(BIN)

$(TARGET): $(BUILD_DIR) $(SOURCE_DIR)/*
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

.PHONY: clean
.PHONY: debug

clean:
	rm -rf $(BUILD_DIR)

debug: $(TARGET)
	gdb -ex run --arg ./$(TARGET)
