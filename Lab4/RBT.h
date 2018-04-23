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

#pragma once
#include "dataStructure.h"

class RBT : public dataStructure
{
public:
	RBT();
	~RBT();
	void insert(char*);
	void list();
	int getHeight();
	int getDistinctKeys();
	int getTotalKeys();
	int getKeyComparisons();
	int getNodePointerUpdates();
	int getUpdates();

private:
	enum RBT_COLOR
	{
		RED = 0,
		BLACK
	};

	int keyComparisons;				//
	int nodePointerUpdates;			//
	int colorUpdates;				//

	struct RBTNode
	{
		RBTNode* parent;
		RBTNode* leftChild;
		RBTNode* rightChild;
		char key[50];
		int count = 1;
		RBT_COLOR color = RED;
	};

	RBTNode* root;
	RBTNode* NIL;

	//int traverse(RBTNode*);
	void insertFixup(RBTNode*);
	void leftRotate(RBTNode*);
	void rightRotate(RBTNode*);

	void inOrderDisplay(RBTNode*);
	int tGetHeight(RBTNode*);
	int tGetDistinctKeys(RBTNode*);
	int tGetTotalKeys(RBTNode*);

	void prettyPrint(int, bool, RBTNode*);
};

