TARGET=fctrl

all: ${TARGET}

CC=g++

${TARGET}: ${TARGET}.o

check: ${TARGET}
	./${TARGET} < ${TARGET}1.txt

clean:
	rm -f *o
	rm -f ${TARGET}
