#include "BinaryTree.h"
#include "BinaryTreeEmployeeInfo.h"

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>

// prototyes
void menu();

// main()
int main()
{
	menu();

	return 0;
}

char getChoice()
{

	std::cout << "Choice: " << std::endl;
	std::cout << "\tI -- Insert" << std::endl;
	std::cout << "\tD -- Display" << std::endl;
	std::cout << "\tS -- Search" << std::endl;
	std::cout << "\tR -- Remove" << std::endl;
	std::cout << "\tQ -- Quit" << std::endl;

	std::cout << std::endl;
	std::cout << "Enter Choice: ";

	char c = _getch();

	while (!(
		c == 'I' || c == 'i' ||
		c == 'D' || c == 'd' ||
		c == 'S' || c == 's' ||
		c == 'R' || c == 'r' ||
		c == 'Q' || c == 'q'
		))
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
	BinaryTree tree;
	char choice = getChoice();


	while (choice != 'Q')
	{
		std::string newString;
		std::string employeeName;
		int employeeId;
		std::cout << std::endl;
		switch (choice)
		{
		case 'I':
			std::cout << "Please enter the employee name: ";
			getline(std::cin, employeeName);
			std::cout << "Please enter the employee ID: ";
			std::cin >> employeeId;
			tree.insert(EmployeeInfo(employeeId,employeeName));
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		case 'D':
			std::cout << "Here is the InOrder display: " << std::endl;
			tree.displayInOrderWithLevel();
			break;
		case 'S':
			std::cout << "Please enter an Employee ID to search for: ";
			std::cin >> employeeId;
			newString = tree.search(employeeId);
			if (newString != "Employee not found.")
				std::cout << "Is value in tree?" << std::endl << "Yes, employee's name is " << newString << "." << std::endl;
			else
				std::cout << "Is value in tree?" << std::endl << newString;
			break;
		case 'R':
			std::cout << "Please enter the ID of the employee to remove: ";
			std::cin >> employeeId;
			tree.remove(employeeId);
			break;
		}

		choice = getChoice();
	}

}