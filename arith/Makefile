all: arith arith_gen

CC=g++

arith: arith.o

arith_gen: arith_gen.o

check: arith
	./arith < arith5.txt

clean:
	rm -f *o
	rm -f arith arith_gen
