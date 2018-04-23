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
#include <fstream>

class AVL : public dataStructure
{
public:
	AVL();
	~AVL();
	void insert(char*);
	void list();
	int getHeight();
	int getDistinctKeys();
	int getTotalKeys();
	int getTotalReads();
	int getTotalWrites();

private:
	int nodeCount;
	std::fstream fileStream;

	struct AVLNode
	{
		int leftChild = NULL;
		int rightChild = NULL;
		char key[50];
		int count = 1;
		char bF = 0;
	};

	int root;

	AVLNode diskRead(int);
	void diskWrite(AVLNode, int);

	void inOrderDisplay(AVLNode);
	int tGetHeight(AVLNode);
	int tGetTotalKeys(AVLNode);
};

