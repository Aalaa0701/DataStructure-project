#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qwidget.h>
#include "ui_ProjectWithGUI.h"
#include "ui_AdminPage.h"
#include "ui_Adduser.h"
#include "ui_deleteOptions.h"
#include "ui_Displayuser.h"
#include "ui_EnterId.h"
#include "ui_statistics.h"
#include "ui_view.h"
#include "ui_viewOptions.h"
#include "ProjectWithGUI.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include<map>

using namespace std;
using namespace Ui;



class User
{
private:
    string name;
    string national_id;
    string password;
    char gender;
    int age;
    string governorate;
    bool vaccinated;
    bool received_both_doses;



public:
    // Constructor
    User();
    ~User();
    User(string name, string national_id, string password, char gender, int age,
        string governorate, bool vaccinated, bool received_both_doses);


    // Getters
    string get_name() const;
    string get_national_id() const;
    string get_password() const;
    char get_gender() const;
    int get_age() const;
    string get_governorate() const;
    bool is_vaccinated() const;
    bool has_received_both_doses() const;
    void set_vaccinated(bool vaccinated);
    void set_received_both_doses(bool received_both_doses);
    //Functions
    bool checkNationalId(map<string, User> user_map, string nationalId);
    void add_user(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map,
        AddUser* addUserPage, bool& viewUserPage);
    void display_user_data(map<string, User> user_map, string nationalId, DisplayUser* displayPage);
    bool ValidDataCheck(map<string, User> user_map, string userName, string password);

    //Edit user data
    void DisplayInfoToBeEdited(map<string, User>& user_map, string nationalId, EditUser* editUserPage);
    void EditUserData(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList, map<string, User>& user_map, EditUser* editUserPage, string vaccinationState);
    void deleteUser(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList, string nationalId, map<string, User>& user_map);

    // Setters

};

class Admin
{
public:
    string userName;
    string password;

public:
    Admin(string adminUserName, string adminPassword);
    Admin();
    //~Admin();
    void Statistics(vector<User>, vector<User>, queue<User>, map<string, User>, StatisticsPage* statisticsPage);
    void ViewRecord(map<string, User> user_map, DisplayOneUser* displayOneUser, NewViewUi* viewUsersPage, int typeofview, string nationalID);
    void DeleteRecord(map<string, User>& user_map, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList, int typeOfDeletion, string nationalID);
    void FilteredRecords(vector<User>firstDose, vector<User>secondDose, int numOfDose, NewViewUi* viewUsersPageFirstDose, NewViewUi* viewUsersPageSecondDose);
    void OrderedByAge(vector<User>firstDose, vector<User>secondDose, NewViewUi* viewUsersPage);
    void view_record(queue<User>waitingList, ViewWaitingList* viewWaitingListPage);

};