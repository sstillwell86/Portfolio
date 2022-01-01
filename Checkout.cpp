//Checkout.cpp

#include <ctime>
#include <iostream>
#include <string>
using namespace std;

int main() {
	int leapYears[35] = { 1904, 1908, 1912, 1916, 1920, 1924, 1928, 1932, 1936, 1940, 1944, 1948, 1952, 1956, 1960, 1964, 1968, 1972, 1976, 1980, 1984, 1988, 1992, 1996, 2000, 2004, 2008, 2012, 2016, 2020, 2024, 2028, 2032, 2036, 2040 };
	int birthMonth = -1, birthDay = -1, birthYear = -1, currentMonth, currentDay, currentYear;
	bool isLeapYear = false;
	double age = -1;
	string rating = "";
	bool canRent = false;
	bool rentalValidation(double age, string rating);
	double ageCalculator(int birthMonth, int birthDay, int birthYear, int currentMonth, int currentDay, int currentYear);
	while (age < 0) {
		birthYear = -1;
		birthMonth = -1;
		birthDay = -1;
		while (birthYear < 1900 && age < 0) {
			cout << "Enter customer birth year: ";
			cin >> birthYear;
			if (birthYear < 1900) {
				cout << "Enter a valid birth year.\n";
			}
		}
		while (birthMonth < 1 || birthMonth > 12 && age < 0) {
			cout << "\nEnter customer birth month: ";
			cin >> birthMonth;
			if (birthMonth < 1 || birthMonth > 12) {
				cout << "Enter a valid birth month.";
			}
		}
		while (birthDay == -1) {
			cout << "\nEnter customer birth day: ";
			cin >> birthDay;
			if (birthMonth == 2 && (birthDay < 1 || birthDay > 28)) {
				if (birthDay == 29) {
					for (int i = 0; i < 35; i++) {
						if (birthYear == leapYears[i]) {
							isLeapYear = true;
						}
					}
				}
				if (birthDay != 29 || (birthDay == 29 && !isLeapYear)) {
					cout << "Enter a valid birth day.";
					birthDay = -1;
				}
			}
			if ((birthMonth == 4 || birthMonth == 6 || birthMonth == 9 || birthMonth == 11) && (birthDay < 1 || birthDay > 30)) {
				cout << "Enter a valid birth day.";
				birthDay = -1;
			}
			if ((birthMonth == 1 || birthMonth == 3 || birthMonth == 5 || birthMonth == 7 || birthMonth == 8 || birthMonth == 10 || birthMonth == 12) && (birthDay < 1 || birthDay > 31)) {
				cout << "Enter a valid birth day.";
				birthDay = -1;
			}
		}
		cout << "\nEnter current year: ";
		cin >> currentYear;
		cout << "\nEnter current month: ";
		cin >> currentMonth;
		cout << "\nEnter current day: ";
		cin >> currentDay;
		age = ageCalculator(birthMonth, birthDay, birthYear, currentMonth, currentDay, currentYear);
		cout << "\nAge: " << age;
		if (age < 0 || birthYear < 1900) {
			cout << "\nInvalid entry.\n";
			age = -1;
		}
	}
	while (rating != "EC" && rating != "E" && rating != "E10" && rating != "T" && rating != "M" && rating != "AO") {
		cout << "\nEnter a rating: ";
		cin.ignore();
		getline(cin, rating);
		if (rating != "EC" && rating != "E" && rating != "E10" && rating != "T" && rating != "M" && rating != "AO") {
			cout << "\nEnter a valid rating.";
		}
	}
	canRent = rentalValidation(age, rating);
	if (canRent == false) {
		cout << "\nCustomer cannot rent item.\n";
	}
	else if (canRent == true) {
		cout << "\nCustomer can rent item.\n";
	}
	system("pause");
}

double ageCalculator(int birthMonth, int birthDay, int birthYear, int currentMonth, int currentDay, int currentYear)
{
	double age = currentYear - birthYear - 1;
	if ((birthMonth < currentMonth) || (birthMonth == currentMonth && birthDay <= currentDay)) {
		age++;
	}
	if (birthMonth <= 6) {
		if (currentMonth < birthMonth) {
			age += .5;
		}
		if (currentMonth == birthMonth && currentDay < birthDay) {
			age += .5;
		}
		if (currentMonth >= (birthMonth + 6)) {
			age += .5;
		}
	}
	else if (birthMonth > 6) {
		if (currentMonth == birthMonth && currentDay < birthDay) {
			age += .5;
		}
		else if (currentMonth <= 6 && ((currentMonth + 6) >= birthMonth)) {
			age += .5;
		}
	}
	return age;
}

bool rentalValidation(double age, string rating) {
	if (rating == "EC") {
		return true;
	}
	else if (rating == "E") {
		if (age >= 8.5) {
			return true;
		}
		else return false;
	}
	else if (rating == "E10") {
		if (age >= 10) {
			return true;
		}
		else return false;
	}
	else if (rating == "T") {
		if (age >= 13) {
			return true;
		}
		else return false;
	}
	else if (rating == "M") {
		if (age >= 17) {
			return true;
		}
		else return false;
	}
	else if (rating == "AO") {
		if (age >= 18) {
			return true;
		}
		else return false;
	}
}