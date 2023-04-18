#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
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

//a vector to hold all the user records
vector<User> firstDose;
vector<User> secondDose;
vector<User>::iterator it;
//a queue to hold the users on the waiting list
queue<User> waiting_list;

void FilteredRecords() {
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



void OrderedByAge() {
    cout << "Sorting Records\n";
    vector<User>both_users;
    both_users.insert(both_users.end(), firstDose.begin(), firstDose.end());
    both_users.insert(both_users.end(), secondDose.begin(), secondDose.end());
    sort(both_users.begin(), both_users.end(), [](const User& a, const User& b) { return a.get_age() < b.get_age(); });//Sorting the vector;
    for ( auto i = both_users.begin(); i < both_users.end(); i++)
    {
        cout << "Age:" << i->get_age() << "\t" << "National_id:" << "\t" << i->get_national_id() << "\t" << "Name:" << "\t" << i->get_name() << "\t" << "Gender:" << "\t" << i->get_gender() << "\t" << "Governorate:" << "\t" << i->get_governorate() << endl;
    }
}
int main() {
	
   /* User user1("basmala", "1234567890123", "hjbetsiejvn", 'f', 20, "cairo", true, false);
    firstDose.push_back(user1);
    User user2("basma", "1234567990123", "hjbetejv", 'm', 19, "cairo", true, false);
    firstDose.push_back(user2);
    User user3("yousef", "1234567890444", "hjbiejvn", 'f', 23, "alex", true, true);
    secondDose.push_back(user3);
    User user4("naeem", "1234567890555", "etsiejvn", 'm', 40, "alex", true, true);
    secondDose.push_back(user4);

    FilteredRecords();

    OrderedByAge();*/


	return 0;
}
