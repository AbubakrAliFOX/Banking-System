#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateRateScreen : protected clsScreen
{

private:
    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:";
        cout << "\n___________________";
        cout << "\nCountry   : " << Currency.Country();
        cout << "\nCode      : " << Currency.CurrencyCode();
        cout << "\nName      : " << Currency.CurrencyName();
        cout << "\nRate($1)  : " << Currency.Rate();
        cout << "\n___________________\n";
    }

    static clsCurrency _FindCurrency(short Answer)
    {
        if (Answer == 1)
        {
            cout << "\nEnter country code: \n";
            string CurrencyCode = clsInputValidate::ReadString();
            while (!clsCurrency::IsCurrencyExist(CurrencyCode))
            {
                cout << "\nCurrency Code not found, choose another one: ";
                CurrencyCode = clsInputValidate::ReadString();
            }
            return clsCurrency::FindByCode(CurrencyCode);
        }
        else
        {
            cout << "\nEnter country name: \n";
            string Country = clsInputValidate::ReadString();
            while (!clsCurrency::IsCurrencyExistByCountry(Country))
            {
                cout << "\nCountry not found, choose another one: ";
                Country = clsInputValidate::ReadString();
            }
            return clsCurrency::FindByCountry(Country);
        }
    }

public:
    static void ShowUpdateRateScreen()
    {
        _DrawScreenHeader("\tUpdate Rate Screen");

        string CurrencyCode;
        cout << "\nEnter Country Code: ";
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency Code not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
        }
        else
        {
            cout << "\nCurrency Was not Found :-(\n";
        }
        _PrintCurrency(Currency);

        char Answer;
        cout << "\nAre you sure you want to update the rate of this currency? (y / n) \n";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            cout << "\nUpdate Currency Rate:\n";
            cout << "\nEnter new rate:";
            float NewRate = clsInputValidate::ReadFloatNumber();
            Currency.UpdateRate(NewRate);
            cout << "\nUpdated Successfully\n";
        }
        else
        {
            cout << "\nOperation Cancelled \n";
        }
    }
};
