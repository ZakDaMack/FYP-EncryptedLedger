#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>

/// Generates a private key to encrypt and decrypt your bank balance
/// Params:
///
/// Returns: string of path for file containing key
string GeneratePrivateKeyFile(){
      // TODO: upload to file, clear pointers
      // set the key parameters (make sure to clean up in later version)
      const int minimum_lambda = 110;
      TFheGateBootstrappingParameterSet* params = new_default_gate_bootstrapping_parameters(minimum_lambda);

      //generate a random key (make sure to clean up in later version)
      long timeSeeder = GetCurrentTime();
      uint32_t seed[] = {
        timeSeeder % 10000,
        timeSeeder % 100000 / 100,
        timeSeeder % 100000000 / 100
      };

      tfhe_random_generator_setSeed(seed, 3);

      TFheGateBootstrappingSecretKeySet* key = new_random_gate_bootstrapping_secret_keyset(params);
      //TFheGateBootstrappingCloudKeySet* cloudkey = &key->cloud;

      cout << "Private key: " << &key << "\nCloud key: " << &key->cloud << '\n';

      return path;
}
