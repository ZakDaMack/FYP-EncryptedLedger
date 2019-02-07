#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <chrono>
#include <iomanip>

using namespace std;

// implements Subtraction using a binary subtractor
void Subtraction(LweSample* result, const LweSample* a, const LweSample* b, const TFheGateBootstrappingCloudKeySet* publicKey)
{
    // init borrow to 0 at 0
    // abOperation at 1
    // borrow part 1 at 2
    // borrow part 2 at 3
    // borrow part 3 at 4
    LweSample* valueStorage = new_gate_bootstrapping_ciphertext_array(5, publicKey->params);
    bootsCONSTANT(&valueStorage[0], 0, publicKey);

    for (int i = 0; i < 64; i++)
    {
        // implemting a full adder for addition
        // AxorB = xor(a, b)
        // difference = xor(AxorB, borrow)
        // borrow = or(andny(a,b), and(AxorB, borrow))
        bootsXOR(&valueStorage[1], &a[i], &b[i], publicKey); //abOperation
        bootsXOR(&result[i], &valueStorage[1], &valueStorage[0], publicKey); // difference

        bootsANDNY(&valueStorage[2], &a[i], &b[i], publicKey); // borrow part 1
        bootsXNOR(&valueStorage[3], &a[i], &b[i], publicKey); // borrow part 2
        bootsAND(&valueStorage[4], &valueStorage[3], &valueStorage[0], publicKey); // borrow part 3
        bootsOR(&valueStorage[0], &valueStorage[2], &valueStorage[4], publicKey); // new borrow assign
    }
}

// implements addition using a full adder
void Addition(LweSample* result, const LweSample* a, const LweSample* b, const TFheGateBootstrappingCloudKeySet* publicKey)
{
    // init carry to 0 at 0
    // abOperation at 1
    // carry part 1 at 2
    // carry part 2 at 3
    LweSample* valueStorage = new_gate_bootstrapping_ciphertext_array(4, publicKey->params);
    bootsCONSTANT(&valueStorage[0], 0, publicKey);

    for (int i = 0; i < 64; i++)
    {
        // implemting a full adder for addition
        // AxorB = xor(a, b)
        // sum = xor(AxorB, carry)
        // carry = or(and(a,b), and(AxorB, carry))
        bootsXOR(&valueStorage[1], &a[i], &b[i], publicKey); //abOperation
        bootsXOR(&result[i], &valueStorage[1], &valueStorage[0], publicKey); // sum - abOperation & carry
        bootsAND(&valueStorage[2], &a[i], &b[i], publicKey); // carry part 1
        bootsAND(&valueStorage[3], &valueStorage[1], &valueStorage[0], publicKey); // carry part 2
        bootsOR(&valueStorage[0], &valueStorage[2], &valueStorage[3], publicKey); // new carry assign
    }
}

long GetCurrentTime()
{
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

void CipherTransactionAmount(LweSample* result, int64_t value, const TFheGateBootstrappingCloudKeySet* publicKey)
{
    for (int i = 0; i < 64; i++) {
        bootsCONSTANT(&result[i], (value >> i)&1, publicKey);
    }
}

/// Generates a private key to encrypt and decrypt your bank balance
/// Params:
///
/// Returns: string of path for file containing key
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
    FILE* private_file = fopen("private.key","wb");
    export_tfheGateBootstrappingSecretKeySet_toFile(private_file, key);
    fclose(private_file);

    //export the cloud key to a file
    FILE* public_file = fopen("public.key","wb");
    export_tfheGateBootstrappingCloudKeySet_toFile(public_file, &key->cloud);
    fclose(public_file);

    //clean up pointers
    delete_gate_bootstrapping_secret_keyset(key);
    delete_gate_bootstrapping_parameters(parameters);

}

TFheGateBootstrappingCloudKeySet* GetPublicKey() {

    FILE* public_file = fopen("public.key","rb");
    TFheGateBootstrappingCloudKeySet* publicKey = new_tfheGateBootstrappingCloudKeySet_fromFile(public_file);
    fclose(public_file);

    return publicKey;

}

void EncryptBankBalance(double bankBalance)
{
    // Fetch the private key for encryption
    FILE* private_file = fopen("private.key","rb");
    TFheGateBootstrappingSecretKeySet* privateKey = new_tfheGateBootstrappingSecretKeySet_fromFile(private_file);
    fclose(private_file);

    // Shift the bank balance to make it an integer
    int64_t shiftedBankBalance = bankBalance * 100;

    // Encrypt the bank balance
    LweSample* encryptedBalance = new_gate_bootstrapping_ciphertext_array(64, privateKey->params);
    for (int i = 0; i < 64; i++) {
        bootsSymEncrypt(&encryptedBalance[i], (shiftedBankBalance >> i) & 1, privateKey);
    }

    //export the balanace to a file
    FILE* balance_file = fopen("balance.data","wb");
    for (int i = 0; i < 64; i++)
    export_gate_bootstrapping_ciphertext_toFile(balance_file, &encryptedBalance[i], privateKey->params);
    fclose(balance_file);


    //clean up pointers
    delete_gate_bootstrapping_secret_keyset(privateKey);
    delete_gate_bootstrapping_ciphertext_array(64, encryptedBalance);

}

string ReadBankBalance()
{
    // Fetch the private key for encryption
    FILE* private_file = fopen("private.key","rb");
    TFheGateBootstrappingSecretKeySet* privateKey = new_tfheGateBootstrappingSecretKeySet_fromFile(private_file);
    fclose(private_file);

    LweSample* cipherBalance = new_gate_bootstrapping_ciphertext_array(64, privateKey->params);

    //import the balance
    FILE* balance_file = fopen("balance.data","rb");
    for (int i = 0; i < 64; i++)
        import_gate_bootstrapping_ciphertext_fromFile(balance_file, &cipherBalance[i], privateKey->params);
    fclose(balance_file);

    int64_t shiftedBalance = 0;
    for (int i = 0; i < 64; i++) {
        int ai = bootsSymDecrypt(&cipherBalance[i], privateKey);
        shiftedBalance |= (ai << i);
    }

    delete_gate_bootstrapping_ciphertext_array(64, cipherBalance);
    delete_gate_bootstrapping_secret_keyset(privateKey);

    // shift the balance back two places
    double balance = shiftedBalance / 100.0;

    return ""; //put_money(balance);
}

void ComputeSenderTransaction(double transactionAmount)
{
    int64_t shiftedTransactionAmount = transactionAmount * 100;

    // Fetch the public key for computing
    FILE* public_file = fopen("public.key","rb");
    TFheGateBootstrappingCloudKeySet* publicKey = new_tfheGateBootstrappingCloudKeySet_fromFile(public_file);
    fclose(public_file);

    // Get the account cipher
    LweSample* cipherBalance = new_gate_bootstrapping_ciphertext_array(64, publicKey->params);
    FILE* data_file = fopen("balance.data","rb");
    for (int i = 0; i < 64; i++)
        import_gate_bootstrapping_ciphertext_fromFile(data_file, &cipherBalance[i], publicKey->params);
    fclose(data_file);

    // cipher the transaction amount, ready for processing
    LweSample* cipherTransaction = new_gate_bootstrapping_ciphertext_array(64, publicKey->params);
    CipherTransactionAmount(cipherTransaction, shiftedTransactionAmount, publicKey);

    Subtraction(cipherBalance, cipherBalance, cipherTransaction, publicKey);

    // write new balance to file
    FILE* balance_file = fopen("balance.data","wb");
    for (int i = 0; i < 64; i++)
        export_gate_bootstrapping_ciphertext_toFile(balance_file, &cipherBalance[i], publicKey->params);
    fclose(balance_file);

    // clear pointers
    delete_gate_bootstrapping_ciphertext_array(64, cipherBalance);
    delete_gate_bootstrapping_ciphertext_array(64, cipherTransaction);
    delete_gate_bootstrapping_cloud_keyset(publicKey);
}

void ComputeReceiverTransaction(double transactionAmount)
{
    int64_t shiftedTransactionAmount = transactionAmount * 100;

    // Fetch the public key for computing
    FILE* public_file = fopen("public.key","rb");
    TFheGateBootstrappingCloudKeySet* publicKey = new_tfheGateBootstrappingCloudKeySet_fromFile(public_file);
    fclose(public_file);

    // Get the account cipher
    LweSample* cipherBalance = new_gate_bootstrapping_ciphertext_array(64, publicKey->params);
    FILE* data_file = fopen("balance.data","rb");
    for (int i = 0; i < 64; i++)
        import_gate_bootstrapping_ciphertext_fromFile(data_file, &cipherBalance[i], publicKey->params);
    fclose(data_file);

    // cipher the transaction amount, ready for processing
    LweSample* cipherTransaction = new_gate_bootstrapping_ciphertext_array(64, publicKey->params);
    CipherTransactionAmount(cipherTransaction, shiftedTransactionAmount, publicKey);

    Addition(cipherBalance, cipherBalance, cipherTransaction, publicKey);

    // write new balance to file
    FILE* balance_file = fopen("balance.data","wb");
    for (int i = 0; i < 64; i++)
        export_gate_bootstrapping_ciphertext_toFile(balance_file, &cipherBalance[i], publicKey->params);
    fclose(balance_file);

    // clear pointers
    delete_gate_bootstrapping_ciphertext_array(64, cipherBalance);
    delete_gate_bootstrapping_ciphertext_array(64, cipherTransaction);
    delete_gate_bootstrapping_cloud_keyset(publicKey);
}

bool VerifyTransaction(bool outgoingTransaction, double transactionAmount)
{

        int64_t shiftedTransactionAmount = transactionAmount * 100;

        // Fetch the public key for computing
        FILE* public_file = fopen("public.key","rb");
        TFheGateBootstrappingCloudKeySet* publicKey = new_tfheGateBootstrappingCloudKeySet_fromFile(public_file);
        fclose(public_file);

        // Get the original balance cipher
        LweSample* originalCipherBalance = new_gate_bootstrapping_ciphertext_array(64, publicKey->params);
        FILE* old_data_file = fopen("oldBalance.data","rb");
        for (int i = 0; i < 64; i++)
            import_gate_bootstrapping_ciphertext_fromFile(old_data_file, &originalCipherBalance[i], publicKey->params);
        fclose(old_data_file);

        // Get the new balance cipher
        LweSample* newCipherBalance = new_gate_bootstrapping_ciphertext_array(64, publicKey->params);
        FILE* new_data_file = fopen("oldBalance.data","rb");
        for (int i = 0; i < 64; i++)
            import_gate_bootstrapping_ciphertext_fromFile(new_data_file, &newCipherBalance[i], publicKey->params);
        fclose(new_data_file);

        // cipher the transaction amount, ready for processing
        LweSample* cipherTransaction = new_gate_bootstrapping_ciphertext_array(64, publicKey->params);
        CipherTransactionAmount(cipherTransaction, shiftedTransactionAmount, publicKey);

        LweSample* computedCipherBalance = new_gate_bootstrapping_ciphertext_array(64, publicKey->params);

        if (outgoingTransaction)
            Subtraction(computedCipherBalance, originalCipherBalance, cipherTransaction, publicKey);
        else
            Addition(computedCipherBalance, originalCipherBalance, cipherTransaction, publicKey);

        // calculate if the two updated balances give the same values
        bool isValid = true;
        for (int i = 0; i < 64; i++)
            if (&computedCipherBalance[i] != &newCipherBalance[i]) {
                isValid = false;
                break;
            }

        // clear pointers
        delete_gate_bootstrapping_ciphertext_array(64, originalCipherBalance);
        delete_gate_bootstrapping_ciphertext_array(64, newCipherBalance);
        delete_gate_bootstrapping_ciphertext_array(64, computedCipherBalance);
        delete_gate_bootstrapping_ciphertext_array(64, cipherTransaction);
        delete_gate_bootstrapping_cloud_keyset(publicKey);

        return isValid;

}
