🏦 Bank Management System

A console-based Bank Management System built with C++ to practice Object-Oriented Programming (OOP), STL, input validation, and file handling.

The project allows users to create and manage bank accounts, perform transactions, and store account information in a local file.

✨ Features

- Create Account — Create new accounts with unique account numbers and phone numbers.
- View All Accounts — Display a list of all registered accounts.
- Search Account — Find an account using its account number.
- Deposit Money — Deposit money into an existing account.
- Withdraw Money — Withdraw money with balance validation.
- Update Account — Update the account holder's name, phone number, and account type.
- Delete Account — Remove an account from the system.
- Bank Information — View the total number of accounts and combined account balance.
- File Handling — Save account information to a local file and load it when the program starts.
- Input Validation — Validate account numbers, phone numbers, transaction amounts, and duplicate entries.

🛠️ Technologies Used

- Language: C++
- Core Concepts: Classes, Objects, Encapsulation, Static Members
- STL: "vector", "lower_bound", "algorithm"
- File Handling: "ifstream", "ofstream"
- Other Concepts: Exception Handling, Input Validation, String Manipulation

📂 Project Structure

Bank-Management-System/
├── main.cpp
├── AccountInfo.txt   # Created/updated by the program
└── README.md

Note: The actual source filename may differ. Update this structure to match your repository.

🚀 Getting Started

Prerequisites

You need a C++ compiler that supports C++11 or later, such as GCC.

Compile

g++ main.cpp -o bank

Run

On Linux or Mac:

./bank

On Windows, run the generated executable:

bank.exe

💾 Data Persistence

The application stores account records in "AccountInfo.txt". When the program starts, it reads the saved records and loads them into memory. Changes are written back to the file when the program exits normally.

Important: Keep a backup of your data file if you need to preserve your test records.

🎯 Learning Goals

This project is part of my journey to strengthen my C++ programming fundamentals through practical implementation.

My main learning goals are:

- Applying OOP concepts in a real project.
- Managing collections of objects using STL containers.
- Implementing efficient account lookup and sorted insertion.
- Handling user input and invalid data.
- Understanding file-based data persistence.
- Improving problem-solving and code organization.

🔮 Future Improvements

- Add transaction history.
- Improve file-data validation and error handling.
- Add confirmation before deleting an account.
- Improve the user interface.
- Separate declarations and implementations into header and source files.
- Explore a database-backed storage system.

⚠️ Disclaimer

This is an educational project developed for learning C++ and software development fundamentals. It is not intended for real banking operations and does not implement production-grade security, authentication, or financial data protection.

👨‍💻 Author

Mrinal Halder

Learning C++ and building projects to improve my programming and problem-solving skills.