#pragma once

#include <iostream>
#include <string>
#include "clsPerson.h";
#include "clsString.h";
#include <vector>
#include <fstream>

class clsBankClient : public clsPerson
{
private:

	enum enMode {EmptyMode = 0, UpdateMode = 1, AddNewClientMode};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string line, string seperator = "#//#")
	{
		vector <string> vClientDate = clsString::Split(line, seperator);

		return clsBankClient(enMode::UpdateMode, vClientDate[0], vClientDate[1], vClientDate[2], vClientDate[3], vClientDate[4], vClientDate[5], stod(vClientDate[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient client, string seperator = "#//#")
	{
		return client.firstName + seperator +
			client.lastName + seperator +
			client.email + seperator +
			client.phone + seperator +
			client.accountNumber() + seperator +
			client.pinCode + seperator + 
			to_string(client.accountBalance);
	}

	struct stTransferLogRecord;
	static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string seperator = "#//#")
	{
		stTransferLogRecord transferLogRecord;

		vector <string> vtransferLogDateLine = clsString::Split(Line, seperator);

		transferLogRecord.dateTime = vtransferLogDateLine[0];
		transferLogRecord.sourceAcc = vtransferLogDateLine[1];
		transferLogRecord.destAcc = vtransferLogDateLine[2];
		transferLogRecord.TransferAmout = stod(vtransferLogDateLine[3]);
		transferLogRecord.sourceAccountBalance = stod(vtransferLogDateLine[4]);
		transferLogRecord.destAccountBalance = stod(vtransferLogDateLine[5]);
		transferLogRecord.username = vtransferLogDateLine[6];

		return transferLogRecord;
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;

		fstream DBFile;
		DBFile.open("DBFile/Clients.txt", ios::in);

		if (DBFile.is_open())
		{
			string line = "";

			while (getline(DBFile, line))
			{
				vClients.push_back(_ConvertLineToClientObject(line));
			}

			DBFile.close();
		}

		return vClients;
	}

	static void _SaveClientDataToFile(vector <clsBankClient> vClients)
	{
		fstream DBFile;
		DBFile.open("DBFile/Clients.txt", ios::out);


		if (DBFile.is_open())
		{
			string dataLine;

			for (clsBankClient client : vClients)
			{
				if (client.markedForDeleted() == false)
				{
					dataLine = _ConvertClientObjectToLine(client);

					DBFile << dataLine << endl;
				}
			}

			DBFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> _vClients;

		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& client : _vClients)
		{
			if (client.accountNumber() == _AccountNumber)
			{
				client = *this;
				break;
			}
		}

		_SaveClientDataToFile(_vClients);
	}

	void _AddDataLineToFile(string dataLine)
	{
		fstream DBFile;

		DBFile.open("DBFile/Clients.txt", ios::app | ios::out);

		if (DBFile.is_open())
		{
			DBFile << dataLine << endl;

			DBFile.close();
		}
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}
	
	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	 string _PerpareTransferLog(float amount, clsBankClient& destinationClient, string username,string Seperator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += _AccountNumber + Seperator;
		LoginRecord += destinationClient.accountNumber() + Seperator;
		LoginRecord += to_string(amount) + Seperator;
		LoginRecord += to_string(_AccountBalance) + Seperator;
		LoginRecord += to_string(destinationClient.accountBalance) + Seperator;
		LoginRecord += username;
		return LoginRecord;
	}

	 void _RegisterTransferLog(float amount, clsBankClient& destinationClient, string username)
	 {
		 string transferLogLine = _PerpareTransferLog(amount, destinationClient, username);

		 fstream myFile;

		 myFile.open("DBFile/TransferLog.txt", ios::out | ios::app);

		 if (myFile.is_open())
		 {
			 myFile << transferLogLine << endl;

			 myFile.close();
		 }
	 }

public:

	struct stTransferLogRecord
	{
		string dateTime;
		string sourceAcc;
		string destAcc;
		float TransferAmout;
		float sourceAccountBalance;
		float destAccountBalance;
		string username;
	};

	clsBankClient(enMode mode,string firstName, string lastName, string email, string phone, string accountNumber, string pinCode, float accountBalance)
		: clsPerson (firstName, lastName, email, phone)
	{
		_Mode = mode;
		_AccountNumber = accountNumber;
		_PinCode = pinCode;
		_AccountBalance = accountBalance;
	}

	bool isEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	// read only
	string accountNumber()
	{
		return _AccountNumber;
	}

	// set properties
	void setPinCode(string pinCode)
	{
		_PinCode = pinCode;
	}

	// get properties
	string getPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = getPinCode, put = setPinCode)) string pinCode;

	// set properties
	void setAccountBalance(float accountBalance)
	{
		_AccountBalance = accountBalance;
	}

	// get properties
	float getAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = getAccountBalance, put = setAccountBalance)) float accountBalance;

	bool markedForDeleted()
	{
		return _MarkedForDelete;
	}

	void deposit(double amount)
	{
		_AccountBalance += amount;
		save();
	}

	bool withdraw(double amount)
	{
		if (amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= amount;
			save();
			return true;
		}
	}

	static clsBankClient find(string accountNumber)
	{

		fstream DBFile;
		DBFile.open("DBFile/Clients.txt", ios::in);

		if (DBFile.is_open())
		{
			string line;
			while (getline(DBFile, line))
			{
				clsBankClient client = _ConvertLineToClientObject(line);
				if (client.accountNumber() == accountNumber)
				{
					DBFile.close();
					return client;
				}
			}

			DBFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient find(string accountNumber, string pinCode)
	{
		
		fstream DBFile;
		DBFile.open("DBFile/Clients.txt", ios::in);

		if (DBFile.is_open())
		{
			string line;
			while (getline(DBFile, line))
			{
				clsBankClient client = _ConvertLineToClientObject(line);

				if (client.accountNumber() == accountNumber && client.pinCode == pinCode)
				{
					DBFile.close();
					return client;
				}

			}

			DBFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient getNewClientObject(string accountNumber)
	{
		return clsBankClient(enMode::AddNewClientMode, "", "", "", "", accountNumber, "", 0);
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

	enSaveResults save()
	{
		switch (_Mode)
		{
		case clsBankClient::EmptyMode:
		{
			return enSaveResults::svFaildEmptyObject;
		}
		case clsBankClient::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
		}
		case clsBankClient::AddNewClientMode:
		{
			if (clsBankClient::isClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();

				//we need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}
		}
	}

	bool deleteClient()
	{
		try
		{
			vector <clsBankClient> vClients = clsBankClient::_LoadClientsDataFromFile();

			for (clsBankClient& client : vClients)
			{
				if (client.accountNumber() == _AccountNumber)
				{
					client._MarkedForDelete = true;
					break;
				}
			}

			_SaveClientDataToFile(vClients);

			*this = clsBankClient::_GetEmptyClientObject();

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	static bool isClientExist(string accountNumber)
	{

		clsBankClient client = clsBankClient::find(accountNumber);

		return !(client.isEmpty());
	}

	static vector <clsBankClient> getClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double getTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::getClientsList();

		double totalBalances = 0;

		for (clsBankClient& client : vClients)
		{
			totalBalances += client.accountBalance;
		}

		return totalBalances;
	}

	bool transfer(float amount, clsBankClient& destinationClient, string username)
	{
		if (amount > _AccountBalance)
		{
			return false;
		}

		withdraw(amount);
		destinationClient.deposit(amount);

		_RegisterTransferLog(amount, destinationClient, username);

		return true;
	}

	static vector <stTransferLogRecord> getTransferLogsList()
	{
		vector <stTransferLogRecord> vTransferLogs;

		fstream MyFile;
		MyFile.open("DBFile/TransferLog.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;

			stTransferLogRecord transferLogRecord;

			while (getline(MyFile, Line))
			{

				transferLogRecord = _ConvertTransferLogLineToRecord(Line);

				vTransferLogs.push_back(transferLogRecord);

			}

			MyFile.close();

		}

		return vTransferLogs;
	}
};

