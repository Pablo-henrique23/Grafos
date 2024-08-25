# Compiler
CXX := g++

# Directories
SRC_DIR := source
INC_DIR := include

# Files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(SRC_DIR)/%.o,$(filter-out main.cpp,$(SRCS)))
MAIN_OBJ := main.o
DEPS := $(wildcard $(INC_DIR)/*.hpp)

# Compiler flags
CXXFLAGS := -std=c++11 -Wall -Wextra -I$(INC_DIR)

# Output executable
TARGET := graph_project

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(MAIN_OBJ): main.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@del /q $(SRC_DIR)\*.o
	@del /q $(MAIN_OBJ) $(TARGET)
