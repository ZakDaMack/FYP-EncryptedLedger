#pragma once
#ifndef BLOCKCHAIN_H
#include <list>
#include <iterator>
#include "block.h"
#define BLOCKCHAIN_H

using namespace std;

class Blockchain {
	list<Block> Chain;

private:
	void AddBlock(Block block);
	Block GetBlock(int id);
	void GenerateGenesisBlock();
	double GetLatestBalance(int userId);

public:
	Blockchain();
	void GiveNewUserStarterBalance(int userId);
	int CreateTransaction(int idSender, int idRecipient, double transactionAmount);
	void DisplayBlock(int id);
	void DisplayChain();
};

#endif
