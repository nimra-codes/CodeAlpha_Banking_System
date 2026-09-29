# Banking Management System

**Code Alpha Internship – C++ Task**

A console-based Banking Management System developed in C++ as part of my Code Alpha internship. This project demonstrates object-oriented programming, customer management, account operations, fund transfers, and transaction tracking.

## Project Overview

The Banking Management System is designed to perform basic banking operations through a menu-driven interface. It allows users to register customers, open accounts, manage balances, and view transaction histories.

## Features

* Create and manage customer records
* Update customer information
* View all registered customers
* Open bank accounts with an initial deposit
* View all bank accounts
* Display account details and account holder information
* Deposit money
* Withdraw money with balance validation
* Transfer funds between accounts
* View account-specific transaction history
* Validate user input and handle invalid entries
* Display balances in Pakistani Rupees (Rs.)

## Concepts Used

* C++ Programming
* Object-Oriented Programming (OOP)
* Classes and Objects
* Encapsulation
* Constructors
* Vectors
* Functions
* Conditional Statements
* Loops
* Input Validation
* String Handling
* Stream Formatting

## Classes

**1. Customer**

Stores customer information, including customer ID, name, phone number, and address. Supports updating and displaying customer details.

**2. Account**

Manages account number, customer ID, and account balance. Supports deposits, withdrawals, and displaying account information.

**3. Transaction**

Stores transaction details, including transaction ID, type, sender account, receiver account, amount, and description.

**4. BankingSystem**

Controls the overall application, including customer and account management, deposits, withdrawals, transfers, and transaction history.

## Menu Options

1. Create Customer
2. Update Customer
3. View All Customers
4. Open Bank Account
5. View All Accounts
6. View Account Details
7. Deposit Money
8. Withdraw Money
9. Transfer Funds
10. Transaction History
11. Exit

## How to Run

**Requirements**

* C++ compiler
* IDE such as VS Code, Dev-C++, or Code::Blocks

**Compile**

```bash
g++ -std=c++14 main.cpp -o banking
```

**Run**

On Windows:

```bash
banking.exe
```

On Linux/macOS:

```bash
./banking
```

## Learning Outcomes

Through this project, I practiced designing a multi-class C++ application and applying OOP concepts to a practical scenario. I also gained experience working with vectors, validating user input, managing account balances, and organizing transaction records.

## Future Improvements

* Add file handling for permanent data storage
* Add user login and authentication
* Improve account number and customer data validation
* Add search and filtering options
* Create a graphical user interface
* Add stronger transaction consistency and security checks

## Internship

**Organization:** Code Alpha
**Track:** C++ Programming
**Project:** Banking Management System

This project was developed as part of my learning journey and practical experience during the Code Alpha internship.

## Disclaimer

This is an educational project designed to practice C++ programming. It is not intended for real banking or financial transactions.

## Author

**Nimra Rab Nawaz**
C++ Programmer | Software Engineering Student
