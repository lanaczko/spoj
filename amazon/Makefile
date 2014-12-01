all: amazon

CC=gcc
CFLAGS=-std=c99 -ggdb

arith: amazon.o

check: amazon
	./amazon < input001.txt
	@echo "result:"
	@cat output.txt

clean:
	rm -f *o amazon
