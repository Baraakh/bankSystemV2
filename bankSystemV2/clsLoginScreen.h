#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsMainScreen.h";
#include "clsUser.h";
#include "Global.h";

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:

	static bool _Login()
	{
		
		bool loginFaild = false;

		string userName, password;

		unsigned short numberOfTrials = 3;

		do
		{
			
			if (loginFaild)
			{
				numberOfTrials--;

				if (0 == numberOfTrials)
				{
					cout << "\nYour are Locked after 3 faild trials\n";
					return false;
				}

				cout << "\nInvlaid Username/Password!\n";
				cout << "\nYou have " << numberOfTrials << " Trial(s) to login.\n\n";
			}

			cout << "Enter Username? ";
			cin >> userName;

			cout << "Enter Password? ";
			cin >> password;

			currentUser = clsUser::find(userName, password);

			loginFaild = currentUser.isEmpty();


		} while (loginFaild);

		// save user data with the date in the Log file
		currentUser.RegisterLogIn();

		clsMainScreen::showMainMenue();	
		return true;
	}

public:

	static void showLoginScreen()
	{

		while (true)
		{
			system("cls");
			_drawScreenHeader("\t     Login Screen");

			if (!_Login()) // if it returns false then the user wasted all his trails.
			{
				break;
			}
		} 		
	}

};

