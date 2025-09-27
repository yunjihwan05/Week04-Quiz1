#include <iostream>
#include <string>
#include <vector>
#include "BankAccount.h"
#include "Date.h"
using namespace std;

static const int daysPerMonth[13] =
{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

BankAccount::BankAccount(int acc, string name, int m, int d, int y, int bal)
    : accountNumber(acc), userName(name), balance(bal)
{
    BirthDate = new Date(m, d, y);
}

void BankAccount::deposit(int money)
{
    balance += money;
}

void BankAccount::withdraw(int money)
{
    if (balance < money)
    {
        cout << "Error: Not enough balance" << endl;
        printAll();
    }
    else
        balance -= money;
}

int BankAccount::Check()
{
    return balance;
}

void BankAccount::printAll()
{
    cout << accountNumber << ", " << userName << ", ";
    BirthDate->print();
    cout << ", " << balance << endl;
}

string BankAccount::getUserName()
{
    return userName;
}

BankAccount::~BankAccount()
{
    delete BirthDate;
}

Date::Date(int m, int d, int y)
{
    bool errorMonth = false, errorDay = false;
    if (m < 1 || m > 12)
    {
        cout << "Error: Month must be 1-12" << endl;
        errorMonth = true;
    }
    month = m;
    year = y;
    try
    {
        day = checkDay(d);
    }
    catch (...)
    {
        cout << "Error: Invalid day for current month and year" << endl;
        errorDay = true;
    }
    if (errorMonth || errorDay)
    {
        month = 1;
        day = 1;
        year = 1900;
    }
    cout << "Date object constructor for date " << month << "/" << day << "/" << year << endl;
}

unsigned int Date::checkDay(int testDay) const
{
    if (testDay > 0 && testDay <= daysPerMonth[month])
        return testDay;
    if (month == 2 &&
        ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)))
        if (testDay == 29)
            return testDay;
    throw invalid_argument("Invalid day");
}

void Date::print() const
{
    cout << month << "/" << day << "/" << year;
}

Date::~Date()
{
    cout << "Date object destructor for date " << month << "/" << day << "/" << year << endl;
}

int main()
{
    vector<BankAccount> accounts;
    accounts.push_back(BankAccount(1001, "Kim", 3, 7, 2000, 5000));
    accounts.push_back(BankAccount(1002, "Lee", 5, 17, 2002, 8000));
    accounts.push_back(BankAccount(1003, "Park", 20, 50, 2008, 15000));

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string name;
        int order, money;
        cin >> name >> order >> money;

        bool found = false;
        for (auto& acc : accounts)
        {
            if (acc.getUserName() == name)
            {
                found = true;
                if (order == 1)
                {
                    acc.deposit(money);
                    acc.printAll();
                }
                else if (order == 2)
                {
                    int before = acc.Check();
                    acc.withdraw(money);
                    if (before >= money)
                        acc.printAll();
                }
                else
                {
                    cout << "Error: Invalid keyword" << endl;
                    acc.printAll();
                }
                break;
            }
        }
        if (!found)
            cout << "Error: No such people." << endl;
    }

    return 0;
}
