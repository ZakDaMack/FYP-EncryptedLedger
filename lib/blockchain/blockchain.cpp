#include "blockchain.h"

Blockchain::Blockchain() {
	GenerateGenesisBlock();
}

int Blockchain::CreateTransaction(int idSender, int idRecipient, double transactionAmount, string senderCloudPath, string recipientCloudPath) {
	stringstream descStream;
	descStream << "Transfer of £" << transactionAmount << " from " << idSender << " to " << idRecipient << ".";

	auto latestBlock = next(Chain.end(), -1); // get the last item in the list
	int newBlockId = latestBlock->GetID() + 1;

	// Do the transaction
	string senderBalance = ComputeSenderTransaction(transactionAmount, GetLatestBalance(idSender), senderCloudPath);
	string receiverBalance = ComputeReceiverTransaction(transactionAmount, GetLatestBalance(idRecipient), recipientCloudPath);

	// Create a block with this information
	AddBlock(Block(newBlockId, descStream.str(), idRecipient, idSender, transactionAmount,
		receiverBalance, senderBalance, latestBlock->GetHash()));
	return newBlockId;
}

string Blockchain::GetLatestBalance(int userId) {
		for (auto it = Chain.rbegin(); it != Chain.rend(); ++it) {
			if (it->GetSenderID() == userId)
				return it->GetSenderBalancePath();
			if (it->GetRecipientID() == userId)
				return it->GetRecipientBalancePath();
		}
}

void Blockchain::InitNewUserBalance(int userId, string newBalance) {
	stringstream descStream;
	descStream << "A new user and their balance has been added to the chain. User ID: " << userId << ".";

	auto latestBlock = next(Chain.end(), -1); // get the last item in the list
	AddBlock(Block(latestBlock->GetID() + 1, descStream.str(), userId, 0, 0, newBalance, "", latestBlock->GetHash()));
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
	AddBlock(Block(0, "Genesis Block", 0, 0, 0, "", "", ""));
}
