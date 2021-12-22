// Steven Stillwell
// CIS 2207 N02
// Assignment 7
// 3/17/2019
#pragma once


class CharStack
{
private:
	struct StackNode
	{
		char ch;
		struct StackNode * previous;
	};

	StackNode *head;

public:
	void push(char);
	char pop();
	bool isEmpty();
	CharStack();
	~CharStack();
};