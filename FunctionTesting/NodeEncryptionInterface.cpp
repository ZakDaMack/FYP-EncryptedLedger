#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <chrono>
#include <node.h>
#include <v8.h>
#include <iomanip>

using namespace std;
using namespace v8;

class FullyHomomorphicEncryption {

public:

    // Let the C++ method receive node args
    Handle<Value> CalculateSenderBalance(const Arguments& args) {
        HandleScope scope;

        // make sure there are 3 args
        if (args.Length() != 3) {
            ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
            return scope.Close(Undefined());
        }

        // make sure the args are correct types
        if (!args[0]->IsNumber() || !args[1]->IsString() || !args[2]->IsString()) {
            ThrowException(Exception::TypeError(String::New("Wrong arguments")));
            return scope.Close(Undefined());
        }

        Local<Number> num = Number::New(args[0]->NumberValue() +
        args[1]->NumberValue());
        return scope.Close(num);
    }

    Handle<Value> CalculateReceiverBalance(const Arguments& args) {
        HandleScope scope;

        // make sure there are 3 args
        if (args.Length() != 3) {
            ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
            return scope.Close(Undefined());
        }

        // make sure the args are correct types
        if (!args[0]->IsNumber() || !args[1]->IsString() || !args[2]->IsString()) {
            ThrowException(Exception::TypeError(String::New("Wrong arguments")));
            return scope.Close(Undefined());
        }

        Local<Number> num = Number::New(args[0]->NumberValue() +
        args[1]->NumberValue());
        return scope.Close(num);
    }

    // Init the C++ class
    void init(Handle<Object> target) {
        target->Set(NewSymbol("CalculateSenderBalance"),
            FunctionTemplate::New(CalculateSenderBalance)->GetFunction());

        target->Set(NewSymbol("CalculateReceiverBalance"),
            FunctionTemplate::New(CalculateReceiverBalance)->GetFunction());
    }

    // Export the node module
    NODE_MODULE(FullyHomomorphicEncryption, init)
}

private:

    void CalculateSenderBalancePrivate(double transactionAmount, String balancePath, String publicKeyPath) {
        int64_t shiftedTransactionAmount = transactionAmount * 100;

        // Fetch the public key for computing
        FILE* public_file = fopen(publicKeyPath.c_str(), "rb");
        TFheGateBootstrappingCloudKeySet* publicKey = new_tfheGateBootstrappingCloudKeySet_fromFile(public_file);
        fclose(public_file);

        // Get the account cipher
        LweSample* cipherBalance = new_gate_bootstrapping_ciphertext_array(64, publicKey->params);
        FILE* data_file = fopen(balancePath.c_str(), "rb");
        for (int i = 0; i < 64; i++)
        import_gate_bootstrapping_ciphertext_fromFile(data_file, &cipherBalance[i], publicKey->params);
        fclose(data_file);

        // calculate the new transaction amount
        LweSample* cipherTransaction = new_gate_bootstrapping_ciphertext_array(64, publicKey->params);
        IntToCipher(cipherTransaction, shiftedTransactionAmount, publicKey);

        Subtraction(cipherBalance, cipherBalance, cipherTransaction, publicKey);

        // write new balance to file
        FILE* balance_file = fopen(balancePath.c_str(), "wb");
        for (int i = 0; i < 64; i++)
        export_gate_bootstrapping_ciphertext_toFile(balance_file, &cipherBalance[i], publicKey->params);
        fclose(balance_file);

        // clear pointers
        delete_gate_bootstrapping_ciphertext_array(64, cipherBalance);
        delete_gate_bootstrapping_ciphertext_array(64, cipherTransaction);
        delete_gate_bootstrapping_cloud_keyset(publicKey);
    }

    void CalculateReceiverBalancePrivate(double transactionAmount, String balancePath, String publicKeyPath) {
        int64_t shiftedTransactionAmount = transactionAmount * 100;

        // Fetch the public key for computing
        FILE* public_file = fopen("public.key","rb");
        TFheGateBootstrappingCloudKeySet* publicKey = new_tfheGateBootstrappingCloudKeySet_fromFile(public_file);
        fclose(public_file);

        // Get the account cipher
        LweSample* cipherBalance = new_gate_bootstrapping_ciphertext_array(64, publicKey->params);
        FILE* data_file = fopen(balancePath.c_str(),"rb");
        for (int i = 0; i < 64; i++)
        import_gate_bootstrapping_ciphertext_fromFile(data_file, &cipherBalance[i], publicKey->params);
        fclose(data_file);

        // cipher the transaction amount, and add to the bank balance
        LweSample* cipherTransaction = new_gate_bootstrapping_ciphertext_array(64, publicKey->params);
        IntToCipher(cipherTransaction, shiftedTransactionAmount, publicKey);

        Addition(cipherBalance, cipherBalance, cipherTransaction, publicKey);

        // write new balance to file
        FILE* balance_file = fopen(balancePath.c_str(),"wb");
        for (int i = 0; i < 64; i++)
        export_gate_bootstrapping_ciphertext_toFile(balance_file, &cipherBalance[i], publicKey->params);
        fclose(balance_file);

        // clear pointers
        delete_gate_bootstrapping_ciphertext_array(64, cipherBalance);
        delete_gate_bootstrapping_ciphertext_array(64, cipherTransaction);
        delete_gate_bootstrapping_cloud_keyset(publicKey);
    }

    void IntToCipher(LweSample* result, int64_t value, const TFheGateBootstrappingCloudKeySet* publicKey) {
        for (int i = 0; i < 64; i++) {
            bootsCONSTANT(&result[i], (value >> i)&1, publicKey);
        }
    }

    // implements Subtraction using a binary subtractor
    void Subtraction(LweSample* result, const LweSample* a, const LweSample* b, const TFheGateBootstrappingCloudKeySet* publicKey) {
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
    void Addition(LweSample* result, const LweSample* a, const LweSample* b, const TFheGateBootstrappingCloudKeySet* publicKey) {
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

    // gets time in milliseconds
    long GetCurrentTime() {
        return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    }

} // end class
