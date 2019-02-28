#pragma once
#ifndef USERDATABASE_H
#include <list>
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
list<User> UserList;

private:
	void Add(User user);

public:
	UserDatabase();
	void AddNewUser(string name);
	User GetUser(int id);
	void DisplayUsers();
};

#endif
