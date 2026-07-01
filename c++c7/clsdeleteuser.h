#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include"clsUsers.h"
#include <iomanip>
class clsDeleteuser :protected clsScreen
{
private:
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
    static void showdeletescreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;// this will exit the function and it will not continue
        }
        _DrawScreenHeader(" delete User Screen");
        string Account_name;
        cout << "\n Enter user Name \n";
        Account_name = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(Account_name))
        {
            cout << "\n user Is not Exsist \n";
            cout << "\n Try Agani \n";
            Account_name = clsInputValidate::ReadString();
        }
        system("cls");
        clsUser client = clsUser::Find(Account_name);
        _PrintUser(client);
        char shure = 'Y';
        cout << " \n Are you shure you Want To Delete { Y/N }\n";
        cin >> shure;
        if (shure == 'y' || shure == 'Y')
        {
            if (client.Delete())
            {
                cout << "\n User Deleate secssfuly \n";
            }
            else
            {
                cout << " \nError User Wasnot Deleted\n ";
            }
        }
    }
};