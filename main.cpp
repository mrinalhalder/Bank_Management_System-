#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//string ud = "undefined";

class Account {
    string name;
    string accountType;
    string address;
    string phoneNumber;
    double balance;
    int accountNumber;

    static int totalAccount;
    static double totalBalance;

public:
    Account(string name, string accountType,
            string address, string phoneNumber,
            int accountNumber, double balance)
    {
        this->name = name;
        this->accountType = accountType;
        this->address = address;
        this->phoneNumber = phoneNumber;
        this->accountNumber = accountNumber;
        this->balance = balance;
    }

    static void addAccount(const Account& user) {
        totalAccount++;
        totalBalance += user.balance;
    }

    void saveToFile(ofstream& accFile) const {
        accFile << name << '|'
                << accountType << '|'
                << address << '|'
                << phoneNumber << '|'
                << accountNumber << '|'
                << balance << '\n';
    }

    /**
    void readToFile(ifstream& accFile) {
        file >> name;
        file >> accountType;
        file >> address;
        file >> phoneNumber;
        file >> accountNumber;
        file >> balance;
    }
    **/

    void display() {
        cout << "Name: " << name << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Bank Balance: " << balance << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Address: " << address << endl;
    }

    void withdraw(double amount) {
        if(amount <= balance) {
            balance -= amount;
            totalBalance -= amount;
        }
        else {
            cout << "You have not enough money to withdrawal!" << endl;
        }
    }

    void deposit(double amount) {
        balance += amount;
        totalBalance += amount;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    static int getTotalAccount() {
        return totalAccount;
    }

    static double getTotalBalance() {
        return totalBalance;
    }

    static void deleteAccount(const Account& user) {
        totalAccount--;
        totalBalance -= user.balance;
    }
};

struct tempAccount {
    string name;
    string accountType;
    string address;
    string phoneNumber;
    int accountNumber;
    double balance;
};

void bankInfo() {
    cout << "Total Bank Balance: " << Account::getTotalBalance() << endl;
    cout << "Total Bank Account: " << Account::getTotalAccount() << endl;
}

int Account::totalAccount = 0;
double Account::totalBalance = 0;

// User Helper Function
void ui();
int readUserChoice();
int processData(vector<Account>& users);

// File Management Function
void storeDataInFile(const vector<Account>& users);
bool readDataInFile(vector<Account>& users);

// Creat Acount Function
Account readAccountInfo();

int main() {
    vector<Account> users;
    readDataInFile(users);

    while(true) {
        if(processData(users) == 1) {
            break;
        }
    }

    return 0;
}

void ui() {
    //cout << "\n";
    cout << "========================================\n";
    cout << "        BANK MANAGEMENT SYSTEM\n";
    cout << "========================================\n";

    cout << "\n";
    cout << "1. Create New Account\n";
    cout << "2. View Account\n";
    cout << "3. Search Account\n";
    cout << "4. Deposit Money\n";
    cout << "5. Withdraw Money\n";
    cout << "6. Update Account\n";
    cout << "7. Delete Account\n";
    cout << "8. Bank Information\n";
    cout << "9. Exit\n";

    cout << "\n----------------------------------------\n";
}

int readUserChoice() {
    int attempt = 0;
    int choice = 0;

    while(true) {
        attempt++;
        if(attempt > 3) {
            cout << "\nTo many invalid inputs are given!" << endl;
            cout << "So the program is back to main menu." << endl;
            return 0;
        }

        cout << "Enter your choice (1-9): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            // Clear the entire input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(attempt < 3)
                cout << "Invalid input! Please enter a number.\n\n";
            continue;
        }

        if (choice < 1 || choice > 9) {
            if(attempt < 3) {
                cout << "Invalid choice! Enter a number between 1 and 9.\n\n";
            }
            continue;
        }

        // Clear remaining characters from buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    return choice;
}

int processData(vector<Account>& users) {
    ui();
    int choice = readUserChoice();

    switch (choice) {
    case 1: {
        // cout << "Create Account\n";
        users.push_back(readAccountInfo());
        Account::addAccount(users.back());
        storeDataInFile(users);
        break;
    }
    case 2: {
        cout << "View Account\n";
        break;
    }
    case 3: {
        cout << "Search Account\n";
        break;
    }
    case 4: {
        cout << "Deposit Money\n";
        break;
    }
    case 5: {
        cout << "Withdraw Money\n";
        break;
    }
    case 6: {
        cout << "Update Account\n";
        break;
    }
    case 7: {
        cout << "Delete Account\n";
        break;
    }
    case 8: {
        bankInfo();
        break;
    }
    case 9: {
        cout << "\nThank you for using our bank system!\n";
        return 1;
    }
    default: {
        cout << "\nInvalid choice! Try again.\n";
    }
    }
    return 0;
}

// File Management Function
void storeDataInFile(const vector<Account>& users) {
    ofstream accFile("AccountInfo.txt");

    if (!accFile) {
        cout << "File could not be opened!" << endl;
        return;
    }

    for(auto user : users) {
        user.saveToFile(accFile);
    }

    accFile.close();
    cout << "\nData saved successfully!\n";
}

bool readDataInFile(vector<Account>& users) {
    ifstream accFile("AccountInfo.txt");

    if (!accFile) {
        return false;
    }

    string line;

    while (getline(accFile, line)) {
        // When line is empty then data is not store and keep moving next
        if (line.empty()) continue;
        
        // Convert line to stream 
        stringstream ss(line);
        tempAccount data; // A temporal structured datatype
        
        // A temporal string variable
        string accNumStr, balanceStr;

        getline(ss, data.name, '|');
        getline(ss, data.accountType, '|');
        getline(ss, data.address, '|');
        getline(ss, data.phoneNumber, '|');
        getline(ss, accNumStr, '|');
        getline(ss, balanceStr, '\n');

        if (!accNumStr.empty() && !balanceStr.empty()) {
            data.accountNumber = stoi(accNumStr);
            data.balance = stod(balanceStr);

            Account user(
                data.name,
                data.accountType,
                data.address,
                data.phoneNumber,
                data.accountNumber,
                data.balance
            );

            users.push_back(user);
            Account::addAccount(user);
        }
    }

    accFile.close();

    // cout << "Account data loaded successfully!" << endl;
    return true;
}

Account readAccountInfo() {
    tempAccount accData;

    cout << "Enter your name: ";
    getline(cin, accData.name);

    cout << "Enter Account Number: ";
    cin >> accData.accountNumber;

    cout << "Enter Account Type (Savings/Current): ";
    cin >> accData.accountType;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Your Address: ";
    getline(cin, accData.address);

    cout << "Enter Your Phone Number: ";
    cin >> accData.phoneNumber;

    cout << "Add Initial Balance: ";
    cin >> accData.balance;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Account user(
        accData.name,
        accData.accountType,
        accData.address,
        accData.phoneNumber,
        accData.accountNumber,
        accData.balance
    );

    return user;
}
    