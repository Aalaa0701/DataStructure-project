#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

// a class for user's personal information
class User {

    string name;
    string national_id;
    string password;
    char gender;
    int age;
    string governorate;
    bool vaccinated;
    bool received_both_doses;

public:
    // Default constructor
    User() : name(""), national_id(""), password(""),
        gender(' '), age(0), governorate(""), vaccinated(false), received_both_doses(false) {}
    // Constructor
    User(string name, string national_id, string password, char gender, int age,
        string governorate, bool vaccinated = false, bool received_both_doses = false) :
        name(name), national_id(national_id), password(password), gender(gender), age(age),
        governorate(governorate), vaccinated(vaccinated), received_both_doses(received_both_doses) {}

    // Getters
    string get_name() const {
        return name;
    }
    string get_national_id() const {
        return national_id;
    }
    string get_password() const {
        return password;
    }
    char get_gender() const {
        return gender;
    }
    int get_age() const {
        return age;
    }
    string get_governorate() const {
        return governorate;
    }
    bool is_vaccinated() const {
        return vaccinated;
    }
    bool has_received_both_doses() const {
        return received_both_doses;
    }

    // Setters
    void set_vaccinated(bool vaccinated) {
        this->vaccinated = vaccinated;
    }
    void set_received_both_doses(bool received_both_doses) {
        this->received_both_doses = received_both_doses;
    }


};


vector<User>users;
vector<User> firstDose;;
vector<User> secondDose;
queue<User> waiting_list;
map<string, User> user_map;

//function to view user record(s) (Admin)
void ViewRecord() {
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
void DeleteRecord() {
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