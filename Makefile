#PROBLEMS := arith onp palin prime1 test
PROBLEMS := arith palin fctrl
all: ${PROBLEMS}

export CXXFLAGS=-ggdb

export CC=g++

${PROBLEMS}:
	cd $@ && $(MAKE)

clean:
	cd arith && make clean

check:
	cd fctrl && make check

.PHONY: ${PROBLEMS}
