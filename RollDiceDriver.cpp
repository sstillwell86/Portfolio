#include "RollDice.h"
#include <iostream>
using namespace std;

int main() {
	int number = 6;
	int rolls;
	RollDice roller;
	int rollCount = 0;
	int arr[6] = { 0,0,0,0,0,0 };
	while (rollCount < 3600000) {
		int* values = new int;
		values = roller.rollDice(2);
		int element = *(values);
		int element2 = *(values + 1);
		if (element == element2) {
			arr[element - 1]++;
		}
		rollCount++;
	}
	for (int i = 0; i < 6; i++) {
		cout << arr[i] << " ";
	}
	system("pause");
}