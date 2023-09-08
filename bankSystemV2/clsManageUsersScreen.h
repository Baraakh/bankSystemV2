#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsListUsersScreen.h";
#include "clsAddNewUserScreen.h";
#include "clsDeleteUserScreen.h";
#include "clsUpdateUserScreen.h";
#include "clsFindUserScreen.h";

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:

    enum enManageUsersManueOptions
    {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
    };

    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadListNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static bool _GoBackToManageUsersMenue()
    {
        cout << "\n\nPress any key to go back to Manage Users Menue...";
        system("pause>0");
        
        return false;

    }

    static void _ShowAllUsersScreen()
    {
        clsListUsersScreen::showUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::showAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::showUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::ShowFindUserScreen();
    }

    static bool _PerfromManageUsersMenueOption(enManageUsersManueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enManageUsersManueOptions::eListUsers:
        {
            system("cls");
            _ShowAllUsersScreen();
            return _GoBackToManageUsersMenue();
            
        }
        case enManageUsersManueOptions::eAddNewUser:
        {
            system("cls");
            _ShowAddNewUserScreen();
            return _GoBackToManageUsersMenue();
            
        }
        case enManageUsersManueOptions::eDeleteUser:
        {
            system("cls");
            _ShowDeleteUserScreen();
            return _GoBackToManageUsersMenue();
            
        }
        case enManageUsersManueOptions::eUpdateUser:
        {
            system("cls");
            _ShowUpdateUserScreen();
            return _GoBackToManageUsersMenue();
            
        }
        case enManageUsersManueOptions::eFindUser:
        {
            system("cls");
            _ShowFindUserScreen();
            return _GoBackToManageUsersMenue();
                
        }
        case enManageUsersManueOptions::eMainMenue:
        {
            return true;
        }
            
        }

    }

public:

	static void showManageUsersMenue()
	{

        if (!checkAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;// this will exit the function and it will not tell the use access it.
        }

        bool outOfManageMenue = false;

        while (!outOfManageMenue)
        {
            system("cls");
            _drawScreenHeader("\t  Manage Users Screen");

            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] List Users.\n";
            cout << setw(37) << left << "" << "\t[2] Add New User.\n";
            cout << setw(37) << left << "" << "\t[3] Delete User.\n";
            cout << setw(37) << left << "" << "\t[4] Update User.\n";
            cout << setw(37) << left << "" << "\t[5] Find User.\n";
            cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            outOfManageMenue = _PerfromManageUsersMenueOption((enManageUsersManueOptions) _ReadMainMenueOption());
        }
        
	}

};

