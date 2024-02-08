#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <fstream>
#include "clsBankClient.h"

class clsTransferLogScreen : protected clsScreen
{

private:
    static void PrintTransferRegisterRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
    {

        cout << setw(8) << left << ""
             << "| " << setw(25) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(8) << left << TransferLogRecord.SourceClientAcct;
        cout << "| " << setw(8) << left << TransferLogRecord.DestionationClientAcct;
        cout << "| " << setw(8) << left << TransferLogRecord.Amount;
        cout << "| " << setw(12) << left << TransferLogRecord.SourceClientBalance;
        cout << "| " << setw(12) << left << TransferLogRecord.DestionationClientBalance;
        cout << "| " << setw(8) << left << TransferLogRecord.UserName;
    }

public:
    static void ShowTransferLogScreen()
    {

        vector<clsBankClient::stTransferLogRecord> vTransferRegisterRecord = clsBankClient::GetTranferRegisterList();

        string Title = "\tTransfer Log Screen";
        string SubTitle = "\t\t(" + to_string(vTransferRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;

        cout << setw(8) << left << ""
             << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(12) << "s.Balance";
        cout << "| " << left << setw(12) << "d.Balance";
        cout << "| " << left << setw(8) << "User";
        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;

        if (vTransferRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (clsBankClient::stTransferLogRecord Record : vTransferRegisterRecord)
            {

                PrintTransferRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
    }
};
