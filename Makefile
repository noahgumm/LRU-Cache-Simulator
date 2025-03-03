# Noah Gumm
# 03/2/2025
# Makefile to compile and run cache simulator

# Noah Gumm
# 02/10/2025
# Makefile to compile and run cache simulator

# Compiler settings
COMPILER = g++
FLAGS = -std=c++17 -O2 -Iheaders  # Add header directory to include path

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# The target executable
TARGET = $(BIN_DIR)/cache_simulator

# Source and object files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Default target
all: $(TARGET)
	@echo "Build complete. Executable is in $(BIN_DIR)/"

# Build target
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	@echo "Linking executable..."
	$(COMPILER) $(FLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Executable created at $(TARGET)"

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compiling $< -> $@"
	$(COMPILER) $(FLAGS) -c $< -o $@

# Create necessary directories if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Run target
run: all
	@echo "Running $(TARGET)..."
	@$(TARGET)

# Clean build files
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
	@echo "Cleaned build artifacts."