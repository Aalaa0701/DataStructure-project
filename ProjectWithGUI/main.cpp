#include "ProjectWithGUI.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <fstream>	
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;


void read_file_waitinglist(queue<User>& waitingList, map<string, User>& user_map);

void read_file_onedose(vector<User>& firstDose, map<string, User>& user_map);

void read_file_twodose(vector<User>& secondDose, map<string, User>& user_map);
void ReadAll(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList, map<string, User>& user_map);

int main(int argc, char *argv[])
{
	vector<User> firstDose, secondDose;
	queue<User> waitingList;
	queue<User> temporary = waitingList;

	map<string, User> user_map;
	map<string, User>::iterator it;
	string nationalId;
	ReadAll(firstDose, secondDose, waitingList, user_map);

	firstDose,secondDose,waitingList,user_map;


    QApplication a(argc, argv);
	QWidget* parent = nullptr;
	//ProjectWithGUI* w = new ProjectWithGUI(parent, adminPageAppear);
	ProjectWithGUI w(parent, firstDose, secondDose, waitingList, user_map);
	w.show();

    return a.exec();
}




// read 


void ReadAll(vector<User>& firstDose, vector<User>& secondDose, queue<User>& waitingList, map<string, User>& user_map) {
	read_file_waitinglist(waitingList, user_map);
	read_file_onedose(firstDose, user_map);
	read_file_twodose(secondDose, user_map);
}

void read_file_waitinglist(queue<User>& waitingList, map<string, User>& user_map)
{
	queue<User> temp;


	User u;
	ifstream infile("waitinglist.txt");
	string name = u.get_name();
	string national_id = u.get_national_id();
	string password = u.get_password();
	char gender = u.get_gender();
	int age = u.get_age();
	string governorate = u.get_governorate();
	bool vaccinated = u.is_vaccinated();
	bool received_both_doses = u.has_received_both_doses();
	//infile >> name >> password >> age >> gender >> governorate >> vaccinated >> received_both_doses;
	
	while (infile >> national_id)
	{
		infile >> name >> password >> age >> gender >> governorate >> vaccinated >> received_both_doses;
		User temp(name, national_id, password, gender, age, governorate, vaccinated, received_both_doses);

		waitingList.push(temp);
		user_map.insert({ national_id,temp });

	}
	//if(!infile)
	infile.close();


}

void read_file_onedose(vector<User>& firstDose, map<string, User>& user_map)
{

	User u;
	ifstream infile("firstDose.txt");
	string name = u.get_name();
	string national_id = u.get_national_id();
	string password = u.get_password();
	char gender = u.get_gender();
	int age = u.get_age();
	string governorate = u.get_governorate();
	bool vaccinated = u.is_vaccinated();
	bool received_both_doses = u.has_received_both_doses();

	while (infile >> name)
	{
		infile >> national_id >> password >> age >> gender >> governorate >> vaccinated >> received_both_doses;
		User temp(name, national_id, password, gender, age, governorate, vaccinated, received_both_doses);

		firstDose.push_back(temp);
		user_map.insert({ national_id,temp });


	}
	infile.close();
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
	while (infile >> name)
	{
		infile >> national_id >> password >> age >> gender >> governorate >> vaccinated >> received_both_doses;
		User temp(name, national_id, password, gender, age, governorate, vaccinated, received_both_doses);
		secondDose.push_back(temp);
		user_map.insert({ national_id,temp });

	}
	infile.close();
}
