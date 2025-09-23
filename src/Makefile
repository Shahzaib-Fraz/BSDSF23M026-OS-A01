# ==== src/Makefile ====
CC := gcc
CFLAGS := -Wall -Wextra -I../include -g -fPIC

# Paths (inherited from root Makefile)
BINDIR ?= ../bin
LIBDIR ?= ../lib
OBJDIR := ../obj

# Files
OBJS := $(OBJDIR)/main.o $(OBJDIR)/myfilefunctions.o $(OBJDIR)/mystrfunctions.o
LIBOBJS := $(OBJDIR)/myfilefunctions.o $(OBJDIR)/mystrfunctions.o

# Targets
all: static dynamic

# ---- Static build ----
static: $(BINDIR)/client_static

$(BINDIR)/client_static: $(OBJS)
	$(CC) -o $@ $(OBJS)

# ---- Dynamic build ----
dynamic: $(LIBDIR)/libmyutils.so $(BINDIR)/client_dynamic

$(LIBDIR)/libmyutils.so: $(LIBOBJS)
	mkdir -p $(LIBDIR)
	$(CC) -shared -o $@ $(LIBOBJS)

$(BINDIR)/client_dynamic: $(OBJDIR)/main.o $(LIBDIR)/libmyutils.so
	mkdir -p $(BINDIR)
	$(CC) -o $@ $(OBJDIR)/main.o -L$(LIBDIR) -lmyutils

# ---- Object files ----
$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ---- Clean ----
clean:
	rm -f $(OBJDIR)/*.o
