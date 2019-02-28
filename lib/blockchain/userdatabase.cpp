#include "userdatabase.h"

User::User(int id, string name) {
	Name = name;
	ID = id;
}

UserDatabase::UserDatabase() { }

int UserDatabase::AddNewUser(string name) {
	int userId = UserList.size() + 1;
	Add(User(userId, name));
	return userId;
}

User UserDatabase::GetUser(int id) {
	for (auto it = UserList.begin(); it != UserList.end(); ++it) {
		if (it->ID == id) {
			return *it;
		}
	}
}

int UserDatabase::Size() {
	return UserList.size();
}

void UserDatabase::DisplayUsers() {
	cout << endl << "User List" << endl << "---------------------" << endl;
	for (auto it = UserList.begin(); it != UserList.end(); ++it) {
		cout << it->ID << ": " << it->Name << endl;
	}
}

void UserDatabase::Add(User user) {
	UserList.push_back(user);
}
