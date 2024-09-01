#include <iostream>
#include <vector>

class Transaction {
public:
    Transaction(int id, double amount) : id(id), amount(amount) {}

    int getId() const {
        return id;
    }

    double getAmount() const {
        return amount;
    }

private:
    int id;
    double amount;
};

class TransactionManager {
public:
    void addTransaction(const Transaction& transaction) {
        transactions.push_back(transaction);
    }

    void printTransactions() const {
        for (const auto& transaction : transactions) {
          std::cout << "Transaction ID: " << transaction.getId()
                    << ", Amount: " << transaction.getAmount() << '\n';
        }
    }

private:
    std::vector<Transaction> transactions;
};

int main() {
    TransactionManager manager;

    Transaction t1(1, 100.0);
    Transaction t2(2, 200.0);
    Transaction t3(3, 300.0);

    manager.addTransaction(t1);
    manager.addTransaction(t2);
    manager.addTransaction(t3);
 
    manager.printTransactions();

    return 0;
}
