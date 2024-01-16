#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string FileName = "Bank.txt";

char ReadChar(string Msg)
{
    char charachter;
    cout << Msg << endl;
    cin >> charachter;

    return charachter;
}

string ReadString(string Msg)
{
    string Str;
    cout << Msg << "\n";
    cin >> Str;
    return Str;
}

float ReadFloat(string Msg)
{
    float Number;
    cout << Msg << "\n";
    cin >> Number;
    return Number;
}

struct User
{
    string Name;
    string AccountNumber, PinCode, Phone;
    float AccountBalance;
};

vector<string> split(string Str, string Delim)
{

    short pos = 0;
    string sWord; // define a string variable  // use find() function to get the position of the delimiters
    short Counter = 0;
    vector<string> vWords;
    while ((pos = Str.find(Delim)) != std::string::npos)
    {
        sWord = Str.substr(0, pos); // store the word
        if (sWord != "")
        {
            vWords.push_back(sWord);
            Counter++;
        }
        Str.erase(0, pos + Delim.length()); /* erase() until positon and move to next word. */
    }
    if (Str != "")
    {
        vWords.push_back(Str); // it print last word of the string.
        Counter++;
    }

    return vWords;
}

bool FindCustomer(string AccountNumber, User &CurrentUser);

User CreateUser()
{
    User UserData;

    cout << "Enter Account Number? ";
    getline(cin >> ws, UserData.AccountNumber);

    while (FindCustomer(UserData.AccountNumber, UserData))
    {
        cout << "[" << UserData.AccountNumber << "] is already used. Please enter a different account number: ";
        getline(cin >> ws, UserData.AccountNumber);
    };

    cout << "Enter PinCode? ";
    getline(cin, UserData.PinCode);
    cout << "Enter Name? ";
    getline(cin, UserData.Name);
    cout << "Enter Phone? ";
    getline(cin, UserData.Phone);
    cout << "Enter AccountBalance? ";
    cin >> UserData.AccountBalance;

    cout << "\n\n Client Created Successfully! \n\n"
         << endl;

    return UserData;
}

string ConvertRecordToLine(User UserData, string Seperator)
{
    string ClientRecord = "";
    ClientRecord += UserData.Name + Seperator;
    ClientRecord += UserData.AccountNumber + Seperator;
    ClientRecord += UserData.PinCode + Seperator;
    ClientRecord += UserData.Phone + Seperator;
    ClientRecord += to_string(UserData.AccountBalance);
    return ClientRecord;
}

User ConvertLineToRecord(string DataLine, string Seperator)
{
    User UserData;
    vector<string> vData = split(DataLine, Seperator);

    UserData.Name = vData[0];
    UserData.AccountNumber = vData[1];
    UserData.PinCode = vData[2];
    UserData.Phone = vData[3];
    UserData.AccountBalance = stof(vData[4]);

    return UserData;
}

void AddCustomersToFile(string LineData)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << LineData << "\n";
        MyFile.close();
    }
}

void CreateCustomers()
{
    char Answer;
    short Counter = 0;
    do
    {
        User CurrentUser;
        ++Counter;
        cout << "\n\nAdding Customer " << Counter << " : \n\n";

        string CustomerLineData = ConvertRecordToLine(CreateUser(), "##");
        AddCustomersToFile(CustomerLineData);

        Answer = ReadChar("Do you want to add more users? (y / n)");

    } while (Answer == 'y' || Answer == 'Y');
}

vector<User> GetUsersFromFile()
{
    fstream MyFile;
    vector<User> vAllUsersRecords;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {
            User CurrentUser = ConvertLineToRecord(Line, "##");
            vAllUsersRecords.push_back(CurrentUser);
        }

        MyFile.close();
    }

    return vAllUsersRecords;
}

void PrintClientRecord(User UserData)
{
    cout << "| " << setw(15) << left << UserData.AccountNumber;
    cout << "| " << setw(10) << left << UserData.PinCode;
    cout << "| " << setw(40) << left << UserData.Name;
    cout << "| " << setw(12) << left << UserData.Phone;
    cout << "| " << setw(12) << left << UserData.AccountBalance;
}

void PrintClientRecordInDetails(User UserData)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << UserData.AccountNumber;
    cout << "\nPin Code     : " << UserData.PinCode;
    cout << "\nName         : " << UserData.Name;
    cout << "\nPhone        : " << UserData.Phone;
    cout << "\nAccount Balance: " << UserData.AccountBalance;
    cout << "\n-----------------------------------\n";
}

void PrintAllCustomer()
{
    vector<User> vAllUsers = GetUsersFromFile();

    cout << "\n\t\t\t\t\tClient List (" << vAllUsers.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    for (User &User : vAllUsers)
    {
        PrintClientRecord(User);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
}

bool FindCustomer(string AccountNumber, User &CurrentUser)
{
    vector<User> vAllUsers = GetUsersFromFile();

    for (User &u : vAllUsers)
    {
        if (AccountNumber == u.AccountNumber)
        {
            CurrentUser = u;
            return true;
        }
    }

    return false;
}

void PrintCustomerSearchResult(string AccountNumber)
{
    User CurrentUser;

    if (FindCustomer(AccountNumber, CurrentUser))
    {
        PrintClientRecordInDetails(CurrentUser);
    }
    else
    {
        cout << "\n Client Not Found" << endl;
    }
}

void OverwriteCutomersToFile(vector<User> vUsers)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (User &u : vUsers)
        {
            MyFile << ConvertRecordToLine(u, "##") << "\n";
        }

        MyFile.close();
    }
}

void RemoveCustomerFromFile(string AccountNumber)
{
    vector<User> vAllUsers = GetUsersFromFile();
    vector<User> vUpdatedUsers;

    for (User &u : vAllUsers)
    {
        if (u.AccountNumber != AccountNumber)
        {
            vUpdatedUsers.push_back(u);
        }
    }

    OverwriteCutomersToFile(vUpdatedUsers);
}

void DeleteCustomer(string AccountNumber)
{
    User CurrentUser;
    char Answer;

    if (FindCustomer(AccountNumber, CurrentUser))
    {
        PrintClientRecordInDetails(CurrentUser);
        cout << "\n\nWould you like to delete this customer? (y / n)" << endl;
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            RemoveCustomerFromFile(AccountNumber);
            cout << "\n\n Deleted Successfully! \n\n";
        }
    }
    else
    {
        cout << "\n Client Not Found" << endl;
    }
}

User CreateUpdatedUser(string AccountNumber)
{
    User UserData;
    cout << "Enter PinCode? ";
    getline(cin >> ws, UserData.PinCode);
    cout << "Enter Name? ";
    getline(cin, UserData.Name);
    cout << "Enter Phone? ";
    getline(cin, UserData.Phone);
    cout << "Enter AccountBalance? ";
    cin >> UserData.AccountBalance;

    UserData.AccountNumber = AccountNumber;

    return UserData;
}

void UpdateCustomerInFile(string AccountNumber)
{
    vector<User> vAllUsers = GetUsersFromFile();
    User UpdatedUser;

    for (User &u : vAllUsers)
    {
        if (u.AccountNumber == AccountNumber)
        {
            u = CreateUpdatedUser(AccountNumber);
            break;
        }
    }

    OverwriteCutomersToFile(vAllUsers);
}

void UpdateCustomer(string AccountNumber)
{
    User CurrentUser;
    char Answer;

    if (FindCustomer(AccountNumber, CurrentUser))
    {
        PrintClientRecordInDetails(CurrentUser);
        cout << "\n\nWould you like to update this customer? (y / n)" << endl;
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            UpdateCustomerInFile(AccountNumber);
            cout << "\n\n Updated Successfully! \n\n";
        }
    }
    else
    {
        cout << "\n Client Not Found" << endl;
    }
}

void ShowMainMenue();

void ShowTransactionsMenu();

void DepositOrWithdraw(string AccountNumber, string TransactionType)
{
    string Msg = "Please Enter " + TransactionType + " Amount: ";
    float Amount = ReadFloat(Msg);

    char Answer = ReadChar("Are you sure you want to complete this transaction? (y / n)");

    if (Answer == 'Y' || Answer == 'y')
    {
        vector<User> vAllUsers = GetUsersFromFile();
        User UpdatedUser;

        for (User &u : vAllUsers)
        {
            if (u.AccountNumber == AccountNumber)
            {
                UpdatedUser = u;
                TransactionType == "Deposit" ? UpdatedUser.AccountBalance += Amount : UpdatedUser.AccountBalance -= Amount;
                u = UpdatedUser;
                break;
            }
        }

        cout << "\n\n New Balance is:" << UpdatedUser.AccountBalance << "\n\n";

        OverwriteCutomersToFile(vAllUsers);
    }
}

void ShowDepositOrWithdrawalMenu(string TransactionsType)
{
    cout << "================================================\n";
    cout << "          " << TransactionsType << "              \n";
    cout << "===============================================\n\n";

    User CurrentUser;
    string AccountNumber = ReadString("Please Enter Account Number: ");

    while (!FindCustomer(AccountNumber, CurrentUser))
    {
        cout << "Client with [" << AccountNumber << "] Doesnt Exist." << endl;
        AccountNumber = ReadString("Please Enter Account Number: ");

    }

    PrintClientRecordInDetails(CurrentUser);
    DepositOrWithdraw(AccountNumber, TransactionsType);
}

void TransactionsOptions()
{
    char Answer;
    cin >> Answer;

    switch (Answer)
    {
    case '1':
        system("cls");
        ShowDepositOrWithdrawalMenu("Deposit");
        ShowTransactionsMenu();
        break;
    case '2':
        system("cls");
        ShowDepositOrWithdrawalMenu("Withdrawal");
        ShowTransactionsMenu();
        break;
    case '3':
        system("cls");
        DeleteCustomer(ReadString("Please Enter Account Number: "));
        ShowTransactionsMenu();
        break;
    case '4':
        system("cls");
        ShowMainMenue();
        break;
    default:
        break;
    }
}

void ShowTransactionsMenu()
{
    cout << "===========================================================================\n";
    cout << "                                 Transactions                                \n";
    cout << "===========================================================================\n\n";
    cout << "        [1] Deposit.                  \n";
    cout << "        [2] Withdraw.                 \n";
    cout << "        [3] Total Balances.           \n";
    cout << "        [4] Main Menu.                \n";

    cout << "\n What would you like to do? (1-4) \n";

    TransactionsOptions();
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}

void AppOptions()
{
    char Answer;
    cin >> Answer;

    switch (Answer)
    {
    case '1':
        system("cls");
        PrintAllCustomer();
        ShowMainMenue();
        break;
    case '2':
        system("cls");
        CreateCustomers();
        ShowMainMenue();
        break;
    case '3':
        system("cls");
        DeleteCustomer(ReadString("Please Enter Account Number: "));
        ShowMainMenue();
        break;
    case '4':
        system("cls");
        UpdateCustomer(ReadString("Please Enter Account Number: "));
        ShowMainMenue();
        break;
    case '5':
        system("cls");
        PrintCustomerSearchResult(ReadString("Please Enter Account Number: "));
        ShowMainMenue();
        break;
    case '6':
        system("cls");
        ShowTransactionsMenu();
        ShowMainMenue();
        break;
    case '7':
        system("cls");
        break;
    default:
        break;
    }
}

void ShowMainMenue()
{
    cout << "===========================================================================\n";
    cout << "                                 Main Menu                                 \n";
    cout << "===========================================================================\n\n";
    cout << "        [1] Show Client List.               \n";
    cout << "        [2] Add New Client.                 \n";
    cout << "        [3] Delete Client.                  \n";
    cout << "        [4] Update Client Info.             \n";
    cout << "        [5] Find Client.                    \n";
    cout << "        [6] Transactions.                   \n";
    cout << "        [7] Exit                            \n";

    cout << "\n What would you like to do? (1-7) \n";

    AppOptions();
}

int main()
{
    ShowMainMenue();

    return 0;
}