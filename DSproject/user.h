#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include<map>
using namespace std;

class User
{
public:
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
    // Setters

};
class Admin 
    {
    public:
        string userName;
        string password;
    void set_vaccinated(bool vaccinated);
    void set_received_both_doses(bool received_both_doses);

    //Functions
   // bool is_national_id_used(string national_id, map<string, User> user_map);
    void add_user(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waiting_list, map<string, User>& user_map);
    void display_user_data(vector<User> firstDose, vector<User> secondDose, queue<User> waiting_list, map<string, User> user_map, string& nationalId);
    void ViewRecord(map<string, User> user_map);
    //Edit user data
    /*void EditUserData(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList, string nationalId);
    void deleteUser(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList, string nationalId, map<string, User>& user_map);*/

    public:
        Admin();
        //~Admin();
        void Statistics(vector<User>, vector<User>, queue<User>);
    };

