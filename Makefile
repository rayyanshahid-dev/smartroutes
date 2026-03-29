SRCDIR = src/
SRCS   = src/*.c
CC 	   = gcc
TARGET = smartroutes 

CFLAGS = -Wall -Wextra -std=c99 -O3 
LDFLAGS = -lX11 -lm

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

run:
	./$(TARGET)

# Clean target to remove the compiled binary
clean:
	rm -f $(TARGET)
