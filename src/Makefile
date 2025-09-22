# src/Makefile: build objects and link into $(BINDIR)/client
CC := gcc
CFLAGS := -Wall -Wextra -I../include -g
SRCDIR := .
OBJDIR := ../obj
BINDIR ?= ../bin

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
TARGET := $(BINDIR)/client

.PHONY: all clean dirs

all: dirs $(TARGET)

dirs:
	@mkdir -p $(OBJDIR) $(BINDIR)

# linking rule (TARGET depends on OBJECTS)
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

# compile each .c to obj/%.o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(TARGET)
