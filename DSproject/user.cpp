#include <iostream>
#include "user.h"
#include <vector>
#include <queue>
using namespace std;
//constructor
Admin::Admin() {
	password = "";
	userName = "";

}
//to calculate some statistics 
void Admin::Statistics(vector<User>firstDose,vector<User>secondDose,queue<User>waitingList) {
	double firstDosePct, secondDosePct, femalePct, malePct;
	double firstRangePct, secondRangePct, thirdRangePct, fourthRangePct, fifthRangePct;
	int fCount = 0; int mCount = 0;
	int firstRange1 = 0; int secondRange1 = 0; int thirdRange1 = 0; int fourthRange1 = 0; int fifthRange1 = 0;
	int firstRange2 = 0; int secondRange2 = 0; int thirdRange2 = 0; int fourthRange2 = 0; int fifthRange2 = 0;
	int firstRange = 0; int secondRange = 0; int thirdRange = 0; int fourthRange = 0; int fifthRange = 0;
	vector<User>::iterator it;
	vector<User>::iterator it1;
	vector<User>::iterator it2;
	vector<User>::iterator it3;

	//calculate the pct of first and second dose
	firstDosePct = (firstDose.size() / (firstDose.size() + secondDose.size() + waitingList.size()))*100.00;
	secondDosePct = (secondDose.size()/ (firstDose.size() + secondDose.size() + waitingList.size()))*100.00;

	//filter males and females from first dose vector
	it = firstDose.begin();
	it1 = secondDose.begin();
	for (int i= 0; i < firstDose.size(); i++) {
		if (firstDose[i].get_gender() == 'M') {
			mCount++;
			it++;
		}
		else if (firstDose[i].get_gender() == 'F') {
			fCount++;
			it++;
		}
	}
	//filter males and females from second dose vector
	for (int i = 0; i < secondDose.size(); i++) {
		if (secondDose[i].get_gender() == 'M') {
			mCount++;
			it1++;
		}
		else if (secondDose[i].get_gender() == 'F') {
			fCount++;
			it1++;
		}
	}
	// filter males and females from waiting list
	queue<User> copy = waitingList;
	while (!copy.empty())
	{
		if (copy.front().get_gender() == 'M') {
			mCount++;
			copy.pop();
		}
		else if (copy.front().get_gender() == 'F') {
			fCount++;
			copy.pop();
		}
	}
	//calculate the pct of males and females
	malePct = (mCount / (firstDose.size() + secondDose.size() + waitingList.size()))*100.00;
	femalePct = (fCount / (firstDose.size() + secondDose.size() + waitingList.size()))*100.00;


	//filter each age group from second dose vector
	it2 = secondDose.begin();
	it3 = firstDose.begin();
	for (int i = 0; i < secondDose.size(); i++) {
		if (secondDose[i].get_age() >= 75) {
			firstRange++;
			it2++;
		}
		else if (secondDose[i].get_age() >= 65 && secondDose[i].get_age() <= 74) {
			secondRange++;
			it2++;
		}
		else if (secondDose[i].get_age() >= 50 && secondDose[i].get_age() <= 64) {
			thirdRange++;
			it2++;
		}
		else if (secondDose[i].get_age() >= 40 && secondDose[i].get_age() <= 49) {
			fourthRange++;
			it2++;
		}
		else if (secondDose[i].get_age() >= 18 && secondDose[i].get_age() <= 39) {
			fifthRange++;
			it2++;
		}
	}
	//filter each age group from first dose vector
	for (int i = 0; i < firstDose.size(); i++) {
		if (firstDose[i].get_age() >= 75) {
			firstRange1++;
			it3++;
		}
		else if (firstDose[i].get_age() >= 65 && firstDose[i].get_age() <= 74) {
			secondRange1++;
			it3++;
		}
		else if (firstDose[i].get_age() >= 50 && firstDose[i].get_age() <= 64) {
			thirdRange1++;
			it3++;
		}
		else if (firstDose[i].get_age() >= 40 && firstDose[i].get_age() <= 49) {
			fourthRange1++;
			it3++;
		}
		else if (firstDose[i].get_age() >= 18 && firstDose[i].get_age() <= 39) {
			fifthRange1++;
			it3++;
		}
	}
	//filter each age group from waiting list
	queue<User> copy_1 = waitingList;
	while (!copy_1.empty()) {
		if (copy_1.front().get_age() >= 75) {
			firstRange2++;
			copy_1.pop();
		}
		else if (copy_1.front().get_age() >= 65 && copy_1.front().get_age() <= 74) {
			secondRange2++;
			copy_1.pop();
		}
		else if (copy_1.front().get_age() >= 50 && copy_1.front().get_age() <= 64) {
			thirdRange2++;
			copy_1.pop();
		}
		else if (copy_1.front().get_age() && copy_1.front().get_age() <= 49) {
			fourthRange2++;
			copy_1.pop();
		}
		else if (copy_1.front().get_age() >= 18 && copy_1.front().get_age() <= 39) {
			fifthRange2++;
			copy_1.pop();
		}
	}
	//calculate the pct of each age group
	fifthRangePct = (fifthRange / (fifthRange + fifthRange1 + fifthRange2)) * 100.00;
	fourthRangePct = (fourthRange / (fourthRange + fourthRange1 + fourthRange2)) * 100.00;
	thirdRangePct = (thirdRange / (thirdRange + thirdRange1 + thirdRange2)) * 100.00;
	secondRangePct = (secondRange / (secondRange + secondRange1 + secondRange2)) * 100.00;
	firstRangePct = (firstRange / (firstRange + firstRange1 + firstRange2)) * 100.00;

	cout << "Percentage of people that have received the first dose : " << firstDosePct << "%" << endl;
	cout << "Percentage of people that have received the second dose : " << secondDosePct << "%" << endl;
	cout << "Percentage of females : " << femalePct << "%" << endl;
	cout << "Percentage of males : " << malePct << "%" << endl;
	cout << "Ages from 75 and over that have been fully vaccinated : " << firstRangePct << "%" << endl;
	cout << "Ages from 65 to 74 that have been fully vaccinated : " << secondRangePct << "%" << endl;
	cout << "Ages from 50 to 64 that have been fully vaccinated : " << thirdRangePct << "%" << endl;
	cout << "Ages from 40 to 49 that have been fully vaccinated : " << fourthRangePct << "%" << endl;
	cout << "Ages from 18 to 39 that have been fully vaccinated : " << fifthRangePct << "%" << endl;

}
