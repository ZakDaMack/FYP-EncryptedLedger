/**
* Sample transaction
* @param {encryptedledger.encryptedTransaction} transfer
* @transaction
*/

async function SecureTransfer(transfer) {
    var factory = getFactory();

    transfer.from.balance -= transfer.amount;
    transfer.to.balance += transfer.amount;

    var result = getAssetRegistry('encryptedledger.Account')
        .then( function(assetRegistry) {
            var toSucc = assetRegistry.update(transfer.to);
            var fromSucc = assetRegistry.update(transfer.from);
            return toSucc && fromSucc; // make sure both updates were successful
        });

    // Create an event to show a transaction has occured
    if (result) {
        var newEvent = factory.newEvent('encryptedledger', 'SuccessfulTransactionEvent');
        newEvent.accountToId = transfer.to;
        newEvent.accountFromId = transfer.from;
        newEvent.detail = "no idea why it worked";
        emit(newEvent);
    }
    else {
        var newEvent = factory.newEvent('encryptedledger', 'FailedTransactionEvent');
        newEvent.accountToId = transfer.to;
        newEvent.accountFromId = transfer.from;
        newEvent.detail = "no idea why it worked";
        emit(newEvent);
    }

    return result;
}
