#pragma once
#ifndef USERDATABASE_H
#include <vector>
#include <iterator>
#include <stdio.h> //C lib
#include <iostream> //C++ lib
#define USERDATABASE_H

using namespace std;

class User {
public:
	int ID;
	string Name;

	User(int id, string name);
};

class UserDatabase {
vector<User> UserList;

private:
	void Add(User user);

public:
	UserDatabase();
	int AddNewUser(string name);
	int Size();
	User GetUser(int id);
	void DisplayUsers();
};

#endif
