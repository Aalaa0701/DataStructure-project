#include "user.h"


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
void User::EditUserData(int firstIndex, int secondIndex, int whichData, vector<User>& firstDose, vector<User>& secondDose, queue<User> waitingList, string password) {
    if (whichData == 0) {
        int choice;
       /* cout << "1 "+ firstDose[index].age << endl;
        cout << "2 "+ firstDose[index].governorate << endl;
        cout << "3 "+ firstDose[index].password << endl;*/
        cout << "Please enter 1 for name, 2 for password, 3 for gender, 4 for age, 5 for governorate or 6 to edit vaccination information" << endl;
        cin >> choice;
        if (choice == 1) {
            string newName;
            getline(cin, newName);
            firstDose[firstIndex].name = newName;
        }
        else if (choice == 2) {
            string newPassword;
            getline(cin,newPassword);
            firstDose[firstIndex].password = newPassword;
        }
        else if (choice == 3) {
            char newGender;
            cin >> newGender;
            firstDose[firstIndex].gender = newGender;
        }
        else if (choice == 4) {
            int newAge;
            cin >> newAge;
            firstDose[firstIndex].age = newAge;
        }
        else if (choice == 5) {
            string newGovernorate;
            getline(cin, newGovernorate);
            firstDose[firstIndex].governorate = newGovernorate;
        }
        else if (choice == 6) {
            char choiceForVaccine;
            cout << "did you recieve the second dose?" << endl;
            cin >> choiceForVaccine;
            if (choiceForVaccine == 'Y' || choiceForVaccine == 'y') {
                User userToBeTransferred(firstDose[firstIndex].name, firstDose[firstIndex].national_id, firstDose[firstIndex].password, firstDose[firstIndex].gender, firstDose[firstIndex].age, firstDose[firstIndex].governorate, firstDose[firstIndex].vaccinated, firstDose[firstIndex].received_both_doses);
                firstDose.erase(firstDose.begin() + firstIndex);
                secondDose.push_back(userToBeTransferred);
            }
            else {
                return;
            }
        }
        else {
            cout << "Invalid Choice" << endl;
        }

    }
    else if (whichData == 1) {
        int choice;
       /* cout << "1 " + secondDose[index].age << endl;
        cout << "2 " + secondDose[index].governorate << endl;
        cout << "3 " + secondDose[index].password << endl;*/
        cout << "Please enter 1 for name, 2 for password, 3 for gender, 4 for age, 5 for governorate" << endl;
        cin >> choice;
        if (choice == 1) {
            string newName;
            getline(cin,newName);
            secondDose[secondIndex].name = newName;
        }
        else if (choice == 2) {
            string newPassword;
            getline(cin,newPassword);
            secondDose[secondIndex].password = newPassword;
        }
        else if (choice == 3) {
            char newGender;
            cin >> newGender;
            if (newGender != 'F' && newGender != 'f' && newGender != 'M' && newGender != 'm') {
                cout << "Please enter valid character" << endl;
            }
            else {
                secondDose[secondIndex].gender = newGender;
            }
        }
        else if (choice == 4) {
            int newAge;
            cin >> newAge;
            secondDose[secondIndex].age = newAge;
        }
        else if (choice == 5) {
            string newGovernorate;
            getline(cin, newGovernorate);
            secondDose[secondIndex].governorate = newGovernorate;
        }
        else {
            cout << "Invalid Choice" << endl;
        }
    }
    else if (whichData == 2) {
        int choice;
        char choiceForLoop;
        queue<User>temp;
        while (!waitingList.empty()) {
            if (waitingList.front().password != password) {
                User temporaryUser(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age, waitingList.front().governorate, waitingList.front().vaccinated, waitingList.front().received_both_doses);
                temp.push(temporaryUser);
                waitingList.pop();
            }
            else {
                do {
                    cout << "Please enter 1 for name, 2 for password, 3 for gender, 4 for age, 5 for governorate or 6 to edit vaccination information" << endl;
                    cin >> choice;
                    if (choice == 1) {
                        cout << "Please enter name" << endl;
                        string newName;
                        getline(cin, newName);
                        waitingList.front().name = newName;
                    }
                    else if (choice == 2) {
                        cout << "Please enter password" << endl;
                        string newPassword;
                        getline(cin, newPassword);
                        waitingList.front().password = newPassword;
                    }
                    else if (choice == 3) {
                        cout << "Please enter gender" << endl;
                        char newGender;
                        cin >> newGender;
                        waitingList.front().gender = newGender;
                    }
                    else if (choice == 4) {
                        cout << "Please enter age" << endl;
                        int newAge;
                        cin >> newAge;
                        waitingList.front().age = newAge;
                    }
                    else if (choice == 5) {
                        cout << "Please enter governorate" << endl;
                        string newGovernorate;
                        getline(cin, newGovernorate);
                        waitingList.front().governorate = newGovernorate;
                    }
                    else if (choice == 6) {
                        cout << "Did you get vaccinated?" << endl;
                        char choiceForVaccination;
                        cin >> choiceForVaccination;
                        if (choiceForVaccination == 'Y' || choiceForVaccination == 'y') {
                            waitingList.front().vaccinated = true;
                            cout << "Did you recieve 1 dose or 2 doses?" << endl;
                            int choiceForNoOfDoses;
                            cin >> choiceForNoOfDoses;
                            if (choiceForNoOfDoses == 1) {
                                waitingList.front().received_both_doses = false;
                                User userToBeTransferred(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age, waitingList.front().governorate, waitingList.front().vaccinated, waitingList.front().received_both_doses);
                                waitingList.pop();
                                firstDose.push_back(userToBeTransferred);
                            }
                            else if (choiceForNoOfDoses == 2) {
                                waitingList.front().received_both_doses = true;
                                User userToBeTransferred2(waitingList.front().name, waitingList.front().national_id, waitingList.front().password, waitingList.front().gender, waitingList.front().age, waitingList.front().governorate, waitingList.front().vaccinated, waitingList.front().received_both_doses);
                                waitingList.pop();
                                secondDose.push_back(userToBeTransferred2);
                            }
                            else {
                                cout << "Invalid choice" << endl;
                            }
                        }
                        else if (choiceForVaccination == 'N' || choiceForVaccination == 'n') {
                            return;
                        }
                        else {
                            cout << "Please enter valid choice" << endl;
                        }
                    }
                    else {
                        cout << "Wrong choice" << endl;
                    }
                    cout << "Do you want to edit another thing" << endl;
                    cin >> choiceForLoop;
                } while (choiceForLoop == 'Y' || choiceForLoop == 'y');
                while (!temp.empty()) {
                    User temp1(temp.front().name, temp.front().national_id, temp.front().password, temp.front().gender, temp.front().age, temp.front().governorate, temp.front().vaccinated, temp.front().received_both_doses);
                    waitingList.push(temp1);
                    temp.pop();
                }
            }
        }
       
    }
    else {
        cout << "Wrong whichData index" << endl;
    }

}
void User::deleteUser(int firstIndex, int secondIndex, int whichData, vector<User>& firstDose, vector<User>& secondDose, queue<User> waitingList, string password) {
    char choice;
    cout << "Do you want to delete your record" << endl;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        if (whichData == 0) {
            firstDose.erase(firstDose.begin() + firstIndex);
        }
        else if (whichData == 1) {
            secondDose.erase(secondDose.begin() + secondIndex);
        }
        else if (whichData == 1) {
            queue<User> temp;
            while (!waitingList.empty()) {
                if (waitingList.front().password != password) {
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
        }
        else {
            cout << "wrong whichIndex" << endl;
        }
    }
    else if (choice == 'n' || choice == 'N') {
        cout << "Okay" << endl;
    }
    else {
        cout << "Invalid Choice" << endl;
    }
}