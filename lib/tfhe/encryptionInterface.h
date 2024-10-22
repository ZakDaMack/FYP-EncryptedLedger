#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <chrono>
#include <iomanip>

using namespace std;

// implements Subtraction using a binary subtractor
void Subtraction(LweSample* result, const LweSample* a, const LweSample* b, const TFheGateBootstrappingCloudKeySet* publicKey);

// implements addition using a full adder
void Addition(LweSample* result, const LweSample* a, const LweSample* b, const TFheGateBootstrappingCloudKeySet* publicKey);

long GetCurrentTime();

void CipherTransactionAmount(LweSample* result, int64_t value, const TFheGateBootstrappingCloudKeySet* publicKey);

/// Generates a private key to encrypt and decrypt your bank balance
/// Params:
///
/// Returns: string of path for file containing key
string GeneratePrivateKeyFile();

/// Generates a cloud key from the private key file
/// Params:
///
/// Returns: string of path for file containing key
string GenerateCloudKeyFile(string privateKeyPath);

/// Returns: file path to balance
string EncryptBankBalance(double bankBalance, string privateKeyPath);

double ReadBankBalance(string balancePath, string privateKeyPath);

string ComputeSenderTransaction(double transactionAmount, string previousBalanceFile, string cloudKeyPath);

string ComputeReceiverTransaction(double transactionAmount, string previousBalanceFile, string cloudKeyPath);

bool VerifyTransactionBalance(bool outgoingTransaction, double transactionAmount, string cloudKeyPath, string originalBalancePath, string newBalancePath);
