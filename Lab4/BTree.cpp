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

#include "stdafx.h"
#include "BTree.h"


BTree::BTree()
{
	root = NULL;
	nodeCount = 0;
	fileStream.open("BTree.data");
}


BTree::~BTree()
{
}

void BTree::insert(char*)
{

}

void BTree::list()
{

}

int BTree::getHeight()
{
	return 0;
}

int BTree::getDistinctKeys()
{
	return 0;
}

int BTree::getTotalKeys()
{
	return 0;
}

int BTree::getTotalReads()
{
	return 0;
}

int BTree::getTotalWrites()
{
	return 0;
}