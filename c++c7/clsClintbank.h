#pragma once
#include <iostream>
#include <string>
#include "Person.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include"clsDate.h"
using namespace std;
class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData = clsString::Split(Line, Seperator);

        clsBankClient client(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

        if (vClientData.size() == 8)
            client._MarkedForDelete = (vClientData[7] == "1");

        return client;
    }

    struct stLoginRegisterRecord;
    
    string _PrepareLogInRecord(string Seperator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += AccountNumber() + Seperator;
        LoginRecord += PinCode + Seperator;
        return LoginRecord;
    }
    string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
        string UserName, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += AccountNumber() + Seperator;
        TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }
    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {
        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance) + Seperator;
        stClientRecord += (Client.MarkedForDeleted() ? "1" : "0");

        return stClientRecord;
    }
    void _RegisterTransfer(float Amount, clsBankClient DestinationClient, string UserName)
    {

        string stDataLine = _PrepareTransferLogRecord( Amount,  DestinationClient,  UserName);

        fstream MyFile;
        MyFile.open("TransferRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }
    static vector<clsBankClient> _LoadClientsDataFromFile()
    {
        vector<clsBankClient> vClients;
        fstream MyFile("Clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return vClients;
    }
    struct stTransferLogRecord;
    static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        vector<string> vData = clsString::Split(Line, Seperator);

        stTransferLogRecord Record;

        if (vData.size() == 7)
        {
            Record.DateTime = vData[0];
            Record.SourceAccount = vData[1];
            Record.DestinationAccount = vData[2];
            Record.Amount = stof(vData[3]);
            Record.SourceBalanceAfter = stof(vData[4]);
            Record.DestinationBalanceAfter = stof(vData[5]);
            Record.PerformedBy = vData[6];
        }

        return Record;
    }

    static vector<stTransferLogRecord> _LoadTransferLogFromFile()
    {
        vector<stTransferLogRecord> vTransferLog;

        fstream MyFile;
        MyFile.open("TransferRegister.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                stTransferLogRecord Record = _ConvertTransferLogLineToRecord(Line);
                vTransferLog.push_back(Record);
            }

            MyFile.close();
        }

        return vTransferLog;
    }
    static void _SaveCleintsDataToFile(vector<clsBankClient> vClients)
    {
        fstream MyFile("Clients.txt", ios::out);
        string DataLine;
        if (MyFile.is_open())
        {
            for (clsBankClient C : vClients)
            {
                if (!C.MarkedForDeleted())
                {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsBankClient> _vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }
        _SaveCleintsDataToFile(_vClients);
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile("Clients.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:
  
    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }
   static struct stTransferLogRecord
    {
       string DateTime;
       string SourceAccount;
       string DestinationAccount;
       float Amount;
       float SourceBalanceAfter;
       float DestinationBalanceAfter;
       string PerformedBy;
    };
    bool IsEmpty() { return (_Mode == enMode::EmptyMode); }
    bool MarkedForDeleted() { return _MarkedForDelete; }
    string AccountNumber() { return _AccountNumber; }

    void SetPinCode(string PinCode) { _PinCode = PinCode; }
    string GetPinCode() { return _PinCode; }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance) { _AccountBalance = AccountBalance; }
    float GetAccountBalance() { return _AccountBalance; }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

 

    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        fstream MyFile("Clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }
    static clsBankClient Find( string PinCode)
    {
        fstream MyFile("Clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if ( Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }


    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
            if (IsEmpty()) return enSaveResults::svFaildEmptyObject;
        case enMode::UpdateMode:
            _Update(); return enSaveResults::svSucceeded;
        case enMode::AddNewMode:
            if (clsBankClient::IsClientExist(_AccountNumber)) return enSaveResults::svFaildAccountNumberExists;
            else { _AddNew(); _Mode = enMode::UpdateMode; return enSaveResults::svSucceeded; }
        }
    }

    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }
    static bool IsPasswordExist(string Pincode)
    {
        clsBankClient Client1 = clsBankClient::Find(Pincode);
        return (!Client1.IsEmpty());
    }

    bool Delete()
    {
        vector<clsBankClient> _vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }
        }
        _SaveCleintsDataToFile(_vClients);
        *this = _GetEmptyClientObject();
        return true;
    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }
    static vector<clsBankClient> printlist()
    {
        return _LoadClientsDataFromFile();
    }

    bool Deposite(double Amount)
    {
        
            _AccountBalance += Amount;
            Save();
            return Amount;
    }
    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
        }
    }

     bool Transfer(double Amount,clsBankClient &distnasion,string UserName)
    {
        if (Amount > AccountBalance)
        {
            return false;
        }
        Withdraw(Amount);
        distnasion.Deposite(Amount);
        _RegisterTransfer(Amount, distnasion, UserName);
        return true;
    }
    static double GetTotalBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::printlist();

        double TotalBalances = 0;

        for (clsBankClient Client : vClients)
        {

            TotalBalances += Client.AccountBalance;
        }

        return TotalBalances;
    }


    vector<stTransferLogRecord> GetMyTransferLog()
    {
        vector<stTransferLogRecord> AllTransfers = _LoadTransferLogFromFile();
        vector<stTransferLogRecord> MyTransfers;

        for (const stTransferLogRecord& Record : AllTransfers)
        {
            if (Record.SourceAccount == AccountNumber() || Record.DestinationAccount == AccountNumber())
            {
                MyTransfers.push_back(Record);
            }
        }

        return MyTransfers;
    }

   
   
};