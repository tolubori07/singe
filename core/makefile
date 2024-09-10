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
chunk.o: chunk.c chunk.h common.h
	$(CC) $(CFLAGS) -c chunk.c

debug.o: debug.c debug.h common.h
	$(CC) $(CFLAGS) -c debug.c

memory.o: memory.c memory.h common.h
	$(CC) $(CFLAGS) -c memory.c

singe.o: singe.c chunk.h debug.h memory.h
	$(CC) $(CFLAGS) -c singe.c

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean

