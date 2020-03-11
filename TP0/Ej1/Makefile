include ../Makefile.inc

BIN = listDir
SOURCES = main.c
PACK = $(BIN).tar.gz
TEST = $(wildcard *.tasks)
VALGRIND_PATH = ../../

all: $(BIN)

$(BIN): $(SOURCES)
	$(GCC) $(GCCFLAGS) $^ -o $@

clean: 
	$(REMOVE) $(BIN) $(PACK) $(TEST)

compress: clean
	$(TAR) $(PACK) *

test: clean
	../pvs.sh
	valgrind ./$(BIN) $(VALGRIND_PATH) 2> valgrind.tasks
	cppcheck --quiet --enable=all --force --inconclusive --suppress=missingIncludeSystem  main.c 2> cppcheck.tasks

.PHONY: all clean compress test
	