# compiler to use
CC=g++

# base TFHE installation directory
TFHE_DIR=/usr/local

# C_INCLUDE_PATH
INCS=-I${TFHE_DIR}/include

# LIBRARY-PATH
LIBS=-L${TFHE_DIR}/lib -Wl,-rpath=${TFHE_DIR}/lib -ltfhe-spqlios-fma

all: block blockchain userdatabase main

block: blockchain/block.cpp
	${CC} $< sha256/sha256.cpp -o $@.o

blockchain: blockchain/blockchain.cpp
	${CC} $< block.o -o $@.o

userdatabase: blockchain/userdatabase.cpp
	${CC} $< -o $@.o

main: main.cpp
	${CC} ${INCS} -c $<
	${CC} -o $@ $@.o blockchain.o userdatabase.o ${LIBS}
