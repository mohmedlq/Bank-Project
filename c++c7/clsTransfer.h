#pragma once
#include <iostream>
#include "clsScreen.h"
#include "Person.h"
#include"clsClintbank.h"
#include "clsInputValidate.h"
class clsTransferClientScreen :protected clsScreen
{

private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\n___________________\n";

    }
  static   string _ReadAccountNumber(string Masseg)
    {
        string AccountNumber;
        cout << Masseg<<endl;
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }
     static float ReadAmount(clsBankClient SourceClient)
     {
         float Amount=0;

         cout << "\nEnter Transfer Amount? ";

         Amount = clsInputValidate::ReadFloatNumber();

         while (Amount > SourceClient.AccountBalance)
         {
             cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
             Amount = clsInputValidate::ReadDblNumber();
         }
         return Amount;
     }

public:
    static void ShowTransferClientScreen()
    {

        _DrawScreenHeader("\tTransfer Client Screen");

        _PrintClient(CurrentClient);
        clsBankClient destnation = clsBankClient::Find(_ReadAccountNumber("\nPlese Enter Account Number To transfer To \n"));
        while (CurrentClient.AccountNumber() == destnation.AccountNumber())
        {
            cout << "\nYou can't transfer to your own account. Please enter a different account number:\n";
            destnation = clsBankClient::Find(_ReadAccountNumber("\nPlese Enter Account Number To transfer To \n"));
        }
        _PrintClient(destnation);
        double Amount=0;
        if (Amount >= 10 && Amount <= 100000)
        {


            Amount = ReadAmount(CurrentClient);
            cout << "\nAre you sure you want to tranfer to this client y/n? ";
            char Answer = 'n';
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                if (CurrentClient.Transfer(Amount, destnation, CurrentUser.UserName))
                {
                    cout << "\nmony added Successfully :-)\n";
                    _PrintClient(destnation);
                }
                else
                {
                    cout << "\nError mony Was not sent\n";
                }
                _PrintClient(CurrentClient);
            }
        }
        else
        {
            cout << "\nAmount must be between 10 and 100000\n";
        }
    }


};

