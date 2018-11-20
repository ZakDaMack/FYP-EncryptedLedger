#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <stdio.h> //C lib
#include <iostream> //C++ lib
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

/**
* Currently works as a basic way of transfers between two bank accounts
* Can only work up to 16 bits
* How can we check that a user has enough money to transfer over?
**/

void TransactionEncrypt(LweSample* result, int value, const int bitLength, const TFheGateBootstrappingCloudKeySet* ck)
{
    cout << "Generating a cipher of " << value << ".... ";

    for (int i = 0; i < bitLength; i++) {
        bootsCONSTANT(&result[i], (value >> i)&1, ck);
        // NB: (plainInt1 >> i)&1 .... Selects the correct bit from the integer and the &1 checks to see if there is a value (1 for yes/ 0 for no)
    }

    cout << "Finished!\n";
}

// implements addition using a full adder
void Addition(LweSample* result, const LweSample* a, const LweSample* b, const int bitLength, const TFheGateBootstrappingCloudKeySet* ck)
{
    // init carry to 0 at 0
    // abOperation at 1
    // carry part 1 at 2
    // carry part 2 at 3
    LweSample* valueStorage = new_gate_bootstrapping_ciphertext_array(4, ck->params);
    bootsCONSTANT(&valueStorage[0], 0, ck);

    for (int i = 0; i < bitLength; i++)
    {
        // implemting a full adder for addition
        // AxorB = xor(a, b)
        // sum = xor(AxorB, carry)
        // carry = or(and(a,b), and(AxorB, carry))
        bootsXOR(&valueStorage[1], &a[i], &b[i], ck); //abOperation
        bootsXOR(&result[i], &valueStorage[1], &valueStorage[0], ck); // sum - abOperation & carry
        bootsAND(&valueStorage[2], &a[i], &b[i], ck); // carry part 1
        bootsAND(&valueStorage[3], &valueStorage[1], &valueStorage[0], ck); // carry part 2
        bootsOR(&valueStorage[0], &valueStorage[2], &valueStorage[3], ck); // new carry assign
    }
}

// implements Subtraction using a binary subtractor
void Subtraction(LweSample* result, const LweSample* a, const LweSample* b, const int bitLength, const TFheGateBootstrappingCloudKeySet* ck)
{
    // init borrow to 0 at 0
    // abOperation at 1
    // borrow part 1 at 2
    // borrow part 2 at 3
    // borrow part 3 at 4
    LweSample* valueStorage = new_gate_bootstrapping_ciphertext_array(5, ck->params);
    bootsCONSTANT(&valueStorage[0], 0, ck);

    for (int i = 0; i < bitLength; i++)
    {
        // implemting a full adder for addition
        // AxorB = xor(a, b)
        // difference = xor(AxorB, borrow)
        // borrow = or(andny(a,b), and(AxorB, borrow))
        bootsXOR(&valueStorage[1], &a[i], &b[i], ck); //abOperation
        bootsXOR(&result[i], &valueStorage[1], &valueStorage[0], ck); // difference

        bootsANDNY(&valueStorage[2], &a[i], &b[i], ck); // borrow part 1
        bootsXNOR(&valueStorage[3], &a[i], &b[i], ck); // borrow part 2
        bootsAND(&valueStorage[4], &valueStorage[3], &valueStorage[0], ck); // borrow part 3
        bootsOR(&valueStorage[0], &valueStorage[2], &valueStorage[4], ck); // new borrow assign
    }
}

long GetCurrentTime()
{
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

void BitRepresentation(int x, int numOfBits)
{
    vector<int> ret;

    for (int i = 0; i < numOfBits; i++) {
        ret.push_back((x >> i)&1);
    }

    reverse(ret.begin(), ret.end());

    copy(ret.begin(),
        ret.end(),
        ostream_iterator<int>(cout, " ")
    );

    cout << '\n';
}

int32_t CollectInputs(string message, int messageLimit = 0)
{
    int32_t value = 0;

    while (true)
    {
        cout << message << ": ";
        cin >> value;

        if (cin.fail() || (messageLimit > 0 && value > messageLimit))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (messageLimit > 0){
                cout << "There is no option with this value, please choose a value, no more than " << messageLimit << "\n";
            }
            else {
                cout << "The value isn't supported\n";
            }
        }
        else
        {
            break;
        }
    }
    return value;
}

int main()
{
    // set the key parameters (make sure to clean up in later version)
    const int minimum_lambda = 110;
    TFheGateBootstrappingParameterSet* params = new_default_gate_bootstrapping_parameters(minimum_lambda);

    //generate a random key (make sure to clean up in later version)
    cout << "Generating keys.....\n";
    long now = GetCurrentTime();
    uint32_t seed[] = { now % 10000, now % 100000 / 100,  now % 100000000 / 100 };
    tfhe_random_generator_setSeed(seed, 3);

    TFheGateBootstrappingSecretKeySet* key = new_random_gate_bootstrapping_secret_keyset(params);
    //TFheGateBootstrappingCloudKeySet* cloudkey = &key->cloud;

    cout << "Private key: " << &key << "\nCloud key: " << &key->cloud << '\n';

    int bankBalanceA = CollectInputs("Provide your bank balance");
    cout << bankBalanceA << '\n';
    BitRepresentation(bankBalanceA, 16);

    int transactionAmount = CollectInputs("Enter the amount to transfer");

    // encrypt the two values
    cout << "Encrypting values... ";

    // for first int
    LweSample* cipherBalanceA = new_gate_bootstrapping_ciphertext_array(16, params);
    // integer assumed to be 16 bit for the moment
    // (what if it's more? can i look at number of bits and insert into array that way?)
    for (int i = 0; i < 16; i++) {
        // bootsSymEncrypt(print result to, current bit to encrypt, encryption key)
        bootsSymEncrypt(&cipherBalanceA[i], (bankBalanceA >> i)&1, key);
        // NB: (plainInt1 >> i)&1 .... Selects the correct bit from the integer and the &1 checks to see if there is a value (1 for yes/ 0 for no)
    }

    // for second int
    int bankBalanceB = 1200;
    LweSample* cipherBalanceB = new_gate_bootstrapping_ciphertext_array(16, params);
    // integer assumed to be 16 bit for the moment
    // (what if it's more? can i look at number of bits and insert into array that way?)
    for (int i = 0; i < 16; i++) {
        // bootsSymEncrypt(print result to, current bit to encrypt, encryption key)
        bootsSymEncrypt(&cipherBalanceB[i], (bankBalanceB >> i)&1, key);
        // NB: (plainInt1 >> i)&1 .... Selects the correct bit from the integer and the &1 checks to see if there is a value (1 for yes/ 0 for no)
    }

    cout << "Done!" << '\n';

    // do an operation with these numbers

    // prepare a cipher array for results
    LweSample* newCipherBankBalanceA = new_gate_bootstrapping_ciphertext_array(16, params);
    LweSample* newCipherBankBalanceB = new_gate_bootstrapping_ciphertext_array(16, params);

    long startTime = GetCurrentTime();
    LweSample* valueTransaction= new_gate_bootstrapping_ciphertext_array(16, params);
    TransactionEncrypt(valueTransaction, transactionAmount, 16, &key->cloud);

    // a is giving to b, so take 20 off account
    Subtraction(newCipherBankBalanceA, cipherBalanceA, valueTransaction, 16, &key->cloud);
    Addition(newCipherBankBalanceB, cipherBalanceB, valueTransaction, 16, &key->cloud);

    int timeElapsed = GetCurrentTime() - startTime;
    cout << "Time elapsed: " << timeElapsed / 1000.0 << "s\n";


    //decipher result
    //decrypt and rebuild the 16-bit plaintext answer for both bank balances
    int16_t newBankBalanceA = 0;
    for (int i = 0; i < 16; i++) {
        int ai = bootsSymDecrypt(&newCipherBankBalanceA[i], key);
        newBankBalanceA |= (ai<<i);
    }

    //decipher result
    //decrypt and rebuild the 16-bit plaintext answer for both bank balances
    int16_t newBankBalanceB = 0;
    for (int i = 0; i < 16; i++) {
        int bi = bootsSymDecrypt(&newCipherBankBalanceB[i], key);
        newBankBalanceB |= (bi<<i);
    }

    // display info to user
    cout << "Previous Bank Account Values" << '\n' << "Account A: " << bankBalanceA << '\n' << "Account B: " << bankBalanceB << '\n';
    cout << "New Bank Account Values" << '\n' << "Account A: " << newBankBalanceA << '\n' << "Account B: " << newBankBalanceB << '\n';
    return 0;
}
