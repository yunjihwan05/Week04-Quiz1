#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include "Date.h"
using namespace std;

class BankAccount
{
private:
    int accountNumber;
    string userName;
    Date* BirthDate;
    int balance;

public:
    explicit BankAccount(int = 0, string = "", int = 1, int = 1, int = 1900, int = 0);
    void deposit(int money);
    void withdraw(int money);
    int Check();
    void printAll();
    string getUserName();
    ~BankAccount();
};

#endif
