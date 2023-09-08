#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsBankClient.h";
#include <vector>

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:

    static void printTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.dateTime;
        cout << "| " << setw(8) << left << TransferLogRecord.sourceAcc;
        cout << "| " << setw(8) << left << TransferLogRecord.destAcc;
        cout << "| " << setw(8) << left << TransferLogRecord.TransferAmout;
        cout << "| " << setw(10) << left << TransferLogRecord.sourceAccountBalance;
        cout << "| " << setw(10) << left << TransferLogRecord.destAccountBalance;
        cout << "| " << setw(8) << left << TransferLogRecord.username;


    }

public:

	static void showTransferLogScreen()
	{

		vector <clsBankClient::stTransferLogRecord> vTransferLogRecords = clsBankClient::getTransferLogsList();

		_drawScreenHeader("\t    Transfer Log List Screen", "\t    (" + to_string(vTransferLogRecords.size()) + ")" + " Record(s).");

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecords.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (clsBankClient::stTransferLogRecord Record : vTransferLogRecords)
            {

                printTransferLogRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

	}

};

