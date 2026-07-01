#pragma once
#include <iostream>
#include "clsScreen.h"
#include"clsUsers.h"
#include "clsInputValidate.h"
#include <iomanip>
using namespace std;


class clsUpdateuser :protected clsScreen
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
    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

       
    }
public:
    static void showUpdatescreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader(" Update USer Screen");
        string Account_name;
        cout << "\n Enter User Name \n";
        Account_name = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(Account_name))
        {
            cout << "\n User Is not Exsist \n";
            cout << "\n Try Agani \n";
            Account_name = clsInputValidate::ReadString();
        }
        system("cls");
        clsUser User = clsUser::Find(Account_name);
        _PrintUser(User);
        char shure = 'Y';
        cout << " \n Are you shure you Want To Update { Y/N }\n";
        cin >> shure;
        if (shure == 'y' || shure == 'Y')
        {
            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";
            clsUser::enSaveResults save;
            _ReadUserInfo(User);
            save = User.Save();
            switch (save)
            {
            case clsUser::svFaildEmptyObject:
                cout << "\n Error Not Save Becuse It Is Empty \n";
                break;
            case clsUser::svSucceeded:
                cout << "\n User Updated secssfuly \n";
                _PrintUser(User);
                break;
            case clsUser::svFaildUserExists:
                cout << "\n User Not Updated Becuse Account Name Is Already Exsit \n";
                break;
            }

        }
    }
    
};