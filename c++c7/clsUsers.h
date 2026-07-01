#pragma once
#include <iostream>
#include <string>
#include "Person.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;

    string _UserName;
    string _Password;
    int _Permissions;

    bool _MarkedForDelete = false;

public:

    struct stLoginRegisterRecord
    {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;
    };

private:

    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stLoginRegisterRecord rec;

        vector<string> data = clsString::Split(Line, Seperator);

        rec.DateTime = data[0];
        rec.UserName = data[1];
        rec.Password = data[2];
        rec.Permissions = stoi(data[3]);

        return rec;
    }

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData = clsString::Split(Line, Seperator);

        return clsUser(
            enMode::UpdateMode,
            vUserData[0],
            vUserData[1],
            vUserData[2],
            vUserData[3],
            vUserData[4],
            vUserData[5],
            stoi(vUserData[6])
        );
    }

    string _PrepareLogInRecord(string Seperator = "#//#")
    {
        string rec;
        rec += clsDate::GetSystemDateTimeString() + Seperator;
        rec += UserName + Seperator;
        rec += Password + Seperator;
        rec += to_string(Permissions);
        return rec;
    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string line;

        line += User.FirstName + Seperator;
        line += User.LastName + Seperator;
        line += User.Email + Seperator;
        line += User.Phone + Seperator;
        line += User.UserName + Seperator;
        line += User.Password + Seperator;
        line += to_string(User.Permissions);

        return line;
    }

    static vector<clsUser> _LoadUsersDataFromFile()
    {
        vector<clsUser> vUsers;
        fstream file;

        file.open("Users.txt", ios::in);

        if (file.is_open())
        {
            string line;

            while (getline(file, line))
            {
                vUsers.push_back(_ConvertLinetoUserObject(line));
            }

            file.close();
        }

        return vUsers;
    }

    static void _SaveUsersDataToFile(vector<clsUser> vUsers)
    {
        fstream file;
        file.open("Users.txt", ios::out);

        if (file.is_open())
        {
            for (clsUser& U : vUsers)
            {
                if (!U.MarkedForDeleted())
                {
                    file << _ConverUserObjectToLine(U) << endl;
                }
            }

            file.close();
        }
    }

    void _Update()
    {
        vector<clsUser> vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }
        }

        _SaveUsersDataToFile(vUsers);
    }

    void _AddNew()
    {
        fstream file;
        file.open("Users.txt", ios::app);

        if (file.is_open())
        {
            file << _ConverUserObjectToLine(*this) << endl;
            file.close();
        }
    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:

    enum enPermissions {
        eAll = -1,
        pListClients = 1,
        pAddNewClient = 2,
        pDeleteClient = 4,
        pUpdateClients = 8,
        pFindClient = 16,
        pTranactions = 32,
        pManageUsers = 64
    };

    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        int Permissions)
        : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty()
    {
        return _Mode == enMode::EmptyMode;
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string GetUserName() { return _UserName; }
    void SetUserName(string value) { _UserName = value; }

    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    string GetPassword() { return _Password; }
    void SetPassword(string value) { _Password = value; }

    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    int GetPermissions() { return _Permissions; }
    void SetPermissions(int value) { _Permissions = value; }

    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    static clsUser Find(string UserName)
    {
        fstream file;
        file.open("Users.txt", ios::in);

        if (file.is_open())
        {
            string line;

            while (getline(file, line))
            {
                clsUser U = _ConvertLinetoUserObject(line);

                if (U.UserName == UserName)
                {
                    file.close();
                    return U;
                }
            }

            file.close();
        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {
        fstream file;
        file.open("Users.txt", ios::in);

        if (file.is_open())
        {
            string line;

            while (getline(file, line))
            {
                clsUser U = _ConvertLinetoUserObject(line);

                if (U.UserName == UserName && U.Password == Password)
                {
                    file.close();
                    return U;
                }
            }

            file.close();
        }

        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
            if (IsEmpty())
                return svFaildEmptyObject;
            break;

        case enMode::UpdateMode:
            _Update();
            return svSucceeded;

        case enMode::AddNewMode:
            if (clsUser::IsUserExist(_UserName))
                return svFaildUserExists;

            _AddNew();
            _Mode = enMode::UpdateMode;
            return svSucceeded;
        }

        return svFaildEmptyObject;
    }

    static bool IsUserExist(string UserName)
    {
        return !Find(UserName).IsEmpty();
    }

    bool Delete()
    {
        vector<clsUser> vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }
        }

        _SaveUsersDataToFile(vUsers);

        *this = _GetEmptyUserObject();

        return true;
    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector<clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    void RegisterLogIn()
    {
        fstream file;
        file.open("LoginRegister.txt", ios::app);

        if (file.is_open())
        {
            file << _PrepareLogInRecord() << endl;
            file.close();
        }
    }

    static vector<stLoginRegisterRecord> _LoadUsersrigstritinoFromFile()
    {
        vector<stLoginRegisterRecord> v;

        fstream file;
        file.open("LoginRegister.txt", ios::in);

        if (file.is_open())
        {
            string line;

            while (getline(file, line))
            {
                v.push_back(_ConvertLoginRegisterLineToRecord(line));
            }

            file.close();
        }

        return v;
    }

    static vector<stLoginRegisterRecord> GetUsersrigstring()
    {
        return _LoadUsersrigstritinoFromFile();
    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        if (Permissions == enPermissions::eAll)
            return true;

        return (Permission & Permissions) == Permission;
    }
};