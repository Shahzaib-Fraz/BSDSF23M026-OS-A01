# Top-level Makefile
.PHONY: all clean distclean build srcclean

# Directories
SRCDIR := src
BINDIR := bin

# default target delegates to src/Makefile
all: build

build:
	$(MAKE) -C $(SRCDIR) all BINDIR=$(abspath $(BINDIR))

clean:
	$(MAKE) -C $(SRCDIR) clean

distclean: clean
	rm -f $(BINDIR)/client
