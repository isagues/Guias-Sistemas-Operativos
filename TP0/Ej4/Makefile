include ../Makefile.inc

SOURCES = $(wildcard *.c)
BINS = $(SOURCES:.c=.out)

all: $(BINS)

%.out: %.c
	$(GCC) $(GCCFLAGS) $^ -o $@

clean: 
	$(REMOVE) $(BINS)

test: clean
	../pvs.sh
	valgrind ./$(BIN) $(VALGRIND_PATH) 2> valgrind.tasks
	cppcheck --quiet --enable=all --force --inconclusive --suppress=missingIncludeSystem  $(SOURCES) 2> cppcheck.tasks


.PHONY: all clean compress test
	