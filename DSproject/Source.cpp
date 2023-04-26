#include <iostream>
#include <fstream>	
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include"user.h"
using namespace std;
 
void WriteWaitingList(queue<User>waitingList);
void read_file_waitinglist(queue<User>& waitingList, map<string, User>& user_map);
void WriteOneDose(vector<User>firstDose);
void read_file_onedose(vector<User>& firstDose, map<string, User>& user_map);
void WriteTwoDose(vector<User>secondDose);
void read_file_twodose(vector<User>& secondDose, map<string, User>& user_map);
void ReadAll(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList, map<string, User>& user_map);
void WriteAll(vector<User> firstDose, vector<User> secondDose, queue<User> waitingList);


int main() {
	string adminId="SosyBosy", adminPassword="1234", userName, password;
	vector<User> firstDose,secondDose;
	queue<User> waitingList;
	queue<User> temporary = waitingList;

	map<string, User> user_map;
	map<string, User>::iterator it;
	int choiceForUser, choiceForAdmin, choiceForMain;
	string nationalId;
    ReadAll(firstDose, secondDose, waitingList,user_map);

	do
	{
		cout << "Enter username: " << endl;
		getline(cin, userName);
		cout << "Enter password: " << endl;
		getline(cin, password);
		if (userName == adminId && password == adminPassword) {
			do {
					cout << "Enter 1 if you want to view users or 2 if you want to delete users or 3 if you want to filter records or 4 if filtered by age or 5 for statistics" << endl;
					cin >> choiceForAdmin;
					cin.ignore();
					if (choiceForAdmin == 1) {
						Admin* adminTemp = new Admin();
						adminTemp->ViewRecord(user_map);
						delete adminTemp;
					}
					else if (choiceForAdmin == 2) {
						Admin* adminTemp = new Admin();
						adminTemp->DeleteRecord(user_map);
						delete adminTemp;
					}
					else if (choiceForAdmin == 3) {
						Admin* adminTemp = new Admin();
						adminTemp->FilteredRecords(firstDose, secondDose);
						delete adminTemp;
					}
					else if (choiceForAdmin == 4) {
						Admin* adminTemp = new Admin();
						adminTemp->OrderedByAge(firstDose, secondDose);
						delete adminTemp;
					}
					else if (choiceForAdmin == 5) {
						Admin* adminTemp = new Admin();
						adminTemp->Statistics(firstDose, secondDose, waitingList,user_map);
						delete adminTemp;
					}
					else {
						break;
					}

			} while (choiceForAdmin == 1 || choiceForAdmin == 2|| choiceForAdmin==3||choiceForAdmin==4||choiceForAdmin==5);
		}
		else {
			do {
				cout << "Enter 1 if you want to add user , 2 to display record or edit or delete, or any other number to exit " << endl;
				cin >> choiceForUser;
				cin.ignore();
				if (choiceForUser == 1) {
					User* temp = new User();
					temp->add_user(firstDose, secondDose, waitingList, user_map);
					delete temp;


				}
				else if (choiceForUser == 2) {
					int choiceForEdit;
					User* temp = new User();
					temp->display_user_data(firstDose, secondDose, waitingList, user_map, nationalId);
					cout << nationalId << endl;
					cout << "Enter 1 to edit or 2 to delete or any number to exit  " << endl;
					cin >> choiceForEdit;
					if (choiceForEdit == 1) {
						temp->EditUserData(firstDose, secondDose, waitingList, user_map,nationalId);
					}
					else if (choiceForEdit == 2) {
						temp->deleteUser(firstDose, secondDose, waitingList, nationalId,user_map);
					}
					else{
						break;
					}
					delete temp;
				}
				else if (choiceForUser == 3) {

				}
				else {
					break;
				}




			} while (choiceForUser == 1 || choiceForUser == 2 || choiceForUser == 3);

		}
		cout << "Repeat Again? if so press 1" << endl;

		cin >> choiceForMain;
		cin.ignore();

	} while (choiceForMain==1);
	

    WriteAll(firstDose,secondDose,waitingList);
	return 0;
}













// read and write


void ReadAll(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList, map<string, User>& user_map) {
    read_file_waitinglist(waitingList,user_map);
    read_file_onedose(firstDose,user_map);
    read_file_twodose(secondDose,user_map);
}
void WriteAll(vector<User> firstDose, vector<User> secondDose, queue<User> waitingList) {
    WriteWaitingList(waitingList);
    WriteOneDose(firstDose);
    WriteTwoDose(secondDose);
}
void WriteWaitingList(queue<User>waitingList) {
    queue<User> temp = waitingList;
	User u;
    ofstream myfile("waitinglist.txt");

    while (!temp.empty())
    {
		u = temp.front();
        myfile << u.get_name() << " " << u.get_national_id() << " "<<u.get_password()<<" " << u.get_age() << " " << u.get_gender() << " " << u.get_governorate() << " " << u.is_vaccinated() << " " << u.has_received_both_doses() << endl;
        temp.pop();

    }
    myfile.close();

}
void read_file_waitinglist(queue<User>& waitingList, map<string, User>& user_map)
{
		queue<User> temp;


		User u ;
        ifstream infile("waitinglist.txt");
        string name = u.get_name();
        string national_id = u.get_national_id();
		string password = u.get_password();
        char gender = u.get_gender();
        int age = u.get_age();
        string governorate = u.get_governorate();
        bool vaccinated = u.vaccinated;
        bool received_both_doses = u.received_both_doses;
        while (infile >> name )
        {
			infile >> national_id >> password >> age >> gender >> governorate >> vaccinated >> received_both_doses;
			User temp(name, national_id, password, gender, age, governorate, vaccinated, received_both_doses);

			waitingList.push(temp);
			user_map.insert({ national_id,temp});
            
        }
        infile.close();
    

}
void WriteOneDose(vector<User>firstDose) {
    ofstream ofile("firstDose.txt");
    for (int i = 0; i < firstDose.size(); i++)
    {
        ofile << firstDose[i].get_name() << " " << firstDose[i].get_national_id() <<" " << firstDose[i].get_password() << " " << firstDose[i].get_age() << " " << firstDose[i].get_gender() << " " << firstDose[i].get_governorate() << " " << firstDose[i].is_vaccinated() << " " << firstDose[i].has_received_both_doses() << endl;
    }
    ofile.close();

}
void read_file_onedose(vector<User>& firstDose, map<string, User>& user_map)
{
   
    User u;
    ifstream infile("firstDose.txt");
    string name = u.name;
    string national_id = u.national_id;
	string password = u.get_password();
    char gender = u.gender;
    int age = u.age;
    string governorate = u.governorate;
    bool vaccinated = u.vaccinated;
    bool received_both_doses = u.received_both_doses;

    while (infile >> name )
    {
        infile>> national_id >>password>> age>> gender >> governorate>> vaccinated>> received_both_doses;
		User temp(name, national_id, password, gender, age, governorate, vaccinated, received_both_doses);

        firstDose.push_back(temp);
		user_map.insert({ national_id,temp });

		
    }
    infile.close();
}
void WriteTwoDose(vector<User>secondDose) {

    ofstream ofile("secondDose.txt");
    for (int i = 0; i < secondDose.size(); i++)
    {
        ofile << secondDose[i].get_name() <<" "<< secondDose[i].get_national_id() << " " << secondDose[i].get_password() << " " << secondDose[i].get_age() << " " << secondDose[i].get_gender() << " " << secondDose[i].get_governorate() << " " << secondDose[i].is_vaccinated() << " " << secondDose[i].has_received_both_doses() << endl;
    }
    ofile.close();

}
void read_file_twodose(vector<User>& secondDose, map<string, User>& user_map)
{
    
    User u;
    ifstream infile("secondDose.txt");
    string name = u.get_name();
    string national_id = u.get_national_id();
	string password = u.get_password();
    char gender = u.get_gender();
    int age = u.get_age();
    string governorate = u.get_governorate();
    bool vaccinated = u.is_vaccinated();
    bool received_both_doses = u.has_received_both_doses();
    while (infile >> name )
    {
		infile>> national_id >> password>>age >> gender >> governorate >> vaccinated >> received_both_doses;
		User temp(name, national_id, password, gender, age, governorate, vaccinated, received_both_doses);
        secondDose.push_back(temp);
		user_map.insert({ national_id,temp });

    }
    infile.close();
}
