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
// Function to check if a national ID is already in use
bool is_national_id_used(string national_id) {
    return (user_map.find(national_id) != user_map.end());
}


// Function to add a new user record
void add_user() {
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
        user_map[national_id] = user; // add user to the map
        return;
    }
    if (vaccinated && received_both_doses) {
        User user(name, national_id, password, gender, age, governorate, vaccinated, received_both_doses);
        secondDose.push_back(user); // add user to the two-dose vector
        cout << "User added to the two-dose list.\n";
        user_map[national_id] = user; // add user to the map
        return;
    }
    if (!vaccinated) {
        User user(name, national_id, password, gender, age, governorate, vaccinated, received_both_doses);
        waiting_list.push(user); // add user to waiting list
        cout << "User added to waiting list.\n";
        user_map[national_id] = user; // add user to the map
        return;
    }
}