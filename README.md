# FYP-EncryptedLedger

### Description

This repository will be used along with my Final Year Project being undertaken at the University of Portsmouth.

This application will attempt to utilise Homomorphic Encryption to hide the data within a Distributed Ledger system.

### Pre-Requisites for TFHE

1. Download TFHE .zip [here](https://tfhe.github.io/tfhe)
2. Unzip the file and open the location in the terminal
3. Create a directory labelled build: ```mkdir build```
4. Enter the build directory and input: ```ccmake ../src``` (If cmake command isn't found, enter: ```sudo apt-get install build-essential cmake cmake-curses-gui```)
5. Configure and generate the ccmake file (should be ok if left as is)
6. Input: ```sudo make && sudo make install```

### Running the Blockchain System

1. ```./run.sh```

### TO-DO

1. Serialisation???
2. Testing
3. Improve UX??? (input validation/output blockchain)
4. Create chain validator

### CHEATING THE SYSTEM

1. Sending money to yourself (easily validated)
2. Sending negative values
3. Bottomless bank account

### Known Issues

1. Sending and receiving currency values seem flipped (subtraction instead of additon, vice versa)
2. Odd dealing with floats
