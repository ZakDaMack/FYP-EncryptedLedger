import {Asset} from './org.hyperledger.composer.system';
import {Participant} from './org.hyperledger.composer.system';
import {Transaction} from './org.hyperledger.composer.system';
import {Event} from './org.hyperledger.composer.system';
// export namespace encryptedledger{
   export class User extends Participant {
      participantKey: string;
      userName: string;
   }
   export class Account extends Asset {
      accountKey: string;
      publicKeyPath: string;
      balancePath: string;
      accountHolder: User;
   }
   export class encryptedTransaction extends Transaction {
      from: Account;
      to: Account;
      transactionAmount: number;
   }
   export class SuccessfulTransactionEvent extends Event {
      toId: string;
      fromId: string;
      detail: string;
   }
   export class FailedTransactionEvent extends Event {
      toId: string;
      fromId: string;
      detail: string;
   }
// }
