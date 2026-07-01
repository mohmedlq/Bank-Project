#pragma once
#include <iostream>
#include "clsScreen.h"
#include"clsClintbank.h"
#include "clsInputValidate.h"
#include <iomanip>
using namespace std;


class clsUpdate :protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }
public:
    static void showUpdatescreen()
    {
        

           

        _DrawScreenHeader("\tUpdate Client Screen");
        string Account_name="";
        cout << "\n Enter Account Name \n";
        Account_name = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(Account_name))
        {
            cout << "\n Account Is not Exsist \n";
            cout << "\n Try Agani \n";
            Account_name = clsInputValidate::ReadString();
        }
        system("cls");
        clsBankClient client = clsBankClient::Find(Account_name);
        _PrintClient(client);
        char shure = 'Y';
        cout << " \n Are you shure you Want To Update { Y/N }\n";
        cin >> shure;
        if (shure == 'y' || shure == 'Y')
        {
            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";
            clsBankClient::enSaveResults save;
            _ReadClientInfo(client);
            save = client.Save();
            switch (save)
            {
            case clsBankClient::svFaildEmptyObject:
                cout << "\n Error Not Save Becuse It Is Empty \n";
                break;
            case clsBankClient::svSucceeded:
                cout << "\n client Updated secssfuly \n";
                _PrintClient(client);
                break;
            case clsBankClient::svFaildAccountNumberExists:
                cout << "\n Clint Not Updated Becuse Account Name Is Already Exsit \n";
                break;
            }

        }
    }
};