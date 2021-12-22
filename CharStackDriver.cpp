// Steven Stillwell
// CIS 2207 N02
// Assignment 7
// 3/17/2019

#include "CharStack.h"

#include <iostream>
#include <string>
#include <fstream>


int main()
{
	std::string inFilename = "input.txt";
	std::string outFilename = "output.txt";

	std::ifstream inFile;
	std::ofstream outFile;

	inFile.open(inFilename);
	outFile.open(outFilename);

	CharStack charStack;
	char c;

	if (inFile.is_open()) {
		while (!inFile.eof())
		{
			char c;
			while (inFile.get(c)) {
				charStack.push(c);
				std::cout << c;
			}
		}

		while (!charStack.isEmpty())
		{
			c = charStack.pop();
			outFile << c;
			std::cout << c;
		}
		outFile.close();
		inFile.close();
	}
	else {
		std::cout << "Error reading file." << std::endl;
	}
	system("pause");

	return 0;
}