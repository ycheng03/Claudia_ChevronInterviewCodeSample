#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

class Account; // forward declaration


class User {
private:
    string name;
    string address;
    Account* account;
    string username;
    string password;

public:
    User(string name, string address) {
        this->name = name;
        this->address = address;
        this->account = nullptr; // initialize the account pointer to null
        this->username = "";
        this->password = "";
    }

    // Getters and setters for name and address
    void setName(string name) {
        this->name = name;
    }

    string getName() const {
        return name;
    }

    void setAddress(string address) {
        this->address = address;
    }

    string getAddress() const {
        return address;
    }

    // Method for managing the account
    Account* getAccount() const {
        return account;
    }

    void addAccount(Account* account) {
    this->account = account;
    }

    // Methods for user authentication
    bool authenticate(string username, string password) const {
        return (this->username == username && this->password == password);
    }

    void setUsername(string username) {
        this->username = username;
    }

    void setPassword(string password) {
        this->password = password;
    }
};



class Transaction {
private:
    string type;
    double amount;
    string date;

public:
    Transaction(string t, double a, string d)
        : type(t), amount(a), date(d) {}

    string getType() const {
        return type;
    }

    double getAmount() const {
        return amount;
    }

    string getDate() const {
        return date;
    }
};




class Account {
private:
    int accountNumber;
    double balance;
    double interestRate;
    vector<Transaction> transactions;
    User* owner;

public:
    Account(int accNum, double bal, double intRate, User* own)
        : accountNumber(accNum), balance(bal), interestRate(intRate), owner(own) {}

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount, "today"));
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            transactions.push_back(Transaction("Withdrawal", amount, "today"));
        } else {
            throw std::logic_error("Insufficient balance");
        }
    }

    void transfer(Account& other, double amount) {
        if (balance >= amount) {
            balance -= amount;
            other.balance += amount;
            transactions.push_back(Transaction("Transfer to " + to_string(other.getAccountNumber()), amount, "today"));
            other.transactions.push_back(Transaction("Transfer from " + to_string(accountNumber), amount, "today"));
        } else {
            throw std::logic_error("Insufficient balance");
        }
    }

    void viewTransactions() const {
        for (const Transaction& t : transactions) {
            cout << t.getType() << " " << t.getAmount() << " on " << t.getDate() << endl;
        }
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    void setAccountNumber(int newAccountNumber) {
        accountNumber = newAccountNumber;
    }

    double getBalance() const {
        return balance;
    }

    User* getOwner() const {
        return owner;
    }

    void addInterest() {
        balance *= (1 + interestRate);
        transactions.push_back(Transaction("Interest added", balance * interestRate, "today"));
    }

    vector<Transaction> getTransactions() const {
        return transactions;
    }

    void setTransactions(const vector<Transaction>& newTransactions) {
        transactions = newTransactions;
    }

    double getInterestRate() const {
        return interestRate;
    }

    void setInterestRate(double newInterestRate) {
        interestRate = newInterestRate;
    }

    void setBalance(double newBalance) {
        balance = newBalance;
    }

    void setOwner(User* newOwner) {
        owner = newOwner;
    }

};




class BankingSystem {
private:
    unordered_map<string, User*> users; // Hash table to store User objects

public:
    void addUser(string name, string address, double initialDeposit) {
        User* newUser = new User(name, address);
        Account* newAccount = new Account(1, initialDeposit, 0.0, newUser);
        newUser->addAccount(newAccount);
        users[name] = newUser;
    }

    double getBalance(string name) {
        User* user = users[name];
        Account* account = user->getAccount();
        return account->getBalance();
    }

    void viewTransactions(string name) {
        User* user = users[name];
        Account* account = user->getAccount();
        account->viewTransactions();
    }

    void deposit(string name, double amount) {
        User* user = users[name];
        Account* account = user->getAccount();
        account->deposit(amount);
    }

    void withdraw(string name, double amount) {
        User* user = users[name];
        Account* account = user->getAccount();
        account->withdraw(amount);
    }

    void transfer(string senderName, string receiverName, double amount) {
    User* sender = users[senderName];
    Account* senderAccount = sender->getAccount();
    User* receiver = users[receiverName];
    Account* receiverAccount = receiver->getAccount();
    senderAccount->transfer(*receiverAccount, amount);
}


    void addInterest(double interestRate) {
        for (auto const& [name, user] : users) {
            Account* account = user->getAccount();
            double balance = account->getBalance();
            double interest = balance * interestRate;
            account->deposit(interest);
        }
    }

    void saveUserData() {
        ofstream file("userData.txt");
        if (!file) {
            cerr << "Error: could not open file" << endl;
            return;
        }

        for (const auto& [name, user] : users) {
            file << user->getName() << "," << user->getAddress() << "," << user->getAccount()->getAccountNumber() << ","
                 << user->getAccount()->getBalance() << "," << user->getAccount()->getInterestRate() << endl;
        }

        file.close();
    }

    void loadUserData() {
        ifstream file("userData.txt");
        if (!file) {
            cerr << "Error: could not open file" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            istringstream ss(line);
            string name, address, accountNumber, balance, interestRate;
            getline(ss, name, ',');
            getline(ss, address, ',');
            getline(ss, accountNumber, ',');
            getline(ss, balance, ',');
            getline(ss, interestRate, ',');
            addUser(name, address, stod(balance));
            User* user = users[name];
            Account* account = user->getAccount();
            account->setAccountNumber(stoi(accountNumber));
            account->setInterestRate(stod(interestRate));
        }

        file.close();
    }
};



int main() {
    BankingSystem bankingSystem;
    bool exitProgram = false;

    // Load saved user data
    ifstream userDataFile("userData.txt");
    if (userDataFile.is_open()) {
        string line;
        while (getline(userDataFile, line)) {
            stringstream ss(line);
            string name, address;
            double initialDeposit;
            ss >> name >> address >> initialDeposit;
            bankingSystem.addUser(name, address, initialDeposit);
        }
        userDataFile.close();
    }

    // Main menu loop
    while (!exitProgram) {
        cout << "\nWelcome to the banking system! Please select an option:\n";
        cout << "1. Create an account\n";
        cout << "2. View account balance\n";
        cout << "3. View transaction history\n";
        cout << "4. Deposit money\n";
        cout << "5. Withdraw money\n";
        cout << "6. Transfer money\n";
        cout << "7. Add interest\n";
        cout << "8. Exit program\n";

        int choice;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, address;
                double initialDeposit;
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter your address: ";
                getline(cin, address);
                cout << "Enter your initial deposit amount: ";
                cin >> initialDeposit;
                bankingSystem.addUser(name, address, initialDeposit);

                // Save new user data to file
                ofstream userDataFile("userData.txt", ios::app);
                if (userDataFile.is_open()) {
                    userDataFile << name << " " << address << " " << initialDeposit << endl;
                    userDataFile.close();
                } else {
                    cout << "Unable to save user data to file." << endl;
                }

                cout << "Account created successfully!\n";
                break;
            }
            case 2: {
                string name;
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);
                double balance = bankingSystem.getBalance(name);
                cout << fixed << setprecision(2);
                cout << "Your account balance is $" << balance << endl;
                break;
            }
            case 3: {
                string name;
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);
                bankingSystem.viewTransactions(name);
                break;
            }
            case 4: {
                string name;
                double amount;
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter the amount to deposit: ";
                cin >> amount;
                bankingSystem.deposit(name, amount);
                cout << "Deposit successful!\n";
                break;
            }
            case 5: {
                string name;
                double amount;
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter the amount to withdraw: ";
                cin >> amount;
                try {
                    bankingSystem.withdraw(name, amount);
                    cout << "Withdrawal successful!\n";
                } catch (const std::exception& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 6: {
                string senderName;
                string receiverName;
                double amount;
                cout << "Enter the sender's name: ";
                cin.ignore();
                getline(cin, senderName);
                cout << "Enter the receiver's name: ";
                getline(cin, receiverName);
                cout << "Enter the amount to transfer: ";
                cin >> amount;
                try {
                    bankingSystem.transfer(senderName, receiverName, amount);
                    cout << "Transfer successful!\n";
                    } catch (const std::exception& e) {
                        cout << e.what() << endl;
                        }
                        break;
                        }
            case 7: {
                double interestRate;
                cout << "Enter the interest rate (as a decimal): ";
                cin >> interestRate;
                bankingSystem.addInterest(interestRate);
                cout << "Interest added to all accounts!\n";
                break;
                }
            case 8: {
                exitProgram = true;
                cout << "Exiting program. Goodbye!\n";
                break;
                }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
                }
            }
        }
        return 0;
};