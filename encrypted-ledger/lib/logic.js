/**
* Sample transaction
* @param {encryptedledger.encryptedTransaction} transfer
* @transaction
*/

function SecureTransfer(transfer) {
    var factory = getFactory();

    transfer.from.balance -= transfer.transactionAmount;
    transfer.to.balance += transfer.transactionAmount;

    var result = getAssetRegistry('encryptedledger.Account')
        .then (function (registry) {
            return registry.update(transfer.from);
        })
        .then (function () {
            return getAssetRegistry('encryptedledger.Account');
        })
        .then(function (registry) {
            return registry.update(transfer.to);
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
        newEvent.toId = transfer.to;
        newEvent.fromId = transfer.from;
        newEvent.detail = "no idea why it failed";
        emit(newEvent);
    }

    return result;
}
