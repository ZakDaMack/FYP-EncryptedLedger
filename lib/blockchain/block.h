#pragma once
#ifndef BLOCK_H
#include <chrono>
#include <sstream>
#include <stdio.h> //C lib
#include <iostream> //C++ lib
#include "../sha256/sha256.h"
#define BLOCK_H

using namespace std;

class Block  {
private:
  int ID;
	// Transaction information
	string TransactionDescription;
	int RecipientId;
	int SenderId;
	double Amount;
	double SenderBalance;
	double RecipientBalance;
	// End transaction information
	long CreationTime;
	string PrevHash;
	string Hash;

	void CommitTransaction(double oldSenderBalance, double oldRecipientBalance);
	void HashBlock();
	long GetCurrentTime();

public:
	Block(int id, string transactionDesc, int recipientId, int senderId, double transactionAmount, double oldSenderBalance, double oldRecipientBalance, string prevHash);
	void DisplayBlockContents();

 	int GetID();
 	int GetSenderID();
 	double GetSenderBalance();
 	int GetRecipientID();
 	double GetRecipientBalance();
 	string GetHash();
};

#endif
