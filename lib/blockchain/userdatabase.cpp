#include "userdatabase.h"

User::User(int id, string name) {
	Name = name;
	ID = id;
}

UserDatabase::UserDatabase() { }

void UserDatabase::AddNewUser(string name) {
	Add(User(UserList.size() + 1, name));
}

User UserDatabase::GetUser(int id) {
	for (auto it = UserList.begin(); it != UserList.end(); ++it) {
		if (it->ID == id) {
			return *it;
		}
	}
}

void UserDatabase::DisplayUsers() {
	cout << "User List" << endl << "---------------------" << endl;
	for (auto it = UserList.begin(); it != UserList.end(); ++it) {
		cout << it->ID << ": " << it->Name << endl;
	}
}

void UserDatabase::Add(User user) {
	UserList.push_back(user);
}
