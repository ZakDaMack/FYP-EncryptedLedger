#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <stdio.h> //C lib
#include <iostream> //C++ lib
#include <chrono>
#include <iomanip>
#include<fstream>

#include "base64.h"

using namespace std;

/**
* HELPER FUNCTIONS
**/

long GetCurrentTime()
{
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

void CreateTextFile(string fileName, string contents)
{
    string fullFileName = fileName + ".txt";
    FILE* text_file = fopen(fullFileName.c_str(), "wb");
    fputs(contents.c_str(), text_file);
    fclose(text_file);
}

/**
* USER FUNCTIONS
**/

void Base64BalanceTest()
{
    const int number_of_bits = 64;
    // set the key parameters (make sure to clean up in later version)
    const int minimum_lambda = 110;
    TFheGateBootstrappingParameterSet* params = new_default_gate_bootstrapping_parameters(minimum_lambda);

    cout << "Generating keys.....\n";
    uint32_t seed[] = { 10000, 100000, 100000000 };
    tfhe_random_generator_setSeed(seed, 3);

    TFheGateBootstrappingSecretKeySet* key = new_random_gate_bootstrapping_secret_keyset(params);
    cout << "Private key: " << &key << "\nCloud key: " << &key->cloud << '\n';

    cout <<"insert int: ";
    int64_t plainInt1;
    cin >> plainInt1;
    LweSample* ciphertext1 = new_gate_bootstrapping_ciphertext_array(number_of_bits, params);
    for (int i = 0; i < number_of_bits; i++) {
        bootsSymEncrypt(&ciphertext1[i], (plainInt1 >> i)&1, key);
    }

    stringstream stream;

    for (int i = 0; i < number_of_bits; i++) {
        export_gate_bootstrapping_ciphertext_toStream(stream, &ciphertext1[i], params);
    }

    string encr = stream.str();
    //string encr = "hello world";
    string encoded = base64_encode(
        reinterpret_cast<const unsigned char*>(encr.c_str()),
        encr.length()
    );

    cout << encoded << endl;
    CreateTextFile("encryptedBalance-" + to_string(plainInt1), encoded);


    // reverse

    stringstream newstream;
    newstream << base64_decode(encoded);

    LweSample* answer = new_gate_bootstrapping_ciphertext_array(number_of_bits, params);
    for (int i = 0; i < number_of_bits; i++) {
        import_gate_bootstrapping_ciphertext_fromStream(newstream, &answer[i], params);
    }

    int64_t shiftedBalance = 0;
    for (int i = 0; i < 64; i++) {
        int ai = bootsSymDecrypt(&answer[i], key);
        shiftedBalance |= (ai << i);
    }

    cout << shiftedBalance << endl;
}

void GenerateABalance()
{
    // get key path and file
    string keyPath;
    cout << "Enter path to your private key: ";
    cin >> keyPath;
    FILE* private_file = fopen(keyPath.c_str(), "rb");

    // Validate exists
    if (private_file == NULL) {
        cout << "Error: File Doesn't Exist!" << endl;
        return;
    }

    TFheGateBootstrappingSecretKeySet* privateKey = new_tfheGateBootstrappingSecretKeySet_fromFile(private_file);
    fclose(private_file);

    // Get the  balance
    double bal;
    cout << "Enter your balance: ";
    cin >> bal;

    // Shift the bank balance to make it an integer
    int64_t shiftedBankBalance = bal * 100;
    cout << to_string(shiftedBankBalance) << endl;

    LweSample* cipherBalance = new_gate_bootstrapping_ciphertext_array(64, privateKey->params);
    for (int i = 0; i < 64; i++) {
        bootsSymEncrypt(&cipherBalance[i], (shiftedBankBalance >> i) & 1, privateKey);
    }

    stringstream ss;
    for (int i = 0; i < 64; i++) {
        export_gate_bootstrapping_ciphertext_toStream(ss, &cipherBalance[i], privateKey->params);
    }

    string encr = ss.str();
    string encoded = base64_encode(
        reinterpret_cast<const unsigned char*>(encr.c_str()),
        encr.length()
    );

    CreateTextFile("encryptedBalance", encoded);
    cout << encoded << endl;

    delete_gate_bootstrapping_ciphertext_array(64, cipherBalance);
    delete_gate_bootstrapping_secret_keyset(privateKey);
}

void GeneratePrivateAndPublicKeyFile()
{
    TFheGateBootstrappingParameterSet* parameters = new_default_gate_bootstrapping_parameters(126);

    //generate a random key
    long timeSeeder = GetCurrentTime();
    uint32_t seed[] = {
        timeSeeder % 10000,
        timeSeeder % 100000 / 100,
        timeSeeder % 100000000 / 100
    };
    tfhe_random_generator_setSeed(seed, 3);

    TFheGateBootstrappingSecretKeySet* key = new_random_gate_bootstrapping_secret_keyset(parameters);

    //export the secret key for decrypting bank balance at other points
    string keyname;
    cout << "Please enter your private key file name: ";
    cin >> keyname;
    keyname = keyname + ".key";
    cout << "Generating keys..." << endl;

    FILE* private_file = fopen(keyname.c_str(), "wb");
    export_tfheGateBootstrappingSecretKeySet_toFile(private_file, key);
    fclose(private_file);

    //encode public key into base64 for easy transfer across the web
    stringstream ss;
    export_tfheGateBootstrappingCloudKeySet_toStream(ss, &key->cloud);
    string encr = ss.str();
    //string encr = "hello world";
    string encodedKey = base64_encode(
        reinterpret_cast<const unsigned char*>(encr.c_str()),
        encr.length()
    );

    CreateTextFile("publickey", encodedKey);

    //clean up pointers
    delete_gate_bootstrapping_secret_keyset(key);
    delete_gate_bootstrapping_parameters(parameters);

    cout << "Done. Make sure not to lose the private key, it is IRREPLACEABLE!" << endl
    << "Private Key Location: " << keyname << endl;
}

void RetrievePublicKey()
{
    // get key path and file
    string keyPath;
    cout << "Enter path to your private key: ";
    cin >> keyPath;
    FILE* private_file = fopen(keyPath.c_str(), "rb");

    // Validate exists
    if (private_file == NULL) {
        cout << "Error: File Doesn't Exist!" << endl;
        return;
    }

    TFheGateBootstrappingSecretKeySet* privateKey = new_tfheGateBootstrappingSecretKeySet_fromFile(private_file);
    fclose(private_file);

    //encode public key into base64 for easy transfer across the web
    stringstream ss;
    export_tfheGateBootstrappingCloudKeySet_toStream(ss, &privateKey->cloud);
    string encr = ss.str();

    string encodedKey = base64_encode(
        reinterpret_cast<const unsigned char*>(encr.c_str()),
        encr.length()
    );

    CreateTextFile("publickey", encodedKey);

    //clean up pointers
    delete_gate_bootstrapping_secret_keyset(privateKey);
}

void ReadBalance()
{
    // get key path and file
    string keyPath;
    cout << "Enter path to your private key: ";
    cin >> keyPath;
    FILE* private_file = fopen(keyPath.c_str(), "rb");

    // Validate exists
    if (private_file == NULL) {
        cout << "Error: File Doesn't Exist!" << endl;
        return;
    }

    TFheGateBootstrappingSecretKeySet* privateKey = new_tfheGateBootstrappingSecretKeySet_fromFile(private_file);
    fclose(private_file);

    // Get the encrypted bank balance
    string encodedBalance;
    cout << "Enter your encrypted bank balance: ";
    cin >> encodedBalance;

    stringstream ss;
    ss << base64_decode(encodedBalance);

    LweSample* cipherBalance = new_gate_bootstrapping_ciphertext_array(64, privateKey->params);
    for (int i = 0; i < 64; i++) {
        import_gate_bootstrapping_ciphertext_fromStream(ss, &cipherBalance[i], privateKey->params);
    }

    int64_t shiftedBalance = 0;
    for (int i = 0; i < 64; i++) {
        int ai = bootsSymDecrypt(&cipherBalance[i], privateKey);
        shiftedBalance |= (ai << i);
    }

    delete_gate_bootstrapping_ciphertext_array(64, cipherBalance);
    delete_gate_bootstrapping_secret_keyset(privateKey);

    // shift the balance back two places
    double balance = shiftedBalance / 100.0;
    cout << endl << "bal: " << balance << endl;

    cout.imbue(locale("en_GB.utf8"));
    cout << put_money(shiftedBalance) << endl;
}

int main(int argc, char* argv[])
{
    cout << endl
    << "Encrypted Ledger Terminal Assistant" << endl
    << "By Zak Dowsett" << endl
    << "Version: 0.1.1" << endl
    << "https://github.com/ZakDaMack/FYP-EncryptedLedger" << endl
    << endl;

    cout
    << "1. Base 64 Test" << endl
    << "2. Generate a Balance" << endl
    << "3. Read Balance" << endl
    << "4. Generate Keys" << endl
    << "5. Get Public Key from .Key file" << endl << endl
    << "Choose an option: ";

    int option;
    cin >> option;

    switch (option) {
        case 1 :
            Base64BalanceTest();
            break;
        case 2 :
            GenerateABalance();
            break;
        case 3 :
            ReadBalance();
            break;
        case 4 :
            GeneratePrivateAndPublicKeyFile();
            break;
        case 5 :
            RetrievePublicKey();
            break;
        default :
            cout << "Please choose a valid option!\n";
            break;
    }

    return 0;
}
