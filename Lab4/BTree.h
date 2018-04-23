//===============================================================================================//
//	.h - 											 //
//																								 //
//	
//																								 //
// Class:		EECS 2510 Nonlinear Data Structures												 //
// Project #4:	B-Tree/AVL Tree Disk Performance Comparison										 //
// Author:		Adam Savel																		 //
// Date:		Apr 23, 2018																	 //
//===============================================================================================//

#pragma once
#include "dataStructure.h"
#include <fstream>

class BTree
{
public:
	BTree();
	~BTree();
	void insert(char*);
	void list();
	int getHeight();
	int getDistinctKeys();
	int getTotalKeys();
	int getTotalReads();
	int getTotalWrites();

private:
	int root;
	int nodeCount;
	std::fstream fileStream;

	struct BTNode
	{

	};

	BTNode diskRead(int);
	void diskWrite(BTNode, int);
};