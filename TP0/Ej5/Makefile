include ../Makefile.inc

SOURCES = $(wildcard *.c)
BINS = $(SOURCES:.c=.out)

all: $(BINS)

%.out: %.c
	$(GCC) $(GCCFLAGS) $^ -o $@

clean: 
	$(REMOVE) $(BINS) *.txt

.PHONY: all clean compress
	