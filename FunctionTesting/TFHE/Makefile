# compiler to use
CC=g++

# base TFHE installation directory
TFHE_DIR=/usr/local

# C_INCLUDE_PATH
INCS=-I${TFHE_DIR}/include

# LIBRARY-PATH
LIBS=-L${TFHE_DIR}/lib -Wl,-rpath=${TFHE_DIR}/lib -ltfhe-spqlios-fma

all: tfheexample tfheexample2 hencInt

tfheexample: tfheexample.cpp
	${CC} ${INCS} -c $<
	${CC} -o $@ $@.o ${LIBS}

tfheexample2: tfheexample2.cpp
	${CC} ${INCS} -c $<
	${CC} -o $@ $@.o ${LIBS}

hencInt: hencInt.cpp
	${CC} ${INCS} -c $<
	${CC} -o $@ $@.o ${LIBS}
