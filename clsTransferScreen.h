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

    static void _Transfer(clsBankClient Client1, clsBankClient Client2, double Amount)
    {
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
            Client1.Withdraw(Amount);
            Client2.Deposit(Amount);
            cout << "\nAmount Transfered Successfully.\n";
            _PrintClient(Client1);
            _PrintClient(Client2);
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
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

        _Transfer(Client1, Client2, Amount);
    }
};
