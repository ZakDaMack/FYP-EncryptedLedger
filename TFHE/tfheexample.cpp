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

// elementary full comparator gate that is used to compare the i-th bit:
//   input: ai and bi the i-th bit of a and b
//          lsb_carry: the result of the comparison on the lowest bits
//   algo: if (a==b) return lsb_carry else return b
void compare_bit(LweSample* result, const LweSample* a, const LweSample* b, const LweSample* lsb_carry, LweSample* tmp, const TFheGateBootstrappingCloudKeySet* bk) {
    bootsXNOR(tmp, a, b, bk);
    bootsMUX(result, tmp, lsb_carry, a, bk);
}

// this function compares two multibit numbers, and puts the min in result
void minimum(LweSample* result, const LweSample* a, const LweSample* b, const int nb_bits, const TFheGateBootstrappingCloudKeySet* bk) {
    LweSample* tmps = new_gate_bootstrapping_ciphertext_array(2, bk->params);

    //initialize the carry to 0
    bootsCONSTANT(&tmps[0], 0, bk);
    //run the elementary comparator gate n times
    for (int i=0; i<nb_bits; i++) {
        compare_bit(&tmps[0], &a[i], &b[i], &tmps[0], &tmps[1], bk);
    }

    //tmps[0] is the result of the comparaison: 0 if a is larger, 1 if b is larger
    //select the max and copy it to the result
    for (int i=0; i<nb_bits; i++) {
        bootsMUX(&result[i], &tmps[0], &b[i], &a[i], bk);
    }
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

void BitRepresentation(int32_t x, int numOfBits)
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

    int32_t plainInt1 = CollectInputs("Provide your first number");
    int32_t plainInt2 = CollectInputs("Provide your second number");
    //cout << "Provide your first number: ";
    //cin >> plainInt1;
    //cout << "Provide your second number: ";
    //cin >> plainInt2;
    cout << plainInt1 << ", " << plainInt2 << '\n';
    BitRepresentation(plainInt1, 32);
    BitRepresentation(plainInt2, 32);

    // encrypt the two values
    cout << "Encrypting values... ";

    // for first int
    LweSample* ciphertext1 = new_gate_bootstrapping_ciphertext_array(32, params);
    // integer assumed to be 16 bit for the moment
    // (what if it's more? can i look at number of bits and insert into array that way?)
    for (int i = 0; i < 32; i++) {
        // bootsSymEncrypt(print result to, current bit to encrypt, encryption key)
        bootsSymEncrypt(&ciphertext1[i], (plainInt1 >> i)&1, key);
        // NB: (plainInt1 >> i)&1 .... Selects the correct bit from the integer and the &1 checks to see if there is a value (1 for yes/ 0 for no)
    }

    //for second int
    LweSample* ciphertext2 = new_gate_bootstrapping_ciphertext_array(32, params);
    for (int i = 0; i < 32; i++) {
        bootsSymEncrypt(&ciphertext2[i], (plainInt2 >> i)&1, key);
    }

    cout << "Done!" << '\n';

    // do an operation with these numbers

    // prepare a cipher array for results
    LweSample* result = new_gate_bootstrapping_ciphertext_array(32, params);

    bool op_completed = true;
    do
    {

        int option;
        cout << "1. Minimum\n2. Addition\n3. Subtraction\nPlease choose an option: ";
        cin >> option;
        long startTime = GetCurrentTime();

        op_completed = true;

        switch (option) {
            case 1 :
            minimum(result, ciphertext1, ciphertext2, 32, &key->cloud);
            break;
            case 2 :
            Addition(result, ciphertext1, ciphertext2, 32, &key->cloud);
            break;
            case 3 :
            Subtraction(result, ciphertext1, ciphertext2, 32, &key->cloud);
            break;
            default :
            cout << "Please choose a valid option!\n";
            op_completed = false;
            break;
        }

        int timeElapsed = GetCurrentTime() - startTime;

        if (op_completed)
            cout << "Time elapsed: " << timeElapsed / 1000.0 << "s\n";

    }
    while (!op_completed);

    //decipher result
    //decrypt and rebuild the 16-bit plaintext answer
    int32_t int_answer = 0;
    for (int i = 0; i < 32; i++) {
        int ai = bootsSymDecrypt(&result[i], key);
        int_answer |= (ai<<i);
    }

    cout << "The answer is: " << int_answer << '\n';

    return 0;
}
