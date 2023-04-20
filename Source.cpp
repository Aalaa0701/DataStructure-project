#include <iostream>
#include <string>
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

map<string, User> user_map;


void display_user_data() {
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

		if (user_map.find(national_id)!=user_map.end())
		{ 

            if (password == user_map[national_id].get_password())
            {

                cout <<"your name is:"<< user_map[national_id].get_name() << endl;
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
        }

	}
}
int main() {
	
    user_map["0123456789000"] =User("Ali","0123456789000","123456789",'F', 18, "egpyt", false, false);
    display_user_data();
    system("pause");
	
	return 0;
}