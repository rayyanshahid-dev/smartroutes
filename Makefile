SRCDIR = src/
SRCS   = src/main.c
CC 	   = gcc
TARGET = smartroutes 

CFLAGS = -Wall -Wextra -O3 
LDFLAGS = -lX11

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
