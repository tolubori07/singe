# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Define the target executable
TARGET = singe

# Define the object files
OBJS = chunk.o debug.o memory.o singe.o

# Default rule to build the target
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile individual .c files into .o object files
chunk.o: ./core/chunk.c ./core/chunk.h ./core/common.h
	$(CC) $(CFLAGS) -c ./core/chunk.c

debug.o: ./core/debug.c ./core/debug.h ./core/common.h
	$(CC) $(CFLAGS) -c ./core/debug.c

memory.o: ./core/memory.c ./core/memory.h ./core/common.h
	$(CC) $(CFLAGS) -c ./core/memory.c

singe.o: ./core/singe.c ./core/chunk.h ./core/debug.h ./core/memory.h
	$(CC) $(CFLAGS) -c ./core/singe.c

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean

