#pragma once
#include <iostream>
#include "clsScreen.h"
#include"clsUsers.h"
#include "clsInputValidate.h"
#include <iomanip>
using namespace std;

class clsFindUser :protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }
public:
    static void showFindUser()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;// this will exit the function and it will not continue
        }
        _DrawScreenHeader(" show User Screen");
        string Account_name;
        cout << "\n Enter Account Name \n";
        Account_name = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(Account_name))
        {
            cout << "\n User Is not Exsist \n";
            cout << "\n Try Agani \n";
            Account_name = clsInputValidate::ReadString();
        }
        system("cls");
        clsUser client = clsUser::Find(Account_name);
        _PrintUser(client);
    }
};

