TARGET=sbank

all: ${TARGET}

CC=g++

export CXXFLAGS=-ggdb

${TARGET}: ${TARGET}.o

check: ${TARGET}
	./${TARGET} < ${TARGET}1.txt

clean:
	rm -f *o
	rm -f ${TARGET}
