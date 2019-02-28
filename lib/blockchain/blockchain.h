#pragma once
#ifndef BLOCKCHAIN_H
#include <list>
#include <iterator>
#include "Block.h"
#define BLOCKCHAIN_H

using namespace std;

class Blockchain {
	list<Block> Chain;

private:
	void AddBlock(Block block);
	Block GetBlock(int id);
	void GenerateGenesisBlock();

public:
	Blockchain();
	void CreateTransaction(int idSender, int idRecipient, double transactionAmount);
	void DisplayBlock(int id);
	void DisplayChain();
};

#endif
