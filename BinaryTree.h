// Steven Stillwell
// CIS 2207 N02
// Assignment 9
// 4/4/2019

#include "BinaryTreeEmployeeInfo.h"

#include <vector>

#pragma once
class BinaryTree
{
private:
	struct TreeNode
	{
		EmployeeInfo employee;
		TreeNode *left;
		TreeNode *right;
	};

	TreeNode *root;

	// Recursive methods
	void destroySubTree(TreeNode *&);
	void insert(TreeNode *&, TreeNode *&);
	void displayInOrder(TreeNode *);
	void displayInOrderWithLevel(TreeNode *, int level);
	void displayPreOrder(TreeNode *);
	void displayPostOrder(TreeNode *);
	void deleteNode(EmployeeInfo employee, TreeNode *&);

	// private method
	void makeDeletion(TreeNode *&);

public:
	// constructor
	BinaryTree() { root = nullptr; }
	// destructor
	~BinaryTree() { destroySubTree(root); }

	// basic methods
	void insert(EmployeeInfo employee);
	void displayInOrder();
	void displayInOrderWithLevel();
	void displayPreOrder();
	void displayPostOrder();
	std::string search(int employeeId);
	void remove(int employeeId);
};