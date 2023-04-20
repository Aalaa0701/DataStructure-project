#include <fstream>	
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;
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

vector<User> firstDose;;
vector<User> secondDose;
queue<User> waiting_list;
map<string, User> user_map;


// Function to add a new user record

void view_record()
{


    User user1 = waiting_list.front();

    cout << user1.get_name();
    cout << user1.get_national_id();
    cout << user1.get_age();
    cout << user1.get_gender();
    cout << user1.get_governorate();


}


void  read_file_waitinglist()
{
    queue<User> temp = waiting_list;
    User u = temp.front();
    ofstream myfile("waitinglist.txt");

    while (!temp.empty())
    {
        myfile << u.get_name() << endl;
        myfile << u.get_national_id() << endl;
        myfile << u.get_age() << endl;
        myfile << u.get_gender() << endl;
        myfile << u.get_governorate() << endl;
        myfile << u.is_vaccinated() << endl;
        myfile << u.has_received_both_doses() << endl;
        temp.pop();

    }

    ifstream infile("waitinglist.txt");
    string name = u.get_name();
    string national_id = u.get_national_id();
    char gender = u.get_gender();
    int age = u.get_age();
    string governorate = u.get_governorate();
    char vaccinated = u.is_vaccinated();
    char received_both_doses = u.has_received_both_doses();
    while (infile >> name >> national_id >> gender >> age >> governorate >> vaccinated >> received_both_doses)
    {
        cout << name << endl;
        cout << national_id << endl;
        cout << gender << endl;
        cout << age << endl;
        cout << governorate << endl;
        cout << vaccinated << endl;
        cout << received_both_doses << endl;
    }
    myfile.close();
    infile.close();

}

void read_file_onedose()
{
    vector<User> temp = firstDose;
    User u = temp[0];
    ofstream ofile("firstDose.txt");
    for (int i = 0; i < temp.size(); i++)
    {
        temp[0];
        ofile << u.get_name() << endl;
        ofile << u.get_national_id() << endl;
        ofile << u.get_age() << endl;
        ofile << u.get_gender() << endl;
        ofile << u.get_governorate() << endl;
        ofile << u.is_vaccinated() << endl;
        ofile << u.has_received_both_doses() << endl;
        temp.pop_back();
    }
    ifstream infile("firstDose.txt");
    string name = u.get_name();
    string national_id = u.get_national_id();
    char gender = u.get_gender();
    int age = u.get_age();
    string governorate = u.get_governorate();
    char vaccinated = u.is_vaccinated();
    char received_both_doses = u.has_received_both_doses();
    while (infile >> name >> national_id >> gender >> age >> governorate >> vaccinated >> received_both_doses)
    {
        cout << name << endl;
        cout << national_id << endl;
        cout << gender << endl;
        cout << age << endl;
        cout << governorate << endl;
        cout << vaccinated << endl;
        cout << received_both_doses << endl;
    }
    ofile.close();
    infile.close();
}
void  read_file_twodose()
{
    vector<User> temp = secondDose;
    User u = temp[0];
    ofstream ofile("secondDose.txt");
    for (int i = 0; i < temp.size(); i++)
    {
        temp[0];
        ofile << u.get_name() << endl;
        ofile << u.get_national_id() << endl;
        ofile << u.get_age() << endl;
        ofile << u.get_gender() << endl;
        ofile << u.get_governorate() << endl;
        ofile << u.is_vaccinated() << endl;
        ofile << u.has_received_both_doses() << endl;
        temp.pop_back();
    }
    ifstream infile("secondDose.txt");
    string name = u.get_name();
    string national_id = u.get_national_id();
    char gender = u.get_gender();
    int age = u.get_age();
    string governorate = u.get_governorate();
    char vaccinated = u.is_vaccinated();
    char received_both_doses = u.has_received_both_doses();
    while (infile >> name >> national_id >> gender >> age >> governorate >> vaccinated >> received_both_doses)
    {
        cout << name << endl;
        cout << national_id << endl;
        cout << gender << endl;
        cout << age << endl;
        cout << governorate << endl;
        cout << vaccinated << endl;
        cout << received_both_doses << endl;
    }
    ofile.close();
    infile.close();
}




