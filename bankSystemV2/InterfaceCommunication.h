#pragma once

#include <iostream>
#include <string>

using namespace std;

class InterfaceCommunication
{

public:
	virtual void sendEmail(string Title, string Body) = 0;
	virtual void sendFax(string Title, string Body) = 0;
	virtual void sendSMS(string Title, string Body) = 0;
};

