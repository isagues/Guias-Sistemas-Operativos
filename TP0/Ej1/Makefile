include ../Makefile.inc

BIN = listdir
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
	./pvs.sh
	valgrind ./$(BIN) $(VALGRIND_PATH) 2> valgrind.tasks > /dev/null
	# Si agrego --suppress=missingIncludeSystem a cppcheck soluciona el error que me marca.
	# No se si es un falso positivo o un verdadero error.
	cppcheck --quiet --enable=all --force --inconclusive  main.c 2> cppcheck.tasks

.PHONY: all clean compress test
	