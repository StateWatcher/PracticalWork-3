CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = main

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
TARGET_PATH = $(BIN_DIR)/$(TARGET)

all: $(TARGET_PATH)

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

$(TARGET_PATH): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET_PATH)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run: $(TARGET_PATH)
	./$(TARGET_PATH)

rebuild: clean all

.PHONY: all clean run rebuild