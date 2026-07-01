#pragma once
#include <iostream>
#include "clsUsers.h"
#include "Globl.h"
#include <ctime>
#include"clsDate.h"
#include "clsClintbank.h"

using namespace std;

class clsScreen
{

protected:
   static  void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";

        // Show logged-in user info only if someone is actually logged in
        if (!CurrentClient.IsEmpty())
        {
            cout << "\n\t\t\t\t\t Hi : " << CurrentClient.FullName() << "\n";
            cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate())
                << "\n\n";
        }
        else if (!CurrentUser.IsEmpty())
        {
            cout << "\n\t\t\t\t\t Hi : " << CurrentUser.UserName << "\n";
            cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate())
                << "\n\n";
        }
        

    }
   static bool CheckAccessRights(clsUser::enPermissions Permission)
   {

       if (!CurrentUser.CheckAccessPermission(Permission))
       {
           cout << "\t\t\t\t\t______________________________________";
           cout << "\n\n\t\t\t\t\t  Access Denied! ";
           cout << "\n\t\t\t\t\t______________________________________\n\n";
           return false;
       }
       else
       {
           return true;
       }

   }

   
};

