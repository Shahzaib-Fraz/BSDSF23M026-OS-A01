# Compiler and tools
CC      := gcc
AR      := ar
RANLIB  := ranlib

CFLAGS  := -Wall -Wextra -Iinclude -fPIC
LDFLAGS := 

# Directories
SRCDIR    := src
OBJDIR    := build/obj
BINDIR    := bin
LIBDIR    := lib
MANDIR    := man/man3

# Files
LIB_OBJS       := $(OBJDIR)/myfilefunctions.o $(OBJDIR)/mystrfunctions.o
CLIENT_OBJS    := $(OBJDIR)/main.o
STATIC_LIB     := $(LIBDIR)/libmyutils.a
SHARED_LIB     := $(LIBDIR)/libmyutils.so
STATIC_CLIENT  := $(BINDIR)/client_static
DYNAMIC_CLIENT := $(BINDIR)/client_dynamic

# Default target
.PHONY: all
all: dirs $(STATIC_LIB) $(SHARED_LIB) $(STATIC_CLIENT) $(DYNAMIC_CLIENT)

# Ensure directories exist
dirs:
	mkdir -p $(OBJDIR) $(BINDIR) $(LIBDIR)

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Static library
$(STATIC_LIB): $(LIB_OBJS)
	$(AR) rcs $@ $^
	$(RANLIB) $@

# Shared library
$(SHARED_LIB): $(LIB_OBJS)
	$(CC) -shared -o $@ $^

# Static client
$(STATIC_CLIENT): $(CLIENT_OBJS) $(STATIC_LIB)
	$(CC) -o $@ $(CLIENT_OBJS) $(STATIC_LIB) $(LDFLAGS)

# Dynamic client
$(DYNAMIC_CLIENT): $(CLIENT_OBJS) $(SHARED_LIB)
	$(CC) -o $@ $(CLIENT_OBJS) -L$(LIBDIR) -lmyutils -Wl,-rpath,'$$ORIGIN/../lib'

# Print variables for debugging
.PHONY: print-vars
print-vars:
	@echo "LIB_OBJS = $(LIB_OBJS)"
	@echo "CLIENT_OBJS = $(CLIENT_OBJS)"
	@echo "STATIC_LIB = $(STATIC_LIB)"
	@echo "SHARED_LIB = $(SHARED_LIB)"
	@echo "STATIC_CLIENT = $(STATIC_CLIENT)"
	@echo "DYNAMIC_CLIENT = $(DYNAMIC_CLIENT)"

# Install (into /usr/local by default)
PREFIX   ?= /usr/local
BINDIR_I := $(PREFIX)/bin
MANDIR_I := $(PREFIX)/share/man/man3

.PHONY: install uninstall
install: all
	install -d $(DESTDIR)$(BINDIR_I) $(DESTDIR)$(MANDIR_I)
	install -m 0755 $(STATIC_CLIENT) $(DESTDIR)$(BINDIR_I)/client
	install -m 0755 $(DYNAMIC_CLIENT) $(DESTDIR)$(BINDIR_I)/client_dynamic
	@if [ -d "$(MANDIR)" ]; then \
	  for m in $(MANDIR)/*; do \
	    [ -f $$m ] || continue; \
	    base=$$(basename $$m); \
	    gzip -c $$m > $(DESTDIR)$(MANDIR_I)/$${base}.gz; \
	  done; \
	fi
	@echo "Installed."

uninstall:
	-rm -f $(DESTDIR)$(BINDIR_I)/client $(DESTDIR)$(BINDIR_I)/client_dynamic
	-rm -f $(DESTDIR)$(MANDIR_I)/*.gz || true
	@echo "Uninstalled."

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BINDIR) $(LIBDIR)
	@echo "Cleaned."
