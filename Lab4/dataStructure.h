//===============================================================================================//
//	dataStructure.h - Header file for the dataStructure object.									 //
//																								 //
//	This file contains the class definition for a dataStructure object.  In this way, the same	 //
// code can be used to test each of the dataStructure objects (BSTs, AVL Trees, etc.) by simply	 //
// changing the instantiated object.															 //
//																								 //
// Class:		EECS 2510 Nonlinear Data Structures												 //
// Project #3:	BST/AVL/RBT/SkipList Comparison 												 //
// Author:		Adam Savel																		 //
// Date:		Mar 17, 2018																	 //
//===============================================================================================//

#pragma once
#include "stdafx.h"
#include "string.h"

class dataStructure
{
public:
	virtual void insert(char*) = 0;

	virtual void list() = 0;
	virtual int getHeight() = 0;
	virtual int getDistinctKeys() = 0;
	virtual int getTotalKeys() = 0;
	virtual int getTotalReads() = 0;
	virtual int getTotalWrites() = 0;
};
