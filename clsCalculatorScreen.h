#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCalculatorScreen : protected clsScreen
{

private:
    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\n___________________";
        cout << "\nCountry   : " << Currency.Country();
        cout << "\nCode      : " << Currency.CurrencyCode();
        cout << "\nName      : " << Currency.CurrencyName();
        cout << "\nRate($1)  : " << Currency.Rate();
        cout << "\n___________________\n";
    }

    static clsCurrency _GetCurrency(string CurrencyName)
    {
        string CurrencyCode;
        cout << "\nEnter " << CurrencyName << " Code: ";
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency Code not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        return clsCurrency::FindByCode(CurrencyCode);
    }

    static void _ConverCurrency(clsCurrency Currency1, clsCurrency Currency2, float Amount)
    {   
        double AmountUSD = Currency1.ConverToUSD(Amount);
        cout << "\nConvert From:\n";
        _PrintCurrency(Currency1);
        cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountUSD << " "
             << "USD" << endl;

        float USDtoCurrency = Currency1.ConverTo(Currency2, Amount);
        cout << "\nConvert From USD to:\n";
        _PrintCurrency(Currency2);
        cout << Amount << " " << Currency2.CurrencyCode() << " = " << USDtoCurrency << " " << Currency2.CurrencyCode() << endl;
    }

public:
    static void ShowCalculatorScreen()
    {
        _DrawScreenHeader("\tExchange Currency Screen");

        char Answer;
        do
        {
            system("cls");
            clsCurrency Currency1 = _GetCurrency("Currency1");
            clsCurrency Currency2 = _GetCurrency("Currency2");

            cout << "\nEnter amount to exchange: ";
            float ExchangeAmount = clsInputValidate::ReadFloatNumber();

            _ConverCurrency(Currency1, Currency2, ExchangeAmount);

            cout << "\nDo you want to make another exchange operation? (y / n)\n";
            cin >> Answer;
        } while (Answer == 'y' || Answer == 'Y');
    }
};
