// Steven Stillwell
// CIS 2207 N02
// 19/SP
// Assignment 6

#include "NumberList.h"

#include <iostream>

NumberList::NumberList()
{
	head = nullptr;
}


NumberList::~NumberList()
{
	clear();
}

void NumberList::appendNode(double num)
{
	// This will add a double to the end of the list
	ListNode *newNode = new ListNode;
	ListNode *nodePtr = head;

	// Add the value and next to newNode
	newNode->value = num;
	newNode->next = nullptr;

	// If list is empty, assign newNode to head
	if (!head)
		head = newNode;
	else // otherwise, find the last node and add it to the end
	{
		// find the last node
		while (nodePtr->next)
			nodePtr = nodePtr->next;

		// insert newNode as the last node
		nodePtr->next = newNode;
	}
}

void NumberList::insertNode(double num)
{
	ListNode *newNode = new ListNode;
	ListNode *nodePtr = head;
	ListNode *previousNode = nullptr;

	newNode->value = num;
	newNode->next = nullptr;

	// if there are no nodes in the list
	if (!head)
	{
		head = newNode;
	}
	else // otherwise, insert the newNode
	{
		// skip all nodes whose value is less then num.
		while (nodePtr != nullptr && nodePtr->value < num)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// if the new node is to be the 1st in the list, insert it before all other nodes.
		if (previousNode == nullptr)
			// if (!previousNode)
		{
			head = newNode;
			newNode->next = nodePtr;
		}
		else // otherwise insert after the previous node
		{
			previousNode->next = newNode;
			newNode->next = nodePtr;
		}
	}
}

void NumberList::deleteNode(double num)
{
	ListNode *nodePtr = head;
	ListNode *previousNode = nullptr;

	// if the list is empty, do nothing
	if (!head)
	{
	}
	else if (head->value == num) // else if the value that head is point to is num, delete it
	{
		nodePtr = head->next;
		delete head;
		head = nodePtr;
	}
	else // else if the value is in the list
	{
		// skip all nodes while value is not equal to num
		while (nodePtr != nullptr && nodePtr->value != num)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		if (nodePtr)
		{
			previousNode->next = nodePtr->next;
			delete nodePtr;
		}
	}

}
int NumberList::search(double num)
{
	ListNode *nodePtr = head;
	ListNode *previousNode = nullptr;
	int i = 1;
	if (!head) //returns 0 since list is empty
	{
		return 0;
	}
	else if (head->value == num)
	{
		return 1;
	}
	{
		while (nodePtr != nullptr && nodePtr->value != num) // iterates through list incrementing i each jump
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
			i++;
		}
		if (nodePtr)
		{
			return i;
		}
		else return 0;
	}
}

void NumberList::displayList() const
{
	// create a pointer to point to the current node
	ListNode *nodePtr = head;

	// while nodePtr points to a node, traverse the list
	while (nodePtr)
	{
		// print this value
		std::cout << nodePtr->value << std::endl;

		// move to the next node
		nodePtr = nodePtr->next;
	}
}

void NumberList::clear()
{
	ListNode *nodePtr = head;
	ListNode *nextNode;

	// while nodePtr is not at the end of the list
	while (nodePtr != nullptr)
	{
		// save the point to the next node
		nextNode = nodePtr->next;

		// delete the nodePtr
		delete nodePtr;

		// set nodePtr to the saved next pointer
		nodePtr = nextNode;
	}

	// set the head to nullptr
	head = nullptr;
}
