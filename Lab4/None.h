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
#include "dataStructure.h";

class None : public dataStructure
{
public:
	None() { return; };
	~None() { return; };
	void insert(char*) { return; };
	void list() { return; };
	int getHeight() { return 0; };
	int getDistinctKeys() { return 0; };
	int getTotalKeys() { return 0; };
	int getTotalReads() { return 0; };
	int getTotalWrites() { return 0; };
};

