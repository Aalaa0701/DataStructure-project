#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class User
{
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
    // Setters
    void set_vaccinated(bool vaccinated);
    void set_received_both_doses(bool received_both_doses);
    //Functions

    //Edit user data
    void EditUserData(int firstIndex, int secondIndex, int whichData, vector<User>& firstDose, vector<User>& secondDose, queue<User> waitingList, string password);
    void deleteUser(int firstIndex, int secondIndex, int whichData, vector<User>& firstDose, vector<User>& secondDose, queue<User> waitingList, string password);

};

