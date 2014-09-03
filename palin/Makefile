PROBLEM=palin
all: ${PROBLEM}

CC=g++

${PROBLEM}: ${PROBLEM}.o

check: ${PROBLEM}
	./${PROBLEM} < ${PROBLEM}1.txt

clean:
	rm -f *o
	rm -f ${PROBLEM}
