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
void read_file_waitinglist(queue<User>& waitingList);
void WriteOneDose(vector<User>firstDose);
void read_file_onedose(vector<User>& firstDose);
void WriteTwoDose(vector<User>secondDose);
void read_file_twodose(vector<User>& secondDose);
void ReadAll(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList);
void WriteAll(vector<User> firstDose, vector<User> secondDose, queue<User> waitingList);


int main() {
	string adminId="SosyBosy", adminPassword="1234", userName, password;
	vector<User> firstDose,secondDose;
	queue<User> waitingList;
	map<string, User> user_map;
	map<string, User>::iterator it;
	int choiceForUser, choiceForAdmin, choiceForMain;
	string nationalId;
    ReadAll(firstDose, secondDose, waitingList);
	
	


	do
	{
		cout << "Enter username: " << endl;
		getline(cin, userName);
		cout << "Enter password: " << endl;
		getline(cin, password);
		if (userName == adminId && password == adminPassword) {
			do {
					cout << "Enter 1 if you want to view users or 2 if you want to delete users or 3 if you want to filter records or 4 if filtered by age" << endl;
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

					else {
						break;
					}

			} while (choiceForAdmin == 1 || choiceForAdmin == 2);
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
					cout << "Enter 1 to edit or 2 to delete  " << endl;
					cin >> choiceForEdit;
					if (choiceForEdit == 1) {
						//temp->EditUserData(firstDose, secondDose, waitingList, nationalId);
					}
					else if (choiceForEdit == 2) {
						//temp->deleteUser(firstDose, secondDose, waitingList, nationalId,user_map);
					}
					else {
						cout << "IDIOT" << endl;
					}
					delete temp;
				}
				else if (choiceForUser == 3) {

				}
				else {
					break;
				}
				for (it = user_map.begin();it != user_map.end();it++) {
					cout << it->first << endl;
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


void ReadAll(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList) {
    read_file_waitinglist(waitingList);
    read_file_onedose(firstDose);
    read_file_twodose(secondDose);
}
void WriteAll(vector<User> firstDose, vector<User> secondDose, queue<User> waitingList) {
    WriteWaitingList(waitingList);
    WriteOneDose(firstDose);
    WriteTwoDose(secondDose);
}
void WriteWaitingList(queue<User>waitingList) {
    queue<User> temp = waitingList;
    User u = temp.front();
    ofstream myfile("waitinglist.txt");

    while (!temp.empty())
    {
        myfile << u.get_name() << " " << u.get_national_id() << " " << u.get_age() << " " << u.get_gender() << " " << u.get_governorate() << " " << u.is_vaccinated() << " " << u.has_received_both_doses() << endl;
        temp.pop();

    }
    myfile.close();

}
void read_file_waitinglist(queue<User>& waitingList)
{
    queue<User> temp = waitingList;
    while (!temp.empty()) {
        User u = temp.front();

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
        infile.close();
    }
    

}
void WriteOneDose(vector<User>firstDose) {
    vector<User> temp = firstDose;
    // User u = temp[0];
    ofstream ofile("firstDose.txt");
    for (int i = 0; i < temp.size(); i++)
    {
        User u = temp[i];
        ofile << u.get_name() << " " << u.get_national_id() << " " << u.get_age() << " " << u.get_gender() << " " << u.get_governorate() << " " << u.is_vaccinated() << " " << u.has_received_both_doses() << endl;
    }
    ofile.close();

}
void read_file_onedose(vector<User>& firstDose)
{
   
    User u;
    ifstream infile("firstDose.txt");
    string name = u.get_name();
    string national_id = u.get_national_id();
    char gender = u.get_gender();
    int age = u.get_age();
    string governorate = u.get_governorate();
    char vaccinated = u.is_vaccinated();
    char received_both_doses = u.has_received_both_doses();
    while (infile >> national_id )
    {
        infile >> name >> national_id >> gender>> age>> governorate>> vaccinated>> received_both_doses;
        firstDose.push_back(u);
    }
    infile.close();
}
void WriteTwoDose(vector<User>secondDose) {
    vector<User> temp = secondDose;

    ofstream ofile("secondDose.txt");
    for (int i = 0; i < temp.size(); i++)
    {
        User u = temp[i];
        ofile << u.get_name() <<" "<< u.get_national_id() <<" "<< u.get_age() << " " << u.get_gender() << " " << u.get_governorate() << " " << u.is_vaccinated() << " " << u.has_received_both_doses()<<endl;
    }
    ofile.close();

}
void read_file_twodose(vector<User>& secondDose)
{
    
    User u;
    ifstream infile("secondDose.txt");
    string name = u.get_name();
    string national_id = u.get_national_id();
    char gender = u.get_gender();
    int age = u.get_age();
    string governorate = u.get_governorate();
    char vaccinated = u.is_vaccinated();
    char received_both_doses = u.has_received_both_doses();
    while (infile >> national_id )
    {
        infile >> name >> national_id >> gender >> age >> governorate >> vaccinated >> received_both_doses;
        secondDose.push_back(u);
    }
    infile.close();
}
