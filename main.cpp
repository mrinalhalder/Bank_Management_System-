#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cmath>
using namespace std;

class Account {
    string name;
    string accountType;
    string address;
    string phoneNumber;
    string balance;
    int accountNumber;

    static int totalAccount;
    static string totalBalance;

public:
    Account(string name, string accountType,
            string address, string phoneNumber,
            int accountNumber, string balance)
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
        updateTotalBalance('+', stod(user.balance));
    }

    static void updateTotalBalance(char type, double balance) {
        double totalAmount = stod(totalBalance);

        if(type == '+') {
            totalAmount += balance;
        } else if(type == '-') {
            totalAmount -= balance;
        } else {
            cout << "Invalid Arithmetic Operation!" << endl;
            return;
        }

        totalBalance = doubleToMoney(totalAmount);
    }

    void saveToFile(ofstream& accFile) const {
        accFile << name << '|'
                << accountType << '|'
                << address << '|'
                << phoneNumber << '|'
                << accountNumber << '|'
                << balance << '\n';
    }


    void display() const {
        cout << "\n";
        cout << "============================================\n";
        cout << "             ACCOUNT DETAILS                \n";
        cout << "============================================\n";

        cout << left
             << setw(20) << "Name"
             << ": " << name << '\n';

        cout << left
             << setw(20) << "Account Number"
             << ": " << accountNumber << '\n';

        cout << left
             << setw(20) << "Bank Balance"
             << ": Rs. " << balance << '\n';

        cout << left
             << setw(20) << "Account Type"
             << ": " << accountType << '\n';

        cout << left
             << setw(20) << "Phone Number"
             << ": " << phoneNumber << '\n';

        cout << left
             << setw(20) << "Address"
             << ": " << address << '\n';

        cout << "============================================\n";
    }

    void viewDisplay() const {
        cout << left
             << setw(12)  << accountNumber
             << setw(18) << name
             << setw(12) << accountType
             << balance
             << '\n';
    }

    void withdraw(double amount) {
        if(amount <= 0) {
            cout << "Amount must be greater than zero!\n";
            return;
        }

        double balanceD = stod(balance);

        if(amount <= balanceD) {
            balanceD -= amount;
            balance = doubleToMoney(balanceD);
            updateTotalBalance('-', amount);
        }
        else {
            cout << "You don't have enough money to withdraw!" << endl;
        }
    }

    void deposit(double amount) {
        if(amount <= 0) {
            cout << "Amount must be greater than zero!\n";
            return;
        }

        double balanceD = stod(balance);
        balanceD += amount;

        balance = doubleToMoney(balanceD);
        updateTotalBalance('+', amount);
    }

    static string doubleToMoney(double amount) {
        ostringstream oss;
        oss << fixed << setprecision(2) << amount;
        return oss.str();
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    string getPhoneNumber() const {
        return phoneNumber;
    }

    static int getTotalAccount() {
        return totalAccount;
    }

    static string getTotalBalance() {
        return totalBalance;
    }

    static void deleteAccount(const Account& user) {
        totalAccount--;
        updateTotalBalance('-', stod(user.balance));
    }
};

struct tempAccount {
    string name;
    string accountType;
    string address;
    string phoneNumber;
    int accountNumber;
    string balance;
};

void bankInfo() {
    cout << "Total Bank Balance: " << Account::getTotalBalance() << endl;
    cout << "Total Bank Account: " << Account::getTotalAccount() << endl;
}

int Account::totalAccount = 0;
string Account::totalBalance = "0";

// User Helper Function
void ui();
int readUserChoice();
int processData(vector<Account>& users);

// File Management Function
void storeDataInFile(const vector<Account>& users);
bool readDataInFile(vector<Account>& users);

// Creat Acount Function
bool readAccountInfo(vector<Account>& users);
// Sub account functions
void readStr(string& str, string type);
int readAccountNumber(const vector<Account>& acc, bool isSearch = false);
string readPhoneNumber(const vector<Account>& acc);
// Helper function to valid phone number
bool isUniquePhoneNumber(const vector<Account>& acc, const string& ph);
bool isValidPhoneNumber(const string& ph);
// Get valid Balence
bool readBalance(string& balance);

// View & Search function
void viewAllAccounts(const vector<Account>& users);
void searchAccount(const vector<Account>& users);

//

int main() {
    vector<Account> users;
    readDataInFile(users);

    while(true) {
        if(processData(users) == 1) {
            break;
        }
    }
    storeDataInFile(users);

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

    cout << "-------------------------------------------------\n";
}

int readUserChoice() {
    int attempt = 0;
    int choice = 0;

    while(true) {
        attempt++;
        if(attempt > 3) {
            cout << "\nToo many invalid inputs were given!" << endl;
            cout << "So the program is back to main menu." << endl;
            return 0;
        }

        cout << "Enter your choice (1-9): ";
        cin >> choice;

        // Clear the entire input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

        break;
    }

    return choice;
}

int processData(vector<Account>& users) {
    ui();
    int choice = readUserChoice();

    switch (choice) {
    case 1: {
        if(!readAccountInfo(users)) {
            return 0;
        }
        cout << "\nAccount created successfully!\n";
        break;
    }
    case 2: {
        viewAllAccounts(users);
        break;
    }
    case 3: {
        searchAccount(users);
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

    for(const auto& user : users) {
        user.saveToFile(accFile);
    }

    accFile.close();
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
        string accNumStr;

        getline(ss, data.name, '|');
        getline(ss, data.accountType, '|');
        getline(ss, data.address, '|');
        getline(ss, data.phoneNumber, '|');
        getline(ss, accNumStr, '|');
        getline(ss, data.balance, '\n');


        if (!accNumStr.empty() && !data.balance.empty()) {
            try {
                size_t pos;
                data.accountNumber = stoi(accNumStr, &pos);

                // Puro string-ta valid integer kina check
                if (pos != accNumStr.length()) {
                    continue;
                }

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
            catch (const invalid_argument&) {
                cout << "Skipping invalid account number in file.\n";
                continue;
            }
            catch (const out_of_range&) {
                cout << "Skipping out-of-range account number in file.\n";
                continue;
            }
        }
    }

    accFile.close();
    return true;
}

// Read valid account details
bool readAccountInfo(vector<Account>& users) {
    tempAccount accData;

    readStr(accData.name, "Name");
    int accNum = readAccountNumber(users);

    if(accNum == -1) {
        return false;
    }

    accData.accountNumber = accNum;
    readStr(accData.accountType, "Account Type");
    readStr(accData.address, "Address");
    string result = readPhoneNumber(users);

    if(result == "error") return false;
    accData.phoneNumber = result;
    if(!readBalance(accData.balance)) return false;

    Account user(
        accData.name,
        accData.accountType,
        accData.address,
        accData.phoneNumber,
        accData.accountNumber,
        accData.balance
    );

    auto it = lower_bound(
                  users.begin(),
                  users.end(),
                  user.getAccountNumber(),
    [](const Account& acc, int accountNumber) {
        return
            acc.getAccountNumber() < accountNumber;
    }
              );

    users.insert(it, user);
    Account::addAccount(user);

    return true;
}

void readStr(string& str, string type) {
    cout << "Enter " << type << ": ";
    getline(cin, str);

    // Remove all pipe '|' character in a string
    str.erase(remove(str.begin(), str.end(), '|'), str.end());
}

int readAccountNumber(const vector<Account>& acc, bool isSearch) {
    int attempt = 0;
    int accNumber;

    while(true) {
        attempt++;
        if(attempt > 3) {
            cout << "\nToo many invalid inputs were given!" << endl;
            cout << "So the program is back to main menu." << endl;
            return -1;
        }

        cout << "Enter Account Number: ";
        cin >> accNumber;

        // Clear the entire input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cin.fail()) {
            cin.clear();
            // Clear the entire input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if(attempt < 3)
                cout << "Invalid input! Please enter a number.\n\n";
            continue;
        }

        if (accNumber <= 0 || accNumber > 999999) {
            if(attempt < 3) {
                cout << "\nInvalid Input!\n";
                cout << "Number must be between 1 and 999999\n\n";
            }
            continue;
        }

        if(!isSearch) {
            auto it = lower_bound(acc.begin(), acc.end(),
            accNumber, [](const Account& account, int accNumber) {
                return account.getAccountNumber() < accNumber;
            });

            if (it != acc.end() && it->getAccountNumber() == accNumber) {
                if(attempt < 3) {
                    cout << "Account number already exists!\n";
                }
                continue;
            }
        }

        break;
    }

    return accNumber;
}

string readPhoneNumber(const vector<Account>& acc) {
    int attempt = 0;
    string phone;

    while(true) {
        attempt++;
        if(attempt > 3) {
            cout << "\nToo many invalid inputs were given!" << endl;
            cout << "So the program is back to main menu." << endl;
            return "error";
        }

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        if(!isValidPhoneNumber(phone)) {
            if(attempt < 3) {
                cout << "\nInvalid Input!\n";
                cout << "Please enter a valid Phone number\n\n";
            }
            continue;
        }

        if(!isUniquePhoneNumber(acc, phone)) {
            if(attempt < 3) {
                cout << "Phone number already exists!\n\n";
            }
            continue;
        }

        break;
    }

    return phone;
}

// Helper Phone Number Function
bool isValidPhoneNumber(const string& ph) {
    if (ph.length() != 10) {
        return false;
    }

    for(const auto& ch : ph) {
        if(!isdigit(static_cast<unsigned char>(ch))) return false;
    }

    return true;
}

bool isUniquePhoneNumber(const vector<Account>& acc, const string& ph) {
    for(const auto& account : acc) {
        if(account.getPhoneNumber() == ph) return false;
    }
    return true;
}

// Get valid Balence
bool readBalance(string& balance) {
    int attempt = 0;

    while(true) {
        attempt++;
        if(attempt > 3) {
            cout << "\nToo many invalid inputs were given!" << endl;
            cout << "So the program is back to main menu." << endl;
            return false;
        }

        cout << "Add Initial Balance: ";
        cin >> balance;

        try {
            size_t pos;
            double  amount = stod(balance, &pos);

            if(pos != balance.length()) {
                throw invalid_argument("Invalid input");
            }

            if(!isfinite(amount) || amount <= 0) {
                if(attempt < 3) {
                    cout << "\nInvalid Input!\n";
                    cout << "Balance must be greater than zero.\n\n";
                }
                continue;
            }

            balance = Account::doubleToMoney(amount);
            break;
        }
        catch(...) {
            if(attempt < 3) {
                cout << "\nInvalid Input!\n";
                cout << "Please enter a valid balance.\n\n";
            }
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

// View all accounts
void viewAllAccounts(const vector<Account>& users) {
    if(users.size() == 0) {
        cout << "\nNo account is available!\n";
        cout << "Please create an account first.\n";
        cout << "\n";
        return;
    }

    cout << "\n";
    cout << left
         << setw(12) << "Acc.No."
         << setw(18) << "Name"
         << setw(12) << "Type"
         << "Balance\n";

    cout << "-------------------------------------------------\n";

    for(const auto& user : users) {
        user.viewDisplay();
    }
    cout << endl;
}

// Search account
void searchAccount(const vector<Account>& users) {
    cout << endl;
    int accNumber = readAccountNumber(users, true);
    if(accNumber == -1) return;

    auto it = lower_bound(users.begin(), users.end(),
    accNumber, [](const Account& account, int accNumber) {
        return account.getAccountNumber() < accNumber;
    });

    if(it != users.end() && it->getAccountNumber() == accNumber) {
        it->display();
    }
    else {
        cout << "Account not found!\n";
    }
    cout << endl;
}
