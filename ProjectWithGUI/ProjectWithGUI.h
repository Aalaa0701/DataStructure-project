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
#include "ui_FilterDosesChoice.h"
#include "ui_DisplayOneUserAdminPage.h"
#include "ui_OrderByAgePage.h"
#include "ui_ViewUsers.h"
#include "ui_NewViewUI.h"
#include "ui_ViewFirstDose.h"
#include "ui_EditUser.h"
#include "ui_ViewSecondDose.h"
#include "ui_EnterIdDelete.h"
#include "UserAndAdmin.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include<map>

using namespace std;
using namespace Ui;




class ProjectWithGUI : public QMainWindow
{
    Q_OBJECT
public:
    //ProjectWithGUI(QWidget* parent = nullptr);
    ProjectWithGUI(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map);

    ~ProjectWithGUI();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list);

    //void takeUsernameAndPassword();
public slots:
    void on_submitButtonLogin_clicked(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map);
    void on_SignUp_clicked(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map);
    void on_exit_clicked(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list);


private:
    Login* loginPage;
    AdminPage* adminPage;
    DisplayUser* displayUserPage;
    AddUser* addUserPage;



};
class AddUserClass : public QMainWindow
{
    Q_OBJECT
public:
    AddUserClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map);
    ~AddUserClass();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);


public slots:
    void on_SumbitButtonClicked(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map, AddUser* addUserPage); 
    void on_login_clicked(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map);


private:
    AddUser* addUserPage;




};
class AdminPageClass : public QMainWindow
{
    Q_OBJECT
public:
    //  
    AdminPageClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    ~AdminPageClass();
    void closeEventAdmin(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);

    AdminPage* adminPage;
public slots:
    void on_display_btn_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    void on_delete_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    void on_viewWaitingList_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    void on_showStatistics_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    void on_orderByAge_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    void on_filterByDoses_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    void on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);


};
class DeleteOptionsClass : public QMainWindow
{
    Q_OBJECT
public:
    DeleteOptionsClass(QWidget* parent , vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    ~DeleteOptionsClass();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);

public slots:
    void on_deleteOneRecord_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    void on_deleteAllRecords_clicked(map<string, User>& user_map, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList);
    void on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);

private:
    DeleteOptions* deleteOptionsPage;



};
class DisplayUserClass : public QMainWindow
{
    Q_OBJECT
public:
    DisplayUserClass(QWidget* parent, string& username, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map);
    ~DisplayUserClass();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);

    string nationalIDForDisplay;
    string vaccinationStateInUI;
public slots:
    void on_Edit_clicked( vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map, string& username);
    void on_delete_clicked(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map);
    void on_logOut_clicked(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map);
private:
    DisplayUser* displayPage;



};
class EnterIDClass : public QMainWindow
{
    Q_OBJECT
public:
    EnterIDClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    ~EnterIDClass();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);

public slots:
    void on_next_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    void on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
private:
    EnterID* enterIdPage;



};
class EnterIdDeleteClass : public QMainWindow
{
    Q_OBJECT
public:
    EnterIdDeleteClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    ~EnterIdDeleteClass();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);

public slots:
    void on_delete_btn_clicked(map<string, User>& user_map, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList);
    void on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);

private:
    EnterIdDelete* enterIdDeletePage;

};
class StatisticsClass : public QMainWindow
{
    Q_OBJECT
public:
    StatisticsClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    ~StatisticsClass();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);

public slots:
    void on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);

private:
    StatisticsPage* statisticsPage;



};
class ViewClass : public QMainWindow
{
    Q_OBJECT
public:
    ViewClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    ~ViewClass();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);

public slots:
    void on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);

private:
    ViewWaitingList* viewWaitingListPage;

};
class ViewOptionsClass : public QMainWindow
{
    Q_OBJECT
public:
    ViewOptionsClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    ~ViewOptionsClass();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);

public slots:
    void on_viewOneRecord_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    void on_viewAllRecords_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    void on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);

private:
    ViewOptions* viewOptionsPage;


};

class DisplayOneUserClass : public QMainWindow
{
    Q_OBJECT
public:
    DisplayOneUserClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list, string nationalID);
    ~DisplayOneUserClass();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);

public slots:
    void on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
public:
    DisplayOneUser* displayOneUserPage;
    ViewUsers* viewUsersPage;
    //Ui::MainWindow* viewUsersPageNew;
    NewViewUi* viewUsersPageNew;

    



};
class ViewUsersClass : public QMainWindow
{
    Q_OBJECT
public:
    ViewUsersClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    ~ViewUsersClass();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);

public slots:
    void on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
public:
    ViewUsers* viewUsersPage;
   //Ui::MainWindow* viewUsersPageNew;
    NewViewUi* viewUsersPageNew;
    DisplayOneUser* displayOneUserPage;

};
class FilterDosesChoiceClass : public QMainWindow
{
    Q_OBJECT
public:
    FilterDosesChoiceClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    ~FilterDosesChoiceClass();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);

public slots:
    void on_firstDose_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    void on_secondDose_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    void on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
private:
    filterDosesChoice* filterDosesChoicePage;
   

};
class ViewFirstDoseClass : public QMainWindow
{
    Q_OBJECT
public:
    ViewFirstDoseClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    ~ViewFirstDoseClass();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);

public slots:
    void on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
private:
    ViewFirstDose* viewFirstDosePage;
    ViewSecondDose* viewSecondDosePage;
    NewViewUi* viewUsersPageSecondDose;
    NewViewUi* viewUsersPageFirstDose;

};
class ViewSecondDoseClass : public QMainWindow
{
    Q_OBJECT
public:
    ViewSecondDoseClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    ~ViewSecondDoseClass();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);

public slots:
    void on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
private:
    ViewFirstDose* viewFirstDosePage;
    ViewSecondDose* viewSecondDosePage;
    NewViewUi* viewUsersPageSecondDose;
    NewViewUi* viewUsersPageFirstDose;

};
class OrderByAgeClass : public QMainWindow
{
    Q_OBJECT
public:
    OrderByAgeClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
    ~OrderByAgeClass();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);

public slots:
    void on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list);
private:
    NewViewUi* viewUsersPageOrdered;
};
class EditUserClass : public QMainWindow
{
    Q_OBJECT
public:
    EditUserClass(QWidget* parent, string username,string vaccinationState, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map);
    ~EditUserClass();
    void closeEvent(QCloseEvent* event, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map);


public slots:
    void on_Confirm_clicked(string vaccinationState, string& nationalID, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map);
private:
    EditUser* editUserPage;
    string userToBeEdited;
    string oldVaccinationState;
};
void WriteAll(vector<User> firstDose, vector<User> secondDose, queue<User> waitingList);
void WriteTwoDose(vector<User>secondDose);
void WriteOneDose(vector<User>firstDose);
void WriteWaitingList(queue<User>waitingList);






