# ==== Root Makefile ====
.PHONY: all clean

# Paths
BINDIR := bin
LIBDIR := lib
SRCDIR := src

# Targets
all: $(BINDIR)/client_static $(BINDIR)/client_dynamic

$(BINDIR)/client_static:
	$(MAKE) -C $(SRCDIR) static BINDIR=../$(BINDIR) LIBDIR=../$(LIBDIR)

$(BINDIR)/client_dynamic:
	$(MAKE) -C $(SRCDIR) dynamic BINDIR=../$(BINDIR) LIBDIR=../$(LIBDIR)

clean:
	$(MAKE) -C $(SRCDIR) clean
	rm -f $(BINDIR)/* $(LIBDIR)/*
