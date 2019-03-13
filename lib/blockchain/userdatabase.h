#pragma once
#ifndef USERDATABASE_H
#include <vector>
#include <iterator>
#include <stdio.h> //C lib
#include <iostream> //C++ lib
#include "../tfhe/encryptionInterface.h"
#define USERDATABASE_H

using namespace std;

class User {
public:
	int ID;
	string Name;
	string PrivateKeyPath;
	string CloudKeyPath;

	User(int id, string name);
};

class UserDatabase {
vector<User> UserList;

void Add(User user);

public:
	UserDatabase();
	int AddNewUser(string name);
	int Size();
	User GetUser(int id);
	void DisplayUsers();
};

#endif
