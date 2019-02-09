# FYP-EncryptedLedger

### Description

This repository will be used along with my Final Year Project being undertaken at the University of Portsmouth.

This application will attempt to utilise Homomorphic Encryption to hide the data within a Distributed Ledger system.

### Pre-Requisites

1. Download TFHE .zip [here](https://tfhe.github.io/tfhe)
2. Unzip the file and open the location in the terminal
3. Create a directory labelled build: ```mkdir build```
4. Enter the build directory and input: ```ccmake ../src``` (If cmake command isn't found, enter: ```sudo apt-get install build-essential cmake cmake-curses-gui```)
5. Configure and generate the ccmake file (should be ok if left as is)
6. Input: ```sudo make && sudo make install```

### First time running encrypted-ledger

1. Follow the tutorial to install the Pre-Requisites [here](https://hyperledger.github.io/composer/latest/introduction/introduction)
2. ```composer network install --archiveFile encrypted-ledger@0.0.1.bna --card PeerAdmin@hlfv1```
3. ```composer network start --networkName encrypted-ledger --networkVersion 0.0.1 --networkAdmin admin --networkAdminEnrollSecret adminpw --card PeerAdmin@hlfv1 --file admin@encryptedLedger.card```
4. ```composer card import --file admin@encryptedLedger.card```

### Running encrypted-ledger again

1. Navigate to your dev server file and run ```./startFabric.sh```
2. Navigate to the encrypted-ledger folder. Type ```composer network install --archiveFile encrypted-ledger@0.0.1.bna --card PeerAdmin@hlfv1```
3. ```composer network start --networkName encrypted-ledger --networkVersion 0.0.1 --networkAdmin admin --networkAdminEnrollSecret adminpw --card PeerAdmin@hlfv1```

### Using TFHE example file

1. Download and unzip repository
2. Navigate to TFHE inside the repository using the terminal
3. Input: ```make```
4. Input ```./tfheexample``` or ```./tfheexample2``` and the program should run
