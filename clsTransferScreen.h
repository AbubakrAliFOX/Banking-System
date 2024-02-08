#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{

private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

    static string _ReadAccountNumber(string Msg = "Please enter AccountNumber? ")
    {
        string AccountNumber = "";
        cout << "\n"
             << Msg;
        cin >> AccountNumber;
        return AccountNumber;
    }

    static clsBankClient _GetClient(string Accountnumber)
    {
        while (!clsBankClient::IsClientExist(Accountnumber))
        {
            cout << "\nClient with [" << Accountnumber << "] does not exist.\n";
            Accountnumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(Accountnumber);
        _PrintClient(Client);
        return Client;
    }

public:
    static void ShowTransfer()
    {
        _DrawScreenHeader("\t   Transfer Screen");

        // From
        clsBankClient Client1 = _GetClient(_ReadAccountNumber("Enter the account you want to transfer from: "));

        // To
        clsBankClient Client2 = _GetClient(_ReadAccountNumber("Enter the account you want to transfer to: "));

        double Amount = 0;
        cout << "\nPlease enter transfer amount? ";
        Amount = clsInputValidate::ReadDblNumber();

        while (Client1.AccountBalance < Amount)
        {
            cout << "\nAmount exceeds the avaliable balance, please enter another amount:";
            Amount = clsInputValidate::ReadDblNumber();
        }

        cout << "\nAre you sure you want to perform this transaction? (y / n)";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client1.Transfer(Amount, Client2))
            {
                cout << "\nSuccessfully transfered\n";
                _PrintClient(Client1);
                _PrintClient(Client2);
            }
            else
            {
                cout << "\nTransfer failed\n!!";
            }
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }
};
