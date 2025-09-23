# Compiler and tools
CC = gcc
CFLAGS = -Wall -Wextra -I../include -g
AR = ar rcs

# Directories
OBJDIR = ../obj
BINDIR = ../bin
LIBDIR = ../lib

# Files
OBJS = $(OBJDIR)/myfilefunctions.o $(OBJDIR)/mystrfunctions.o
LIB = $(LIBDIR)/libmyutils.a
TARGET = $(BINDIR)/client_static

# Default target
all: $(TARGET)

# Compile .c -> .o
$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build static library
$(LIB): $(OBJS)
	$(AR) $@ $^

# Build client linked with static lib
$(TARGET): $(OBJDIR)/main.o $(LIB)
	$(CC) $(CFLAGS) $< -L$(LIBDIR) -lmyutils -o $@

# Clean up
clean:
	rm -f $(OBJDIR)/*.o $(TARGET) $(LIB)

