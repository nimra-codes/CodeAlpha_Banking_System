
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>
#include <algorithm>
using namespace std;

// ================= TRANSACTION CLASS =================
class Transaction {
private:
    int transactionID;
    string type;
    string fromAccount;
    string toAccount;
    double amount;
    string details;
public:
    Transaction(int id, string t, string from, string to,
                double amt, string info)
        : transactionID(id), type(t), fromAccount(from),
          toAccount(to), amount(amt), details(info) {}

    void display() const {
        cout << left << setw(8) << transactionID
             << setw(15) << type
             << setw(14) << fromAccount
             << setw(14) << toAccount
             << setw(12) << fixed << setprecision(2)
             << amount << details << '\n';
    }
    bool matches(const string& number) const {
    return fromAccount == number ||
           toAccount == number;
}
};

// ================= CUSTOMER CLASS =================
class Customer {
private:
    int customerID;
    string name;
    string phone;
    string address;

public:
    Customer(int id, string n, string p, string a)
        : customerID(id), name(n), phone(p), address(a) {}

    int getID() const { return customerID; }
    string getName() const { return name; }

    void update(string n, string p, string a) {
        name = n;
        phone = p;
        address = a;
    }

    void display() const {
        cout << "\nCustomer ID: " << customerID
             << "\nName: " << name
             << "\nPhone: " << phone
             << "\nAddress: " << address << '\n';
    }
};

// ================= ACCOUNT CLASS =================
class Account {
private:
    string accountNumber;
    int customerID;
    double balance;

public:
    Account(string number, int id, double initial)
        : accountNumber(number), customerID(id),
          balance(initial) {}

    string getNumber() const { return accountNumber; }
    int getCustomerID() const { return customerID; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance)
            return false;

        balance -= amount;
        return true;
    }

    void display() const {
        cout << "\nAccount Number: " << accountNumber
             << "\nCustomer ID: " << customerID
             << "\nBalance: Rs. " << fixed
             << setprecision(2) << balance << '\n';
    }
};

// ================= BANKING SYSTEM =================
class BankingSystem {
private:
    vector<Customer> customers;
    vector<Account> accounts;
    vector<Transaction> transactions;

    int nextCustomerID = 1;
    int nextAccountID = 100001;
    int nextTransactionID = 1;

    Customer* findCustomer(int id) {
        for (auto& c : customers)
            if (c.getID() == id)
                return &c;
        return nullptr;
    }

    Account* findAccount(string number) {
        for (auto& a : accounts)
            if (a.getNumber() == number)
                return &a;
        return nullptr;
    }

    void record(string type, string from, string to,
                double amount, string details) {
        transactions.emplace_back(
            nextTransactionID++, type, from, to,
            amount, details
        );
    }

    double readAmount() {
        double amount;
        while (true) {
            cout << "Enter amount (Rs.): ";
            string line;
            getline(cin, line);
            stringstream ss(line);
            char extra;

            if (ss >> amount && !(ss >> extra) &&
                amount > 0 && amount <= 1000000000000.0) {
                return amount;
            }
            cout << "Invalid amount. Please try again.\n";
        }
    }

public:
    // Create customer
    void createCustomer() {
        string name, phone, address;

        cout << "\nEnter customer name: ";
        getline(cin, name);
        cout << "Enter phone number: ";
        getline(cin, phone);
        cout << "Enter address: ";
        getline(cin, address);

        if (name.empty() || phone.empty()) {
            cout << "Name and phone are required.\n";
            return;
        }

        customers.emplace_back(
            nextCustomerID++, name, phone, address
        );

        cout << "\nCustomer created successfully!"
             << "\nCustomer ID: "
             << customers.back().getID() << '\n';
    }

    // Update customer
    void updateCustomer() {
        int id;
        cout << "Enter customer ID: ";
        if (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID.\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Customer* c = findCustomer(id);
        if (!c) {
            cout << "Customer not found.\n";
            return;
        }

        string name, phone, address;
        cout << "New name: ";
        getline(cin, name);
        cout << "New phone: ";
        getline(cin, phone);
        cout << "New address: ";
        getline(cin, address);

        if (name.empty() || phone.empty()) {
            cout << "Name and phone are required.\n";
            return;
        }

        c->update(name, phone, address);
        cout << "Customer updated successfully.\n";
    }

    // Display all customers
    void showCustomers() const {
        if (customers.empty()) {
            cout << "No customers registered.\n";
            return;
        }

        cout << "\n========== CUSTOMERS ==========\n";
        for (const auto& c : customers)
            c.display();
    }

    // Open account
    void openAccount() {
        int id;
        cout << "Enter customer ID: ";
        if (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID.\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!findCustomer(id)) {
            cout << "Customer not found. Create customer first.\n";
            return;
        }

        double initial;
        cout << "Enter initial deposit (Rs., 0 allowed): ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        char extra;

        if (!(ss >> initial) || (ss >> extra) ||
            initial < 0 || initial > 1000000000000.0) {
            cout << "Invalid initial deposit.\n";
            return;
        }

        string number = to_string(nextAccountID++);
        accounts.emplace_back(number, id, initial);

        cout << "\nAccount opened successfully!"
             << "\nAccount Number: " << number << '\n';

        if (initial > 0) {
            record("Deposit", "Cash", number,
                   initial, "Initial deposit");
        }
    }

    // Display all accounts
    void showAccounts() const {
        if (accounts.empty()) {
            cout << "No accounts available.\n";
            return;
        }

        cout << "\n========== BANK ACCOUNTS ==========\n";
        cout << left << setw(16) << "Account No."
             << setw(14) << "Customer ID"
             << "Balance (Rs.)\n";
        cout << "------------------------------------------\n";

        for (const auto& a : accounts) {
            cout << left << setw(16) << a.getNumber()
                 << setw(14) << a.getCustomerID()
                 << fixed << setprecision(2)
                 << a.getBalance() << '\n';
        }
    }

    // Account information
    void accountDetails() {
        string number;
        cout << "Enter account number: ";
        getline(cin, number);

        Account* a = findAccount(number);
        if (!a) {
            cout << "Account not found.\n";
            return;
        }

        a->display();
        Customer* c = findCustomer(a->getCustomerID());
        if (c) {
            cout << "\nAccount Holder:\n";
            c->display();
        }
    }

    // Deposit money
    void depositMoney() {
        string number;
        cout << "Enter account number: ";
        getline(cin, number);

        Account* a = findAccount(number);
        if (!a) {
            cout << "Account not found.\n";
            return;
        }

        double amount = readAmount();
        if (a->getBalance() + amount > 1000000000000.0) {
            cout << "Balance limit exceeded.\n";
            return;
        }

        a->deposit(amount);
        record("Deposit", "Cash", number, amount,
               "Cash deposit");

        cout << "Deposit successful!\n"
             << "New balance: Rs. "
             << fixed << setprecision(2)
             << a->getBalance() << '\n';
    }

    // Withdraw money
    void withdrawMoney() {
        string number;
        cout << "Enter account number: ";
        getline(cin, number);

        Account* a = findAccount(number);
        if (!a) {
            cout << "Account not found.\n";
            return;
        }

        double amount = readAmount();
        if (!a->withdraw(amount)) {
            cout << "Insufficient balance.\n";
            return;
        }

        record("Withdrawal", number, "Cash",
               amount, "Cash withdrawal");

        cout << "Withdrawal successful!\n"
             << "Remaining balance: Rs. "
             << fixed << setprecision(2)
             << a->getBalance() << '\n';
    }

    // Transfer funds
    void transferMoney() {
        string from, to;
        cout << "Enter sender account number: ";
        getline(cin, from);
        cout << "Enter receiver account number: ";
        getline(cin, to);

        if (from == to) {
            cout << "Cannot transfer to the same account.\n";
            return;
        }

        Account* sender = findAccount(from);
        Account* receiver = findAccount(to);

        if (!sender || !receiver) {
            cout << "One or both accounts not found.\n";
            return;
        }

        double amount = readAmount();

        if (sender->getBalance() < amount) {
            cout << "Insufficient balance.\n";
            return;
        }

        if (receiver->getBalance() + amount >
            1000000000000.0) {
            cout << "Receiver balance limit exceeded.\n";
            return;
        }

        sender->withdraw(amount);
        receiver->deposit(amount);

        record("Transfer", from, to,
               amount, "Fund transfer");

        cout << "Transfer successful!\n"
             << "Sender balance: Rs. "
             << fixed << setprecision(2)
             << sender->getBalance() << '\n'
             << "Receiver balance: Rs. "
             << receiver->getBalance() << '\n';
    }

    // Transaction history
    void transactionHistory() {
        if (transactions.empty()) {
            cout << "No transactions available.\n";
            return;
        }

        string number;
        cout << "Enter account number: ";
        getline(cin, number);

        if (!findAccount(number)) {
            cout << "Account not found.\n";
            return;
        }

        cout << "\n========== TRANSACTION HISTORY ==========\n";
        cout << left << setw(8) << "ID"
             << setw(15) << "Type"
             << setw(14) << "From"
             << setw(14) << "To"
             << setw(12) << "Amount"
             << "Details\n";
        cout << "------------------------------------------------"
             << "----------------\n";

        bool found = false;
        for (const auto& t : transactions) {
            // Transaction display is filtered below by
            // storing the account number in its text fields.
            // Use the account-specific check method instead.
        }

        // Print matching records using transaction data
        // through the helper below.
        showAccountTransactions(number, found);

        if (!found)
            cout << "No transactions for this account.\n";
    }

    void showAccountTransactions(const string& number,
                                bool& found) const {
        for (const auto& t : transactions) {
            // Access transaction account fields via matches()
            if (t.matches(number)) {
                t.display();
                found = true;
            }
        }
    }

    // Main menu
    void menu() {
        while (true) {
            cout << "\n====================================\n";
            cout << "       BANKING MANAGEMENT SYSTEM\n";
            cout << "====================================\n";
            cout << "1. Create Customer\n";
            cout << "2. Update Customer\n";
            cout << "3. View All Customers\n";
            cout << "4. Open Bank Account\n";
            cout << "5. View All Accounts\n";
            cout << "6. View Account Details\n";
            cout << "7. Deposit Money\n";
            cout << "8. Withdraw Money\n";
            cout << "9. Transfer Funds\n";
            cout << "10. Transaction History\n";
            cout << "0. Exit\n";
            cout << "------------------------------------\n";
            cout << "Enter choice: ";

            int choice;
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
                case 1: createCustomer(); break;
                case 2: updateCustomer(); break;
                case 3: showCustomers(); break;
                case 4: openAccount(); break;
                case 5: showAccounts(); break;
                case 6: accountDetails(); break;
                case 7: depositMoney(); break;
                case 8: withdrawMoney(); break;
                case 9: transferMoney(); break;
                case 10: transactionHistory(); break;
                case 0:
                    cout << "Thank you for using our bank!\n";
                    return;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        }
    }
};

int main() {
    BankingSystem bank;
    bank.menu();
    return 0;
}