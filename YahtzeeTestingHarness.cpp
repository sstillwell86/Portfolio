//YahtzeeTestingHarness.cpp

#include "YahtzeeScoreModule.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	string testCaseFilename = "Yahtzee Test Cases.txt";
	ifstream testCases;
	testCases.open(testCaseFilename);
	YahtzeeScoreModule *scoreModule = new YahtzeeScoreModule();
	int caseNumber = 1;
	int rolls[5] = { 0,0,0,0,0 };
	if (testCases.is_open()) {
		while (!testCases.eof()) {
			string category;
			getline(testCases, category);
			if (category == "NewGame") {
				delete scoreModule;
				YahtzeeScoreModule *scoreModule = new YahtzeeScoreModule();
				getline(testCases, category);
			}
			string rollData;
			getline(testCases, rollData);
			for (int i = 0; i < 5; i++) {
				rolls[i] = rollData[i] - '0';
			}
			int expectedResult = 0;
			expectedResult = (((int)rollData[5] - '0') * 100) + (((int)rollData[6]-'0') * 10) + ((int)rollData[7] - '0');
			if (expectedResult < 0) {
				scoreModule->functionCaller(rolls, category);
				getline(testCases, category);
				getline(testCases, rollData);
				for (int i = 0; i < 5; i++) {
					rolls[i] = rollData[i] - '0';
				}
				int result = (scoreModule->functionCaller(rolls, category));
				if (result == -1) {
					cout << "Test Case " << caseNumber << " Passed\n";
				}
				else {
					cout << "Test Case " << caseNumber << " Failed\n";
				}
				caseNumber++;
			}
			else {
				int result = (scoreModule->functionCaller(rolls, category));
				if (expectedResult == result) {
					cout << "Test Case " << caseNumber << " Passed\n";
					caseNumber++;
				}
				else if (expectedResult >= 0) {
					cout << "Test Case " << caseNumber << " Failed: Expected " << expectedResult << ", got " << result << ".\n";
					caseNumber++;
				}
			}	
		}
	}
	else {
		cout << "Error opening file.\n";
	}
	system("pause");
	return 0;
}