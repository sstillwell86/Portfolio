// Steven Stillwell
// CIS 2207 N02
// Assignment 8 "Palindrome Detector"
// 3/23/19

#include <iostream>
#include <string>

bool isPalindrome(int first, int last, std::string palindrome);

int main() {
	std::string string1;
	std::cout << "Enter a word or phrase: " << std::endl;
	getline(std::cin, string1);
	std::string palindrome;
	for (unsigned int i = 0; i < string1.length(); i++) //builds a new string without spaces, commas, or apostrophes
	{
		if (isalnum(string1[i]))
		{
			if (isupper(string1[i]))
			{
				palindrome += tolower(string1[i]); //converts uppercase to lowercase for comparison
			}
			else
			{
				palindrome += string1[i];
			}
		}
	}
	int first = 0;
	int last = palindrome.size() -1;
	bool status = isPalindrome(first, last, palindrome);
	if (status == true)
	{
		std::cout << string1 << " is a palindrome." << std::endl;
	}
	else
	{
		std::cout << string1 << " is not a palindrome." << std::endl;
	}
	system("pause");
	return 0;
}

bool isPalindrome(int first, int last, std::string palindrome) 
{
	while (first < last)
	{
		if (palindrome[first] != palindrome[last])
		{
			return false;
		}
		else
		{
			first++;
			last--;
			isPalindrome(first, last, palindrome);
		}
	}
	return true;
}