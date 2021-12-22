// Steven Stillwell
// CIS 2207 N02
// 19/SP
// Assignment 6

#include "NumberList.h"

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>

// prototypes
void menu();
char *getCharArray();

// main routine
int main()
{
	menu();

	//	char *dummy = getCharArray();

	return 0;
}

char *getCharArray()
{
	/*	char * array;

		array = new char[10];

		return array;
	*/
	return new char[10];
}

double *getDoubleArray()
{
	double * array;

	array = new double[10];

	return array;
}

char getChoice()
{
	std::cout << "Choice: " << std::endl;

	std::cout << "\tA -- Append" << std::endl;
	std::cout << "\tI -- Insert" << std::endl;
	std::cout << "\tD -- Delete" << std::endl;
	std::cout << "\tC -- Clear" << std::endl;
	std::cout << "\tP -- Print" << std::endl;
	std::cout << "\tQ -- Quit" << std::endl;
	std::cout << "\tS -- Search" << std::endl;

	std::cout << std::endl;
	std::cout << "Enter Choice: ";

	char c = _getch();

	while (!(c == 'C' || c == 'c' ||
		c == 'D' || c == 'd' ||
		c == 'I' || c == 'i' ||
		c == 'Q' || c == 'q' ||
		c == 'a' || c == 'A' ||
		c == 'P' || c == 'p' ||
		c == 's' || c == 'S'))
	{
		std::cout << "Error, you entered a '" << c << "'" << std::endl;
		std::cout << "Enter Choice: ";
		c = _getch();
	}

	c = _toupper(c);

	std::cin.clear();
	return c;

}


void menu()
{
	NumberList numbers;
	double numberValue;
	char c = getChoice();

	std::cout << std::endl;

	while (c != 'Q')
	{
		switch (c)
		{
		case 'A':
		case 'a':
			std::cout << "Enter a number: ";
			std::cin >> numberValue;

			numbers.appendNode(numberValue);
			break;
		case 'I':
			std::cout << "Enter a number: ";
			std::cin >> numberValue;

			numbers.insertNode(numberValue);
			break;
		case 'D':
			std::cout << "Enter a number to remove: ";
			std::cin >> numberValue;

			numbers.deleteNode(numberValue);
			break;
		case 'P':
		case 'p':
			numbers.displayList();
			break;
		case 'C':
			numbers.clear();
			break;
		case 'S':
			std::cout << "Enter a number: ";
			std::cin >> numberValue;

			if (numbers.search(numberValue) == 0)
			{
				std::cout << "Number not found." << std::endl;
			}
			else
			{
				std::cout << "Number found at position " << numbers.search(numberValue) << " in list." << std::endl;
			}
			break;
		}

		c = getChoice();
		std::cout << std::endl;
	}
}