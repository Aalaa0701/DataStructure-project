#include "user.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include<map>

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
// Function to add a new user record
void User::add_user(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map) {
    string name, national_id, password, governorate;
    char gender;
    int age;

    // Get user input for personal information
    cout << "Enter full name: ";
    getline(cin, name);
  

    /*do
    {
        cout << "Enter national ID (13 digits): ";
        getline(cin, national_id);

    } while (national_id.length() != 13 || !all_of(national_id.begin(), national_id.end(), ::isdigit) || user_map.find(national_id) != user_map.end());*/

    cout << "Enter national ID (13 digits): ";
    getline(cin, national_id);
    while (national_id.length() != 13 || !all_of(national_id.begin(), national_id.end(), ::isdigit) || user_map.find(national_id) != user_map.end())
    {
        cout << "Invalid national ID or ID already exists. Please enter a unique 13-digit number: ";
        getline(cin, national_id);
    }

    cout << "Enter password: ";
    getline(cin, password);

    cout << "Enter gender (M/F): ";
    cin >> gender;
    cin.ignore();

    cout << "Enter age: ";
    cin >> age;
    cin.ignore();

    cout << "Enter governorate: ";
    getline(cin, governorate);

    bool vaccinated = false, received_both_doses = false;
    cout << "Have you been vaccinated yet? (Y/N): ";
    char vaccinated_input;
    cin >> vaccinated_input;
    cin.ignore();
    vaccinated = (vaccinated_input == 'Y' || vaccinated_input == 'y');
    if (vaccinated) {
        cout << "Have you received both doses of the vaccine? (Y/N): ";
        char received_both_doses_input;
        cin >> received_both_doses_input;
        cin.ignore();
        received_both_doses = (received_both_doses_input == 'Y' || received_both_doses_input == 'y');
    }
    if (vaccinated && !received_both_doses) {
        User user(name, national_id, password, gender, age, governorate, vaccinated, received_both_doses);
        firstDose.push_back(user); // add user to the one-dose vector
        cout << "User added to the one-dose list.\n";
        user_map.insert({ national_id,user });
        //user_map[national_id] = user; // add user to the map
        return;
    }
    if (vaccinated && received_both_doses) {
        User user(name, national_id, password, gender, age, governorate, vaccinated, received_both_doses);
        secondDose.push_back(user); // add user to the two-dose vector
        cout << "User added to the two-dose list.\n";
        user_map.insert({ national_id,user });
        //user_map[national_id] = user; // add user to the map
        return;
    }
    if (!vaccinated) {
        User user(name, national_id, password, gender, age, governorate, vaccinated, received_both_doses);
        waiting_list.push(user); // add user to waiting list
        cout << "User added to waiting list.\n";
        user_map.insert({national_id,user});
        //user_map[national_id] = user; // add user to the map
        return;
    }
}

//Function to display User
void User::display_user_data(vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map, string& nationalId) {
    string  national_id;
    string  password;
    bool if_exist = true;
    while (if_exist == true)
    {


        cout << "Enter national ID (13 digits) :";
        getline(cin, national_id);

        while (national_id.length() != 13)
        {
            cout << "Please,Enter national ID (13 digits) : ";
            getline(cin, national_id);
        }
        cout << "Enter password :";
        getline(cin, password);

        if (user_map.find(national_id) != user_map.end())
        {

            if (password == user_map[national_id].get_password())
            {

                cout << "your name is:" << user_map[national_id].get_name() << endl;
                cout << "your  national ID is:" << user_map[national_id].get_national_id() << endl;
                cout << "your gender is:" << user_map[national_id].get_gender() << endl;
                cout << "your age is:" << user_map[national_id].get_age() << endl;
                cout << "your governorate is:" << user_map[national_id].get_governorate() << endl;
                cout << "If you are vaccinated:" << user_map[national_id].is_vaccinated() << endl;
                cout << "IF you have received both doses:" << user_map[national_id].has_received_both_doses() << endl;
                nationalId = national_id;
                if_exist = false;
            }
            else
            {
                cout << "Please try again , Your password or national Id isn't correct" << endl;
            }

        }
        else
        {
            cout << "Please try again , Your password or national Id isn't correct" << endl;
        }

    }
}


//void User::EditUserData(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList, string nationalId) {
//    //vector<User>::iterator firstDoseIt, secondDoseIt;
//    /*if (whichData == 0) {
//        char ChoiceForEditingAgain;
//        int choice;
//        do
//        {
//            cout << "Please enter 1 for name, 2 for password, 3 for gender, 4 for age, 5 for governorate or 6 to edit vaccination information" << endl;
//            cin >> choice;
//            if (choice == 1) {
//                string newName;
//                cout << "PLease enter new Name" << endl;
//                getline(cin, newName);
//                firstDose[firstIndex].name = newName;
//            }
//            else if (choice == 2) {
//                string newPassword;
//                cout << "Please enter new password" << endl;
//                getline(cin, newPassword);
//                firstDose[firstIndex].password = newPassword;
//            }
//            else if (choice == 3) {
//                char newGender;
//                cout << "Please enter gender" << endl;
//                cin >> newGender;
//                if (newGender != 'F' && newGender != 'f' && newGender != 'M' && newGender != 'm') {
//                    cout << "Please enter valid character" << endl;
//                    return;
//                }
//                else {
//                    firstDose[firstIndex].gender = newGender;
//                }
//
//            }
//            else if (choice == 4) {
//                int newAge;
//                cout << "Please enter updated age" << endl;
//                cin >> newAge;
//                firstDose[firstIndex].age = newAge;
//            }
//            else if (choice == 5) {
//                string newGovernorate;
//                cout << "please enter updated governorate" << endl;
//                getline(cin, newGovernorate);
//                firstDose[firstIndex].governorate = newGovernorate;
//            }
//            else if (choice == 6) {
//                char choiceForVaccine;
//                cout << "did you recieve the second dose?" << endl;
//                cin >> choiceForVaccine;
//                if (choiceForVaccine == 'Y' || choiceForVaccine == 'y') {
//                    User userToBeTransferred(firstDose[firstIndex].name, firstDose[firstIndex].national_id, firstDose[firstIndex].password, firstDose[firstIndex].gender, firstDose[firstIndex].age, firstDose[firstIndex].governorate, firstDose[firstIndex].vaccinated, firstDose[firstIndex].received_both_doses);
//                    firstDose.erase(firstDose.begin() + firstIndex);
//                    secondDose.push_back(userToBeTransferred);
//                }
//                else {
//                    return;
//                }
//            }
//            else {
//                cout << "Invalid Choice" << endl;
//            }
//            cout << "Do you want to edit another info?" << endl;
//            cin >> ChoiceForEditingAgain;
//        } while (ChoiceForEditingAgain=='Y'||ChoiceForEditingAgain=='y');
//       
//
//    }*/
//    /*else if (whichData == 1) {
//        int choice;
//        char choiceForEditing;
//        do
//        {
//            cout << "Please enter 1 for name, 2 for password, 3 for gender, 4 for age, 5 for governorate" << endl;
//            cin >> choice;
//            if (choice == 1) {
//                string newName;
//                cout << "Please enter new Name" << endl;
//                getline(cin, newName);
//                secondDose[secondIndex].name = newName;
//            }
//            else if (choice == 2) {
//                string newPassword;
//                cout << "Please enter new password" << endl;
//                getline(cin, newPassword);
//                secondDose[secondIndex].password = newPassword;
//            }
//            else if (choice == 3) {
//                char newGender;
//                cout << "Please enter Gender" << endl;
//                cin >> newGender;
//                if (newGender != 'F' && newGender != 'f' && newGender != 'M' && newGender != 'm') {
//                    cout << "Please enter valid character" << endl;
//                    return;
//                }
//                else {
//                    secondDose[secondIndex].gender = newGender;
//                }
//            }
//            else if (choice == 4) {
//                int newAge;
//                cout << "Please enter updated Age" << endl;
//                cin >> newAge;
//                secondDose[secondIndex].age = newAge;
//            }
//            else if (choice == 5) {
//                string newGovernorate;
//                cout << "Please enter updated governorate" << endl;
//                getline(cin, newGovernorate);
//                secondDose[secondIndex].governorate = newGovernorate;
//            }
//            else {
//                cout << "Invalid Choice" << endl;
//            }
//
//            cout << "Do you want to edit another Info?" << endl;
//            cin >> choiceForEditing;
//
//        } while (choiceForEditing=='Y'||choiceForEditing=='y');
//       
//        
//    }*/
//    /*else if (whichData == 2) {
//        int choice;
//        char choiceForLoop;
//        queue<User>temp;
//        while (!waitingList.empty()) {
//            if (waitingList.front().get_national_id() != nationalId) {
//                User temporaryUser(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age, waitingList.front().governorate, waitingList.front().vaccinated, waitingList.front().received_both_doses);
//                temp.push(temporaryUser);
//                waitingList.pop();
//            }
//            else {
//                do {
//                    cout << "Please enter 1 for name, 2 for password, 3 for gender, 4 for age, 5 for governorate or 6 to edit vaccination information" << endl;
//                    cin >> choice;
//                    if (choice == 1) {
//                        cout << "Please enter name" << endl;
//                        string newName;
//                        getline(cin, newName);
//                        waitingList.front().name = newName;
//                    }
//                    else if (choice == 2) {
//                        cout << "Please enter password" << endl;
//                        string newPassword;
//                        getline(cin, newPassword);
//                        waitingList.front().password = newPassword;
//                    }
//                    else if (choice == 3) {
//                        cout << "Please enter gender" << endl;
//                        char newGender;
//                        cin >> newGender;
//                        if (newGender != 'F' && newGender != 'f' && newGender != 'M' && newGender != 'm') {
//                            cout << "Please enter valid character" << endl;
//                            return;
//                        }
//                        else {
//                            waitingList.front().gender = newGender;
//                        }
//                    }
//                    else if (choice == 4) {
//                        cout << "Please enter age" << endl;
//                        int newAge;
//                        cin >> newAge;
//                        waitingList.front().age = newAge;
//                    }
//                    else if (choice == 5) {
//                        cout << "Please enter governorate" << endl;
//                        string newGovernorate;
//                        getline(cin, newGovernorate);
//                        waitingList.front().governorate = newGovernorate;
//                    }
//                    else if (choice == 6) {
//                        cout << "Did you get vaccinated?" << endl;
//                        char choiceForVaccination;
//                        cin >> choiceForVaccination;
//                        if (choiceForVaccination == 'Y' || choiceForVaccination == 'y') {
//                            waitingList.front().vaccinated = true;
//                            cout << "Did you recieve 1 dose or 2 doses?" << endl;
//                            int choiceForNoOfDoses;
//                            cin >> choiceForNoOfDoses;
//                            if (choiceForNoOfDoses == 1) {
//                                waitingList.front().received_both_doses = false;
//                                User userToBeTransferred(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age, waitingList.front().governorate, waitingList.front().vaccinated, waitingList.front().received_both_doses);
//                                waitingList.pop();
//                                firstDose.push_back(userToBeTransferred);
//                            }
//                            else if (choiceForNoOfDoses == 2) {
//                                waitingList.front().received_both_doses = true;
//                                User userToBeTransferred2(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age, waitingList.front().governorate, waitingList.front().vaccinated, waitingList.front().received_both_doses);
//                                waitingList.pop();
//                                secondDose.push_back(userToBeTransferred2);
//                            }
//                            else {
//                                cout << "Invalid choice" << endl;
//                            }
//                        }
//                        else if (choiceForVaccination == 'N' || choiceForVaccination == 'n') {
//                            return;
//                        }
//                        else {
//                            cout << "Please enter valid choice" << endl;
//                        }
//                    }
//                    else {
//                        cout << "Wrong choice" << endl;
//                    }
//                    cout << "Do you want to edit another thing" << endl;
//                    cin >> choiceForLoop;
//                } while (choiceForLoop == 'Y' || choiceForLoop == 'y');
//                while (!temp.empty()) {
//                    User temp1(temp.front().name, temp.front().national_id, temp.front().password, temp.front().gender, temp.front().age, temp.front().governorate, temp.front().vaccinated, temp.front().received_both_doses);
//                    waitingList.push(temp1);
//                    temp.pop();
//                }
//            }
//        }
//       
//    }
//    else {
//        cout << "Wrong whichData index" << endl;
//    }*/
//    queue<User>temp;
//    int counterForFirstDose = 0, counterForSecondDose = 0;
//
//    for (int i = 0;i < firstDose.size();i++) {
//        if (firstDose[i].national_id == nationalId) {
//            char ChoiceForEditingAgain;
//            int choice;
//            do
//            {
//                cout << "Please enter 1 for name, 2 for password, 3 for gender, 4 for age, 5 for governorate or 6 to edit vaccination information" << endl;
//                cin >> choice;
//                cin.ignore();
//                if (choice == 1) {
//                    string newName;
//                    cout << "PLease enter new Name" << endl;
//                    getline(cin, newName);
//                    firstDose[i].name = newName;
//                }
//                else if (choice == 2) {
//                    string newPassword;
//                    cout << "Please enter new password" << endl;
//                    getline(cin, newPassword);
//                    firstDose[i].password = newPassword;
//                }
//                else if (choice == 3) {
//                    char newGender;
//                    cout << "Please enter gender" << endl;
//                    cin >> newGender;
//                    cin.ignore();
//                    if (newGender != 'F' && newGender != 'f' && newGender != 'M' && newGender != 'm') {
//                        cout << "Please enter valid character" << endl;
//                        return;
//                    }
//                    else {
//                        firstDose[i].gender = newGender;
//                    }
//
//                }
//                else if (choice == 4) {
//                    int newAge;
//                    cout << "Please enter updated age" << endl;
//                    cin >> newAge;
//                    cin.ignore();
//                    firstDose[i].age = newAge;
//                }
//                else if (choice == 5) {
//                    string newGovernorate;
//                    cout << "please enter updated governorate" << endl;
//                    getline(cin, newGovernorate);
//                    firstDose[i].governorate = newGovernorate;
//                }
//                else if (choice == 6) {
//                    char choiceForVaccine;
//                    cout << "did you recieve the second dose?" << endl;
//                    cin >> choiceForVaccine;
//                    cin.ignore();
//                    if (choiceForVaccine == 'Y' || choiceForVaccine == 'y') {
//                        User userToBeTransferred(firstDose[i].name, firstDose[i].national_id, firstDose[i].password, firstDose[i].gender, firstDose[i].age, firstDose[i].governorate, firstDose[i].vaccinated, firstDose[i].received_both_doses);
//                        firstDose.erase(firstDose.begin() + counterForFirstDose);
//                        secondDose.push_back(userToBeTransferred);
//                    }
//                    else {
//                        return;
//                    }
//                }
//                else {
//                    cout << "Invalid Choice" << endl;
//                }
//                cout << "Do you want to edit another info?" << endl;
//                cin >> ChoiceForEditingAgain;
//            } while (ChoiceForEditingAgain == 'Y' || ChoiceForEditingAgain == 'y');
//            break;
//
//        }
//    }
//    for (int i = 0; i < secondDose.size();i++) {
//        if (secondDose[i].get_national_id() == nationalId) {
//            int choice;
//            char choiceForEditing;
//            do
//            {
//                cout << "Please enter 1 for name, 2 for password, 3 for gender, 4 for age, 5 for governorate" << endl;
//                cin >> choice;
//                cin.ignore();
//                if (choice == 1) {
//                    string newName;
//                    cout << "Please enter new Name" << endl;
//                    getline(cin, newName);
//                    secondDose[i].name = newName;
//                }
//                else if (choice == 2) {
//                    string newPassword;
//                    cout << "Please enter new password" << endl;
//                    getline(cin, newPassword);
//                    secondDose[i].password = newPassword;
//                }
//                else if (choice == 3) {
//                    char newGender;
//                    cout << "Please enter Gender" << endl;
//                    cin >> newGender;
//                    cin.ignore();
//                    if (newGender != 'F' && newGender != 'f' && newGender != 'M' && newGender != 'm') {
//                        cout << "Please enter valid character" << endl;
//                        return;
//                    }
//                    else {
//                        secondDose[i].gender = newGender;
//                    }
//                }
//                else if (choice == 4) {
//                    int newAge;
//                    cout << "Please enter updated Age" << endl;
//                    cin >> newAge;
//                    cin.ignore();
//                    secondDose[i].age = newAge;
//                }
//                else if (choice == 5) {
//                    string newGovernorate;
//                    cout << "Please enter updated governorate" << endl;
//                    getline(cin, newGovernorate);
//                    secondDose[i].governorate = newGovernorate;
//                }
//                else {
//                    cout << "Invalid Choice" << endl;
//                }
//
//                cout << "Do you want to edit another Info?" << endl;
//                cin >> choiceForEditing;
//
//            } while (choiceForEditing == 'Y' || choiceForEditing == 'y');
//            break;
//        }
//
//    }
//
//    /*for (firstDoseIt = firstDose.begin();firstDoseIt < firstDose.end();firstDoseIt++) {
//        if (nationalId == firstDoseIt->get_national_id()) {
//            char ChoiceForEditingAgain;
//            int choice;
//            do
//            {
//                cout << "Please enter 1 for name, 2 for password, 3 for gender, 4 for age, 5 for governorate or 6 to edit vaccination information" << endl;
//                cin >> choice;
//                cin.ignore();
//                if (choice == 1) {
//                    string newName;
//                    cout << "PLease enter new Name" << endl;
//                    getline(cin, newName);
//                    firstDoseIt->name = newName;
//                }
//                else if (choice == 2) {
//                    string newPassword;
//                    cout << "Please enter new password" << endl;
//                    getline(cin, newPassword);
//                    firstDoseIt->password = newPassword;
//                }
//                else if (choice == 3) {
//                    char newGender;
//                    cout << "Please enter gender" << endl;
//                    cin >> newGender;
//                    cin.ignore();
//                    if (newGender != 'F' && newGender != 'f' && newGender != 'M' && newGender != 'm') {
//                        cout << "Please enter valid character" << endl;
//                        return;
//                    }
//                    else {
//                        firstDoseIt->gender = newGender;
//                    }
//
//                }
//                else if (choice == 4) {
//                    int newAge;
//                    cout << "Please enter updated age" << endl;
//                    cin >> newAge;
//                    cin.ignore();
//                    firstDoseIt->age = newAge;
//                }
//                else if (choice == 5) {
//                    string newGovernorate;
//                    cout << "please enter updated governorate" << endl;
//                    getline(cin, newGovernorate);
//                    firstDoseIt->governorate = newGovernorate;
//                }
//                else if (choice == 6) {
//                    char choiceForVaccine;
//                    cout << "did you recieve the second dose?" << endl;
//                    cin >> choiceForVaccine;
//                    cin.ignore();
//                    if (choiceForVaccine == 'Y' || choiceForVaccine == 'y') {
//                        User userToBeTransferred(firstDoseIt->name, firstDoseIt->national_id, firstDoseIt->password, firstDoseIt->gender, firstDoseIt->age, firstDoseIt->governorate, firstDoseIt->vaccinated, firstDoseIt->received_both_doses);
//                        firstDose.erase(firstDose.begin() + counterForFirstDose);
//                        secondDose.push_back(userToBeTransferred);
//                    }
//                    else {
//                        return;
//                    }
//                }
//                else {
//                    cout << "Invalid Choice" << endl;
//                }
//                cout << "Do you want to edit another info?" << endl;
//                cin >> ChoiceForEditingAgain;
//            } while (ChoiceForEditingAgain == 'Y' || ChoiceForEditingAgain == 'y');
//            break;
//
//        }
//        else {
//            counterForFirstDose++;
//        }
//    }
//    for (secondDoseIt = secondDose.begin();secondDoseIt < secondDose.end();secondDoseIt++) {
//        if (nationalId == secondDoseIt->get_national_id()) {
//            int choice;
//            char choiceForEditing;
//            do
//            {
//                cout << "Please enter 1 for name, 2 for password, 3 for gender, 4 for age, 5 for governorate" << endl;
//                cin >> choice;
//                cin.ignore();
//                if (choice == 1) {
//                    string newName;
//                    cout << "Please enter new Name" << endl;
//                    getline(cin, newName);
//                    secondDoseIt->name = newName;
//                }
//                else if (choice == 2) {
//                    string newPassword;
//                    cout << "Please enter new password" << endl;
//                    getline(cin, newPassword);
//                    secondDoseIt->password = newPassword;
//                }
//                else if (choice == 3) {
//                    char newGender;
//                    cout << "Please enter Gender" << endl;
//                    cin >> newGender;
//                    cin.ignore();
//                    if (newGender != 'F' && newGender != 'f' && newGender != 'M' && newGender != 'm') {
//                        cout << "Please enter valid character" << endl;
//                        return;
//                    }
//                    else {
//                        secondDoseIt->gender = newGender;
//                    }
//                }
//                else if (choice == 4) {
//                    int newAge;
//                    cout << "Please enter updated Age" << endl;
//                    cin >> newAge;
//                    cin.ignore();
//                    secondDoseIt->age = newAge;
//                }
//                else if (choice == 5) {
//                    string newGovernorate;
//                    cout << "Please enter updated governorate" << endl;
//                    getline(cin, newGovernorate);
//                    secondDoseIt->governorate = newGovernorate;
//                }
//                else {
//                    cout << "Invalid Choice" << endl;
//                }
//
//                cout << "Do you want to edit another Info?" << endl;
//                cin >> choiceForEditing;
//
//            } while (choiceForEditing == 'Y' || choiceForEditing == 'y');
//        }
//        else {
//            counterForSecondDose++;
//        }
//    }*/
//    while (!waitingList.empty()) {
//        string newName, newPassword, newGovernorate;
//        char newGender;
//        int newAge;
//        if (waitingList.front().get_national_id() != nationalId) {
//            User temporaryUser(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age, waitingList.front().governorate, waitingList.front().vaccinated, waitingList.front().received_both_doses);
//            temp.push(temporaryUser);
//            waitingList.pop();
//        }
//        else {
//            char choiceForLoop;
//            int choice;
//            do {
//                cout << "Please enter 1 for name, 2 for password, 3 for gender, 4 for age, 5 for governorate or 6 to edit vaccination information" << endl;
//                cin >> choice;
//                cin.ignore();
//                if (choice == 1) {
//                    cout << "Please enter name" << endl;
//                    getline(cin, newName);
//                    waitingList.front().name = newName;
//                }
//                else if (choice == 2) {
//                    cout << "Please enter password" << endl;
//                    getline(cin, newPassword);
//                    waitingList.front().password = newPassword;
//                }
//                else if (choice == 3) {
//                    cout << "Please enter gender" << endl;
//                    cin >> newGender;
//                    cin.ignore();
//                    if (newGender != 'F' && newGender != 'f' && newGender != 'M' && newGender != 'm') {
//                        cout << "Please enter valid character" << endl;
//                        return;
//                    }
//                    else {
//                        waitingList.front().gender = newGender;
//                    }
//                }
//                else if (choice == 4) {
//                    cout << "Please enter age" << endl;
//                    cin >> newAge;
//                    cin.ignore();
//                    waitingList.front().age = newAge;
//                }
//                else if (choice == 5) {
//                    cout << "Please enter governorate" << endl;
//                    getline(cin, newGovernorate);
//                    waitingList.front().governorate = newGovernorate;
//                }
//                else if (choice == 6) {
//                    cout << "Did you get vaccinated?" << endl;
//                    char choiceForVaccination;
//                    cin >> choiceForVaccination;
//                    cin.ignore();
//                    if (choiceForVaccination == 'Y' || choiceForVaccination == 'y') {
//                        waitingList.front().vaccinated = true;
//                        cout << "Did you recieve 1 dose or 2 doses?" << endl;
//                        int choiceForNoOfDoses;
//                        cin >> choiceForNoOfDoses;
//                        cin.ignore();
//                        if (choiceForNoOfDoses == 1) {
//                            waitingList.front().received_both_doses = false;
//                            User userToBeTransferred(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age, waitingList.front().governorate, waitingList.front().vaccinated, waitingList.front().received_both_doses);
//                            waitingList.pop();
//                            firstDose.push_back(userToBeTransferred);
//                        }
//                        else if (choiceForNoOfDoses == 2) {
//                            waitingList.front().received_both_doses = true;
//                            User userToBeTransferred2(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age, waitingList.front().governorate, waitingList.front().vaccinated, waitingList.front().received_both_doses);
//                            waitingList.pop();
//                            secondDose.push_back(userToBeTransferred2);
//                        }
//                        else {
//                            cout << "Invalid choice" << endl;
//                        }
//                    }
//                    else if (choiceForVaccination == 'N' || choiceForVaccination == 'n') {
//                        break;
//                    }
//                    else {
//                        cout << "Please enter valid choice" << endl;
//                    }
//                }
//                else {
//                    cout << "Wrong choice" << endl;
//                }
//                cout << "Do you want to edit another thing" << endl;
//                cin >> choiceForLoop;
//                cin.ignore();
//            } while (choiceForLoop == 'Y' || choiceForLoop == 'y');
//            break;
//            while (!temp.empty()) {
//                User temp1(temp.front().name, temp.front().national_id, temp.front().password, temp.front().gender, temp.front().age, temp.front().governorate, temp.front().vaccinated, temp.front().received_both_doses);
//                waitingList.push(temp1);
//                temp.pop();
//            }
//        }
//    }
//
//
//}
//void User::deleteUser(vector<User>& firstDose, vector<User>& secondDose, queue<User> &waitingList, string nationalId, map<string, User>& user_map) {
//    char choice;
//    int counterForFirstDose = 0, counterForSecondDose = 0;
//    User temporaryUser;
//    queue<User> temp;
// 
//    cout << "Do you want to delete your record" << endl;
//    cin >> choice;
//    cin.ignore();
//    
//    
//
//    if (choice == 'y' || choice == 'Y') {
//        for (int i = 0; i < firstDose.size();i++) {
//            if (firstDose[i].get_national_id() == nationalId) {
//                firstDose.erase(firstDose.begin() + i);
//                user_map.erase(nationalId);
//                break;
//            }
//        }
//
//        for (int i = 0; i < secondDose.size();i++) {
//            if (secondDose[i].get_national_id() == nationalId) {
//                secondDose.erase(secondDose.begin() + i);
//                user_map.erase(nationalId);
//                break;
//            }
//        }
//            while (!waitingList.empty()) {
//                if (waitingList.front().national_id != nationalId) {
//                    User tempUser(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age, waitingList.front().governorate, waitingList.front().vaccinated, waitingList.front().received_both_doses);
//                    temp.push(tempUser);
//                    waitingList.pop();
//                }
//                else {
//                    waitingList.pop();
//                }
//                while (!temp.empty()) {
//                    User tempUser1(temp.front().name, temp.front().national_id, temp.front().password, temp.front().gender, temp.front().age, temp.front().governorate, temp.front().vaccinated, temp.front().received_both_doses);
//                    waitingList.push(tempUser1);
//                    temp.pop();
//                }
//            }
//            user_map.erase(nationalId);
//
//        
//      
//    }
//    else if (choice == 'n' || choice == 'N') {
//        cout << "Okay" << endl;
//    }
//    else {
//        cout << "Invalid Choice" << endl;
//    }
//}

User::~User() {
   
}

