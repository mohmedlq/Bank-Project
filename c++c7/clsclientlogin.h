#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUsers.h"
#include <iomanip>
#include "Globl.h"
#include<string>
#include"clsAddnew.h"
#include"clsReadytologin.h"
#include"clsClientsmainmenu.h"
#include"CurrentClient.h"
class clsaclientlogin :clsScreen
{
private:
	static void _ClientLogin()
	{
		_DrawScreenHeader("\tClient Login Screen");
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

			Limit--;

			cout << "\nEnter Username: ";
			username = clsInputValidate::ReadString();

			cout << "Enter Password: ";
			cin >> password;

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
	static void Clientlogin()
	{
		_ClientLogin();
	}
};

