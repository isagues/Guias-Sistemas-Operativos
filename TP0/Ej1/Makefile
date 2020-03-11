include ../Makefile.inc

BIN = listDir
SOURCES = main.c
PACK = $(BIN).tar.gz

all: $(BIN)

$(BIN): $(SOURCES)
	$(GCC) $(GCCFLAGS) $^ -o $@

clean: 
	$(REMOVE) $(BIN) $(PACK)

compress: clean
	$(TAR) $(PACK) *


.PHONY: all clean compress
	