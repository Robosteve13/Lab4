//===============================================================================================//
//	BST.h - 											 //
//																								 //
//	
//																								 //
// Class:		EECS 2510 Nonlinear Data Structures												 //
// Project #3:	BST/AVL/RBT/SkipList Comparison 												 //
// Author:		Adam Savel																		 //
// Date:		Mar 17, 2018																	 //
//===============================================================================================//

#pragma once
#include "dataStructure.h"

class BST : public dataStructure
{
public:
	BST();
	~BST();
	void insert(char*);
	void list();
	int getHeight();
	int getDistinctKeys();
	int getTotalKeys();
	int getKeyComparisons();
	int getNodePointerUpdates();
	int getUpdates();

private:
	int keyComparisons;				//
	int nodePointerUpdates;			//
	int colorUpdates;				//

	struct BSTNode
	{
		BSTNode* leftChild;
		BSTNode* rightChild;
		char key[50];
		int count;
	};

	BSTNode* root;

	void inOrderDisplay(BSTNode*);
	int tGetHeight(BSTNode*);
	int tGetDistinctKeys(BSTNode*);
	int tGetTotalKeys(BSTNode*);
};

