CXX      := $(CROSS_COMPILE)g++
CXXFLAGS := -pedantic-errors -Wall -Wno-psabi -Wextra -D__LINUX_ALSA__
LDFLAGS  := -L$(TARGET_DIR)/usr/lib -lstdc++ -lm -lpthread -lasound -lrtmidi
BUILD    := build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := miditest
SRCDIRS  := src
SRCEXTS  := .cpp .CPP .c++ .cxx .cp
INCLUDE  := -I./include/ -I./include/midictrl -I./include/observer -I $(TARGET_DIR)/usr/include/rtmidi
SRC      :=  \
   $(wildcard src/midictrl/*.cpp) \
   $(wildcard src/observer/*.cpp) \
   $(wildcard src/*.cpp)         \

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
