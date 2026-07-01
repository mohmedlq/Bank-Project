#pragma once
#include <iostream>
#include "clsScreen.h"
#include"clsClintbank.h"
#include "clsInputValidate.h"
#include <iomanip>
using namespace std;


class clswithdraw :protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

public:
    static void showdwithdrawscreen()
    {
        _DrawScreenHeader(" show withdraw Screen");
        
        system("cls");
        
        _PrintClient(CurrentClient);

        double Amount;
        cout << "\n Enter the Amount to withdraw \n";
        cin >> Amount;
        while (Amount > CurrentClient.AccountBalance)
        {
            cout << "\nthe Amount is more then your mony\n";
            cin >> Amount;
        }
        while (Amount < 10 || Amount>100000)
        {
            cout << "\n Enter the Amount to withdraw limit[10]/max[100000] \n";
            cin >> Amount;
        }
       
        char shure = 'Y';
        cout << "\nAre you sure you want to withdraw " << Amount << " to account [" << CurrentClient.AccountNumber() << "]? (Y/N): ";
        cin >> shure;

        if (shure == 'Y' || shure == 'y')
        {
            CurrentClient.Withdraw(Amount);
            cout << "\n Amount withdrawed Secssfuly \n ";
            cout << "\n The new Balance is \n"<< CurrentClient.AccountBalance;
        }
        else
        {
            cout << "\n OPrition Was canceld\n";
        }

    }
};


