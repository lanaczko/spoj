all: arith onp palin prime1 test

export CXXFLAGS=-ggdb

export CC=g++

arith:
	cd $@ && $(MAKE)

onp:

palin:

prime1:

test:

.PHONY: arith onp palin prime1 test
