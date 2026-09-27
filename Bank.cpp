#include <iostream>
#include <vector>
using namespace std;

string ud = "undefined";

class Account {
    string name;
    string accountType;
    string address;
    string phoneNumber;
    int accountNumber;
    double balance;

    static int totalAccount;
    static double totalBalance;

public:
    Account(string name = ud, string accountType = ud,
            string address = ud, string phoneNumber = ud,
            int accountNumber = 0, double balance = 0)
    {
        this->name = name;
        this->accountType = accountType;
        this->address = address;
        this->phoneNumber = phoneNumber;
        this->accountNumber = accountNumber;
        this->balance = balance;

        totalAccount++;
        totalBalance += balance;
    }

    void display() {
        cout << "Name: " << name << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Bank Balance: " << balance << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Address: " << address << endl;
    }

    void updateBalance(double amount, string purpose) {
        if(amount < 0) amount = -amount;

        if(purpose == "withdrawal") {
            if(amount <= balance) {
                this->balance -= amount;
                totalBalance -= amount;
            }
            else {
                cout << "You have not enough money to withdrawal" << endl;
            }
        }
        else if(purpose == "deposit") {
            this->balance += amount;
            totalBalance += amount;
        }
        else {
            cout << "Please enter a valid type...!" << endl;
        }
    }
    
    static int getTotalAccount() {
        return totalAccount;
    }
    
    static double getTotalBalance() {
        return totalBalance;
    }
};

void bankInfo() {
    cout << "Total Bank Balance: " << Account::getTotalBalance() << endl;
    cout << "Total Bank Account: " << Account::getTotalAccount() << endl;
}

int Account::totalAccount = 0;
double Account::totalBalance = 0;

int main() {
    /**
    Account a1("Mrinal", "Saving", "Delhi", "1829",
               1, 1000);
    Account a2("Kunal", "Privet", "Mumbai", "9137",
               2, 2000);

    cout << "Before: " << endl;
    a1.display();
    a2.display();
    bankInfo();
    a1.updateBalance(500, "deposit");
    a2.updateBalance(1000, "withdrawal");

    cout << endl << "After: " << endl;
    a1.display();
    a2.display();
    bankInfo();
    **/

    return 0;
}