# Banking System Simulation


## Overview
This project is a C++ program that simulates a basic banking system. The program provides users with features such as creating an account, viewing account balances, viewing transaction history, depositing and withdrawing money, and transferring money to other accounts.


## Implementation

The project is implemented using modern C++ features, such as smart pointers and exception handling, and consists of several classes:

* `User`: The project is implemented using modern C++ features, such as smart pointers and exception handling, and consists of several classes:
* `Account`: Represents a bank account and stores the account balance and transaction history.
* `Transaction`: Represents a transaction and stores details such as transaction type, amount, and date/time.
* `BankingSystem`: The main class that manages the users, accounts, and transactions. It provides methods for creating accounts, depositing and withdrawing money, transferring money, and retrieving account and transaction information.

To store and retrieve user and account information efficiently, the program uses a hash table data structure. To handle transfers between accounts, the program uses sorting and searching algorithms.


## File Structure
The project contains the following files:

* `BankingSystemSimulation.cpp`: Contains the implementation of all classes and the main function.
* `userData.txt`: A text file containing sample user and account data for testing purposes.


## Future Improvements
Here are some possible improvements for this project:

* Add support for multi-threading to improve program performance.
* Use a more secure method for storing user and account information (e.g., encryption).
* Add support for different types of bank accounts (e.g., savings, checking, credit).
* Implement a GUI for the program to improve user experience.


## Author
This program was created by Claudia Cheng.

