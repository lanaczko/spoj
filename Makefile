#PROBLEMS := arith onp palin prime1 test
PROBLEMS := arith palin
all: ${PROBLEMS}

export CXXFLAGS=-ggdb

export CC=g++

${PROBLEMS}:
	cd $@ && $(MAKE)

clean:
	cd arith && make clean

.PHONY: ${PROBLEMS}
