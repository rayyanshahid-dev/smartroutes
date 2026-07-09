SRCDIR = src/
SRCS   = src/*.c
CC 	   = gcc
TARGET = smartroutes 

CFLAGS = -Wall -Wextra -std=c99 -O3 
DBGFLAG = -g
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
	rm -f $(TARGET) *.o *.data *.annotation

debug:
	$(TARGET): $(SRCS)
		$(CC) $(DBGFLAG) -o $(TARGET) $(SRCS) $(LDFLAGS)	

