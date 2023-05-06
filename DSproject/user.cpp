#include <iostream>
#include "user.h"
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include<map>
using namespace std;
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
        user_map.insert({ national_id,user });
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
                if_exist = false;
            }
            else
            {
                cout << "Please try again , Your password is not true." << endl;
            }

        }
        else
        {
            cout << " Please try again ,  Your national ID is not exist." << endl;
            cout << "Choice one of three options :" << endl;
            cout << "1-Option one :Try again." << endl;
            cout << "2-Option one :Add user." << endl;
            cout << "3-Option one :Exit." << endl;
            cout << "Enter number of option that you want:" << endl;
            int num_of_option;
            cin >> num_of_option;
            cin.ignore();
            if (num_of_option == 2) {
                add_user(firstDose, secondDose, waiting_list, user_map);
            }
            else if (num_of_option == 3) {
                if_exist = false;
            }


        }

    }
}


void User::EditUserData(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList, map<string, User>& user_map, string nationalId) {
   
    queue<User>temp;
    char choiceForVaccineFirstDose, choiceForVaccineWaitingList, ChoiceForEditingFirstDose, choiceForEditingSecondDose, choiceorEditingWaitingList;
    int choiceForFirstDose, choiceForSecondDose, choiceForWaitingList;

    for (int i = 0; i < secondDose.size();i++) {
        if (secondDose[i].get_national_id() == nationalId) {
            do
            {
                cout << "Please enter 1 for name, 2 for password, 3 for gender, 4 for age, 5 for governorate" << endl;
                cin >> choiceForSecondDose;
                cin.ignore();
                if (choiceForSecondDose == 1) {
                    string newName;
                    cout << "Please enter new Name" << endl;
                    getline(cin, newName);
                    secondDose[i].name = newName;
                    user_map[nationalId] = secondDose[i];
                }
                else if (choiceForSecondDose == 2) {
                    string newPassword;
                    cout << "Please enter new password" << endl;
                    getline(cin, newPassword);
                    secondDose[i].password = newPassword;
                    user_map[nationalId] = secondDose[i];

                }
                else if (choiceForSecondDose == 3) {
                    char newGender;
                    cout << "Please enter Gender" << endl;
                    cin >> newGender;
                    cin.ignore();
                    if (newGender != 'F' && newGender != 'f' && newGender != 'M' && newGender != 'm') {
                        cout << "Please enter valid character" << endl;
                        return;
                    }
                    else {
                        secondDose[i].gender = newGender;
                        user_map[nationalId] = secondDose[i];

                    }
                }
                else if (choiceForSecondDose == 4) {
                    int newAge;
                    cout << "Please enter updated Age" << endl;
                    cin >> newAge;
                    cin.ignore();
                    secondDose[i].age = newAge;
                    user_map[nationalId] = secondDose[i];

                }
                else if (choiceForSecondDose == 5) {
                    string newGovernorate;
                    cout << "Please enter updated governorate" << endl;
                    getline(cin, newGovernorate);
                    secondDose[i].governorate = newGovernorate;
                    user_map[nationalId] = secondDose[i];

                }
                else {
                    cout << "Invalid Choice" << endl;
                }

                cout << "Do you want to edit another Info?" << endl;
                cin >> choiceForEditingSecondDose;

            } while (choiceForEditingSecondDose == 'Y' || choiceForEditingSecondDose == 'y');
            break;
        }

    }
    

    for (int i = 0;i < firstDose.size();i++) {
        if (firstDose[i].national_id == nationalId) {
            do
            {
                cout << "Please enter 1 for name, 2 for password, 3 for gender, 4 for age, 5 for governorate or 6 to edit vaccination information" << endl;
                cin >> choiceForFirstDose;
                cin.ignore();
                if (choiceForFirstDose == 1) {
                    string newName;
                    cout << "PLease enter new Name" << endl;
                    getline(cin, newName);
                    firstDose[i].name = newName;  
                    user_map[nationalId] = firstDose[i];
                }
                else if (choiceForFirstDose == 2) {
                    string newPassword;
                    cout << "Please enter new password" << endl;
                    getline(cin, newPassword);
                    firstDose[i].password = newPassword;
                    user_map[nationalId] = firstDose[i];
                }
                else if (choiceForFirstDose == 3) {
                    char newGender;
                    cout << "Please enter gender" << endl;
                    cin >> newGender;
                    cin.ignore();
                    if (newGender != 'F' && newGender != 'f' && newGender != 'M' && newGender != 'm') {
                        cout << "Please enter valid character" << endl;
                        return;
                    }
                    else {
                        firstDose[i].gender = newGender;
                        user_map[nationalId] = firstDose[i];
                    }

                }
                else if (choiceForFirstDose == 4) {
                    int newAge;
                    cout << "Please enter updated age" << endl;
                    cin >> newAge;
                    cin.ignore();
                    firstDose[i].age = newAge;
                    user_map[nationalId] = firstDose[i];
                }
                else if (choiceForFirstDose == 5) {
                    string newGovernorate;
                    cout << "please enter updated governorate" << endl;
                    getline(cin, newGovernorate);
                    firstDose[i].governorate = newGovernorate;
                    user_map[nationalId] = firstDose[i];
                }
                else if (choiceForFirstDose == 6) {
                    cout << "did you recieve the second dose?" << endl;
                    cin >> choiceForVaccineFirstDose;
                    cin.ignore();
                    if (choiceForVaccineFirstDose == 'Y' || choiceForVaccineFirstDose == 'y') {
                        firstDose[i].received_both_doses = true;
                        user_map[nationalId] = firstDose[i];
                        User userToBeTransferred(firstDose[i].name, firstDose[i].national_id, firstDose[i].password, firstDose[i].gender, firstDose[i].age, firstDose[i].governorate, firstDose[i].vaccinated, firstDose[i].received_both_doses);
                        secondDose.push_back(userToBeTransferred);
                        firstDose.erase(firstDose.begin() + i);
                    }
                    else {
                        return;
                    }
                }
                else {
                    cout << "Invalid Choice" << endl;
                }
                cout << "Do you want to edit another info?" << endl;
                cin >> ChoiceForEditingFirstDose;
            } while (ChoiceForEditingFirstDose == 'Y' || ChoiceForEditingFirstDose == 'y');
            break;
           /* if (ChoiceForEditingFirstDose != 'Y' && ChoiceForEditingFirstDose != 'y') {
                if (choiceForVaccineFirstDose == 'Y' || choiceForVaccineFirstDose == 'y') {
                    
                }
            }*/

        }

    }
    

   
    while (!waitingList.empty()) {
        string newName, newPassword, newGovernorate;
        char newGender;
        int newAge;
        if (waitingList.front().get_national_id() != nationalId) {
            User temporaryUser(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age, waitingList.front().governorate, waitingList.front().vaccinated, waitingList.front().received_both_doses);
            temp.push(temporaryUser);
            waitingList.pop();
        }
        else {
           
            do {
                cout << "Please enter 1 for name, 2 for password, 3 for gender, 4 for age, 5 for governorate or 6 to edit vaccination information" << endl;
                cin >> choiceForWaitingList;
                cin.ignore();
                if (choiceForWaitingList == 1) {
                    cout << "Please enter name" << endl;
                    getline(cin, newName);
                    waitingList.front().name = newName;
                    user_map[nationalId] = waitingList.front();
                }
                else if (choiceForWaitingList == 2) {
                    cout << "Please enter password" << endl;
                    getline(cin, newPassword);
                    waitingList.front().password = newPassword;
                    user_map[nationalId] = waitingList.front();

                }
                else if (choiceForWaitingList == 3) {
                    cout << "Please enter gender" << endl;
                    cin >> newGender;
                    cin.ignore();
                    if (newGender != 'F' && newGender != 'f' && newGender != 'M' && newGender != 'm') {
                        cout << "Please enter valid character" << endl;
                        return;
                    }
                    else {
                        waitingList.front().gender = newGender;
                        user_map[nationalId] = waitingList.front();

                    }
                }
                else if (choiceForWaitingList == 4) {
                    cout << "Please enter age" << endl;
                    cin >> newAge;
                    cin.ignore();
                    waitingList.front().age = newAge;
                    user_map[nationalId] = waitingList.front();

                }
                else if (choiceForWaitingList == 5) {
                    cout << "Please enter governorate" << endl;
                    getline(cin, newGovernorate);
                    waitingList.front().governorate = newGovernorate;
                    user_map[nationalId] = waitingList.front();

                }
                else if (choiceForWaitingList == 6) {
                    cout << "Did you get vaccinated?" << endl;
                    cin >> choiceForVaccineWaitingList;
                    cin.ignore();
                    if (choiceForVaccineWaitingList == 'Y' || choiceForVaccineWaitingList == 'y') {
                        waitingList.front().vaccinated = true;
                        cout << "Did you recieve 1 dose or 2 doses?" << endl;
                        int choiceForNoOfDoses;
                        cin >> choiceForNoOfDoses;
                        cin.ignore();
                        if (choiceForNoOfDoses == 1) {
                            waitingList.front().received_both_doses = false;
                            User userToBeTransferred(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age, waitingList.front().governorate, waitingList.front().vaccinated, waitingList.front().received_both_doses);
                            firstDose.push_back(userToBeTransferred);
                        }
                        else if (choiceForNoOfDoses == 2) {
                            waitingList.front().received_both_doses = true;
                            User userToBeTransferred2(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age, waitingList.front().governorate, waitingList.front().vaccinated, waitingList.front().received_both_doses);
                            secondDose.push_back(userToBeTransferred2);
                        }
                        else {
                            cout << "Invalid choice" << endl;
                        }
                    }
                    else if (choiceForVaccineWaitingList == 'N' || choiceForVaccineWaitingList == 'n') {
                        break;
                    }
                    else {
                        cout << "Please enter valid choice" << endl;
                    }
                }
                else {
                    cout << "Wrong choice" << endl;
                }
                cout << "Do you want to edit another thing" << endl;
                cin >> choiceorEditingWaitingList;
                cin.ignore();
            } while (choiceorEditingWaitingList == 'Y' || choiceorEditingWaitingList == 'y');
            break;
            if (choiceorEditingWaitingList != 'Y' && choiceorEditingWaitingList != 'y') {
                if (choiceForVaccineWaitingList == 'Y' || choiceForVaccineWaitingList == 'y') {
                    waitingList.pop();
                }
            }
            while (!temp.empty()) {
                User temp1(temp.front().name, temp.front().national_id, temp.front().password, temp.front().gender, temp.front().age, temp.front().governorate, temp.front().vaccinated, temp.front().received_both_doses);
                waitingList.push(temp1);
                temp.pop();
            }
        }
    }


}
void User::deleteUser(vector<User>& firstDose, vector<User>& secondDose, queue<User> &waitingList, string nationalId, map<string, User>& user_map) {
    char choice;
    int counterForFirstDose = 0, counterForSecondDose = 0;
    User temporaryUser;
    queue<User> temp;
 
    cout << "Do you want to delete your record" << endl;
    cin >> choice;
    cin.ignore();
    
    

    if (choice == 'y' || choice == 'Y') {
        for (int i = 0; i < firstDose.size();i++) {
            if (firstDose[i].get_national_id() == nationalId) {
                firstDose.erase(firstDose.begin() + i);
                user_map.erase(nationalId);
                break;
            }
        }

        for (int i = 0; i < secondDose.size();i++) {
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
    else if (choice == 'n' || choice == 'N') {
        cout << "Okay" << endl;
    }
    else {
        cout << "Invalid Choice" << endl;
    }
}


User::~User() {

}

//constructor
Admin::Admin() {
	password = "";
	userName = "";

}
//to calculate some statistics 
void Admin::Statistics(vector<User>firstDose,vector<User>secondDose,queue<User>waitingList, map<string, User> user_map) {
	double firstDosePct, secondDosePct, femalePct, malePct;
	double firstRangePct=0.0, secondRangePct=0, thirdRangePct=0, fourthRangePct=0, fifthRangePct=0;
    double allUsers = user_map.size();
	int fCount = 0, mCount = 0;
	int firstRange1 = 0, secondRange1 = 0, thirdRange1 = 0, fourthRange1 = 0, fifthRange1 = 0;
	int firstRange2 = 0, secondRange2 = 0, thirdRange2 = 0, fourthRange2 = 0,  fifthRange2 = 0;
	int firstRange = 0, secondRange = 0, thirdRange = 0, fourthRange = 0, fifthRange = 0;
	


	//calculate the pct of first and second dose
	firstDosePct = ((double)firstDose.size() / allUsers)*100.0;
	secondDosePct = ((double)secondDose.size()/ allUsers)*100.00;

	//filter males and females from first dose vector
	
	for (int i= 0; i < firstDose.size(); i++) {
		if (firstDose[i].get_gender() == 'M'|| firstDose[i].get_gender() == 'm') {
			mCount++;
		}
        else if (firstDose[i].get_gender() == 'F' || firstDose[i].get_gender() == 'f') {
            fCount++;
        }
    }
    //filter males and females from second dose vector
    for (int i = 0; i < secondDose.size(); i++) {
        if (secondDose[i].get_gender() == 'M' || secondDose[i].get_gender() == 'm') {
            mCount++;
        }
        else if (secondDose[i].get_gender() == 'F' || secondDose[i].get_gender() == 'f') {
            fCount++;
        }
    }
    // filter males and females from waiting list
    queue<User> copy = waitingList;
    while (!copy.empty())
    {
        if (copy.front().get_gender() == 'M' || copy.front().get_gender() == 'm') {
            mCount++;
            copy.pop();
        }
        else if (copy.front().get_gender() == 'F' || copy.front().get_gender() == 'f') {
            fCount++;
            copy.pop();
        }
    }
    //calculate the pct of males and females
    malePct = ((double)mCount / allUsers) * 100.00;
    femalePct = ((double)fCount / allUsers) * 100.00;


    //filter each age group from second dose vector
    for (int i = 0; i < secondDose.size(); i++) {
        if (secondDose[i].get_age() >= 75) {
            firstRange++;
        }
        else if (secondDose[i].get_age() >= 65 && secondDose[i].get_age() <= 74) {
            secondRange++;
        }
        else if (secondDose[i].get_age() >= 50 && secondDose[i].get_age() <= 64) {
            thirdRange++;
        }
        else if (secondDose[i].get_age() >= 40 && secondDose[i].get_age() <= 49) {
            fourthRange++;
        }
        else if (secondDose[i].get_age() >= 18 && secondDose[i].get_age() <= 39) {
            fifthRange++;
        }
    }
    //filter each age group from first dose vector
    for (int i = 0; i < firstDose.size(); i++) {
        if (firstDose[i].get_age() >= 75) {
            firstRange1++;
        }
        else if (firstDose[i].get_age() >= 65 && firstDose[i].get_age() <= 74) {
            secondRange1++;
        }
        else if (firstDose[i].get_age() >= 50 && firstDose[i].get_age() <= 64) {
            thirdRange1++;
        }
        else if (firstDose[i].get_age() >= 40 && firstDose[i].get_age() <= 49) {
            fourthRange1++;
        }
        else if (firstDose[i].get_age() >= 18 && firstDose[i].get_age() <= 39) {
            fifthRange1++;
        }
    }
    //filter each age group from waiting list
    queue<User> copy_1 = waitingList;
    while (!copy_1.empty()) {
        if (copy_1.front().get_age() >= 75) {
            firstRange2++;
            copy_1.pop();
        }
        else if (copy_1.front().get_age() >= 65 && copy_1.front().get_age() <= 74) {
            secondRange2++;
            copy_1.pop();
        }
        else if (copy_1.front().get_age() >= 50 && copy_1.front().get_age() <= 64) {
            thirdRange2++;
            copy_1.pop();
        }
        else if (copy_1.front().get_age() >=40 && copy_1.front().get_age() <= 49) {
            fourthRange2++;
            copy_1.pop();
        }
        else if (copy_1.front().get_age() >= 18 && copy_1.front().get_age() <= 39) {
            fifthRange2++;
            copy_1.pop();
        }
    }
    //calculate the pct of each age group
    if ((firstRange + firstRange1 + firstRange2) != 0) {
        firstRangePct = ((double)firstRange / ((double)(firstRange + firstRange1 + firstRange2))) * 100.00;

    }
    if ((secondRange + secondRange1 + secondRange2) != 0){
        secondRangePct = ((double)secondRange / ((double)(secondRange + secondRange1 + secondRange2))) * 100.00;

    }
    if ((thirdRange + thirdRange1 + thirdRange2) != 0) {
        thirdRangePct = ((double)thirdRange / ((double)(thirdRange + thirdRange1 + thirdRange2))) * 100.00;

    }
    if ((fourthRange + fourthRange1 + fourthRange2) != 0) {
        fourthRangePct = ((double)fourthRange / ((double)(fourthRange + fourthRange1 + fourthRange2))) * 100.00;

    }
    if ((fifthRange + fifthRange1 + fifthRange2) != 0) {
        fifthRangePct = ((double)fifthRange / ((double)(fifthRange + fifthRange1 + fifthRange2))) * 100.00;

    }
	cout << "Percentage of people that have received the first dose : " << firstDosePct << "%" << endl;
	cout << "Percentage of people that have received the second dose : " << secondDosePct << "%" << endl;
	cout << "Percentage of females : " << femalePct << "%" << endl;
	cout << "Percentage of males : " << malePct << "%" << endl;
	cout << "Ages from 75 and over that have been fully vaccinated : " << firstRangePct << "%" << endl;
	cout << "Ages from 65 to 74 that have been fully vaccinated : " << secondRangePct << "%" << endl;
	cout << "Ages from 50 to 64 that have been fully vaccinated : " << thirdRangePct << "%" << endl;
	cout << "Ages from 40 to 49 that have been fully vaccinated : " << fourthRangePct << "%" << endl;
	cout << "Ages from 18 to 39 that have been fully vaccinated : " << fifthRangePct << "%" << endl;

}
// view records of users
void Admin::ViewRecord(map<string, User> user_map) {
    if (user_map.empty())
        cout << "there is no records to view.";

    else {
        cout << "if you want to view all records press 1 \n\t\t    one record press 2\nplease enter your choice: ";
        int typeofview;
        string NationalId;
        bool review = true;
        char choice;
        cin >> typeofview;
        switch (typeofview)
        {
        case 1:
            for (auto itr = user_map.begin();itr != user_map.end();++itr)
            {
                cout << "Name: " << itr->second.get_name() << endl;
                cout << "NationalID: " << itr->second.get_national_id() << endl;
                cout << "Password: " << itr->second.get_password() << endl;
                cout << "Governorate: " << itr->second.get_governorate() << endl;
                cout << "Gender: " << itr->second.get_gender() << endl;
                cout << "Age: " << itr->second.get_age() << endl;
                if (!itr->second.is_vaccinated())
                    cout << itr->second.get_name() << " hasn't recieved any dose of Vaccine." << endl;
                else {
                    if (!itr->second.has_received_both_doses())
                        cout << itr->second.get_name() << " has recieved one dose of Vaccine." << endl;
                    else
                        cout << itr->second.get_name() << " has recieved both doses of Vaccine." << endl;
                }
            }
            break;
        case 2:
            while (review) {
                cout << "please enter NationalID: ";
                cin >> NationalId;
                if (user_map.find(NationalId) != user_map.end()) {
                    cout << "Name: " << user_map[NationalId].get_name() << endl;
                    cout << "NationalID: " << user_map[NationalId].get_national_id() << endl;
                    cout << "Password: " << user_map[NationalId].get_password() << endl;
                    cout << "Governorate: " << user_map[NationalId].get_governorate() << endl;
                    cout << "Gender: " << user_map[NationalId].get_gender() << endl;
                    cout << "Age: " << user_map[NationalId].get_age() << endl;
                    if (!user_map[NationalId].is_vaccinated())
                        cout << user_map[NationalId].get_name() << " hasn't recieved any dose of Vaccine." << endl;
                    else {
                        if (!user_map[NationalId].has_received_both_doses())
                            cout << user_map[NationalId].get_name() << " has recieved one dose of Vaccine." << endl;
                        else
                            cout << user_map[NationalId].get_name() << " has recieved both doses of Vaccine." << endl;
                    }
                }
                else {
                    cout << "This NationalID is invalid. \n";
                }
                cout << "Do you want to view onther record? Y or N: ";
                cin >> choice;
                if (choice == 'Y' || choice == 'y')
                    review = true;
                else
                    review = false;
            }
            break;
        default:
            break;
        }
    }
}
//function to delete user record(s) (Admin)
void Admin::DeleteRecord(map<string, User>& user_map) {
    if (user_map.empty())
        cout << "there is no records to delete.";

    else {
        cout << "if you want to delete all records press 1 \n\t\t      one record press 2\nplease enter your choice: ";
        int typeofdeletion;
        string NationalId;
        bool redelete = true;
        char choice;
        cin >> typeofdeletion;
        switch (typeofdeletion)
        {
        case 1:
            user_map.clear();
            break;
        case 2:
            while (redelete) {
                cout << "please enter NationalID: ";
                cin >> NationalId;
                if (user_map.find(NationalId) != user_map.end()) {
                    user_map.erase(NationalId);
                    cout << "Record is deleted successfully.\n";
                }
                else {
                    cout << "This NationalID is invalid. \n";
                }
                cout << "Do you want to delete onther record? Y or N: ";
                cin >> choice;
                if (choice == 'Y' || choice == 'y')
                    redelete = true;
                else
                    redelete = false;
            }
            break;
        default:
            break;
        }
    }

}
// filterRecords by no. of doses or age
void Admin::FilteredRecords(vector<User>firstDose, vector<User>secondDose) {
    vector<User>::iterator it;
    int numOfDose;
    cout << "Enter the Number of Doses \n";
    cin >> numOfDose;
    if (numOfDose == 1) {

        it = firstDose.begin();
        while (it != firstDose.end())
        {
            cout << "National_id:" << "\t" << it->get_national_id() << "\t" << "Name:" << "\t" << it->get_name() << "\t" << "Gender:" << "\t" << it->get_gender() << "\t" << "Age:" << "\t" << it->get_age() << "\t" << "Governorate:" << "\t" << it->get_governorate() << endl;
            it++;
        }

    }
    else if (numOfDose == 2) {
        it = secondDose.begin();
        while (it != secondDose.end())
        {
            cout << "National_id:" << "\t" << it->get_national_id() << "\t" << "Name:" << "\t" << it->get_name() << "\t" << "Gender:" << "\t" << it->get_gender() << "\t" << "Age:" << "\t" << it->get_age() << "\t" << "Governorate:" << "\t" << it->get_governorate() << endl;
            it++;
        }
    }
    else
        cout << "Invalid Number";
}
void Admin::OrderedByAge(vector<User>firstDose, vector<User>secondDose) {
    cout << "Sorting Records\n";
    vector<User>both_users;
    both_users.insert(both_users.end(), firstDose.begin(), firstDose.end());
    both_users.insert(both_users.end(), secondDose.begin(), secondDose.end());
    sort(both_users.begin(), both_users.end(), [](const User& a, const User& b) { return a.get_age() < b.get_age(); });//Sorting the vector;
    for (auto i = both_users.begin(); i < both_users.end(); i++)
    {
        cout << "Age:" << i->get_age() << "\t" << "National_id:" << "\t" << i->get_national_id() << "\t" << "Name:" << "\t" << i->get_name() << "\t" << "Gender:" << "\t" << i->get_gender() << "\t" << "Governorate:" << "\t" << i->get_governorate() << endl;
    }
}
//view record in waiting list
void Admin::view_record(queue<User>waitingList)
{


    User user1 = waitingList.front();

    cout << user1.get_name() << endl;
    cout << user1.get_national_id() << endl;
    cout << user1.get_age() << endl;
    cout << user1.get_gender() << endl;
    cout << user1.get_governorate() << endl;


}
