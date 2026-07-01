#pragma once
#include <iostream>
#include "clsScreen.h"
#include"clsClintbank.h"
#include "clsInputValidate.h"
#include <iomanip>
using namespace std;

class clsFind:protected clsScreen
{
private:
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
	static void showFindscreen()
	{

        
        _DrawScreenHeader(" show Client Screen");
       
        system("cls");
        _PrintClient(CurrentClient);
	}
};

