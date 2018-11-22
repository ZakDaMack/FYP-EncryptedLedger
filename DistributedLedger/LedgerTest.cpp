
using namespace std;

struct Data {
    public:
        int64_t transaction_amount;
        string to_Id;
        string from_Id;
        time timeSent;
}

struct Ledger {
    public:
        int index;
        Data transaction_data;

        Ledger CreateGenesis();
}

struct DistributedLedger {
public:
    vector<Ledger> Ledgers;

}





struct User {
    public:
        string userId;
        int64_t balance;

        User User();
}

struct UserList {
    public:
        vector<User> userList;
        userList userList();

        user newUser();
        bool isIdUnique(string id);
}
