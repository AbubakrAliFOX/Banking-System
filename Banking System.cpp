#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string FileName = "Bank.txt";
const string UsersFile = "Users.txt";

struct Client
{
    string Name;
    string AccountNumber, PinCode, Phone;
    float AccountBalance;
};

struct User
{
    string UserName;
    string Password;
    int Permissions;
};

User LogedInUser;

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

enum enMainMenuePermissions
{
    eAll = -1,
    pListClients = 1,
    pAddNewClient = 2,
    pDeleteClient = 4,
    pUpdateClients = 8,
    pFindClient = 16,
    pTranactions = 32,
    pManageUsers = 64
};

bool FindCustomer(string AccountNumber, Client &CurrentClient);
bool FindUser(string UserName, string Password, User &CurrentUser);
bool FindUser(string UserName, User &CurrentUser);
void ShowAccessDeniedMessage();
bool CheckPermission(enMainMenuePermissions Permission);
void GoBackToMainMenue();

int ReadPermissions()
{
    int Permissions = 0;
    char Answer = 'n';

    cout << "\nDo you want to give full access? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        return -1;
    }

    cout << "\nDo you want to give access to : \n ";
    cout << "\nShow Client List? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pListClients;
    }

    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pAddNewClient;
    }

    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pDeleteClient;
    }

    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pUpdateClients;
    }

    cout << "\nFind Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pFindClient;
    }

    cout << "\nTransactions? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pTranactions;
    }

    cout << "\nManage Users? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pManageUsers;
    }

    return Permissions;
}

Client CreateClient()
{
    Client ClientData;

    cout << "Enter Account Number? ";
    getline(cin >> ws, ClientData.AccountNumber);

    while (FindCustomer(ClientData.AccountNumber, ClientData))
    {
        cout << "[" << ClientData.AccountNumber << "] is already used. Please enter a different account number: ";
        getline(cin >> ws, ClientData.AccountNumber);
    };

    cout << "Enter PinCode? ";
    getline(cin, ClientData.PinCode);
    cout << "Enter Name? ";
    getline(cin, ClientData.Name);
    cout << "Enter Phone? ";
    getline(cin, ClientData.Phone);
    cout << "Enter AccountBalance? ";
    cin >> ClientData.AccountBalance;

    cout << "\n\n Client Created Successfully! \n\n"
         << endl;

    return ClientData;
}

User CreateUser()
{
    User UserData;

    cout << "Enter User Name? ";
    getline(cin >> ws, UserData.UserName);

    while (FindUser(UserData.UserName, UserData))
    {
        cout << "[" << UserData.UserName << "] is already used. Please enter a different user name: ";
        getline(cin >> ws, UserData.UserName);
    };

    cout << "\nEnter Password? ";
    getline(cin >> ws, UserData.Password);

    cout << "Enter Permissions? ";
    UserData.Permissions = ReadPermissions();

    cout << "\n\n User Created Successfully! \n\n"
         << endl;

    return UserData;
}

string ConvertRecordToLine(Client ClientData, string Seperator)
{
    string ClientRecord = "";
    ClientRecord += ClientData.Name + Seperator;
    ClientRecord += ClientData.AccountNumber + Seperator;
    ClientRecord += ClientData.PinCode + Seperator;
    ClientRecord += ClientData.Phone + Seperator;
    ClientRecord += to_string(ClientData.AccountBalance);
    return ClientRecord;
}

string ConvertRecordToLine(User UserData, string Seperator, bool IsUser)
{
    string UserRecord = "";
    UserRecord += UserData.UserName + Seperator;
    UserRecord += UserData.Password + Seperator;
    UserRecord += to_string(UserData.Permissions);
    return UserRecord;
}

Client ConvertLineToRecord(string DataLine, string Seperator)
{
    Client ClientData;
    vector<string> vData = split(DataLine, Seperator);

    ClientData.Name = vData[0];
    ClientData.AccountNumber = vData[1];
    ClientData.PinCode = vData[2];
    ClientData.Phone = vData[3];
    ClientData.AccountBalance = stof(vData[4]);

    return ClientData;
}

User ConvertLineToRecord(string DataLine, string Seperator, bool IsUser)
{
    User UserData;
    vector<string> vData = split(DataLine, Seperator);

    UserData.UserName = vData[0];
    UserData.Password = vData[1];
    UserData.Permissions = stoi(vData[2]);

    return UserData;
}

void AddCustomersToFile(string LineData, string File = "Bank.txt")
{
    fstream MyFile;

    MyFile.open(File, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << LineData << "\n";
        MyFile.close();
    }
}

void CreateCustomers()
{
    if (!CheckPermission(enMainMenuePermissions::pAddNewClient))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenue();
        return;
    }

    char Answer;
    short Counter = 0;
    do
    {
        Client CurrentClient;
        ++Counter;
        cout << "\n\nAdding Customer " << Counter << " : \n\n";

        string CustomerLineData = ConvertRecordToLine(CreateClient(), "##");
        AddCustomersToFile(CustomerLineData);

        Answer = ReadChar("Do you want to add more clients? (y / n)");

    } while (Answer == 'y' || Answer == 'Y');
}

void CreateUsers()
{
    char Answer;
    short Counter = 0;
    do
    {
        User CurrentUser;
        ++Counter;
        cout << "\n\nAdding User " << Counter << " : \n\n";

        string CustomerLineData = ConvertRecordToLine(CreateUser(), "##", true);
        AddCustomersToFile(CustomerLineData, "Users.txt");

        Answer = ReadChar("Do you want to add more clients? (y / n)");

    } while (Answer == 'y' || Answer == 'Y');
}

vector<Client> GetClientsFromFile()
{
    fstream MyFile;
    vector<Client> vAllClientsRecords;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {
            Client CurrentClient = ConvertLineToRecord(Line, "##");
            vAllClientsRecords.push_back(CurrentClient);
        }

        MyFile.close();
    }

    return vAllClientsRecords;
}

vector<User> GetUsersFromFile()
{
    fstream MyFile;
    vector<User> vAllUsersRecords;

    MyFile.open(UsersFile, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {
            User CurrentUser = ConvertLineToRecord(Line, "##", true);
            vAllUsersRecords.push_back(CurrentUser);
        }

        MyFile.close();
    }

    return vAllUsersRecords;
}

void PrintClientRecord(Client ClientData, bool ShowBalancesOnly)
{
    cout << "| " << setw(15) << left << ClientData.AccountNumber;
    cout << "| " << setw(40) << left << ClientData.Name;
    if (!ShowBalancesOnly)
    {
        cout << "| " << setw(10) << left << ClientData.PinCode;
        cout << "| " << setw(12) << left << ClientData.Phone;
    }
    cout << "| " << setw(12) << left << ClientData.AccountBalance;
}

void PrintUserRecord(User UserData)
{
    cout << "| " << setw(30) << left << UserData.UserName;
    cout << "| " << setw(30) << left << UserData.Password;
    cout << "| " << setw(30) << left << UserData.Permissions;
}

void PrintClientRecordInDetails(Client ClientData)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << ClientData.AccountNumber;
    cout << "\nPin Code     : " << ClientData.PinCode;
    cout << "\nName         : " << ClientData.Name;
    cout << "\nPhone        : " << ClientData.Phone;
    cout << "\nAccount Balance: " << ClientData.AccountBalance;
    cout << "\n-----------------------------------\n";
}

void PrintUserRecordInDetails(User UserData)
{
    cout << "\nThe following are the user details:\n";
    cout << "-----------------------------------";
    cout << "\nUser Name    : " << UserData.UserName;
    cout << "\nPassword     : " << UserData.Password;
    cout << "\nPermissions  : " << UserData.Permissions;
    cout << "\n-----------------------------------\n";
}

void PrintAllCustomer(bool ShowBalancesOnly = false)
{

    if (!ShowBalancesOnly)
    {
        if (!CheckPermission(enMainMenuePermissions::pListClients))
        {
            ShowAccessDeniedMessage();
            GoBackToMainMenue();
            return;
        }
    }

    vector<Client> vAllClients = GetClientsFromFile();
    float TotalBalances = 0;

    cout << "\n\t\t\t\t\tClient List (" << vAllClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    if (!ShowBalancesOnly)
    {
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Phone";
    }
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    for (Client &Client : vAllClients)
    {
        PrintClientRecord(Client, ShowBalancesOnly);
        TotalBalances += Client.AccountBalance;
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    if (ShowBalancesOnly)
    {
        cout << "\n_________________________________Total Balances: " << TotalBalances << "_________________________________________\n\n";
    }
}

void PrintAllUsers()
{
    vector<User> vAllUsers = GetUsersFromFile();
    float TotalBalances = 0;

    cout << "\n\t\t\t\t\tClient List (" << vAllUsers.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "| " << left << setw(30) << "User Name";
    cout << "| " << left << setw(30) << "Password";
    cout << "| " << left << setw(30) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    for (User &User : vAllUsers)
    {
        PrintUserRecord(User);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
}

bool FindCustomer(string AccountNumber, Client &CurrentClient)
{
    vector<Client> vAllClients = GetClientsFromFile();

    for (Client &u : vAllClients)
    {
        if (AccountNumber == u.AccountNumber)
        {
            CurrentClient = u;
            return true;
        }
    }

    return false;
}

bool FindUser(string UserName, string Password, User &CurrentUser)
{
    vector<User> vAllUsers = GetUsersFromFile();

    for (User &u : vAllUsers)
    {
        if (UserName == u.UserName && Password == u.Password)
        {
            CurrentUser = u;
            return true;
        }
    }

    return false;
}

bool FindUser(string UserName, User &CurrentUser)
{
    vector<User> vAllUsers = GetUsersFromFile();

    for (User &u : vAllUsers)
    {
        if (UserName == u.UserName)
        {
            CurrentUser = u;
            return true;
        }
    }
    return false;
}

void PrintCustomerSearchResult()
{

    if (!CheckPermission(enMainMenuePermissions::pFindClient))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenue();
        return;
    }

    string AccountNumber = ReadString("Please Enter Account Number: ");

    Client CurrentClient;

    if (FindCustomer(AccountNumber, CurrentClient))
    {
        PrintClientRecordInDetails(CurrentClient);
    }
    else
    {
        cout << "\n Client Not Found" << endl;
    }
}

void PrintUserSearchResult(string UserName)
{
    User CurrentUser;

    if (FindUser(UserName, CurrentUser))
    {
        PrintUserRecordInDetails(CurrentUser);
    }
    else
    {
        cout << "\n User Not Found" << endl;
    }
}

void OverwriteCutomersToFile(vector<Client> vClients)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (Client &u : vClients)
        {
            MyFile << ConvertRecordToLine(u, "##") << "\n";
        }

        MyFile.close();
    }
}

void OverwriteUsersToFile(vector<User> vUsers)
{
    fstream MyFile;

    MyFile.open(UsersFile, ios::out);

    if (MyFile.is_open())
    {
        for (User &u : vUsers)
        {
            MyFile << ConvertRecordToLine(u, "##", true) << "\n";
        }

        MyFile.close();
    }
}

void RemoveCustomerFromFile(string AccountNumber)
{
    vector<Client> vAllClients = GetClientsFromFile();
    vector<Client> vUpdatedClients;

    for (Client &u : vAllClients)
    {
        if (u.AccountNumber != AccountNumber)
        {
            vUpdatedClients.push_back(u);
        }
    }

    OverwriteCutomersToFile(vUpdatedClients);
}

void RemoveUserFromFile(string UserName)
{
    vector<User> vAllUsers = GetUsersFromFile();
    vector<User> vUpdatedUsers;

    for (User &u : vAllUsers)
    {
        if (u.UserName != UserName)
        {
            vUpdatedUsers.push_back(u);
        }
    }

    OverwriteUsersToFile(vUpdatedUsers);
}

void DeleteCustomer()
{
    if (!CheckPermission(enMainMenuePermissions::pDeleteClient))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenue();
        return;
    }

    string AccountNumber = ReadString("Please Enter Account Number: ");
    Client CurrentClient;
    char Answer;

    if (FindCustomer(AccountNumber, CurrentClient))
    {
        PrintClientRecordInDetails(CurrentClient);
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

void DeleteUser(string UserName)
{
    User CurrentUser;
    char Answer;

    if (FindUser(UserName, CurrentUser))
    {
        PrintUserRecordInDetails(CurrentUser);
        cout << "\n\nWould you like to delete this user? (y / n)" << endl;
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            RemoveUserFromFile(UserName);
            cout << "\n\n Deleted Successfully! \n\n";
        }
    }
    else
    {
        cout << "\n User Not Found" << endl;
    }
}

Client CreateUpdatedClient(string AccountNumber)
{
    Client ClientData;
    cout << "Enter PinCode? ";
    getline(cin >> ws, ClientData.PinCode);
    cout << "Enter Name? ";
    getline(cin, ClientData.Name);
    cout << "Enter Phone? ";
    getline(cin, ClientData.Phone);
    cout << "Enter AccountBalance? ";
    cin >> ClientData.AccountBalance;

    ClientData.AccountNumber = AccountNumber;

    return ClientData;
}

User CreateUpdatedUser(string UserName)
{
    User UserData;

    UserData.UserName = UserName;

    cout << "\nEnter Password? ";
    getline(cin >> ws, UserData.Password);

    cout << "Enter Permissions? ";
    cin >> UserData.Permissions;

    return UserData;
}

void UpdateCustomerInFile(string AccountNumber)
{
    vector<Client> vAllClients = GetClientsFromFile();
    Client UpdatedClient;

    for (Client &u : vAllClients)
    {
        if (u.AccountNumber == AccountNumber)
        {
            u = CreateUpdatedClient(AccountNumber);
            break;
        }
    }

    OverwriteCutomersToFile(vAllClients);
}

void UpdateUserInFile(string UserName)
{
    vector<User> vAllUsers = GetUsersFromFile();
    User UpdatedUser;

    for (User &u : vAllUsers)
    {
        if (u.UserName == UserName)
        {
            u = CreateUpdatedUser(UserName);
            break;
        }
    }

    OverwriteUsersToFile(vAllUsers);
}

void UpdateCustomer()
{

    if (!CheckPermission(enMainMenuePermissions::pUpdateClients))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenue();
        return;
    }

    string AccountNumber = ReadString("Please Enter Account Number: ");
    Client CurrentClient;
    char Answer;

    if (FindCustomer(AccountNumber, CurrentClient))
    {
        PrintClientRecordInDetails(CurrentClient);
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

void UpdateUser(string UserName)
{
    User CurrentUser;
    char Answer;

    if (FindUser(UserName, CurrentUser))
    {
        PrintUserRecordInDetails(CurrentUser);
        cout << "\n\nWould you like to update this user? (y / n)" << endl;
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            UpdateUserInFile(UserName);
            cout << "\n\n Updated Successfully! \n\n";
        }
    }
    else
    {
        cout << "\n User Not Found" << endl;
    }
}

void ShowMainMenue();

void ShowTransactionsMenu();

void LogInScreen();

void ShowManageUsersMenu();

void DepositOrWithdraw(string AccountNumber, string TransactionType)
{
    string Msg = "Please Enter " + TransactionType + " Amount: ";
    float Amount = ReadFloat(Msg);

    vector<Client> vAllClients = GetClientsFromFile();
    Client UpdatedClient;

    for (Client &u : vAllClients)
    {
        if (u.AccountNumber == AccountNumber)
        {
            UpdatedClient = u;
            if (TransactionType == "Withdrawal")
            {
                while (Amount > UpdatedClient.AccountBalance)
                {
                    cout << "The withdrawal amount exceeds the balance, you can withdraw up to " << UpdatedClient.AccountBalance << endl;
                    Amount = ReadFloat(Msg);
                }
                UpdatedClient.AccountBalance -= Amount;
            }
            else
            {
                UpdatedClient.AccountBalance += Amount;
            }

            u = UpdatedClient;
            break;
        }
    }

    char Answer = ReadChar("Are you sure you want to complete this transaction? (y / n)");

    if (Answer == 'Y' || Answer == 'y')
    {
        OverwriteCutomersToFile(vAllClients);
    }

    cout << "\n\n New Balance is:" << UpdatedClient.AccountBalance << "\n\n";
}

void ShowDepositOrWithdrawalMenu(string TransactionsType)
{
    cout << "================================================\n";
    cout << "          " << TransactionsType << "              \n";
    cout << "===============================================\n\n";

    Client CurrentClient;
    string AccountNumber = ReadString("Please Enter Account Number: ");

    while (!FindCustomer(AccountNumber, CurrentClient))
    {
        cout << "Client with [" << AccountNumber << "] Doesnt Exist." << endl;
        AccountNumber = ReadString("Please Enter Account Number: ");
    }

    PrintClientRecordInDetails(CurrentClient);
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
        PrintAllCustomer(true);
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

void ShowAccessDeniedMessage()
{
    cout << "\n------------------------------------\n";
    cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin.";
    cout << "\n------------------------------------\n";
}

bool CheckPermission(enMainMenuePermissions Permission)
{
    if (LogedInUser.Permissions == enMainMenuePermissions::eAll)
    {
        return true;
    }

    if ((Permission & LogedInUser.Permissions) == Permission)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void UsersOptions()
{
    char Answer;
    cin >> Answer;

    switch (Answer)
    {
    case '1':
        system("cls");
        PrintAllUsers();
        ShowManageUsersMenu();
        break;
    case '2':
        system("cls");
        CreateUsers();
        ShowManageUsersMenu();
        break;
    case '3':
        system("cls");
        DeleteUser(ReadString("Please Enter User Name: "));
        ShowManageUsersMenu();
        break;
    case '4':
        system("cls");
        UpdateUser(ReadString("Please Enter User Name: "));
        ShowManageUsersMenu();
        break;
    case '5':
        system("cls");
        PrintUserSearchResult(ReadString("Please Enter User Name: "));
        ShowManageUsersMenu();
        break;
    case '6':
        system("cls");
        ShowMainMenue();
        break;
    default:
        break;
    }
}

void ShowTransactionsMenu()
{

    if (!CheckPermission(enMainMenuePermissions::pTranactions))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenue();
        return;
    }

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

void ShowManageUsersMenu()
{

    if (!CheckPermission(enMainMenuePermissions::pManageUsers))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenue();
        return;
    }

    cout << "===========================================================================\n";
    cout << "                                 Users Manager                                \n";
    cout << "===========================================================================\n\n";
    cout << "        [1] List Users.                  \n";
    cout << "        [2] Add New User.                 \n";
    cout << "        [3] Delete User.           \n";
    cout << "        [4] Update User.                \n";
    cout << "        [5] Find User.                \n";
    cout << "        [6] Main Menu.                \n";

    cout << "\n What would you like to do? (1-4) \n";

    UsersOptions();
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...\n\n";
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
        DeleteCustomer();
        ShowMainMenue();
        break;
    case '4':
        system("cls");
        UpdateCustomer();
        ShowMainMenue();
        break;
    case '5':
        system("cls");
        PrintCustomerSearchResult();
        ShowMainMenue();
        break;
    case '6':
        system("cls");
        ShowTransactionsMenu();
        ShowMainMenue();
        break;
    case '7':
        system("cls");
        ShowManageUsersMenu();
        ShowMainMenue();
        break;
    case '8':
        system("cls");
        LogInScreen();
        break;
    default:
        cout << "Invalid Input!!!" << endl;
        ShowMainMenue();
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
    cout << "        [7] Manage Users.                   \n";
    cout << "        [8] Logout                            \n";

    cout << "\n What would you like to do? (1-8) \n";

    AppOptions();
}

void LogIn()
{
    string UserName = ReadString("Please Enter User Name: ");
    string Password = ReadString("Please Enter Password: ");

    while (!FindUser(UserName, Password, LogedInUser))
    {
        system("cls");
        cout << "Invalid Username/Password!" << endl;
        UserName = ReadString("Please Enter User Name: ");
        Password = ReadString("Please Enter Password: ");
    }

    system("cls");
    ShowMainMenue();
}

void LogInScreen()
{
    cout << "------------------------------------------------------------------------------\n";
    cout << "                                Log In Screen                                 \n";
    cout << "------------------------------------------------------------------------------\n\n";
    LogIn();
}

int main()
{
    LogInScreen();

    return 0;
}