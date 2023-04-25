#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include"user.h"
using namespace std;
 


int main() {
	vector<User> firstDose,secondDose;
	queue<User> waitingList;
	map<string, User> user_map;
	map<string, User>::iterator it;
	int choiceForMain;
	string nationalId;


	do
	{
		cout << "Enter 1 if you want to add user , 2 to display record, or any other number to exit " << endl;
		cin >> choiceForMain;
		cin.ignore();
		if (choiceForMain == 1) {
			User* temp = new User();
			temp->add_user(firstDose, secondDose, waitingList, user_map);
			delete temp;
			
		
		}
		else if (choiceForMain == 2) {
			int choiceForEdit;
			User* temp = new User();
			temp->display_user_data(firstDose, secondDose, waitingList, user_map, nationalId);
			cout << "Enter 1 to edit or 2 to delete  " << endl;
			cin >> choiceForEdit;
			if (choiceForEdit==1) {
				temp->EditUserData(firstDose, secondDose, waitingList, nationalId);
			}
			else if (choiceForEdit ==2) {
				temp->deleteUser(firstDose, secondDose, waitingList, nationalId,user_map);
			}
			else {
				cout << "IDIOT" << endl;
			}
			delete temp;
		}
		else if (choiceForMain == 3) {
			
		}
		else if (choiceForMain == 4) {
		
		}
		else {
			break;
		}
		for (it = user_map.begin();it != user_map.end();it++) {
			cout << it->first << endl;
		}





	} while (choiceForMain==1||choiceForMain==2|| choiceForMain == 3|| choiceForMain == 4);
	







	return 0;
}