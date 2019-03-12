#pragma once
#ifndef BLOCKCHAIN_H
#include <vector>
#include <iterator>
#include "block.h"
#define BLOCKCHAIN_H

using namespace std;

class Blockchain {
private:
	vector<Block> Chain;

	void AddBlock(Block block);
	Block GetBlock(int id);
	double GetLatestBalance(int userId);

public:
	Blockchain();
	void GenerateGenesisBlock();
	void GiveNewUserStarterBalance(int userId);
	int CreateTransaction(int idSender, int idRecipient, double transactionAmount);
	void DisplayBlock(int id);
	void DisplayChain();
};

#endif
