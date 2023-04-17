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
void User::EditUserData(int index, int whichData, vector<User>& firstDose, vector<User>& secondDose) {
    int choice;
    if (whichData == 0) {
        cout << "1 "+ firstDose[index].age << endl;
        cout << "2 "+ firstDose[index].governorate << endl;
        cout << "3 "+ firstDose[index].password << endl;
        cout << "Enter 1 if you want to edit your age or 2 for governorate or 3 for password" << endl;
        if (choice == 1) {
            int age;
            cin >> age;
            firstDose[index].age = age;
        }
        else if (choice == 2) {
            string governorate;
            cin >> governorate;
            firstDose[index].governorate = governorate;
        }
        else if (choice == 3) {
            string password;
            cin >> password;
            firstDose[index].password = password;
        }
        else {
            cout << "Invalid Choice" << endl;
        }

    }
    else if (whichData == 1) {
        cout << "1 " + secondDose[index].age << endl;
        cout << "2 " + secondDose[index].governorate << endl;
        cout << "3 " + secondDose[index].password << endl;
        cout << "Enter 1 if you want to edit your age or 2 for governorate or 3 for password" << endl;
        if (choice == 1) {
            int age;
            cin >> age;
            secondDose[index].age = age;
        }
        else if (choice == 2) {
            string governorate;
            cin >> governorate;
            secondDose[index].governorate = governorate;
        }
        else if (choice == 3) {
            string password;
            cin >> password;
            secondDose[index].password = password;
        }
        else {
            cout << "Invalid Choice" << endl;
        }
    }
    else {
        cout << "Wrong whichData index" << endl;
    }

}
void User::deleteUser(int index, int whichData, vector<User>& firstDose, vector<User>& secondDose) {
    char choice;
    cout << "Do you want to delete your record" << endl;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        if (whichData == 0) {
            firstDose.erase(firstDose.begin() + index);
        }
        else if (whichData == 1) {
            secondDose.erase(secondDose.begin() + index);
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