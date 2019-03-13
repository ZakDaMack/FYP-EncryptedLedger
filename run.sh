mkdir -p bin

g++ lib/tfhe/encryptionInterface.cpp lib/blockchain/userdatabase.cpp lib/sha256/sha256.cpp lib/blockchain/block.cpp lib/blockchain/blockchain.cpp lib/main.cpp -ltfhe-spqlios-fma -o bin/main

cd bin
./main
