#include "blockchain/userdatabase.h"
#include "blockchain/blockchain.h"
#include "tfhe/encryptionInterface.h"

using namespace std;

Blockchain blockchain = Blockchain();
UserDatabase userDB = UserDatabase();

// Adds a new user to the user database and creates a block
int NewUser(string name, double startingBalance) {
  int userId = userDB.AddNewUser(name);
  string balancePath = EncryptBankBalance(startingBalance, userDB.GetUser(userId).PrivateKeyPath);

  blockchain.InitNewUserBalance(userId, balancePath);
  return userId;
}

int CommitTransaction(int senderId, int recipId, double amount) {
  string senderPath = userDB.GetUser(senderId).CloudKeyPath;
  string recipientPath = userDB.GetUser(recipId).CloudKeyPath;
  return blockchain.CreateTransaction(senderId, recipId, amount, senderPath, recipientPath);
}

void VerificationMenu() {
  // UI Menu
  cout << "Verification Menu" << endl
    << "---------------------" << endl
    << "0: Go Back" << endl
    << "1: Verify Block" << endl
    << "2: Verify Entire Chain" << endl
    << "3: Verify User Account Balance" << endl << endl;

  bool stayInMenu = true;

  while (stayInMenu) {

    int option;
    cout << "Please Enter a Value: ";
    cin >> option;

    switch (option) {
      case 0:
        stayInMenu = false;
        break;

      case 1:
        {
          int transactionBlock;
          cout << "Enter a transaction block to verify: ";
          cin >> transactionBlock;
          
          // make sure its valid transaction block
          if (!blockchain.IsTransactionBlock(transactionBlock))
          {
            cout << "Error: Enter a valid transaction block!" << endl << endl;
            break;
          }

          Block b = blockchain.GetBlock(transactionBlock);
          string senderPath = userDB.GetUser(b.GetSenderID()).CloudKeyPath;
          string recipientPath = userDB.GetUser(b.GetRecipientID()).CloudKeyPath;

          bool isVerified = b.GetTransactionAmount() >= 0 
                          && b.GetSenderID() != b.GetRecipientID() 
                          && blockchain.VerifyTransaction(transactionBlock, senderPath, recipientPath);

          if (isVerified)
            cout << "Transaction block " << transactionBlock << " has been validated successfully" << endl << endl;
          else
            cout << "Transaction block " << transactionBlock << " is not a valid block!!!" << endl << endl;  

        }        
        break;

      case 2:
        cout << "Currently Unsupported!" << endl << endl;
        break;

      case 3:
        cout << "Currently Unsupported!" << endl << endl;
        break;

      default:
        cout << "Please enter a valid option!" << endl << endl;
        break;
    }
  }  
}


void InitUsersAndTransactions() {
  // Would be nice if this did deserialisatino at some point
  // Add users to db and give them some money
  cout << "Populating the encrypted ledger with some users!! Please wait..." << endl;
  NewUser("User 1", 200);
  cout << "User 1 with a balance of £200 has been created" << endl;
  NewUser("User 2", 20);
  cout << "User 2 with a balance of £20 has been created" << endl;
  //NewUser("User 3", 51);
  //cout << "User 3 with a balance of £51 has been created" << endl;
  CommitTransaction(1, 2, 20);
  cout << "A transaction of £20 between 1 and 2 has been created" << endl;
  //CommitTransaction(1, 3, 90);
  //cout << "A transaction of £90 between 1 and 3 has been created" << endl;
  cout << "Done!!!" << endl << endl;
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
      double balance;
      cout << "Enter a Starting Balance: ";
      cin >> balance;
      cout << endl;
      return NewUser(uname, balance);
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
  // SPLASH
  cout << endl
    << "Encrypted Ledger Interactive Menu" << endl
    << "By Zak Dowsett" << endl
    << "Version: 1.0.2" << endl
    << "https://github.com/ZakDaMack/FYP-EncryptedLedger" << endl
    << endl;

  InitUsersAndTransactions();

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
      << "3: Verification Menu" << endl
      << "4: View a Single Block" << endl
      << "5: View Entire Blockchain" << endl
      << "6: View Users" << endl
      << "7: View My Balance" << endl << endl;

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
          cout << "Transaction In Progress...." << endl;
          int blockId = CommitTransaction(currentUser, recipId, amount);
          cout << "Transaction Successful! Your block ID is: " << blockId << endl << endl;
        }
        break;
      case 3:
          VerificationMenu();
        break;

      case 4:
        {
          int block;
          cout << "Enter Block ID: ";
          cin >> block;
          blockchain.DisplayBlock(block);
          //WaitForUserInput();
        }
        break;

      case 5:
        blockchain.DisplayChain();
        //WaitForUserInput();
        break;

      case 6:
        userDB.DisplayUsers();
	      cout << endl;
        //WaitForUserInput();
        break;

      case 7:
        cout << "Getting your current balance..." << endl;
        cout << "Your current balance is: £" << 
          ReadBankBalance(blockchain.GetLatestBalance(currentUser),
            userDB.GetUser(currentUser).PrivateKeyPath)
          << endl << endl;
        //viewbalance
        break;

      default:
        cout << "Please enter a valid option!" << endl << endl;
        break;
    }
  }

  cout << "GOODBYE!!!" << endl;
  return 0;
}
