#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen
{

private:
    enum enCurrencyMenuOptions
    {
        eListCurrencies = 1,
        eFindCurrency = 2,
        eUpdateRate = 3,
        eCurrencyCalculator = 4,
        eMainMenue = 5
    };

    static short ReadCurrencyMenueOption()
    {
        cout << setw(37) << left << ""
             << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _GoBackToCurrencyExchangeMenue()
    {
        cout << "\n\nPress any key to go back to Manage Users Menue...";
        system("pause>0");
        ShowCurrencyExchangeScreen();
    }

    static void _ShowListCurrenciesScreen()
    {
        // cout << "\nList Users Screen Will Be Here.\n";
        clsListCurrenciesScreen::ShowUsersList();
    }

    static void _ShowFindCurrencyScreen()
    {
        // cout << "\nAdd New User Screen Will Be Here.\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        // cout << "\nDelete User Screen Will Be Here.\n";
        clsUpdateRateScreen::ShowUpdateRateScreen();
    }

    static void _ShowCalculatorScreen()
    {
        // cout << "\nUpdate User Screen Will Be Here.\n";
        clsCalculatorScreen::ShowCalculatorScreen();
    }

    static void _PerformCurrencyMenueOption(enCurrencyMenuOptions ManageUsersMenueOption)
    {

        switch (ManageUsersMenueOption)
        {
        case enCurrencyMenuOptions::eListCurrencies:
        {
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }

        case enCurrencyMenuOptions::eFindCurrency:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }

        case enCurrencyMenuOptions::eUpdateRate:
        {
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }

        case enCurrencyMenuOptions::eCurrencyCalculator:
        {
            system("cls");
            _ShowCalculatorScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }

        case enCurrencyMenuOptions::eMainMenue:
        {
            // do nothing here the main screen will handle it :-) ;
        }
        }
    }

public:
    static void ShowCurrencyExchangeScreen()
    {

        system("cls");
        _DrawScreenHeader("\t Currency Exchange Screen");

        cout << setw(37) << left << ""
             << "===========================================\n";
        cout << setw(37) << left << ""
             << "\t\t  Currency Exchange Menu\n";
        cout << setw(37) << left << ""
             << "===========================================\n";
        cout << setw(37) << left << ""
             << "\t[1] List Currency.\n";
        cout << setw(37) << left << ""
             << "\t[2] Find Currency.\n";
        cout << setw(37) << left << ""
             << "\t[3] Update Rate.\n";
        cout << setw(37) << left << ""
             << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << ""
             << "\t[5] Main Menue.\n";
        cout << setw(37) << left << ""
             << "===========================================\n";

        _PerformCurrencyMenueOption((enCurrencyMenuOptions)ReadCurrencyMenueOption());
    }
};
