#pragma once
#include <iostream>
#include "clsScreen.h"
#include"clsClintbank.h"
#include "clsInputValidate.h"
#include <iomanip>
using namespace std;


class clsdeposite :protected clsScreen
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
    static void showdepositescreen()
    {
        _DrawScreenHeader(" show deposite Screen");
       
        system("cls");
        _PrintClient(CurrentClient);

        double Amount;
        cout<<"\n Enter the Amount to Deposite \n";
        cin >> Amount;
        while (Amount < 10 || Amount>100000)
        {
            cout << "\n Enter the Amount to Deposite limit[10]/max[100000] \n";
            cin >> Amount;
        }
        char shure = 'Y';
        cout << "\nAre you sure you want to deposit " << Amount << " ? (Y/N): ";
        cin >>shure;

        if (shure=='Y'||shure=='y')
        {
            CurrentClient.Deposite(Amount);
            cout << "\n Amount Deposted Secssfuly \n ";
            cout << "\n The new Balance is \n" << CurrentClient.AccountBalance;
        }
        else
        {
            cout << "\n OPrition Was canceld\n";
        }
        
    }
};


