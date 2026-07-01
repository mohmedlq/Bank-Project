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
#include"clscurrancymain.h"
using namespace std;

class clsTransactionsScreen :protected clsScreen
{


private:
    enum enTransactionsMenueOptions {
        eDeposit = 1, eWithdraw = 2,
        eShowTotalBalance = 3, eTransfr = 4, eShowtransationlog = 5, eShowMainMenue = 6
    };

    static short ReadTransactionsMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 7, "Enter Number between 1 to 7? ");
        return Choice;
    }


    static void _ShowDepositScreen()
    {
        clsdeposite::showdepositescreen();
    }

    static void _ShowWithdrawScreen()
    {
        clswithdraw::showdwithdrawscreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalances();
    }


    static void _ShowTransferScreen()
    {
        clsTransferClientScreen::ShowTransferClientScreen();
    }


    static void _ShowTransferlogScreen()
    {
        clsListtransferig::ShowTransferLogList();
    }


    static void _ShowCurrncyScrn()
    {
        clsListtransferig::ShowTransferLogList();
    }
    static void _ShowCurrancyScreen()
    {
        clsCurancyScreen::ShowCurrancyMenue();
	}
    static void _GoBackToTransactionsMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowTransactionsMenue();

    }

    static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
    {
        switch (TransactionsMenueOption)
        {
        case enTransactionsMenueOptions::eDeposit:
        {
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eWithdraw:
        {
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eShowTotalBalance:
        {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;
        }


        case enTransactionsMenueOptions::eTransfr:
        {
            system("cls");
            _ShowTransferScreen();
         _GoBackToTransactionsMenue();
            break;
        }
        case enTransactionsMenueOptions::eShowtransationlog:
        {
            system("cls");
            _ShowTransferlogScreen();
            _GoBackToTransactionsMenue();
            break;
        }
      
		case enTransactionsMenueOptions::eShowMainMenue:
        {
            //do nothing here the main screen will handle it :-) ;
        }
        }


    }
public:


    static void ShowTransactionsMenue()
    {

        

        system("cls");
        _DrawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfeer.\n";
        cout << setw(37) << left << "" << "\t[5] My Transfeer log history.\n";
        cout << setw(37) << left << "" << "\t[6] Back To Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
    }

};

