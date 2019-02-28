#include "blockchain.h"

Blockchain::Blockchain() {
	GenerateGenesisBlock();
}

void Blockchain::CreateTransaction(int idSender, int idRecipient, double transactionAmount) {
	double latestRecipientBalance, latestSenderBalance;

	// reverse through loop
		for (auto it = Chain.rbegin(); it != Chain.rend(); ++it) {
			if (latestSenderBalance == NULL && it->GetSenderID() == idSender)
				latestSenderBalance = it->GetSenderBalance();
			if (latestRecipientBalance == NULL && it->GetRecipientID())
				latestRecipientBalance = it->GetRecipientBalance();
		}

	auto latestBlock = next(Chain.end(), -1); // get the last item in the list
	AddBlock(Block(latestBlock->GetID() + 1, idRecipient, idSender, transactionAmount,
		latestRecipientBalance, latestSenderBalance, latestBlock->GetHash()));
}

void Blockchain::GiveNewUserStarterBalance(int userId, ) {

	// reverse through loop
		for (auto it = Chain.rbegin(); it != Chain.rend(); ++it) {
			if (latestSenderBalance == NULL && it->GetSenderID() == idSender)
				latestSenderBalance = it->GetSenderBalance();
			if (latestRecipientBalance == NULL && it->GetRecipientID())
				latestRecipientBalance = it->GetRecipientBalance();
		}

	auto latestBlock = next(Chain.end(), -1); // get the last item in the list
	AddBlock(Block(latestBlock->GetID() + 1, idRecipient, idSender, transactionAmount,
		latestRecipientBalance, latestSenderBalance, latestBlock->GetHash()));
}

void Blockchain::DisplayBlock(int id) {
	GetBlock(id).DisplayBlockContents();
}

void Blockchain::DisplayChain() {
	for (auto it = Chain.begin(); it != Chain.end(); ++it) {
		it->DisplayBlockContents();
	}
	cout << "Chain size: " << Chain.size() << endl;
}

void Blockchain::AddBlock(Block block) {
	Chain.push_back(block);
}

Block Blockchain::GetBlock(int id) {
	for (auto it = Chain.begin(); it != Chain.end(); ++it) {
		if (it->GetID() == id) {
			return *it;
		}
	}
}

void Blockchain::GenerateGenesisBlock() {
	AddBlock(Block(0, 0, 0, 0, 0, 0, "0"));
}


int main() {
	// test that the genesis block can be created properly
	cout << "working.." << endl;
	Blockchain c = Blockchain();
	c.CreateTransaction(0, 0, 0);
	c.CreateTransaction(0, 0, 0);
	c.CreateTransaction(0, 0, 0);
	cout << "printing.." << endl;
	c.DisplayChain();
	c.DisplayBlock(2);
	return 0;
}
