//===============================================================================================//
//	.h - 											 //
//																								 //
//	
//																								 //
// Class:		EECS 2510 Nonlinear Data Structures												 //
// Project #3:	BST/AVL/RBT/SkipList Comparison 												 //
// Author:		Adam Savel																		 //
// Date:		Mar 17, 2018																	 //
//===============================================================================================//

#include "stdafx.h"
#include <iostream>
#include "RBT.h"

#define _CRT_SECURE_NO_WARNINGS

RBT::RBT()
{
	RBT::keyComparisons = 0;
	RBT::nodePointerUpdates = 0;
	RBT::colorUpdates = 0;

	RBT::NIL = new RBT::RBTNode();
	RBT::NIL->color = BLACK;
	RBT::NIL->count = 0;
	RBT::NIL->parent = RBT::NIL->leftChild = RBT::NIL->rightChild = RBT::NIL;


	for (int i = 0; i < 50; i++)
	{
		RBT::NIL->key[i] = '\0';
	}

	RBT::root = RBT::NIL;
}

RBT::~RBT()
{

}

void RBT::insert(char* key)
{
	//	Returns 0 if the new key does not already exist within the tree. Returns 1 if the key
	// already exists within the tree. Returns -1 if failed to insert.

	RBTNode* x = root;				//	X and Y are used to keep track of our position in the tree
	RBTNode* y = RBT::NIL;				// as we traverse it.

	int cmp = 0;

	//	*Block comment here.

	while (x != RBT::NIL)
	{
		y = x;
		cmp = strcmp(key, x->key);

		RBT::keyComparisons++;

		if (cmp < 0) x = x->leftChild;
		else if (cmp > 0) x = x->rightChild;
		else
		{
			x->count++;
			return ;
		}
	}

	// If the node is not found, create a new node with key value.
	RBTNode* z = new RBTNode();
	z->parent = RBT::NIL;
	z->leftChild = RBT::NIL;
	z->rightChild = RBT::NIL;
	strcpy_s(z->key, key);
	z->count = 1;

	RBT::nodePointerUpdates += 3;

	// If y is null, then the tree is empty and the root should point at the new node,
	if (y == RBT::NIL)
	{
		RBT::root = z;
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

	z->parent = y;

	RBT::nodePointerUpdates++;
	RBT::keyComparisons++;

	RBT::insertFixup(z);

	//RBT::prettyPrint(0, false, RBT::root);

	return;
}

void RBT::insertFixup(RBTNode* node)
{
	while (node->parent->color == RBT::RED)
	{
		if (node->parent == node->parent->parent->leftChild)
		{
			RBTNode* y = node->parent->parent->rightChild;
			if (y->color == RBT::RED)
			{
				node->parent->color = RBT::BLACK;
				y->color = RBT::BLACK;
				node->parent->parent->color = RBT::RED;
				RBT::colorUpdates += 3;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->rightChild)
				{
					node = node->parent;
					leftRotate(node);
				}
				node->parent->color = RBT::BLACK;
				node->parent->parent->color = RBT::RED;
				RBT::colorUpdates += 2;
				rightRotate(node->parent->parent);
			}
		}
		else
		{
			RBTNode* y = node->parent->parent->leftChild;
			if (y->color == RBT::RED)
			{
				node->parent->color = RBT::BLACK;
				y->color = RBT::BLACK;
				node->parent->parent->color = RBT::RED;
				RBT::colorUpdates += 3;
				node = node->parent->parent;
			}
			else 
			{
				if (node == node->parent->leftChild)
				{
					node = node->parent;
					rightRotate(node);
				}
				node->parent->color = RBT::BLACK;
				node->parent->parent->color = RBT::RED;
				RBT::colorUpdates += 2;
				leftRotate(node->parent->parent);
			}
		}
	}
	RBT::root->color = RBT::BLACK;
	RBT::colorUpdates++;
}

void RBT::leftRotate(RBTNode* node)
{
	RBT::RBTNode* y = node->rightChild;
	node->rightChild = y->leftChild;

	if (y->leftChild != RBT::NIL)
	{
		y->leftChild->parent = node;
		RBT::nodePointerUpdates++;
	}

	y->parent = node->parent;
	RBT::nodePointerUpdates++;

	if (node->parent == RBT::NIL)
	{
		RBT::root = y;
	}
	else if (node == node->parent->leftChild)
	{
		node->parent->leftChild = y;
	}
	else
	{
		node->parent->rightChild = y;
	}
	RBT::nodePointerUpdates++;

	y->leftChild = node;
	node->parent = y;

	RBT::nodePointerUpdates += 2;
}

void RBT::rightRotate(RBTNode* node)
{
	RBT::RBTNode* y = node->leftChild;
	node->leftChild = y->rightChild;

	if (y->rightChild != RBT::NIL)
	{
		y->rightChild->parent = node;
		RBT::nodePointerUpdates++;
	}

	y->parent = node->parent;
	RBT::nodePointerUpdates++;

	if (node->parent == RBT::NIL)
	{
		RBT::root = y;
	}
	else if (node == node->parent->rightChild)
	{
		node->parent->rightChild = y;
	}
	else
	{
		node->parent->leftChild = y;
	}
	RBT::nodePointerUpdates++;

	y->rightChild = node;
	node->parent = y;
	RBT::nodePointerUpdates += 2;
}

void RBT::list()
{
	RBT::inOrderDisplay(root);
	return;
}

int RBT::getHeight()
{
	return RBT::tGetHeight(root);
}

int RBT::getDistinctKeys()
{
	return RBT::tGetDistinctKeys(root);
}

int RBT::getTotalKeys()
{
	return RBT::tGetTotalKeys(root);
}

int RBT::getKeyComparisons()
{
	return RBT::keyComparisons;
}

int RBT::getNodePointerUpdates()
{
	return RBT::nodePointerUpdates;
}

int RBT::getUpdates()
{
	return RBT::colorUpdates;
}

void RBT::inOrderDisplay(RBTNode* node)
{
	if (node->leftChild != NIL) RBT::inOrderDisplay(node->leftChild);
	std::cout << node->key << " " << node->count << std::endl;
	if (node->rightChild != NIL) RBT::inOrderDisplay(node->rightChild);
}

int RBT::tGetHeight(RBTNode* node)
{
	if (node == NIL) return 0;

	int leftHeight = 0;
	int rightHeight = 0;

	if (node->leftChild !=NIL) leftHeight = RBT::tGetHeight(node->leftChild);
	if (node->rightChild != NIL) rightHeight = RBT::tGetHeight(node->rightChild);

	if (leftHeight >= rightHeight) return leftHeight + 1;
	return rightHeight + 1;
}

int RBT::tGetDistinctKeys(RBTNode* node)
{
	if (node == NIL) return -1;

	int leftNodes = 0;
	int rightNodes = 0;

	if (node->leftChild != NIL) leftNodes = RBT::tGetDistinctKeys(node->leftChild);
	if (node->rightChild != NIL) rightNodes = RBT::tGetDistinctKeys(node->rightChild);

	return leftNodes + rightNodes + 1;
}

int RBT::tGetTotalKeys(RBTNode* node)
{
	if (node == NIL) return -1;

	int leftNodes = 0;
	int rightNodes = 0;

	if (node->leftChild != NIL) leftNodes = RBT::tGetTotalKeys(node->leftChild);
	if (node->rightChild != NIL) rightNodes = RBT::tGetTotalKeys(node->rightChild);

	return leftNodes + rightNodes + node->count;
}

void RBT::prettyPrint(int indent, bool last, RBT::RBTNode* node)
{
	for (int i = 0; i < indent; i++)
	{
		std::cout << " ";
	}
	std::cout << "+-" << node->key << std::endl;

	if (node->leftChild != RBT::NIL) RBT::prettyPrint(indent + 1, false, node->leftChild);
	if (node->rightChild != RBT::NIL) RBT::prettyPrint(indent + 1, false, node->rightChild);
}