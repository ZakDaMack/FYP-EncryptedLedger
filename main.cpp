#include "lib/blockchain/userdatabase.h"
#include "lib/blockchain/blockchain.h"

using namespace std;

Blockchain blockchain = Blockchain();
UserDatabase userDB = UserDatabase();

// Adds a new user to the user database and creates a block
int NewUser(string name) {
  int userId = userDB.AddNewUser(name);
  blockchain.GiveNewUserStarterBalance(userId);
  return userId;
}

void InitUsersAndTransactions() {
  // Would be nice if this did deserialisatino at some point
  // Add users to db and give them some money
  NewUser("User 1");
  NewUser("User 2");
  NewUser("User 3");
  blockchain.CreateTransaction(1, 2, 20.37);
  blockchain.CreateTransaction(1, 3, 90);
}

void WaitForUserInput() {
  string spoofVal;
  cout << endl << "Press enter to continue...." << endl;
  cin >> spoofVal;
}

int LoginAsUser() {
  userDB.DisplayUsers();
  cout << "---------------------" << endl << "0: CREATE NEW USER" << endl << endl;

  while (true) {
    int userId;
    cout << "Login As: ";
    cin >> userId;

    // make sure it is a valid number
    if (userId == 0) {
      string uname;
      cout << "Enter a Username: ";
      cin >> uname;
      cout << endl;
      return NewUser(uname);
    }
    else if (userId > 0 && userId <= userDB.Size()) {
      cout << endl;
      return userId;
    }
    else
      cout << "Please enter a valid user ID!" << endl << endl;
  }
}

int main(int argc, char const *argv[]) {
  InitUsersAndTransactions();
  // SPLASH
  cout << endl
    << "Encrypted Ledger Interactive Menu" << endl
    << "By Zak Dowsett" << endl
    << "Version: 0.2.0" << endl
    << "https://github.com/ZakDaMack/FYP-EncryptedLedger" << endl
    << endl;

  // Login as a user
  int currentUser = LoginAsUser();

  // Go to main UI menu
  bool quitting = false;
  while (!quitting) { // repeat until quit is chosen
    // UI Menu
    cout << "Encrypted Ledger Interactive Menu" << endl
      << "---------------------" << endl
      << "0: Quit Application" << endl
      << "1: Logout" << endl
      << "2: Create a New Transaction" << endl
      << "3: View a Single Block" << endl
      << "4: View Entire Blockchain" << endl
      << "5: View Users" << endl << endl;

    int option;
    cout << "Please Enter a Value: ";
    cin >> option;

    // go through the different options
    switch (option) {
      case 0:
        quitting = true;
        break;

      case 1:
        currentUser = LoginAsUser();
        break;

      case 2:
        {
          double amount;
          cout << "Amount to Send: ";
          cin >> amount;
          double recipId;
          cout << "Recipient (User ID): ";
          cin >> recipId;
          int blockId = blockchain.CreateTransaction(currentUser, recipId, amount);
          cout << "Transaction Successful! Your block ID is: " << blockId << endl << endl;
        }
        break;

      case 3:
        {
          cout << "Enter Block ID: ";
          int block;
          cin >> block;
          blockchain.DisplayBlock(block);
          //WaitForUserInput();
        }
        break;

      case 4:
        blockchain.DisplayChain();
        //WaitForUserInput();
        break;

      case 5:
        userDB.DisplayUsers();
	      cout << endl;
        //WaitForUserInput();
        break;

      default:
        cout << "Please enter a valid option!" << endl << endl;
        break;
    }
  }

  cout << "GOODBYE!!!" << endl;
  return 0;
}
