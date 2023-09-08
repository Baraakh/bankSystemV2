#pragma once

#include <iostream>
#include <string>
#include "InterfaceCommunication.h"
using namespace std;

class clsPerson : public InterfaceCommunication
{
private:
	string _FirstName, _LastName, _Email, _Phone;

public:

	clsPerson(string firstName, string lastName, string email, string phone)
	{
		_FirstName = firstName;
		_LastName = lastName;
		_Email = email;
		_Phone = phone;
	}

	// firstName set propertie
	void setFirstName(string firstName)
	{
		_FirstName = firstName;
	}

	// firstName get propertie
	string getFirstName()
	{
		return _FirstName;
	}

	__declspec(property(get = getFirstName, put = setFirstName)) string firstName;

	// lastName set propertie
	void setLastName(string lastName)
	{
		_LastName = lastName;
	}

	// lastName get propertie
	string getLastName()
	{
		return _LastName;
	}

	__declspec(property(get = getLastName, put = setLastName)) string lastName;

	// email set propertie
	void setEmailName(string email)
	{
		_Email = email;
	}

	// email get propertie
	string getEmailName()
	{
		return _Email;
	}

	__declspec(property(get = getEmailName, put = setEmailName)) string email;

	// phone set propertie
	void setPhone(string phone)
	{
		_Phone = phone;
	}

	// phone get propertie
	string getPhone()
	{
		return _Phone;
	}

	__declspec(property(get = getPhone, put = setPhone)) string phone;

	string fullName()
	{
		return _FirstName + " " + _LastName;
	}
	
	void print()
	{
		cout << "\nInfo:";
		cout << "\n___________________";
		cout << "\nFirstName: " << _FirstName;
		cout << "\nLastName : " << _LastName;
		cout << "\nFull Name: " << fullName();
		cout << "\nEmail    : " << _Email;
		cout << "\nPhone    : " << _Phone;
		cout << "\n___________________\n";
	}

	void sendEmail(string Title, string Body)
	{

	}

	void sendFax(string Title, string Body)
	{

	}

	void sendSMS(string Title, string Body)
	{


	}

};

