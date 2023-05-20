#include "ProjectWithGUI.h"
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include<map>
#include <fstream>	
using namespace std;




ProjectWithGUI::ProjectWithGUI(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map)
    : QMainWindow(parent)
{
    loginPage = new Login;
    loginPage->setupUi(this);
    
    connect(loginPage->submitButtonLogin, &QPushButton::clicked, this, [&]() {on_submitButtonLogin_clicked(firstDose, secondDose, waiting_list, user_map); });
    connect(loginPage->commandLinkButton, &QCommandLinkButton::clicked, this, [&]() {on_SignUp_clicked(firstDose, secondDose, waiting_list, user_map); });
    connect(loginPage->Exit, &QPushButton::clicked, this, [&]() {on_exit_clicked(firstDose, secondDose, waiting_list); });
   


}
void ProjectWithGUI::on_submitButtonLogin_clicked(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map) {
    Admin admin("Admin","1234");
    User* usertemp = new User();
    string userName = loginPage->UserName->text().toStdString();
    string password = loginPage->Password->text().toStdString();
  

    if (userName == admin.userName && password == admin.password) {
       loginPage->label_5->setText(QString::fromStdString("succeed"));
      
       AdminPageClass* adminPageObj = new AdminPageClass(this,firstDose,secondDose,user_map,waiting_list);
       adminPageObj->show();

       hide();
     
     
    }
    if (usertemp->ValidDataCheck(user_map,userName,password)) {
        loginPage->label_5->setText(QString::fromStdString("found"));

        DisplayUserClass* displayUserObj = new DisplayUserClass(this, userName,firstDose, secondDose, waiting_list, user_map);
        displayUserObj->show();
        hide();

  

    }
    else {
        loginPage->label_5->setText(QString::fromStdString("Try again"));

    }
    delete usertemp;
}

void ProjectWithGUI::on_SignUp_clicked(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map) {
    loginPage->label_5->setText(QString::fromStdString("SignUpPage"));

    AddUserClass* addUserObj = new AddUserClass(this,firstDose,secondDose,waiting_list,user_map);
    addUserObj->show();
    hide();
}
void ProjectWithGUI::on_exit_clicked(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();
}
void ProjectWithGUI::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list) {

    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();
    
}

ProjectWithGUI::~ProjectWithGUI()
{
    delete loginPage;
}

AddUserClass::AddUserClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map)  : QMainWindow(parent)
{
    addUserPage = new AddUser;
    //QFont BellMT("Bell MT", 14, QFont::Bold); 
   

    addUserPage->setupUi(this);
    addUserPage->comboBox->addItem("-  None  -");
    addUserPage->comboBox->addItem("Not vaccinated");
    addUserPage->comboBox->addItem("One Dose");
    addUserPage->comboBox->addItem("Two Doses");
    addUserPage->governorateCombo->addItem("-  None  -");
    addUserPage->governorateCombo->addItem("Cairo");
    addUserPage->governorateCombo->addItem("Giza");
    addUserPage->governorateCombo->addItem("Matruh");
    addUserPage->governorateCombo->addItem("Asyut");
    addUserPage->governorateCombo->addItem("South Sinai");
    addUserPage->governorateCombo->addItem("Aswan");
    addUserPage->governorateCombo->addItem("Luxor");
    addUserPage->governorateCombo->addItem("Alexandria");


    connect(addUserPage->submitButtonAdd, &QPushButton::clicked, this, [&]() {on_SumbitButtonClicked(firstDose,secondDose,waiting_list,user_map, addUserPage); });
    connect(addUserPage->LogInPage, &QCommandLinkButton::clicked, this, [&]() {on_login_clicked(firstDose, secondDose, waiting_list, user_map); });

   


 }
void AddUserClass::on_SumbitButtonClicked(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map, AddUser* addUserPage) {
  
    User userTemp;
    bool viewUserPage = true;
   
    userTemp.add_user(firstDose, secondDose, waiting_list, user_map, addUserPage, viewUserPage);
    if (!viewUserPage) {
        ProjectWithGUI* logInPage = new ProjectWithGUI(this, firstDose, secondDose, waiting_list, user_map);
        logInPage->show();
        hide();
    }
    else {
        show();
    }
}
void AddUserClass::on_login_clicked(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map) {
    ProjectWithGUI* projectWithGUIObj = new ProjectWithGUI(this, firstDose, secondDose, waiting_list, user_map);
    projectWithGUIObj->show();
    hide();
}
void AddUserClass::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}
AddUserClass::~AddUserClass() {
    delete addUserPage;
}

//
AdminPageClass::AdminPageClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) : QMainWindow(parent)
{
    adminPage = new AdminPage;
    adminPage->setupUi(this);

    connect(adminPage->DisplayUser, &QPushButton::clicked, this, [&]() {on_display_btn_clicked(firstDose,secondDose, user_map, waiting_list); });
    connect(adminPage->DeleteUser, &QPushButton::clicked, this, [&]() {on_delete_clicked(firstDose, secondDose,user_map,waiting_list); });
    connect(adminPage->viewWaitingList, &QPushButton::clicked, this, [&]() {on_viewWaitingList_clicked(firstDose,secondDose,user_map, waiting_list); });
    connect(adminPage->ShowStat, &QPushButton::clicked, this, [&]() {on_showStatistics_clicked(firstDose,secondDose,user_map,waiting_list); });
    connect(adminPage->OrderByAge, &QPushButton::clicked, this, [&]() {on_orderByAge_clicked(firstDose,secondDose,user_map,waiting_list); });
    connect(adminPage->FilterDoses, &QPushButton::clicked, this, [&]() {on_filterByDoses_clicked(firstDose,secondDose,user_map,waiting_list); });
    connect(adminPage->Return, &QPushButton::clicked, this, [&]() {on_return_clicked(firstDose, secondDose,user_map,waiting_list); });



}
void AdminPageClass::on_display_btn_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
  //  adminPage->label_2->setText("Display");

    ViewOptionsClass* viewOptionsObj = new ViewOptionsClass(this,firstDose,secondDose, user_map, waiting_list);
    viewOptionsObj->show();
    hide();
}
void AdminPageClass::on_delete_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
  //  adminPage->label_2->setText("Delete");

    DeleteOptionsClass* deleteOptionsObj = new DeleteOptionsClass(this,firstDose,secondDose, user_map,waiting_list);
    deleteOptionsObj->show();
    hide();


   
}
void AdminPageClass::on_viewWaitingList_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    if (!waiting_list.empty()) {
        ViewClass* viewWaitingListObj = new ViewClass(this,firstDose,secondDose,user_map, waiting_list);
        viewWaitingListObj->show();
        hide();
    }
    else {
         adminPage->label_2->setText("Waiting List Is Empty");
    }
   
}
void AdminPageClass::on_showStatistics_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    StatisticsClass* statisticsObj = new StatisticsClass(this, firstDose, secondDose, user_map, waiting_list);
    statisticsObj->show();
    hide();
}
void AdminPageClass::on_orderByAge_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    OrderByAgeClass* orderByAgeObj = new OrderByAgeClass(this, firstDose, secondDose,user_map,waiting_list);
    orderByAgeObj->show();
    hide();
}
void AdminPageClass::on_filterByDoses_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    FilterDosesChoiceClass* filterDosesChoiceObj = new FilterDosesChoiceClass(this, firstDose, secondDose,user_map,waiting_list);
    filterDosesChoiceObj->show();
    hide();
}
void AdminPageClass::on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    ProjectWithGUI* projectWithGUIObj = new ProjectWithGUI(this, firstDose, secondDose, waiting_list, user_map);
    projectWithGUIObj->show();
    hide();
}
void AdminPageClass::closeEventAdmin(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}

AdminPageClass::~AdminPageClass() {
    delete adminPage;
}
DeleteOptionsClass::DeleteOptionsClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) : QMainWindow(parent)
{
    deleteOptionsPage = new DeleteOptions;
    deleteOptionsPage->setupUi(this);

    connect(deleteOptionsPage->DeleteOneRecord, &QPushButton::clicked, this, [&]() {on_deleteOneRecord_clicked(firstDose,secondDose, user_map,waiting_list); });
    connect(deleteOptionsPage->Deleteallrecords, &QPushButton::clicked, this, [&]() {on_deleteAllRecords_clicked(user_map,firstDose,secondDose,waiting_list); });
    connect(deleteOptionsPage->Return, &QPushButton::clicked, this, [&]() {on_return_clicked(firstDose,secondDose,user_map,waiting_list); });


}
void DeleteOptionsClass::on_deleteOneRecord_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list){

    EnterIdDeleteClass* enterIdDeleteObj = new EnterIdDeleteClass(this,firstDose,secondDose, user_map,waiting_list);
    enterIdDeleteObj->show();
    hide();

}
void DeleteOptionsClass::on_deleteAllRecords_clicked(map<string, User>& user_map, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList) {
    deleteOptionsPage->label->setText(QString::fromStdString(to_string(!user_map.empty())));
    if (user_map.empty()) {
        Admin adminTemp;
        adminTemp.DeleteRecord(user_map,firstDose,secondDose,waitingList, 1, "");
    }

}
void DeleteOptionsClass::on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    AdminPageClass* adminPageObj = new AdminPageClass(this, firstDose, secondDose, user_map, waiting_list);
    adminPageObj->show();
    hide();
}
void DeleteOptionsClass::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}

DeleteOptionsClass::~DeleteOptionsClass() {
    delete deleteOptionsPage;
}
DisplayUserClass::DisplayUserClass(QWidget* parent, string& username, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map) : QMainWindow(parent)
{

    

    displayPage = new DisplayUser;
    displayPage->setupUi(this);  



    connect(displayPage->Deleterecord, &QPushButton::clicked, this, [&]() {on_delete_clicked(firstDose,secondDose,waiting_list,user_map, username); });
    connect(displayPage->EditRecord, &QPushButton::clicked, this, [&]() {on_Edit_clicked( firstDose,secondDose,waiting_list,user_map,username); });
    connect(displayPage->logOut, &QPushButton::clicked, this, [&]() {on_logOut_clicked(firstDose, secondDose, waiting_list, user_map); });


    User usertemp(user_map[username].get_name(), user_map[username].get_national_id(), user_map[username].get_password(), user_map[username].get_gender(), user_map[username].get_age()
        , user_map[username].get_governorate(), user_map[username].is_vaccinated(), user_map[username].has_received_both_doses());


    usertemp.display_user_data(user_map, username, displayPage);


    //delete usertemp;

}
void DisplayUserClass::on_delete_clicked( vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map, string& username) {
    string name = displayPage->Name->text().toStdString();
    string nationalID = displayPage->Id->text().toStdString();
    string password = displayPage->password->text().toStdString();
    string gender = displayPage->Gender->text().toStdString();
    string governorate = displayPage->Governorate->text().toStdString();
    string vaccinationState = displayPage->VaccinationState->text().toStdString();
    int age = displayPage->Age->text().toInt();
    char genderCharacter;
    bool isVaccinated, recievedBothDoses;
    if (gender == "Female") {
        genderCharacter = 'F';
    }
    else if (gender == "Male") {
        genderCharacter = 'M';
    }
    if (vaccinationState == "In waiting List") {
        isVaccinated = false;
        recievedBothDoses = false;
    }
    else if (vaccinationState == "Received First Dose") {
        isVaccinated = true;
        recievedBothDoses = false;
    }
    else if (vaccinationState == "Recieved Both Doses") {
        isVaccinated = true;
        recievedBothDoses = true;
    }


    //displayPage->label_8->setText(QString::fromStdString(nationalID));
    User userTemp(name, nationalID, password, genderCharacter, age, governorate, isVaccinated, recievedBothDoses);
    userTemp.deleteUser(firstDose, secondDose, waiting_list, nationalID, user_map);

    ProjectWithGUI* projectWithGUIObj = new ProjectWithGUI(this, firstDose, secondDose, waiting_list, user_map);
    projectWithGUIObj->show();
    hide();

}
void DisplayUserClass::on_Edit_clicked(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map, string& username) {
    string vaccinationState = displayPage->VaccinationState->text().toStdString();
    string nationalID = displayPage->Id->text().toStdString();
    nationalIDForDisplay = nationalID;
    vaccinationStateInUI = vaccinationState;
    EditUserClass* editUserObj = new EditUserClass(this, nationalIDForDisplay,vaccinationStateInUI, firstDose, secondDose, waiting_list, user_map);
    editUserObj->show();
    hide();
}
void DisplayUserClass::on_logOut_clicked(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map) {
    ProjectWithGUI* projectWithGUIObj = new ProjectWithGUI(this, firstDose, secondDose, waiting_list, user_map);
    projectWithGUIObj->show();
    hide();
}
void DisplayUserClass::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}

DisplayUserClass::~DisplayUserClass() {
    delete displayPage;
}
EnterIDClass::EnterIDClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) : QMainWindow(parent)
{
    enterIdPage = new EnterID;
    enterIdPage->setupUi(this);
    connect(enterIdPage->next, &QPushButton::clicked, this, [&]() {on_next_clicked (firstDose, secondDose, user_map, waiting_list); });
    connect(enterIdPage->Return, &QPushButton::clicked, this, [&]() {on_return_clicked(firstDose, secondDose, user_map, waiting_list); });

}
void EnterIDClass::on_next_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    string nationalID = enterIdPage->NationalID->text().toStdString();
    User* userTemp = new User(user_map[nationalID].get_name(), user_map[nationalID].get_national_id(), user_map[nationalID].get_password(), user_map[nationalID].get_gender(), user_map[nationalID].get_age(),
        user_map[nationalID].get_governorate(), user_map[nationalID].is_vaccinated(), user_map[nationalID].has_received_both_doses());

    enterIdPage->label_2->setText(QString::fromStdString(userTemp->get_name()));

    if (nationalID.length() != 13 || !all_of(nationalID.begin(), nationalID.end(), ::isdigit)) {
        enterIdPage->label_2->setText("NotValid");
        return;
    }
    else {
        if (user_map[nationalID].get_name() != "") {
            enterIdPage->label_2->setText("Found");
            DisplayOneUserClass* displayOneUserObj = new DisplayOneUserClass(this,firstDose,secondDose, user_map,waiting_list, nationalID);
            displayOneUserObj->show();
            hide();
        }
        else {
            enterIdPage->label_2->setText("notFound");
           
        }

       
    }
    delete userTemp;
}
void EnterIDClass::on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    AdminPageClass* adminPageObj = new AdminPageClass(this, firstDose, secondDose, user_map, waiting_list);
    adminPageObj->show();
    hide();
}
void EnterIDClass::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}
EnterIDClass::~EnterIDClass() {
    delete enterIdPage;
}
EnterIdDeleteClass::EnterIdDeleteClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    enterIdDeletePage = new EnterIdDelete;
    enterIdDeletePage->setupUi(this);
    connect(enterIdDeletePage->next, &QPushButton::clicked, this, [&]() {on_delete_btn_clicked(user_map,firstDose,secondDose,waiting_list); });
    connect(enterIdDeletePage->Return, &QPushButton::clicked, this, [&]() {on_return_clicked(firstDose, secondDose, user_map, waiting_list); });

}
void EnterIdDeleteClass::on_delete_btn_clicked(map<string, User>& user_map, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList) {
    string nationalID = enterIdDeletePage->NationalID->text().toStdString();
    Admin adminTemp;
    adminTemp.DeleteRecord(user_map,firstDose,secondDose, waitingList, 2, nationalID);
}
void EnterIdDeleteClass::on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    AdminPageClass* adminPageObj = new AdminPageClass(this, firstDose, secondDose, user_map, waiting_list);
    adminPageObj->show();
    hide();
}
void EnterIdDeleteClass::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}
EnterIdDeleteClass::~EnterIdDeleteClass() {
    delete enterIdDeletePage;
}
StatisticsClass::StatisticsClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) : QMainWindow(parent)
{
    statisticsPage = new StatisticsPage;
    statisticsPage->setupUi(this);
    Admin adminTemp;
    adminTemp.Statistics(firstDose, secondDose, waiting_list, user_map, statisticsPage);
    connect(statisticsPage->Return, &QPushButton::clicked, this, [&]() {on_return_clicked(firstDose,secondDose,user_map,waiting_list); });

}
void StatisticsClass::on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    AdminPageClass* adminPageObj = new AdminPageClass(this, firstDose, secondDose, user_map, waiting_list);
    adminPageObj->show();
    hide();
}
void StatisticsClass::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}
StatisticsClass::~StatisticsClass() {
    delete statisticsPage;
}
ViewClass::ViewClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) : QMainWindow(parent)
{
    viewWaitingListPage = new ViewWaitingList;
    viewWaitingListPage->setupUi(this);
    Admin adminTemp;
    adminTemp.view_record(waiting_list, viewWaitingListPage);
    
    connect(viewWaitingListPage->Return, &QPushButton::clicked, this, [&]() {on_return_clicked(firstDose, secondDose, user_map, waiting_list); });
}
void ViewClass::on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    AdminPageClass* adminPageObj = new AdminPageClass(this, firstDose, secondDose, user_map, waiting_list);
    adminPageObj->show();
    hide();
}
void ViewClass::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}
ViewClass::~ViewClass() {
    delete viewWaitingListPage;
}
ViewOptionsClass::ViewOptionsClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) : QMainWindow(parent)
{
    viewOptionsPage = new ViewOptions;
    viewOptionsPage->setupUi(this);
    connect(viewOptionsPage->ViewOneRecord, &QPushButton::clicked, this, [&]() {on_viewOneRecord_clicked(firstDose,secondDose, user_map, waiting_list); });
    connect(viewOptionsPage->ViewAllRecords, &QPushButton::clicked, this, [&]() {on_viewAllRecords_clicked(firstDose,secondDose, user_map,waiting_list); });
    connect(viewOptionsPage->Return, &QPushButton::clicked, this, [&]() {on_return_clicked(firstDose,secondDose,user_map,waiting_list); });

}
void ViewOptionsClass::on_viewOneRecord_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    EnterIDClass* enterIdObj = new EnterIDClass(this,firstDose,secondDose, user_map, waiting_list);
    enterIdObj->show();
    hide();
}
void ViewOptionsClass::on_viewAllRecords_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    ViewUsersClass* viewUsersObj = new ViewUsersClass(this,firstDose,secondDose, user_map,waiting_list);
    viewUsersObj->show();
    hide();
}
void ViewOptionsClass::on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    AdminPageClass* adminPageObj = new AdminPageClass(this, firstDose, secondDose, user_map, waiting_list);
    adminPageObj->show();
    hide();
}
void ViewOptionsClass::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}
ViewOptionsClass::~ViewOptionsClass() {
    delete viewOptionsPage;
}
DisplayOneUserClass::DisplayOneUserClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list, string nationalID) : QMainWindow(parent)
{
    displayOneUserPage = new DisplayOneUser;
    displayOneUserPage->setupUi(this);
    Admin adminTemp;
    adminTemp.ViewRecord(user_map, displayOneUserPage, viewUsersPageNew, 2, nationalID);
    connect(displayOneUserPage->Return, &QPushButton::clicked, this, [&]() {on_return_clicked(firstDose, secondDose, user_map, waiting_list); });
}
void DisplayOneUserClass::on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    AdminPageClass* adminPageObj = new AdminPageClass(this, firstDose, secondDose, user_map, waiting_list);
    adminPageObj->show();
    hide();
}
void DisplayOneUserClass::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}
DisplayOneUserClass::~DisplayOneUserClass() {
    delete displayOneUserPage;
    delete viewUsersPage;
    delete viewUsersPageNew;
}
ViewUsersClass::ViewUsersClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) :QMainWindow(parent)
{
    viewUsersPageNew = new NewViewUi;
    viewUsersPageNew->setupUi(this);
    Admin adminTemp;
    adminTemp.ViewRecord(user_map, displayOneUserPage, viewUsersPageNew, 1, "");
    connect(viewUsersPageNew->Return, &QPushButton::clicked, this, [&]() {on_return_clicked(firstDose, secondDose, user_map, waiting_list); });

}
void ViewUsersClass::on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    AdminPageClass* adminPageObj = new AdminPageClass(this, firstDose, secondDose, user_map, waiting_list);
    adminPageObj->show();
    hide();
}
void ViewUsersClass::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}
ViewUsersClass::~ViewUsersClass() {
    delete viewUsersPage;
    delete displayOneUserPage;
    delete viewUsersPageNew;
}
FilterDosesChoiceClass::FilterDosesChoiceClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) : QMainWindow(parent)
{
    filterDosesChoicePage = new filterDosesChoice;
    filterDosesChoicePage->setupUi(this);
    connect(filterDosesChoicePage->FirstDoseRecords, &QPushButton::clicked, this, [&]() {on_firstDose_clicked(firstDose,secondDose,user_map,waiting_list); });
    connect(filterDosesChoicePage->SecondDoseRecords, &QPushButton::clicked, this, [&]() {on_secondDose_clicked(firstDose,secondDose,user_map,waiting_list); });
    connect(filterDosesChoicePage->Return, &QPushButton::clicked, this, [&]() {on_return_clicked(firstDose, secondDose, user_map, waiting_list); });



}
void FilterDosesChoiceClass::on_firstDose_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    ViewFirstDoseClass* viewFirstDoseObj = new ViewFirstDoseClass(this, firstDose, secondDose,user_map,waiting_list);
    viewFirstDoseObj->show();
    hide();
    
}
void FilterDosesChoiceClass::on_secondDose_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    ViewSecondDoseClass* viewSecondDoseObj = new ViewSecondDoseClass(this, firstDose, secondDose, user_map,waiting_list);
    viewSecondDoseObj->show();
    hide();
}
void FilterDosesChoiceClass::on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    AdminPageClass* adminPageObj = new AdminPageClass(this, firstDose, secondDose, user_map, waiting_list);
    adminPageObj->show();
    hide();
}
void FilterDosesChoiceClass::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}
FilterDosesChoiceClass::~FilterDosesChoiceClass() {
    delete filterDosesChoicePage;
   
}
ViewFirstDoseClass::ViewFirstDoseClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) : QMainWindow(parent)
{
    viewUsersPageFirstDose = new NewViewUi;
    viewUsersPageFirstDose->setupUi(this);
    Admin adminTemp;
    adminTemp.FilteredRecords(firstDose, secondDose, 1, viewUsersPageFirstDose, viewUsersPageSecondDose);
    connect(viewUsersPageFirstDose->Return, &QPushButton::clicked, this, [&]() {on_return_clicked(firstDose, secondDose, user_map, waiting_list); });

    
}
void ViewFirstDoseClass::on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    AdminPageClass* adminPageObj = new AdminPageClass(this, firstDose, secondDose, user_map, waiting_list);
    adminPageObj->show();
    hide();
}
void ViewFirstDoseClass::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}
ViewFirstDoseClass::~ViewFirstDoseClass() {
    delete viewFirstDosePage;
    delete viewSecondDosePage;
    delete viewUsersPageFirstDose;
    delete viewUsersPageSecondDose;
}
ViewSecondDoseClass::ViewSecondDoseClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) : QMainWindow(parent)
{
    viewUsersPageSecondDose = new NewViewUi;
    viewUsersPageSecondDose->setupUi(this);
    Admin adminTemp;
    adminTemp.FilteredRecords(firstDose, secondDose, 2, viewUsersPageFirstDose, viewUsersPageSecondDose);
    connect(viewUsersPageSecondDose->Return, &QPushButton::clicked, this, [&]() {on_return_clicked(firstDose, secondDose, user_map, waiting_list); });



}
void ViewSecondDoseClass::on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    AdminPageClass* adminPageObj = new AdminPageClass(this, firstDose, secondDose, user_map, waiting_list);
    adminPageObj->show();
    hide();
}
void ViewSecondDoseClass::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}
ViewSecondDoseClass::~ViewSecondDoseClass() {
    delete viewSecondDosePage;
    delete viewFirstDosePage;
    delete viewUsersPageFirstDose;
    delete viewUsersPageSecondDose;
}
OrderByAgeClass::OrderByAgeClass(QWidget* parent, vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) : QMainWindow(parent)
{
    viewUsersPageOrdered = new NewViewUi;
    viewUsersPageOrdered->setupUi(this);
    Admin adminTemp;
    adminTemp.OrderedByAge(firstDose, secondDose, viewUsersPageOrdered);
    connect(viewUsersPageOrdered->Return, &QPushButton::clicked, this, [&]() {on_return_clicked(firstDose, secondDose, user_map, waiting_list); });


}
void OrderByAgeClass::on_return_clicked(vector<User>& firstDose, vector<User>& secondDose, map<string, User>& user_map, queue<User>& waiting_list) {
    AdminPageClass* adminPageObj = new AdminPageClass(this, firstDose, secondDose, user_map, waiting_list);
    adminPageObj->show();
    hide();
}
void OrderByAgeClass::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}
OrderByAgeClass::~OrderByAgeClass() {
    delete viewUsersPageOrdered;
}
EditUserClass::EditUserClass(QWidget* parent, string username, string vaccinationState, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map) : QMainWindow(parent)
{
    editUserPage = new EditUser;
    editUserPage->setupUi(this);

    editUserPage->comboBox->addItem("In waiting List");
    editUserPage->comboBox->addItem("Received First Dose");
    editUserPage->comboBox->addItem("Recieved Both Doses");

    editUserPage->governorateCombo->addItem("Cairo");
    editUserPage->governorateCombo->addItem("Giza");
    editUserPage->governorateCombo->addItem("Matruh");
    editUserPage->governorateCombo->addItem("Asyut");
    editUserPage->governorateCombo->addItem("South Sinai");
    editUserPage->governorateCombo->addItem("Aswan");
    editUserPage->governorateCombo->addItem("Luxor");
    editUserPage->governorateCombo->addItem("Alexandria");

    


    User userTemp(user_map[username].get_name(), user_map[username].get_national_id(), user_map[username].get_password(), user_map[username].get_gender(), user_map[username].get_age(),
        user_map[username].get_governorate(), user_map[username].is_vaccinated(), user_map[username].has_received_both_doses());
    userTemp.DisplayInfoToBeEdited(user_map, username, editUserPage);


   /* string nationalID = user_map[username].get_national_id();
    string vaccinationStateOld = vaccinationState;*/
    userToBeEdited = username;
    oldVaccinationState = vaccinationState;


    connect(editUserPage->Confirm, &QPushButton::clicked, this, [&]() {on_Confirm_clicked(oldVaccinationState,userToBeEdited, firstDose,secondDose,waiting_list,user_map); });

}
void EditUserClass::on_Confirm_clicked(string vaccinationState, string& username, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map) {

    User userTemporary(user_map[username].get_name(), user_map[username].get_national_id(), user_map[username].get_password(), user_map[username].get_gender(), user_map[username].get_age(),
        user_map[username].get_governorate(), user_map[username].is_vaccinated(), user_map[username].has_received_both_doses());
    userTemporary.EditUserData(firstDose, secondDose, waiting_list, user_map, editUserPage, vaccinationState);
    DisplayUserClass* displayUserObj = new DisplayUserClass(this, userToBeEdited, firstDose, secondDose, waiting_list, user_map);
    displayUserObj->show();
    hide();
    

}
void EditUserClass::closeEvent(QCloseEvent* closeEvent, vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map) {
    WriteAll(firstDose, secondDose, waiting_list);
    QApplication::quit();

}
EditUserClass::~EditUserClass() {
    delete editUserPage;
}




User::User() {
    this->name = "";
    this->national_id = "";
    this->password = "";
    this->gender = 'F';
    this->age = 0;
    this->governorate = "";
    this->vaccinated = false;
    this->received_both_doses = false;

}

User::User(string name, string national_id, string password, char gender, int age,
    string governorate, bool vaccinated, bool received_both_doses) {
    this->name = name;
    this->national_id = national_id;
    this->password = password;
    this->gender = gender;
    this->age = age;
    this->governorate = governorate;
    this->vaccinated = vaccinated;
    this->received_both_doses = received_both_doses;
}

string User::get_name() const {
    return name;
}
string User::get_national_id() const {
    return national_id;
}
string User::get_password() const {
    return password;
}
char User::get_gender() const {
    return gender;
}
int User::get_age() const {
    return age;
}
string User::get_governorate() const {
    return governorate;
}
bool User::is_vaccinated() const {
    return vaccinated;
}
bool User::has_received_both_doses() const {
    return received_both_doses;
}

// Setters
void User::set_vaccinated(bool vaccinated) {
    this->vaccinated = vaccinated;
}
void User::set_received_both_doses(bool received_both_doses) {
    this->received_both_doses = received_both_doses;
}
bool User::checkNationalId(map<string, User> user_map, string nationalId) {
    if (nationalId.length() != 13 || !all_of(nationalId.begin(), nationalId.end(), ::isdigit) || user_map.find(nationalId) != user_map.end()) {
        return false;
    }
    else {
        return true;
    }
}
// Function to add a new user record
void User::add_user(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map,
    AddUser* addUserPage, bool& viewUserPage) {
    char gender;
    bool recievedBothDoses, vaccinatedOrNot ;
    int age;


    string userName = addUserPage->Name->text().toStdString();
    string password = addUserPage->Password->text().toStdString();
    string nationalID = addUserPage->ID->text().toStdString();
    string governorate = addUserPage->governorateCombo->currentText().toStdString();
    string ageString = addUserPage->Age->text().toStdString();

    if (ageString == "") {
        age = -1;
    }
    else {
        int temp = stoi(ageString);
        if (temp <= 0) {
            age = -1;
        }
        else {
            age = temp;
        }
    }
    QString vaccinationState = addUserPage->comboBox->currentText();
    string vaccination = vaccinationState.toStdString();

    if (addUserPage->Male->isChecked() == true) {
        gender = 'M';
    }
    else if (addUserPage->Female->isChecked() == true) {
        gender = 'F';
    }

    if (userName == "" || password == "" || nationalID == "" || governorate == "-  None  -" || age == -1 ) {
        addUserPage->label_4->setText(QString::fromStdString("Please Enter appropriate values in their approriate fields"));

        return;
    }
    else if (addUserPage->Male->isChecked() == false && addUserPage->Female->isChecked() == false) {
        addUserPage->label_4->setText(QString::fromStdString("Choose  Gender Please"));

        return;
    }
    else if (vaccination== "-  None  -") {
        addUserPage->label_4->setText(QString::fromStdString("Choose Vaccination State Please"));

        return;
    }

    else {

        if (nationalID.length() != 13 || !all_of(nationalID.begin(), nationalID.end(), ::isdigit) || user_map.find(nationalID) != user_map.end()) {
                addUserPage->label_4->setText(QString::fromStdString("failed"));
            return;
        }
        else {
           

            if (vaccination == "Not vaccinated") {
                vaccinatedOrNot = false;
                recievedBothDoses = false;

                User userTemp(userName, nationalID, password, gender, age, governorate, vaccinatedOrNot, recievedBothDoses);
                user_map.insert({ nationalID,userTemp });
                waiting_list.push(userTemp);
                addUserPage->label_4->setText(QString::fromStdString("waitingList"));
                viewUserPage = false;
            }
            else if (vaccination == "One Dose") {
                vaccinatedOrNot = true;
                recievedBothDoses = false;

                User userTemp(userName, nationalID, password, gender, age, governorate, vaccinatedOrNot, recievedBothDoses);
                user_map.insert({ nationalID,userTemp });

                firstDose.push_back(userTemp);
                addUserPage->label_4->setText(QString::fromStdString("FirstDose"));
                viewUserPage = false;

            }
            else if (vaccination == "Two Doses") {
                vaccinatedOrNot = true;
                recievedBothDoses = true;

                User userTemp(userName, nationalID, password, gender, age, governorate, vaccinatedOrNot, recievedBothDoses);
                user_map.insert({ nationalID,userTemp });

                secondDose.push_back(userTemp);
                addUserPage->label_4->setText(QString::fromStdString("SecondDose"));
                viewUserPage = false;

            }

            
        }
        

    }
}
//function to check if data entered for display is valid
bool User::ValidDataCheck(map<string, User> user_map,string userName, string password) {
    if (userName.length() == 13 && user_map.find(userName) != user_map.end() && password == user_map[userName].get_password()) {
        return true;
    }
    else {
        return false;
    }
}
//Function to display User
void User::display_user_data(map<string, User> user_map, string nationalId, DisplayUser* displayPage) {
  
    displayPage->Name->setText(QString::fromStdString(user_map[nationalId].get_name()));
    displayPage->Age->setText(QString::number(user_map[nationalId].get_age()));
    displayPage->Id->setText(QString::fromStdString(user_map[nationalId].get_national_id()));
    if (user_map[nationalId].get_gender() == 'f' || user_map[nationalId].get_gender() == 'F') {
        displayPage->Gender->setText(QString::fromStdString("Female"));
    }
    else if (user_map[nationalId].get_gender() == 'm' || user_map[nationalId].get_gender() == 'M') {
        displayPage->Gender->setText(QString::fromStdString("Male"));
    }
    if (user_map[nationalId].is_vaccinated() == false) {
        displayPage->VaccinationState->setText("In waiting List");
    }
    else if (user_map[nationalId].is_vaccinated() == true && user_map[nationalId].has_received_both_doses() == false) {
        displayPage->VaccinationState->setText("Received First Dose");
    }
    else if (user_map[nationalId].is_vaccinated() == true && user_map[nationalId].has_received_both_doses() == true) {
        displayPage->VaccinationState->setText("Recieved Both Doses");
    }
    displayPage->Governorate->setText(QString::fromStdString(user_map[nationalId].get_governorate()));
    displayPage->password->setText(QString::fromStdString(user_map[nationalId].get_password()));


    
}


void User::DisplayInfoToBeEdited(map<string, User>& user_map, string nationalId, EditUser* editUserPage) {
    //getting UserInfo
    string gender, vaccinationState;

    string name = user_map[nationalId].get_name();
    string nationalID = user_map[nationalId].get_national_id();
    string password = user_map[nationalId].get_password();
    char genderCharacter = user_map[nationalId].get_gender();
    string governorate = user_map[nationalId].get_governorate();
    int age = user_map[nationalId].get_age();
    bool isVaccinated = user_map[nationalId].is_vaccinated();
    bool recievedBothDoses = user_map[nationalId].has_received_both_doses();
    if (genderCharacter == 'f' || genderCharacter == 'F') {
        gender = "Female";
        editUserPage->Female->setChecked(true);
    }
    else if (genderCharacter == 'm' || genderCharacter == 'M') {
        gender = "Male";
        editUserPage->Male->setChecked(true);
    }
    if (isVaccinated == false) {
        vaccinationState = "In waiting List";
    }
    else if (isVaccinated == true && recievedBothDoses == false) {
        vaccinationState = "Received First Dose";
    }
    else if (isVaccinated == true && recievedBothDoses == true) {
        vaccinationState = "Recieved Both Doses";
    }

    //setting UI
    editUserPage->Name->setText(QString::fromStdString(name));
    editUserPage->Id->setText(QString::fromStdString(nationalID));
    editUserPage->password->setText(QString::fromStdString(password));
    //editUserPage->Gender->setText(QString::fromStdString(gender));
    editUserPage->Age->setText(QString::fromStdString(to_string(age)));
    editUserPage->governorateCombo->setCurrentText(QString::fromStdString(governorate));
    editUserPage->comboBox->setCurrentText(QString::fromStdString(vaccinationState));












}
void User::EditUserData(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList, map<string, User>& user_map, EditUser* editUserPage, string vaccinationState) {

    queue<User>temp;
    char choiceForVaccineFirstDose, choiceForVaccineWaitingList, ChoiceForEditingFirstDose, choiceForEditingSecondDose, choiceorEditingWaitingList;
    int choiceForFirstDose, choiceForSecondDose, choiceForWaitingList;

    char newGender;
    bool isVaccinated, recievedBothDoses;

    string newName = editUserPage->Name->text().toStdString();
    string newPassword = editUserPage->password->text().toStdString();
    string nationalID = editUserPage->Id->text().toStdString();
    int newAge = editUserPage->Age->text().toInt();
    string newGovernorate = editUserPage->governorateCombo->currentText().toStdString();
    string vaccinationStateNew = editUserPage->comboBox->currentText().toStdString();
    if (editUserPage->Female->isChecked() == true) {
        newGender = 'F';
    }
    else if (editUserPage->Male->isChecked() == true) {
        newGender = 'M';
    }



    if (vaccinationState == "In waiting List") {

        while (!waitingList.empty()) {
            if (waitingList.front().get_national_id() != nationalID) {
                User temporaryUser(waitingList.front().get_name(), waitingList.front().get_national_id(), waitingList.front().get_password(), waitingList.front().get_gender(), waitingList.front().get_age(),
                    waitingList.front().get_governorate(), waitingList.front().is_vaccinated(), waitingList.front().has_received_both_doses());
                temp.push(temporaryUser);
                waitingList.pop();
            }
            else {
                waitingList.front().name = newName;
                waitingList.front().password = newPassword;
                waitingList.front().gender = newGender;
                waitingList.front().age = newAge;
                waitingList.front().governorate = newGovernorate;
                user_map[nationalID] = waitingList.front();
                if (vaccinationStateNew == "In waiting List") {
                    isVaccinated = false;
                    recievedBothDoses = false;
                    while (!temp.empty()) {
                        User temp1(temp.front().name, temp.front().national_id, temp.front().password, temp.front().gender, temp.front().age, temp.front().governorate, temp.front().vaccinated, temp.front().received_both_doses);
                        waitingList.push(temp1);
                        temp.pop();
                    }
                }
                else if (vaccinationStateNew == "Received First Dose") {
                    isVaccinated = true;
                    recievedBothDoses = false;
                    User userTemp(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age,
                        waitingList.front().governorate, isVaccinated, recievedBothDoses);
                    user_map[nationalID] = userTemp;
                    firstDose.push_back(userTemp);
                    waitingList.pop();
                    while (!temp.empty()) {
                        User temp1(temp.front().name, temp.front().national_id, temp.front().password, temp.front().gender, temp.front().age, temp.front().governorate, temp.front().vaccinated, temp.front().received_both_doses);
                        waitingList.push(temp1);
                        temp.pop();
                    }
                }
                else if (vaccinationStateNew == "Recieved Both Doses") {
                    isVaccinated = true;
                    recievedBothDoses = true;
                    User userTemp(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age,
                        waitingList.front().governorate, isVaccinated, recievedBothDoses);
                    user_map[nationalID] = userTemp;
                    secondDose.push_back(userTemp);
                    waitingList.pop();
                    while (!temp.empty()) {
                        User temp1(temp.front().name, temp.front().national_id, temp.front().password, temp.front().gender, temp.front().age, temp.front().governorate, temp.front().vaccinated, temp.front().received_both_doses);
                        waitingList.push(temp1);
                        temp.pop();
                    }
                }
               
            }

        }
    }
    else if (vaccinationState == "Received First Dose") {
        for (int i = 0; i < firstDose.size();i++) {
            if (firstDose[i].get_national_id() == nationalID) {
                firstDose[i].name = newName;
                firstDose[i].password = newPassword;
                firstDose[i].gender = newGender;
                firstDose[i].age = newAge;
                firstDose[i].governorate = newGovernorate;
                user_map[nationalID] = firstDose[i];
                if (vaccinationStateNew == "In waiting List") {
                    isVaccinated = false;
                    recievedBothDoses = false;
                    User userTemp(firstDose[i].name, firstDose[i].national_id, firstDose[i].password, firstDose[i].gender, firstDose[i].age,
                        firstDose[i].governorate, isVaccinated, recievedBothDoses);
                    user_map[nationalID] = userTemp;
                    waitingList.push(userTemp);
                    firstDose.erase(firstDose.begin() + i);
                }
                else if (vaccinationStateNew == "Recieved Both Doses") {
                    isVaccinated = true;
                    recievedBothDoses = true;
                    User userTemp(firstDose[i].name, firstDose[i].national_id, firstDose[i].password, firstDose[i].gender, firstDose[i].age,
                        firstDose[i].governorate, isVaccinated, recievedBothDoses);
                    user_map[nationalID] = userTemp;
                    secondDose.push_back(userTemp);
                    firstDose.erase(firstDose.begin() + i);
                }

            }
        }
    }
    else if (vaccinationState == "Recieved Both Doses") {
        for (int i = 0; i < secondDose.size(); i++) {
            if (secondDose[i].get_national_id() == nationalID) {
                secondDose[i].name = newName;
                secondDose[i].password = newPassword;
                secondDose[i].gender = newGender;
                secondDose[i].age = newAge;
                secondDose[i].governorate = newGovernorate;
                user_map[nationalID] = secondDose[i];
                if (vaccinationStateNew == "In waiting List") {
                    isVaccinated = false;
                    recievedBothDoses = false;
                    User userTemp(secondDose[i].name, secondDose[i].national_id, secondDose[i].password, secondDose[i].gender, secondDose[i].age,
                        secondDose[i].governorate, isVaccinated, recievedBothDoses);
                    user_map[nationalID] = userTemp;
                    waitingList.push(userTemp);
                    secondDose.erase(secondDose.begin() + i);
                }
                else if (vaccinationStateNew == "Received First Dose") {
                    isVaccinated = true;
                    recievedBothDoses = false;
                    User userTemp(secondDose[i].name, secondDose[i].national_id, secondDose[i].password, secondDose[i].gender, secondDose[i].age,
                        secondDose[i].governorate, isVaccinated, recievedBothDoses);
                    user_map[nationalID] = userTemp;
                    firstDose.push_back(userTemp);
                    secondDose.erase(secondDose.begin() + i);
                }
            }
        }
    }


























}
void User::deleteUser(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList, string nationalId, map<string, User>& user_map) {
   
    User temporaryUser;
    queue<User> temp;

    for (int i = 0; i < firstDose.size(); i++) {
        if (firstDose[i].get_national_id() == nationalId) {
            firstDose.erase(firstDose.begin() + i);
            user_map.erase(nationalId);
            break;
        }
    }
    for (int i = 0; i < secondDose.size(); i++) {
        if (secondDose[i].get_national_id() == nationalId) {
            secondDose.erase(secondDose.begin() + i);
            user_map.erase(nationalId);
            break;
        }
    }
    while (!waitingList.empty()) {
        if (waitingList.front().national_id != nationalId) {
            User tempUser(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age, waitingList.front().governorate, waitingList.front().vaccinated, waitingList.front().received_both_doses);
            temp.push(tempUser);
            waitingList.pop();
        }
        else {
            waitingList.pop();
        }
        while (!temp.empty()) {
            User tempUser1(temp.front().name, temp.front().national_id, temp.front().password, temp.front().gender, temp.front().age, temp.front().governorate, temp.front().vaccinated, temp.front().received_both_doses);
            waitingList.push(tempUser1);
            temp.pop();
        }
    }
    user_map.erase(nationalId);



  
}


User::~User() {

}

//constructor
Admin::Admin() {
    password = "";
    userName = "";

}
Admin::Admin(string adminUserName, string adminPassword) {
    this->userName = adminUserName;
    this->password = adminPassword;
}
//to calculate some statistics 
void Admin::Statistics(vector<User>firstDose, vector<User>secondDose, queue<User>waitingList, map<string, User> user_map, StatisticsPage* statisticsPage) {
    double firstDosePct, secondDosePct, femalePct, malePct;
    double firstRangePct = 0.0, secondRangePct = 0, thirdRangePct = 0, fourthRangePct = 0, fifthRangePct = 0;
    double allUsers = user_map.size();
    int fCount = 0, mCount = 0;
    int firstRange1 = 0, secondRange1 = 0, thirdRange1 = 0, fourthRange1 = 0, fifthRange1 = 0;
    int firstRange = 0, secondRange = 0, thirdRange = 0, fourthRange = 0, fifthRange = 0;



    //calculate the pct of first and second dose
    firstDosePct = ((double)firstDose.size() / allUsers) * 100.0;
    secondDosePct = ((double)secondDose.size() / allUsers) * 100.00;

    //filter males and females from first dose vector
    map<string, User>::iterator usersIt;
    for (usersIt = user_map.begin(); usersIt != user_map.end(); usersIt++) {
        if (usersIt->second.get_gender() == 'f' || usersIt->second.get_gender() == 'F') {
            fCount++;
        }
        else if(usersIt->second.get_gender() == 'm' || usersIt->second.get_gender() == 'M') {
            mCount++;
        }
    }


    malePct = ((double)mCount / allUsers) * 100.00;
    femalePct = ((double)fCount / allUsers) * 100.00;


    
    
    for (usersIt = user_map.begin(); usersIt != user_map.end(); usersIt++) {
        if (usersIt->second.get_age() >= 75 && usersIt->second.is_vaccinated() && usersIt->second.has_received_both_doses()) {
            firstRange++;
        }
        else if (usersIt->second.get_age() >= 65 && usersIt->second.get_age() <= 74 && usersIt->second.is_vaccinated() && usersIt->second.has_received_both_doses()) {
            secondRange++;
        }
        else if (usersIt->second.get_age() >= 50 && usersIt->second.get_age() <= 64 && usersIt->second.is_vaccinated() && usersIt->second.has_received_both_doses()) {
            thirdRange++;
        }
        else if (usersIt->second.get_age() >= 40 && usersIt->second.get_age() <= 49 && usersIt->second.is_vaccinated() && usersIt->second.has_received_both_doses()) {
            fourthRange++;
        }
        else if (usersIt->second.get_age() >= 18 && usersIt->second.get_age() <= 39 && usersIt->second.is_vaccinated() && usersIt->second.has_received_both_doses()) {
            fifthRange++;
        }
        else if (usersIt->second.get_age() >= 75 ) {
            firstRange1++;
        }
        else if (usersIt->second.get_age() >= 65 && usersIt->second.get_age() <= 74) {
            secondRange1++;
        }
        else if (usersIt->second.get_age() >= 50 && usersIt->second.get_age() <= 64) {
            thirdRange1++;
        }
        else if (usersIt->second.get_age() >= 40 && usersIt->second.get_age() <= 49) {
            fourthRange1++;
        }
        else if (usersIt->second.get_age() >= 18 && usersIt->second.get_age() <= 39) {
            fifthRange1++;
        }

    }
    



    //calculate the pct of each age group
    if ((firstRange + firstRange1) != 0) {
        firstRangePct = ((double)firstRange / ((double)(firstRange + firstRange1))) * 100.00;

    }
    if ((secondRange + secondRange1) != 0) {
        secondRangePct = ((double)secondRange / ((double)(secondRange + secondRange1))) * 100.00;

    }
    if ((thirdRange + thirdRange1) != 0) {
        thirdRangePct = ((double)thirdRange / ((double)(thirdRange + thirdRange1))) * 100.00;

    }
    if ((fourthRange + fourthRange1) != 0) {
        fourthRangePct = ((double)fourthRange / ((double)(fourthRange + fourthRange1))) * 100.00;

    }
    if ((fifthRange + fifthRange1 ) != 0) {
        fifthRangePct = ((double)fifthRange / ((double)(fifthRange + fifthRange1))) * 100.00;

    }
   

    statisticsPage->firstdosePct->setText(QString::fromStdString(to_string(firstDosePct))+"%");
    statisticsPage->secondPct->setText(QString::fromStdString(to_string(secondDosePct) + "%"));
    statisticsPage->femalesPct->setText(QString::fromStdString(to_string(femalePct) + "%"));
    statisticsPage->malesPct->setText(QString::fromStdString(to_string(ceilf(malePct)) + "%"));
    statisticsPage->firstRangePct->setText(QString::fromStdString(to_string(firstRangePct) + "%"));
    statisticsPage->secondRangePct->setText(QString::fromStdString(to_string(secondRangePct) + "%"));
    statisticsPage->thirdRangePct->setText(QString::fromStdString(to_string(thirdRangePct) + "%"));
    statisticsPage->fourthRangePct->setText(QString::fromStdString(to_string(fourthRangePct) + "%"));
    statisticsPage->fifthRangePct->setText(QString::fromStdString(to_string(fifthRangePct) + "%"));



    //bonus 

    double cairoPct = 0, gizaPct = 0, matruhPct = 0, asyutPct = 0, southPct = 0, aswanPct = 0, luxorPct = 0, alexPct = 0;
    int countCairo = 0, countGiza = 0, countMatruh = 0, countAsyut = 0, countSouth = 0, countAswan = 0, countLuxor = 0, countAlex = 0;
    //filter each governorate from first dose
    for (int i = 0; i < firstDose.size(); i++) {
        if (firstDose[i].get_governorate() == "Cairo") {
            countCairo++;
        }
        else if (firstDose[i].get_governorate() == "Giza") {
            countGiza++;
        }
        else if (firstDose[i].get_governorate() == "Matruh") {
            countMatruh++;
        }
        else if (firstDose[i].get_governorate() == "Asyut") {
            countAsyut++;
        }
        else if (firstDose[i].get_governorate() == "South Sinai") {
            countSouth++;
        }
        else if (firstDose[i].get_governorate() == "Aswan") {
            countAswan++;
        }
        else if (firstDose[i].get_governorate() == "Luxor") {
            countLuxor++;
        }
        else if (firstDose[i].get_governorate() == "Alexandria") {
            countAlex++;
        }
    }
    //Filter each governorate from second dose
    for (int i = 0; i < secondDose.size(); i++) {
        if (secondDose[i].get_governorate() == "Cairo") {
            countCairo++;
        }
        else if (secondDose[i].get_governorate() == "Giza") {
            countGiza++;
        }
        else if (secondDose[i].get_governorate() == "Matruh") {
            countMatruh++;
        }
        else if (secondDose[i].get_governorate() == "Asyut") {
            countAsyut++;
        }
        else if (secondDose[i].get_governorate() == "South Sinai") {
            countSouth++;
        }
        else if (secondDose[i].get_governorate() == "Aswan") {
            countAswan++;
        }
        else if (secondDose[i].get_governorate() == "Luxor") {
            countLuxor++;
        }
        else if (secondDose[i].get_governorate() == "Alexandria") {
            countAlex++;
        }
    }
   
 
    double vaccinatedUsers = allUsers - waitingList.size();
    //calculate the percentage of each governorate
    if (countCairo != 0) {
        cairoPct = ((double)countCairo / vaccinatedUsers) * 100.00;
    }
    if (countGiza != 0) {
        gizaPct = ((double)countGiza / vaccinatedUsers) * 100.00;
    }
    if (countMatruh != 0) {
        matruhPct = ((double)countMatruh / vaccinatedUsers) * 100.00;
    }
    if (countAsyut != 0) {
        asyutPct = ((double)countAsyut / vaccinatedUsers) * 100.00;
    }
    if (countSouth != 0) {
        southPct = ((double)countSouth / vaccinatedUsers) * 100.00;
    }
    if (countAswan != 0) {
        aswanPct = ((double)countAswan / vaccinatedUsers) * 100.00;
    }
    if (countLuxor != 0) {
        luxorPct = ((double)countLuxor / vaccinatedUsers) * 100.00;
    }
    if (countAlex != 0) {
        alexPct = ((double)countAlex / vaccinatedUsers) * 100.00;
    }


    statisticsPage->Cairo->setText(QString::fromStdString(to_string(cairoPct)) + "%");
    statisticsPage->Giza->setText(QString::fromStdString(to_string(gizaPct)) + "%");
    statisticsPage->Matruh->setText(QString::fromStdString(to_string(matruhPct)) + "%");
    statisticsPage->Asyut->setText(QString::fromStdString(to_string(asyutPct)) + "%");
    statisticsPage->Sinai->setText(QString::fromStdString(to_string(southPct)) + "%");
    statisticsPage->Aswan->setText(QString::fromStdString(to_string(aswanPct)) + "%");
    statisticsPage->Luxor->setText(QString::fromStdString(to_string(luxorPct)) + "%");
    statisticsPage->Alex->setText(QString::fromStdString(to_string(alexPct)) + "%");





   

}
// view records of users
void Admin::ViewRecord(map<string, User> user_map, DisplayOneUser* displayOneUser, NewViewUi* viewUsersPage, int typeofview, string nationalID) {
   
       switch (typeofview)
       {
        case 1:
            for (auto itr = user_map.begin(); itr != user_map.end(); ++itr)
            {
                string gender, vaccinationState;
                if (itr->second.get_gender() == 'f' || itr->second.get_gender() == 'F') {
                    gender = "Female";
                }
                else if (itr->second.get_gender() == 'm' || itr->second.get_gender() == 'M') {
                    gender = "Male";
                }
                if (!itr->second.is_vaccinated()) {
                    vaccinationState = "In Waiting List";

                }
                else {
                    if (!itr->second.has_received_both_doses()) {
                        vaccinationState = "Recieved First Dose";
                    }               
                    else {
                        vaccinationState = "Recieved Both Doses";
                    }
                }

                string userRecord = "Name: " + itr->second.get_name() + " \t" + "NationalID: " + itr->second.get_national_id() + "\t " + "Password: " + itr->second.get_password() + "\t " +
                    "Governorate: " + itr->second.get_governorate() + "\t " + "Gender: " + gender + "\t " + "Age: " + to_string(itr->second.get_age()) + "\t " + "Vaccination State: " + vaccinationState;
              
                QFont BellMT("Bell MT", 14, QFont::Bold);

                QLineEdit* userRecordLine = new QLineEdit();
                userRecordLine->setText(QString::fromStdString(userRecord));
                userRecordLine->setReadOnly(true);
                userRecordLine->setFont(BellMT);
                userRecordLine->setStyleSheet("QLineEdit {color: rgb(46, 68, 147)}");
                viewUsersPage->verticalLayout_3->addWidget(userRecordLine);
            }
            break;
        case 2:
            displayOneUser->Name->setText(QString::fromStdString(user_map[nationalID].get_name()));
            displayOneUser->NationalID->setText(QString::fromStdString(user_map[nationalID].get_national_id()));
            displayOneUser->Password->setText(QString::fromStdString(user_map[nationalID].get_password()));
            displayOneUser->Age->setText(QString::fromStdString(to_string(user_map[nationalID].get_age())));
            displayOneUser->Governorate->setText(QString::fromStdString(user_map[nationalID].get_governorate()));
            if (user_map[nationalID].get_gender() == 'f' || user_map[nationalID].get_gender() == 'F') {
                displayOneUser->Gender->setText("Female");
            }
            else if (user_map[nationalID].get_gender() == 'm' || user_map[nationalID].get_gender() == 'M') {
                displayOneUser->Gender->setText("Male");

            }
            if (!user_map[nationalID].is_vaccinated()) {
                displayOneUser->VaccinationState->setText("In Waiting List");
            }
            else {
                if (!user_map[nationalID].has_received_both_doses()) {
                    displayOneUser->VaccinationState->setText("Recieved One Dose");
                }
                else {
                    displayOneUser->VaccinationState->setText("Recieved Both Doses");
                }
            }       
            break;
        default:
            break;
       }
    
}
void Admin::DeleteRecord(map<string, User>& user_map, vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList, int typeOfDeletion, string nationalID) {
    if (user_map.empty())
        cout << "there is no records to delete.";

    else {
        switch (typeOfDeletion)
        {
        case 1:
            user_map.clear();
            firstDose.clear();
            secondDose.clear();
            while (!waitingList.empty()) {
                waitingList.pop();
            }
            break;
        case 2:
            if (user_map.find(nationalID) != user_map.end()) {
                user_map.erase(nationalID);
            }
            
            break;
        default:
            break;
        }
    }

}
// filterRecords by no. of doses or age
void Admin::FilteredRecords(vector<User>firstDose, vector<User>secondDose, int numOfDose, NewViewUi* viewUsersPageFirstDose, NewViewUi* viewUsersPageSecondDose) {
    vector<User>::iterator it;
    string gender;

    if (numOfDose == 1) {
        

        it = firstDose.begin();
        while (it != firstDose.end())
        {
            if (it->get_gender() == 'f' || it->get_gender() == 'F') {
                gender = "Female";
            }
            else if (it->get_gender() == 'm' || it->get_gender() == 'M') {
                gender = "Male";
            }
            string firstDoseRecord = "National_id:  " + it->get_national_id() + "  \t " + "Name:  " + it->get_name() + " \t  "+"Password:  "+it->get_password()+ "  \t " + "Gender:  " + gender + "   \t" + "Age:  "
                    + to_string(it->get_age()) + "  \t " + "Governorate:  " + "  \t " + it->get_governorate();
            it++;

            QFont BellMT("Bell MT", 14, QFont::Bold);

            QLineEdit* userRecordLine = new QLineEdit();
            userRecordLine->setText(QString::fromStdString(firstDoseRecord));
            userRecordLine->setReadOnly(true);
            userRecordLine->setFont(BellMT);
            userRecordLine->setStyleSheet("QLineEdit {color: rgb(46, 68, 147)}");
            viewUsersPageFirstDose->verticalLayout_3->addWidget(userRecordLine);
        }

    }
    else if (numOfDose == 2) {
        it = secondDose.begin();
        while (it != secondDose.end())
        {
            if (it->get_gender() == 'f' || it->get_gender() == 'F') {
                gender = "Female";
            }
            else if (it->get_gender() == 'm' || it->get_gender() == 'M') {
                gender = "Male";
            }
            string secondDoseRecord = "National_id:  " + it->get_national_id() + " \t  " + "Name:  " + it->get_name() + "  \t " + "Password:  " + it->get_password() + "  \t " + "Gender:  " + gender + " \t  " + "Age:  "
                + to_string(it->get_age()) + "  \t " + "Governorate:  " + "  \t " + it->get_governorate();
            it++;

            QFont BellMT("Bell MT", 14, QFont::Bold);

            QLineEdit* userRecordLine = new QLineEdit();
            userRecordLine->setText(QString::fromStdString(secondDoseRecord));
            userRecordLine->setReadOnly(true);
            userRecordLine->setFont(BellMT);
            userRecordLine->setStyleSheet("QLineEdit {color: rgb(46, 68, 147)}");
            viewUsersPageSecondDose->verticalLayout_3->addWidget(userRecordLine);
        }
    }
   
}
void Admin::OrderedByAge(vector<User>firstDose, vector<User>secondDose, NewViewUi* viewUsersPageOrderedByAge) {
    vector<User>both_users;
    both_users.insert(both_users.end(), firstDose.begin(), firstDose.end());
    both_users.insert(both_users.end(), secondDose.begin(), secondDose.end());
    sort(both_users.begin(), both_users.end(), [](const User& a, const User& b) { return a.get_age() < b.get_age(); });//Sorting the vector;
    for (auto i = both_users.begin(); i < both_users.end(); i++)
    {
        string gender, vaccinationState;
        if (i->get_gender() == 'F' || i->get_gender() == 'f') {
            gender = "Female";
        }
        else if (i->get_gender() == 'M' || i->get_gender() == 'm') {
            gender = "Male";
        }
        if (i->is_vaccinated() == true && i->has_received_both_doses() == false) {
            vaccinationState = "First Dose Only";
        }
        else if (i->is_vaccinated() == true && i->has_received_both_doses() == true) {
            vaccinationState = "Recieved Both Doses";
        }
        string record = "Age: " + to_string(i->get_age()) + "\t" + "National ID: " + i->get_national_id() + "\t" + "Name: " + i->get_name() + "\t" + "Gender: " + gender + "\t" + "Password: " +
            i->get_password() + "\t" + "Governorate: " + i->get_governorate() + "\t"+"Vaccination State : " + vaccinationState;
        QFont BellMT("Bell MT", 14, QFont::Bold);

        QLineEdit* userRecordLine = new QLineEdit();
        userRecordLine->setText(QString::fromStdString(record));
        userRecordLine->setReadOnly(true);
        userRecordLine->setFont(BellMT);
        userRecordLine->setStyleSheet("QLineEdit {color: rgb(46, 68, 147)}");
        viewUsersPageOrderedByAge->verticalLayout_3->addWidget(userRecordLine);

    }
}
//view record in waiting list
void Admin::view_record(queue<User>waitingList, ViewWaitingList* viewWaitingListPage)
{


    User user1 = waitingList.front();
    viewWaitingListPage->Name->setText(QString::fromStdString(user1.get_name()));
    viewWaitingListPage->NationalId->setText(QString::fromStdString(user1.get_national_id()));
    viewWaitingListPage->Password->setText(QString::fromStdString(user1.get_password()));
    viewWaitingListPage->Age->setText(QString::fromStdString(to_string(user1.get_age())));
    if (user1.get_gender() == 'f' || user1.get_gender() == 'F') {
        viewWaitingListPage->Gender->setText(QString::fromStdString("Female"));
    }
    else if (user1.get_gender() == 'm' || user1.get_gender() == 'M') {
        viewWaitingListPage->Gender->setText(QString::fromStdString("Male"));
    }
    viewWaitingListPage->governorate->setText(QString::fromStdString(user1.get_governorate()));




}
void WriteAll(vector<User> firstDose, vector<User> secondDose, queue<User> waitingList) {
    WriteWaitingList(waitingList);
    WriteOneDose(firstDose);
    WriteTwoDose(secondDose);
}
void WriteTwoDose(vector<User>secondDose) {

    ofstream ofile("secondDose.txt");
    for (int i = 0; i < secondDose.size(); i++)
    {
        ofile << secondDose[i].get_name() << " " << secondDose[i].get_national_id() << " " << secondDose[i].get_password() << " " << secondDose[i].get_age() << " " << secondDose[i].get_gender() << " " << secondDose[i].get_governorate() << " " << secondDose[i].is_vaccinated() << " " << secondDose[i].has_received_both_doses() << endl;
    }
    ofile.close();

}
void WriteOneDose(vector<User>firstDose) {
    ofstream ofile("firstDose.txt");
    for (int i = 0; i < firstDose.size(); i++)
    {
        ofile << firstDose[i].get_name() << " " << firstDose[i].get_national_id() << " " << firstDose[i].get_password() << " " << firstDose[i].get_age() << " " << firstDose[i].get_gender() << " " << firstDose[i].get_governorate() << " " << firstDose[i].is_vaccinated() << " " << firstDose[i].has_received_both_doses() << endl;
    }
    ofile.close();

}
void WriteWaitingList(queue<User>waitingList) {
    queue<User> temp = waitingList;
    User u;
    ofstream myfile("waitinglist.txt");

    while (!temp.empty())
    {
        u = temp.front();
        myfile << u.get_national_id() << " " << u.get_name() << " " <<  u.get_password() << " " << u.get_age() << " " << u.get_gender() << " " << u.get_governorate() << " " << u.is_vaccinated() << " " << u.has_received_both_doses() << endl;
        temp.pop();

    }
    myfile.close();

}
