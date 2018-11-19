# compiler to use
CC=g++

# base TFHE installation directory
TFHE_DIR=/usr/local

# C_INCLUDE_PATH
INCS=-I${TFHE_DIR}/include

# LIBRARY-PATH
LIBS=-L${TFHE_DIR}/lib -Wl,-rpath=${TFHE_DIR}/lib -ltfhe-spqlios-fma

tfheexample: tfheexample.cpp
	${CC} ${INCS} -c $<
	${CC} -o $@ $@.o ${LIBS}
 

