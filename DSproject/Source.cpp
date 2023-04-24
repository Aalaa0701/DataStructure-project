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


	do
	{
		cout << "Enter 1 if you want to add user , 2 to display record, 3 to edit , 3 to delete or any other number to exit " << endl;
		cin >> choiceForMain;
		cin.ignore();
		if (choiceForMain == 1) {
			User* temp = new User();
			temp->add_user(firstDose, secondDose, waitingList, user_map);
			delete temp;
			
		
		}
		else if (choiceForMain == 2) {
			char choiceForEdit;
			User* temp = new User();
			temp->display_user_data(firstDose, secondDose, waitingList, user_map);
			cout << "Do you want to edit your record?  Y/N" << endl;
			cin >> choiceForEdit;
			if (choiceForEdit == 'Y' || choiceForEdit == 'y') {
			}
			else if (choiceForEdit == 'N' || choiceForEdit == 'n') {
				cout << "Smart" << endl;
				break;
			}
			else {
				cout << "IDIOT" << endl;
				break;
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





	} while (choiceForMain==1||choiceForMain==2|| choiceForMain == 3|| choiceForMain == 4);
	







	return 0;
}