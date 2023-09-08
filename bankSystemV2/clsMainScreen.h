#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include "clsInputValidate.h";
#include "clsScreen.h";
#include "clsClientListScreen.h"; 
#include "clsAddNewClientScreen.h";
#include "clsDeleteClientScreen.h";
#include "clsUpdateClientScreen.h";
#include "clsFindClientScreen.h";
#include "clsTransactionsScreen.h";
#include "clsManageUsersScreen.h";
#include "clsLoginRegisterScreen.h";
#include "clsCurrencyExchangeScreen.h";
#include "Global.h";

using namespace std;


class clsMainScreen : protected clsScreen
{

private:

    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9, eExit = 10
    };

    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short Choice = clsInputValidate::ReadListNumberBetween(1, 10, "Enter Number between 1 to 10? ");
        return Choice;
    }

    static  bool _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");

        return false;
    }

    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::showClientsList();
    }

    static void _ShowAddNewClientScreen()
    {
        clsAddNewClientScreen::showAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue()
    {
        clsManageUsersScreen::showManageUsersMenue();
    }

    static void _ShowLoginRegisterScreen()
    {
        clsLoginRegisterScreen::showLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeMenueScreen()
    {
        clsCurrencyExchangeScreen::showCurrencyExchangeMenue();
    }

    static void _Logout()
    {
        currentUser = clsUser::find("", "");
    }

    static bool _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            return _GoBackToMainMenue();
        }
        case enMainMenueOptions::eAddNewClient:
        {
            system("cls");
            _ShowAddNewClientScreen();
            return _GoBackToMainMenue(); 
        }
        case enMainMenueOptions::eDeleteClient:
        {
            system("cls");
            _ShowDeleteClientScreen();
            return _GoBackToMainMenue();
        }
        case enMainMenueOptions::eUpdateClient:
        {
            system("cls");
            _ShowUpdateClientScreen();
            return _GoBackToMainMenue(); 
        }
        case enMainMenueOptions::eFindClient:
        {
            system("cls");
            _ShowFindClientScreen();
            return _GoBackToMainMenue();     
        }
        case enMainMenueOptions::eShowTransactionsMenue:
        {
            system("cls");
            _ShowTransactionsMenue();
            return false();    
        }
        case enMainMenueOptions::eManageUsers:
        {
            system("cls");
            _ShowManageUsersMenue();
            return false;
        }
        case enMainMenueOptions::eLoginRegister:
        {
            system("cls");
            _ShowLoginRegisterScreen();
            return _GoBackToMainMenue();
        }
        case enMainMenueOptions::eCurrencyExchange:
        {
            system("cls");
            _ShowCurrencyExchangeMenueScreen();
            return false;
        }
        case enMainMenueOptions::eExit:
        {
            system("cls");
            _Logout();
            return true;
        }
            
        }

    }

public:

	static void showMainMenue()
	{
        bool outOfMainMenue = false;

        while (!outOfMainMenue)
        {
            system("cls");
            _drawScreenHeader("\t\tMain Screen");

            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
            cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
            cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
            cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
            cout << setw(37) << left << "" << "\t[5] Find Client.\n";
            cout << setw(37) << left << "" << "\t[6] Transactions.\n";
            cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
            cout << setw(37) << left << "" << "\t[8] Login Register.\n";
            cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
            cout << setw(37) << left << "" << "\t[10] Logout.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            outOfMainMenue = _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
        }
        
	}
};

