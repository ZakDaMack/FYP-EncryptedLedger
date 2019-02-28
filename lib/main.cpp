#include "blockchain/userdatabase.h"
#include "blockchain/blockchain.h"

using namespace std;

Blockchain blockchain = Blockchain();
UserDatabase userDB = UserDatabase();

void NewUser(string name) {
  int userId = userDB.AddNewUser(name);
  blockchain.GiveNewUserStarterBalance(userId);
}

int main(int argc, char const *argv[]) {
  // Add users to db and give them some money
  NewUser("User 1");
  NewUser("User 2");
  userDB.DisplayUsers();

  blockchain.CreateTransaction(1, 2, 20.37);

  blockchain.DisplayChain();
  return 0;
}
