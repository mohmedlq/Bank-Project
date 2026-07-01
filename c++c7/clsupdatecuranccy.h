#pragma once
#include <iostream>
#include "clsScreen.h"
#include"clsCurancy.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyScreen :protected clsScreen
{

private:
    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }

    static void _ShowResults(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nCurrency Was not Found :-(\n";
            system("pause");
        }
    }

public:

    static void ShowUpdateCurrencyScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;// this will exit the function and it will not continue
        }


        _DrawScreenHeader("\t  Find Currency Screen");

            string CurrencyCode;
            cout << "\nPlease Enter Currency Code: ";
            CurrencyCode = clsInputValidate::ReadString();
            while (!clsCurrency::IsCurrencyExist(CurrencyCode))
            {
                cout << "\n Currency Code was not found chose anthoer one: ";
                CurrencyCode = clsInputValidate::ReadString();
            }
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            _ShowResults(Currency);
            cout << "\nAre you shure you want to update Currancy\n";
            char shure ='n';
            cin >> shure;
            if (shure== 'y'||shure=='Y')
            {
                cout << "\n Enter the new rate\n";
                float newrate;
                cin >> newrate;
                Currency.UpdateRate(newrate);
                _ShowResults(Currency);
            }
            cout << "\n Currancy updated secsessfuly\n";
            





    }

};

