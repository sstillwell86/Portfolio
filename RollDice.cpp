//RollDice.cpp
#include "RollDice.h"
#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;

int* RollDice::rollDice(int number)
{
	int arr[6] = { 0,0,0,0,0,0 };

	for (int i = 0; i < number; i++) {
		arr[i] = rand() % 6 + 1;
	}
	return arr;
}