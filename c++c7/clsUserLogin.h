#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUsers.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Globl.h"
#include<string>
#include"clsAddnew.h"
#include"clsReadytologin.h"
#include"clsManageUsers.h"
#include"clsUsermain.h"
class clsUserLogin:clsScreen
{
private:
	static void _Userlogin()
	{
		system("cls");
		_DrawScreenHeader("\tLogin Screen");
		bool Loginfailed = false;
		string username, password;
		short Limit = 3;
		do
		{
			if (Loginfailed)
			{
				cout << "\nInvalid username/password\n";
				cout << "\nYou will be blocked after " << Limit << " tries.\n";
			}


			cout << "\nEnter Username: ";
			cin >> username;

			cout << "Enter Password: ";
			cin >> password;

			Limit--;
			CurrentUser = clsUser::Find(username, password);
			Loginfailed = CurrentUser.IsEmpty();

			if (Limit == 0)
			{
				system("cls");
				cout << "\nYou are blocked because you hit the limit of login attempts.\n";
				exit(0);
			}

		} while (Loginfailed);
		clsMainForUser::ShowMainMenu();
	}
public:
	static void UserLogin()
	{
		_Userlogin();
	}


};

