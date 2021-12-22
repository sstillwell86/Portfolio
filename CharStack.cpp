// Steven Stillwell
// CIS 2207 N02
// Assignment 7
// 3/17/2019

#include "CharStack.h"

#include <iostream>

void CharStack::push(char ch) {
	StackNode *newNode = new StackNode;
	StackNode *nodePtr = head;
	newNode->ch = ch;
	newNode->previous = head;
	head = newNode;
}

bool CharStack::isEmpty() {
	if (!head) {
		return true;
	}
	else return false;
}

char CharStack::pop() {
	StackNode *nodePtr = head;
	char temp = nodePtr->ch;
	nodePtr = head->previous;
	delete head;
	head = nodePtr;
	return temp;
}

CharStack::CharStack()
{
	head = nullptr;
}


CharStack::~CharStack()
{
	StackNode *nodePtr = head;
	StackNode *previousNode;

	while (nodePtr != nullptr)
	{
		previousNode = nodePtr->previous;
		delete nodePtr;
		nodePtr = previousNode;
	}
	head = nullptr;
}