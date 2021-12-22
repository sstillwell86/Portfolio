// Steven Stillwell
// CIS 2207 N02
// 19/SP
// Assignment 6

#pragma once
class NumberList
{
private:
	struct ListNode
	{
		double value;
		struct ListNode * next;
	};

	ListNode *head;
public:
	NumberList();
	~NumberList();

	// accessors

	// mutators

	// methods
	int search(double);
	void appendNode(double);
	void insertNode(double);
	void deleteNode(double);
	void displayList() const;
	void clear();
};

