#include "blockchain.h"

Blockchain::Blockchain() {
	GenerateGenesisBlock();
}

int Blockchain::CreateTransaction(int idSender, int idRecipient, double transactionAmount) {
	stringstream descStream;
	descStream << "Transfer of £" << transactionAmount << " from " << idSender << " to " << idRecipient << ".";

	auto latestBlock = next(Chain.end(), -1); // get the last item in the list
	int newBlockId = latestBlock->GetID() + 1;
	AddBlock(Block(newBlockId, descStream.str(), idRecipient, idSender, transactionAmount,
		GetLatestBalance(idRecipient), GetLatestBalance(idSender), latestBlock->GetHash()));
	return newBlockId;
}

double Blockchain::GetLatestBalance(int userId) {
		for (auto it = Chain.rbegin(); it != Chain.rend(); ++it) {
			if (it->GetSenderID() == userId)
				return it->GetSenderBalance();
			if (it->GetRecipientID() == userId)
				return it->GetRecipientBalance();
		}
}

void Blockchain::GiveNewUserStarterBalance(int userId) {
	stringstream descStream;
	descStream << "Adding £500 to new user id: " << userId << ".";

	auto latestBlock = next(Chain.end(), -1); // get the last item in the list
	AddBlock(Block(latestBlock->GetID() + 1, descStream.str(), userId, 0, 0, 500, 0, latestBlock->GetHash()));
}

void Blockchain::DisplayBlock(int id) {
	cout << endl;
	GetBlock(id).DisplayBlockContents();
}

void Blockchain::DisplayChain() {
	cout << endl;
	for (auto it = Chain.begin(); it != Chain.end(); ++it) {
		it->DisplayBlockContents();
	}
	cout << "Chain size: " << Chain.size() << endl << endl;
}

void Blockchain::AddBlock(Block block) {
	Chain.push_back(block);
}

Block Blockchain::GetBlock(int id) {
	for (auto it = Chain.begin(); it != Chain.end(); ++it)
		if (it->GetID() == id)
			return *it;

}

void Blockchain::GenerateGenesisBlock() {
	AddBlock(Block(0, "Genesis Block", 0, 0, 0, 0, 0, ""));
}
