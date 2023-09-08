#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h";
#include "clsScreen.h";

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:

    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.firstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.lastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.pinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.accountBalance = clsInputValidate::ReadNumber<float>();
    }

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.firstName;
        cout << "\nLastName    : " << Client.lastName;
        cout << "\nFull Name   : " << Client.fullName();
        cout << "\nEmail       : " << Client.email;
        cout << "\nPhone       : " << Client.phone;
        cout << "\nAcc. Number : " << Client.accountNumber();
        cout << "\nPassword    : " << Client.pinCode;
        cout << "\nBalance     : " << Client.accountBalance;
        cout << "\n___________________\n";

    }

public:

	static void showAddNewClientScreen()
	{

        if (!checkAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;// this will exit the function and it will not tell the use access it.
        }

        _drawScreenHeader("\t  Add New Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::isClientExist(AccountNumber))
        {
            cout << "\nAccount Number Is Already Used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::getNewClientObject(AccountNumber);


        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult = NewClient.save();

        switch (SaveResult)
        {
        case  clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Addeded Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;

        }
        }
	}

};

