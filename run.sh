mkdir -p bin

g++ -I/usr/local/include lib/tfhe/encryptionInterface.cpp lib/blockchain/userdatabase.cpp lib/sha256/sha256.cpp lib/blockchain/block.cpp lib/blockchain/blockchain.cpp lib/main.cpp -L/usr/local/lib -Wl,-rpath=/usr/local/lib -ltfhe-spqlios-fma -o bin/main -w

cd bin
./main
