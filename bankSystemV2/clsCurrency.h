#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>

class clsCurrency
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;


	static clsCurrency _ConvertLineToCurrencyObject(string line)
	{
		vector <string> currencyDataLine = clsString::Split(line, "#//#");

		return clsCurrency(enMode::UpdateMode, currencyDataLine[0], currencyDataLine[1], currencyDataLine[2], stod(currencyDataLine[3]));
	}

	static string _ConverCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
	{

		string stCurrencyRecord = "";
		stCurrencyRecord += Currency.country() + Seperator;
		stCurrencyRecord += Currency.currencyCode() + Seperator;
		stCurrencyRecord += Currency.currencyName() + Seperator;
		stCurrencyRecord += to_string(Currency.rate());

		return stCurrencyRecord;

	}

	static vector <clsCurrency> _LoadCurrenciesDataFromFile()
	{
		vector <clsCurrency> vCurrencys;

		fstream MyFile;
		MyFile.open("DBFile/Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;

			while (getline(MyFile, Line))
			{

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				vCurrencys.push_back(Currency);
			}

			MyFile.close();

		}

		return vCurrencys;
	}
		
	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencys)
	{

		fstream MyFile;
		MyFile.open("DBFile/Currencies.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsCurrency C : vCurrencys)
			{
				DataLine = _ConverCurrencyObjectToLine(C);
				MyFile << DataLine << endl;
			}

			MyFile.close();

		}

	}

	void _Update()
	{
		vector <clsCurrency> vCurrencys;
		vCurrencys = _LoadCurrenciesDataFromFile();

		for (clsCurrency& c : vCurrencys)
		{
			if (c.currencyCode() == _CurrencyCode)
			{
				c = *this;
				break;
			}
		}

		_SaveCurrencyDataToFile(vCurrencys);

	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode mode, string country, string currencyCode, string currencyName, float rate)
	{
		_Mode = mode;
		_Country = country;
		_CurrencyCode = currencyCode;
		_CurrencyName = currencyName;
		_Rate = rate;
	}

	bool isEmpty()
	{
		return enMode::EmptyMode == _Mode;
	}

	string country()
	{
		return _Country;
	}

	string currencyCode()
	{
		return _CurrencyCode;
	}

	string currencyName()
	{
		return _CurrencyName;
	}

	void updateRate(float newRate)
	{
		_Rate = newRate;
		_Update();
	}

	float rate()
	{
		return _Rate;
	}

	static clsCurrency findByCode(string currencyCode)
	{
		currencyCode = clsString::UpperAllString(currencyCode);

		fstream myFile;
		myFile.open("DBFile/Currencies.txt", ios::in);

		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				clsCurrency currency = _ConvertLineToCurrencyObject(line);
				if (currency.currencyCode() == currencyCode)
				{
					myFile.close();
					return currency;
				}
			}
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency findByCountry(string country)
	{
		country = clsString::UpperAllString(country);

		fstream myFile;
		myFile.open("DBFile/Currencies.txt", ios::in);

		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				clsCurrency currency = _ConvertLineToCurrencyObject(line);
				if (currency.country() == country)
				{
					myFile.close();
					return currency;
				}
			}
		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency C1 = clsCurrency::findByCode(CurrencyCode);
		return (!C1.isEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.currencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * Currency2.rate());

	}
};

