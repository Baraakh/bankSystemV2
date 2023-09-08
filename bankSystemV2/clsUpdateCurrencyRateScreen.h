#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:

    static float _ReadRate()
    {
        cout << "\nEnter New Rate: ";
        float NewRate = 0;

        NewRate = clsInputValidate::ReadNumber<float>();
        return NewRate;
    }

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.country();
        cout << "\nCode       : " << Currency.currencyCode();
        cout << "\nName       : " << Currency.currencyName();
        cout << "\nRate(1$) = : " << Currency.rate();

        cout << "\n_____________________________\n";

    }

public:

    static void ShowUpdateCurrencyRateScreen()
    {

        _drawScreenHeader("\tUpdate Currency Screen");

        string CurrencyCode = "";

        cout << "\nPlease Enter Currency Code: ";
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::findByCode(CurrencyCode);
        _PrintCurrency(Currency);

        cout << "\nAre you sure you want to update the rate of this Currency y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            cout << "\n\nUpdate Currency Rate:";
            cout << "\n____________________\n";

            Currency.updateRate(_ReadRate());

            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrency(Currency);


        }

    }
};

