#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeScreen : protected clsScreen
{
private:

    enum enCurrencyExchangeOptions
    {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3, eCurrencyCalculator = 4, eMainMenue = 5
    };

    static short _ReadCurrencyExchangeMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadListNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static  bool _GoBackToCurrencyExchangeMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Currency Exchange Menue...\n";

        system("pause>0");

        return false;
    }

    static void _ShowAllCurrenciesListScreen()
    {
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void  _ShowFindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateCurrencyRateScreen()
    {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        clsCurrencyCalculatorScreen::showCurrencyCalculatorScreen();
    }

    static bool _PerformCurrencyExchangeOptions(enCurrencyExchangeOptions option)
    {
        switch (option)
        {
        case enCurrencyExchangeOptions::eListCurrencies:
        {
            system("cls");
            _ShowAllCurrenciesListScreen();
            return _GoBackToCurrencyExchangeMenue();
        }
        case enCurrencyExchangeOptions::eFindCurrency:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            return _GoBackToCurrencyExchangeMenue();
        }
        case enCurrencyExchangeOptions::eUpdateRate:
        {
            system("cls");
            _ShowUpdateCurrencyRateScreen();
            return _GoBackToCurrencyExchangeMenue();
        }
        case enCurrencyExchangeOptions::eCurrencyCalculator:
        {
            system("cls");
            _ShowCurrencyCalculatorScreen();
            return _GoBackToCurrencyExchangeMenue();
        }
        case enCurrencyExchangeOptions::eMainMenue:
        {
            return true;
        }
        
        }
    }

public:


        static void showCurrencyExchangeMenue()
        {
            bool outOfExchangeMenue = false;

            while (!outOfExchangeMenue)
            {
                system("cls");
                _drawScreenHeader("\tCurrency Exhange Main Screen");

                cout << setw(37) << left << "" << "===========================================\n";
                cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
                cout << setw(37) << left << "" << "===========================================\n";
                cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
                cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
                cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
                cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
                cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
                cout << setw(37) << left << "" << "===========================================\n";

                outOfExchangeMenue = _PerformCurrencyExchangeOptions((enCurrencyExchangeOptions) _ReadCurrencyExchangeMenueOption());
            }  
        }

};

