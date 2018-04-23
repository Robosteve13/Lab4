//===============================================================================================//
//	BST.cpp - 
//																								 //
//	(Insert a description here)
//																								 //
// Class:		EECS 2510 Nonlinear Data Structures												 //
// Project #3:	BST/AVL/RBT/SkipList Comparison 												 //
// Author:		Adam Savel																		 //
// Date:		Mar 17, 2018																	 //
//===============================================================================================//

#include "stdafx.h"
#include "BST.h"
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

BST::BST()
{
	//	Constructor to iniviallize variables root as NULL.
	BST::keyComparisons = 0;
	BST::nodePointerUpdates = 0;

	BST::root = NULL;
}


BST::~BST()
{

}

void BST::insert(char* key)
{
	//	Returns 0 if the new key does not already exist within the tree. Returns 1 if the key
	// already exists within the tree. Returns -1 if failed to insert.

	BSTNode* x = root;				//	X and Y are used to keep track of our position in the tree
	BSTNode* y = NULL;				// as we traverse it.

	int cmp = 0;

	while (x != NULL)
	{
		y = x;
		cmp = strcmp(key, x->key);

		BST::keyComparisons++;

		if (cmp < 0) x = x->leftChild;
		else if (cmp > 0) x = x->rightChild;
		else
		{
			x->count++;
			return;
		}
	}

	// If the node is not found, create a new node with key value.
	BSTNode* z = new BSTNode();
	z->leftChild = NULL;
	z->rightChild = NULL;
	strcpy_s(z->key, key);
	z->count = 1;

	// If y is null, then the tree is empty and the root should point at the new node,
	if (y == NULL)
	{
		BST::root = z;
	}
	// Otherwise, set the new node as the appropriate child.
	else if (strcmp(z->key, y->key) < 0)
	{
		y->leftChild = z;
	}
	else
	{
		y->rightChild = z;
	}

	BST::nodePointerUpdates += 3;
	BST::keyComparisons++;

	return;
}

void BST::list()
{
	BST::inOrderDisplay(BST::root);
	return;
}

int BST::getHeight()
{
	return BST::tGetHeight(root);
}

int BST::getDistinctKeys()
{
	return BST::tGetDistinctKeys(root);
}

int BST::getTotalKeys()
{
	return BST::tGetTotalKeys(root);
}

int BST::getKeyComparisons()
{
	return BST::keyComparisons;
}

int BST::getNodePointerUpdates()
{
	return BST::nodePointerUpdates;
}

int BST::getUpdates()
{
	return 0;
}

void BST::inOrderDisplay(BSTNode* node)
{
	if (node->leftChild != NULL) BST::inOrderDisplay(node->leftChild);
	std::cout << node->key << " " << node->count << std::endl;
	if (node->rightChild != NULL) BST::inOrderDisplay(node->rightChild);
}

int BST::tGetHeight(BSTNode* node)
{
	if (node == NULL) return 0;

	int leftHeight = 0;
	int rightHeight = 0;

	if (node->leftChild != NULL) leftHeight = BST::tGetHeight(node->leftChild);
	if (node->rightChild != NULL) rightHeight = BST::tGetHeight(node->rightChild);

	if (leftHeight >= rightHeight) return leftHeight + 1;
	return rightHeight + 1;
}

int BST::tGetDistinctKeys(BSTNode* node)
{
	if (node == NULL) return -1;

	int leftNodes = 0;
	int rightNodes = 0;

	if (node->leftChild != NULL) leftNodes = BST::tGetDistinctKeys(node->leftChild);
	if (node->rightChild != NULL) rightNodes = BST::tGetDistinctKeys(node->rightChild);

	return leftNodes + rightNodes + 1;
}

int BST::tGetTotalKeys(BSTNode* node)
{
	if (node == NULL) return -1;

	int leftNodes = 0;
	int rightNodes = 0;

	if (node->leftChild != NULL) leftNodes = BST::tGetTotalKeys(node->leftChild);
	if (node->rightChild != NULL) rightNodes = BST::tGetTotalKeys(node->rightChild);

	return leftNodes + rightNodes + node->count;
}