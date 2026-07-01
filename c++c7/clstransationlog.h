#pragma once
#include <iostream>
#include "clsScreen.h"
#include"clsClintbank.h"
#include <iomanip>
#include"clsDate.h"
class clsListtransferig :protected clsScreen
{
private:
    
    static void _PrintRecord(clsBankClient::stTransferLogRecord Record)
    {
        cout << "| " << left << setw(20) << Record.DateTime
            << "| " << setw(15) << Record.SourceAccount
            << "| " << setw(15) << Record.DestinationAccount
            << "| " << setw(10) << Record.Amount
            << "| " << setw(15) << Record.SourceBalanceAfter
            << "| " << setw(15) << Record.DestinationBalanceAfter
            << "| " << setw(15) << Record.PerformedBy << "|\n";
    }
public:

    static void ShowTransferLogList()
    {
       
        vector<clsBankClient::stTransferLogRecord> vTransfers =CurrentClient.GetMyTransferLog();

        string Title = "\t  Transfer Log Screen";
        string SubTitle = "\t    (" + to_string(vTransfers.size()) + ") Transfer(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(20) << "Date/Time";
        cout << "| " << left << setw(10) << "From";
        cout << "| " << left << setw(10) << "To";
        cout << "| " << left << setw(12) << "Amount";
        cout << "| " << left << setw(18) << "From Balance After";
        cout << "| " << left << setw(22) << "To Balance After";
        cout << "| " << left << setw(12) << "By User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (vTransfers.empty())
        {
            cout << "\t\t\t\tNo Transfer  is not Found!";
        }
        else
        {
            for (clsBankClient::stTransferLogRecord Record : vTransfers)
            {
                if (!CurrentClient.IsEmpty())
                cout << setw(8) << left << "" << "| " << left << setw(20) << Record.DateTime;
                cout << "| " << left << setw(10) << Record.SourceAccount;
                cout << "| " << left << setw(10) << Record.DestinationAccount;
                cout << "| " << left << setw(12) << Record.Amount;
                cout << "| " << left << setw(18) << Record.SourceBalanceAfter;
                cout << "| " << left << setw(22) << Record.DestinationBalanceAfter;
                cout << "| " << left << setw(12) << Record.PerformedBy << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }


};