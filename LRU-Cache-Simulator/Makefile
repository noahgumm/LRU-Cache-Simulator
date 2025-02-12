# Noah Gumm
# 02/10/2025
# Makefile to compile and run cache simulator

# Use g++ COMPILER, set language version to c++17 and optimize code
COMPILER = g++
FLAGS = -std=c++17 -O2

# The target to create
TARGET = cache_simulator

SOURCE = main.cpp Cache.cpp CacheStatistics.cpp
OBJECTS = $(SOURCE:.cpp=.o)

# Default
all: $(TARGET)

# Build
$(TARGET) : ${OBJECTS}
	$(COMPILER) $(FLAGS) -o $(TARGET) $(OBJECTS) 

# Compile (w/out creating executable, with TARGET as the name)
%.o:%.cpp
	$(COMPILER) $(FLAGS) -c $< -o $@ 

# Clean
clean: 
	rm -f $(TARGET) $(OBJECTS)