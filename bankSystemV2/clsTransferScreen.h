#pragma once

#include <iostream>
#include <cmath>
#include "clsScreen.h";
#include "clsBankClient.h";
#include "clsInputValidate.h";

class clsTransferScreen : protected clsScreen
{

private:

	static clsBankClient _GetClient(string errorMessage)
	{
		string AccountNumber;

		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::isClientExist(AccountNumber))
		{
			cout << errorMessage;
			AccountNumber = clsInputValidate::ReadString();
		}

		return clsBankClient::find(AccountNumber);
	}

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.fullName();
		cout << "\nAcc. Number : " << Client.accountNumber();
		cout << "\nBalance     : " << Client.accountBalance;
		cout << "\n___________________\n";
	}

	static float _ReadAmount(clsBankClient& clientTransferFrom)
	{
		float Amount = 0;
		cout << "\nEnter Transfer Amount? ";
		Amount = abs(clsInputValidate::ReadNumber<double>());

		while (clientTransferFrom.accountBalance < Amount)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount? ";
			Amount = clsInputValidate::ReadNumber<double>();
		}

		return Amount;
	}

public:
	
	static void showTransferScreen()
	{

		_drawScreenHeader("\t    Transfer Screen");

		cout << "\nPlease Enter Account Number to Transfer From: ";
		clsBankClient clientTransferFrom = _GetClient("\nAccount number is not found, choose another one to Transfer From: ");

		_PrintClient(clientTransferFrom);


		cout << "\nPlease Enter Account Number to Transfer To: ";
		clsBankClient clientTransferTo = _GetClient("\nAccount number is not found, choose another one to Transfer To: ");

		_PrintClient(clientTransferTo);

		double amount = _ReadAmount(clientTransferFrom);

		cout << "\nAre you sure you want to perform this operation? (Y/N)";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (clientTransferFrom.transfer(amount, clientTransferTo, currentUser.userName))
			{
				cout << "\nTransfer done successfully\n";
			}
			else
			{
				cout << "\nTransfer Faild \n";
			}

			_PrintClient(clientTransferFrom);
			_PrintClient(clientTransferTo);
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}


	}
};

