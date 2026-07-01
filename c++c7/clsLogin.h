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
#include "clsUserLogin.h"
#include"clsUsermain.h"
#include"ClsLoginClient.h"
class clsLogin:clsScreen
{
	static void _Login()
	{
		_DrawScreenHeader("\t Login Screen");
		bool Loginfailed = false;
		bool userlogin = false;
		string username, password;
		short Limit = 3;
		int choise = 0;
		system("cls");
		_DrawScreenHeader("====== Welcome to My Bank System =====");
		cout << "[1] Login to your account as a User\n";
		cout << "[2] Login To Your Account As A Client\n";
		cout << "[3] Create New Account \n";
		cout << "[4] Exit\n";
		cout << "\n Choise One\n";
		cout << "==================================================\n";
		cin >> choise;
		if (choise == 1)
		{
			system("cls");
		    clsUserLogin::UserLogin();
		}
		else if (choise == 2)
		{
			system("cls");
			ClsLoginClient::Login();
		}
		else if (choise == 3)
		{
			system("cls");
			clsAddnew::AddNewClient();
		}
		else if (choise==4)
		{
			cout << "\n Thank you For Using Our App\n";
			exit(0);
		}
		else
		{
			cout << "\n Invalid choice, please try again.\n";
			system("pause");
		}

	}

public:
	
	static void Login()
	{
		_Login();
	}




};
