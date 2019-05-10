#pragma once
#ifndef BLOCK_H
#include <chrono>
#include <sstream>
#include <stdio.h> //C lib
#include <iostream> //C++ lib
#include "../sha256/sha256.h"
#define BLOCK_H

using namespace std;

class Block {
private:
  int ID;
	// Transaction information
	string TransactionDescription;
	int RecipientId;
	int SenderId;
	double Amount;
	string SenderBalancePath;
	string RecipientBalancePath;
	// End transaction information
	long CreationTime;
	string PrevHash;
	string Hash;

	void HashBlock();
	long GetCurrentTime();

public:
	Block(int id, string transactionDesc, int recipientId, int senderId, double transactionAmount, string recipientBalance, string senderBalance, string prevHash);
	void DisplayBlockContents();
 	int GetID();
 	int GetSenderID();
 	string GetSenderBalancePath();
 	int GetRecipientID();
 	string GetRecipientBalancePath();
 	string GetHash();
	double GetTransactionAmount();
};

#endif
