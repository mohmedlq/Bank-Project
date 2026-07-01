#pragma once
#include<iostream>
#include<string>
#include"clsScreen.h"
#include"clsMainScreen.h"
#include"clsInputValidate.h"
#include"clsClintbank.h"
#include"clsclientlogin.h"
#include"clsUserLogin.h"
#include"clstransationlog.h"
#include"clstotalbalnces.h"
#include"Globl.h" 
class clsMainForUser : protected clsScreen
{
private:
    enum enMainMenuOptionsUser {
        eListClients = 1, eUpdateClient = 2, eFindClient = 3,
        eShowTransactionsHistory = 4,entotalblances=5 ,Usermanagement = 6, exit = 7
    };

    static short _ReadMainMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 7]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 7, "Enter Number between 1 to 7? ");
        return Choice;
    }

    static void _GoBackToMainMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menu...\n";
        system("pause>0");
        ShowMainMenu();
    }

    static void _ShowAllClientsScreen()
    {
        system("cls");
        clslist::ShowUsersList();
    }

    static void _ShowUpdateClientScreen()
    {
        system("cls");

        clsUpdate::showUpdatescreen();
    }

    static void _ShowFindClientScreen()
    {
        system("cls");

        clsFind::showFindscreen();
    }

    static void _ShowTransactionsHistory()
    {
        system("cls");

        clsListtransferig::ShowTransferLogList();
    }
    static void _ShowtotalBlances()
    {
        system("cls");

        clsTotalBalancesScreen::ShowTotalBalances();
    }
    static void _UsersManage()
    {
        system("cls");

        clsManageUsersScreen::ShowManageUsersMenue();
    }
    static void _ShowEndScreen()
    {
        CurrentUser = clsUser::Find("", "");
    }

    static void _PerformMainMenuOption(enMainMenuOptionsUser option)
    {
        switch (option)
        {
        case eListClients:
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenu();
            break;

        case eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenu();
            break;

        case eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenu();
            break;

        case eShowTransactionsHistory:
            _ShowTransactionsHistory();
            _GoBackToMainMenu();
            break;
        
        case entotalblances:
            _ShowtotalBlances();
            _GoBackToMainMenu();
            break;
        case Usermanagement:
            _UsersManage();
            _GoBackToMainMenu();
            break;

        case exit:
            system("cls");
            _ShowEndScreen();
            break;
        }
    }

public:
    static void ShowMainMenu()
    {
        system("cls");
        _DrawScreenHeader("\t    User Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t      Main Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[3] Find Client.\n";
        cout << setw(37) << left << "" << "\t[4] Show Transactions History.\n";
        cout << setw(37) << left << "" << "\t[5] Show Total Blances.\n";
        cout << setw(37) << left << "" << "\t[6] Users Manigment.\n";
        cout << setw(37) << left << "" << "\t[7] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformMainMenuOption((enMainMenuOptionsUser)_ReadMainMenuOption());
    }
};
