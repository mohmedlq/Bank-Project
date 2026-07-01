#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include"clsClintbank.h"
#include"clsList.h"
#include <iomanip>
#include"clsAddnew.h"
#include"clsDelete.h"
#include"clsUpdate.h"
#include"clsFind.h"
#include"clstransaction.h"
#include"clsManageUsers.h"
#include"Globl.h"
#include"clsusersrig.h"
#include"clscurrancymain.h"
using namespace std;

class clsMainMenuForClient : protected clsScreen
{
private:
    enum enMainMenuOptionsClient {
        eUpdateClient = 1, eFindClient = 2, eShowTransactionsMenu = 3, currency = 4,exit=5
    };

    static short _ReadMainMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 4? ");
        return Choice;
    }

    static void _GoBackToMainMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menu...\n";
        system("pause>0");
        ShowMainMenu();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdate::showUpdatescreen();
    }

    static void _ShowFindClientScreen()
    {
        clsFind::showFindscreen();
    }

    static void _ShowTransactionsMenu()
    {
        clsTransactionsScreen::ShowTransactionsMenue();
    } 
    static void _CurrancyMenue()
    {
        clsCurancyScreen::ShowCurrancyMenue();
	}

   

    static void _PerformMainMenuOption(enMainMenuOptionsClient option)
    {
        switch (option)
        {
        case eUpdateClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenu();
            break;

        case eFindClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenu();
            break;

        case eShowTransactionsMenu:
            system("cls");
            _ShowTransactionsMenu();
            _GoBackToMainMenu();
            break;

		case enMainMenuOptionsClient::currency:
            system("cls");
            _CurrancyMenue();
            _GoBackToMainMenu();
            break;

        case exit:
            system("cls");
            break;
        }
    }

public:
    static void ShowMainMenu()
    {
        system("cls");
        _DrawScreenHeader("\t   Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\      Main Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] MY Informition.\n";
        cout << setw(37) << left << "" << "\t[2] Update My Informition.\n";
        cout << setw(37) << left << "" << "\t[3] Transactions.\n";
        cout << setw(37) << left << "" << "\t[4] Currency.\n";
        cout << setw(37) << left << "" << "\t[5] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformMainMenuOption((enMainMenuOptionsClient)_ReadMainMenuOption());
    }
};
