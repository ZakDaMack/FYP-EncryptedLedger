#pragma once
#ifndef BLOCKCHAIN_H
#include <vector>
#include <iterator>
#include "block.h"
#include "../tfhe/encryptionInterface.h"
#define BLOCKCHAIN_H

using namespace std;

class Blockchain {
private:
	vector<Block> Chain;

	void AddBlock(Block block);
	Block GetBlock(int id);

public:
	Blockchain();
	void GenerateGenesisBlock();
	void InitNewUserBalance(int userId, string newBalancePath);
	string GetLatestBalance(int userId);
	int CreateTransaction(int idSender, int idRecipient, double transactionAmount, string senderCloudPath, string recipientCloudPath);
	void DisplayBlock(int id);
	void DisplayChain();
};

#endif