#include "block.h"

void Block::HashBlock() {
	stringstream ss;
	ss << ID << TransactionDescription <<RecipientId << SenderId << Amount
		<< SenderBalancePath << RecipientBalancePath << CreationTime << PrevHash;
	Hash = sha256(ss.str());
}

long Block::GetCurrentTime() {
	return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

Block::Block(int id, string transactionDesc, int recipientId, int senderId, double transactionAmount, string recipientBalance, string senderBalance, string prevHash) {
	ID = id;
	TransactionDescription = transactionDesc;
	RecipientId = recipientId;
	SenderId = senderId;
	Amount = transactionAmount;
	PrevHash = prevHash;
	CreationTime = GetCurrentTime();
	SenderBalancePath = senderBalance;
	RecipientBalancePath = recipientBalance;
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

string Block::GetSenderBalancePath() {
	return SenderBalancePath;
}

int Block::GetRecipientID() {
	return RecipientId;
}

string Block::GetRecipientBalancePath() {
	return RecipientBalancePath;
}

double Block::GetTransactionAmount() {
	return Amount;
}

void Block::DisplayBlockContents() {
	cout << "Block " << ID << endl
	<< "-------------------------" << endl
	<< "Transaction Description: " << TransactionDescription << endl
	<< "Recipient Id: " << RecipientId << endl
	<< "Sender Id: " << SenderId << endl
	<< "Recipient Balance Path: " << RecipientBalancePath << endl
	<< "Sender Balance Path: " << SenderBalancePath << endl
	<< "Transaction Amount: " << Amount << endl
	<< "Creation Time: " << CreationTime << endl
	<< "Previous Hash: " << PrevHash << endl
	<< "Block Hash: " << Hash << endl << endl;
}
