#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include"clsdedeposite.h"
#include"clswithdraw.h"
#include"clstotalbalnces.h"
#include"clsTransfer.h"
#include"clstransationlog.h"
#include"clsCurancy.h"
#include"clsListcurrancy.h"
#include"clsFindcurrancy.h"
#include"clsupdatecuranccy.h"
#include"clsconvertcurrncy.h"
#include"global.h"
using namespace std;

class clsCurancyScreen :protected clsScreen
{


private:
    enum enCuranccyMenueOptions {
        eListcurrency = 1, eFindcurrancy = 2,
        eUpdatecurrancy = 3, eCurrencycul = 4,eShowmainmenu=5
    };

    static short ReadTransactionsMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 7? ");
        return Choice;
    }


    static void _ShowcurrancylistScreen()
    {
        clsCuranccylist::ShowcuranciesList();
    }

    static void _ShowFindcuranccyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdatecuranciesScreen()
    {
        clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
    }


    static void _ShowcurrancyculcltourScreen()
    {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }
    static void _GoBackToTransactionsMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowCurrancyMenue();

    }

    static void _PerformTransactionsMenueOption(enCuranccyMenueOptions option)
    {
        switch (option)
        {
        case eListcurrency:
            system("cls");
            _ShowcurrancylistScreen();
            _GoBackToTransactionsMenue();
            break;

        case eFindcurrancy:
            system("cls");
            _ShowFindcuranccyScreen();
            _GoBackToTransactionsMenue();
            break;

        case eUpdatecurrancy:
            if (!CurrentUser.IsEmpty())
            {
                system("cls");
                _ShowUpdatecuranciesScreen();
            }
            _GoBackToTransactionsMenue();
            break;

        case eCurrencycul:
            system("cls");
            _ShowcurrancyculcltourScreen();
            _GoBackToTransactionsMenue();
            break;

        case eShowmainmenu:
            break;
        }
    }public:


    static void ShowCurrancyMenue()
    {

       
        system("cls");
        _DrawScreenHeader("\t currancy exhaging Menue Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  currancy exhaging Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Curanccy.\n";
        cout << setw(37) << left << "" << "\t[2] Find Curancy.\n";
        if (!CurrentUser.IsEmpty())
        {
            cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
            cout << setw(37) << left << "" << "\t[4] Curanccy Cuclutor.\n";
            cout << setw(37) << left << "" << "\t[5] Back To Main Menu.\n";

        }
        cout << setw(37) << left << "" << "\t[3] Curanccy Cuclutor.\n";
        cout << setw(37) << left << "" << "\t[4] Back To Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOption((enCuranccyMenueOptions)ReadTransactionsMenueOption());
    }

};
