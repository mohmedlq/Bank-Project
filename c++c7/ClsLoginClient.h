#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUsers.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Globl.h"
#include<string>
#include"clsAddnew.h"
#include"CurrentClient.h"
#include"clsclientlogin.h"
#include"clsUsermain.h"


class ClsLoginClient :clsScreen
{
private:
	static void _Clientlogin()
	{
		system("cls");
		_DrawScreenHeader("\t Client Login Screen");
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
			CurrentClient = clsBankClient::Find(username, password);
			Loginfailed = CurrentClient.IsEmpty();

			if (Limit == 0)
			{
				system("cls");
				cout << "\nYou are blocked because you hit the limit of login attempts.\n";
				exit(0);
			}

		} while (Loginfailed);
		clsMainMenuForClient::ShowMainMenu();
	}
public:
	static void Login()
	{
		_Clientlogin();
	}
};

