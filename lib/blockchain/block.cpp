#include "block.h"

void Block::CommitTransaction(double oldSenderBalance, double oldRecipientBalance) {
	SenderBalance = oldSenderBalance - Amount;
	RecipientBalance = oldRecipientBalance + Amount;
	// Get latest blocks containing ID, or will i need to import?
}

void Block::HashBlock() {
	stringstream ss;
	ss << ID << TransactionDescription <<RecipientId << SenderId << Amount
		<< SenderBalance << RecipientBalance << CreationTime << PrevHash;
	Hash = sha256(ss.str());
}

long Block::GetCurrentTime() {
	return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

Block::Block(int id, string transactionDesc, int recipientId, int senderId, double transactionAmount, double oldRecipientBalance, double oldSenderBalance, string prevHash) {
	ID = id;
	TransactionDescription = transactionDesc;
	RecipientId = recipientId;
	SenderId = senderId;
	Amount = transactionAmount;
	PrevHash = prevHash;
	CreationTime = GetCurrentTime();
	CommitTransaction(oldSenderBalance, oldRecipientBalance);
	HashBlock(); // Hashing needs to be the last thing to be done
}

int Block::GetID() {
	return ID;
}

string Block::GetHash() {
	return Hash;
}

int Block::GetSenderID() {
	return SenderId;
}

double Block::GetSenderBalance() {
	return SenderBalance;
}

int Block::GetRecipientID() {
	return RecipientId;
}

double Block::GetRecipientBalance() {
	return RecipientBalance;
}

void Block::DisplayBlockContents() {
	cout << "Block " << ID << endl
	<< "-------------------------" << endl
	<< "Transaction Description: " << TransactionDescription << endl
	<< "Recipient Id: " << RecipientId << endl
	<< "Sender Id: " << SenderId << endl
	<< "Recipient Balance: " << RecipientBalance << endl
	<< "Sender Balance: " << SenderBalance << endl
	<< "Transaction Amount: " << Amount << endl
	<< "Creation Time: " << CreationTime << endl
	<< "Previous Hash: " << PrevHash << endl
	<< "Block Hash: " << Hash << endl << endl;
}
