include ../Makefile.inc

BIN = listdir
PACK = $(BIN).tar.gz
SOURCES = main.c

all: $(BIN)

$(BIN): $(SOURCES)
	$(GCC) $(GCCFLAGS) $^ -o $@

clean: 
	$(REMOVE) $(BIN) $(PACK)

compress: clean
	$(TAR) $(PACK) *

.PHONY: all clean compress
	