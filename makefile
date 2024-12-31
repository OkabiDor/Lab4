# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -g

# Source Files
SRCS = $(wildcard *.c)

# Object Files
OBJS = $(SRCS:.c=.o)

# Executable Name
EXEC = hexeditplus

# Default Rule
all: $(EXEC)

# Linking Step
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compilation Step
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Rule
clean:
	rm -f $(OBJS) $(EXEC)

# Run the Program
run: $(EXEC)
	./$(EXEC)
