#include "BinaryTree.h"
#include <iostream>
#include <vector>

void BinaryTree::destroySubTree(TreeNode *&nodePtr)
{
	if (nodePtr)
	{
		if (nodePtr->left)
			destroySubTree(nodePtr->left);
		if (nodePtr->right)
			destroySubTree(nodePtr->right);
		delete nodePtr;

		nodePtr = nullptr;
	}
}

void BinaryTree::insert(TreeNode *&nodePtr, TreeNode *&newNode)
{
	if (nodePtr == nullptr)
		nodePtr = newNode;
	else if (newNode->employee < nodePtr->employee)
		insert(nodePtr->left, newNode);
	else
		insert(nodePtr->right, newNode);
}

void BinaryTree::insert(EmployeeInfo employee)
{
	TreeNode *newNode = new TreeNode;

	newNode->employee = employee;
	newNode->right = newNode->left = nullptr;

	// Insert newNode into tree
	insert(root, newNode);
}

void BinaryTree::displayInOrder(TreeNode *nodePtr)
{
	if (nodePtr)
	{
		displayInOrder(nodePtr->left);
		std::cout << nodePtr->employee << std::endl;
		displayInOrder(nodePtr->right);
	}
}

void BinaryTree::displayInOrderWithLevel(TreeNode *nodePtr, int level)
{
	if (nodePtr)
	{
		displayInOrderWithLevel(nodePtr->left, level + 1);
		for (int index = 0; index < level; index++)
			std::cout << "\t";
		std::cout << nodePtr->employee << std::endl;
		displayInOrderWithLevel(nodePtr->right, level + 1);
	}
}


void BinaryTree::displayPostOrder(TreeNode *nodePtr)
{
	if (nodePtr)
	{
		displayPostOrder(nodePtr->left);
		displayPostOrder(nodePtr->right);
		std::cout << nodePtr->employee << std::endl;
	}
}

void BinaryTree::displayPreOrder(TreeNode *nodePtr)
{
	if (nodePtr)
	{
		std::cout << nodePtr->employee << std::endl;
		displayPreOrder(nodePtr->left);
		displayPreOrder(nodePtr->right);
	}
}

void BinaryTree::displayInOrder()
{
	displayInOrder(root);
}

void BinaryTree::displayInOrderWithLevel()
{
	displayInOrderWithLevel(root, 0);
}

void BinaryTree::displayPreOrder()
{
	displayPreOrder(root);
}

void BinaryTree::displayPostOrder()
{
	displayPostOrder(root);
}

std::string BinaryTree::search(int employeeId)
{
	TreeNode *nodePtr = root;
	EmployeeInfo employee;
	employee.setEmployeeId(employeeId);

	while (nodePtr)
	{
		if (nodePtr->employee == employee) {
			return nodePtr->employee.getEmployeeName();
		}	
		else if (employee < nodePtr->employee)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}

	return "Employee not found.";
}

void BinaryTree::deleteNode(EmployeeInfo employee, TreeNode *&nodePtr)
{
	if (employee < nodePtr->employee)
		deleteNode(employee, nodePtr->left);
	else if (employee > nodePtr->employee)
		deleteNode(employee, nodePtr->right);
	else
		makeDeletion(nodePtr);
}

void BinaryTree::makeDeletion(TreeNode *&nodePtr)
{
	// Define a temporary pointer to use in reattaching the left subtree
	TreeNode *tempNodePtr = nullptr;

	if (nodePtr == nullptr)
		std::cout << "Cannot delete an empty node" << std::endl;
	else if (nodePtr->right == nullptr) // reattach the left child
	{
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->left;
		delete tempNodePtr;
	}
	else if (nodePtr->left == nullptr) // reattach the right child
	{
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right;
		delete tempNodePtr;
	}
	// if the node has two children
	else
	{
		// move one node to the right.
		tempNodePtr = nodePtr->right;

		// Go to the end left node
		while (tempNodePtr->left)
			tempNodePtr = tempNodePtr->left;

		// reattach the left subtree
		tempNodePtr->left = nodePtr->left;
		tempNodePtr = nodePtr;

		// reattach the right subtree
		nodePtr = nodePtr->right;

		delete tempNodePtr;
	}
}

void BinaryTree::remove(int employeeId)
{
	EmployeeInfo employee;
	employee.setEmployeeId(employeeId);
	deleteNode(employee, root);
}