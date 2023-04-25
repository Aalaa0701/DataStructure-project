#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include"user.h"
using namespace std;
 


int main() {
	string adminId="SosyBosy", adminPassword="1234", userName, password;
	vector<User> firstDose,secondDose;
	queue<User> waitingList;
	map<string, User> user_map;
	map<string, User>::iterator it;
	int choiceForUser, choiceForAdmin, choiceForMain;
	string nationalId;


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
	







	return 0;
}