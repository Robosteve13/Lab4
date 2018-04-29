//===============================================================================================//
//	None.h - Defines a class in which all the functions do nothing.								 //
//																								 //
//	This class is used to give a base time performance for insertions.  Nothing is actually done //
// in this class.  Because of this, an idea of the time it takes to perform everything BUT the	 //
// actual insertion into a data structure can be measured.										 //
//																								 //
// Class:		EECS 2510 Nonlinear Data Structures												 //
// Project #4:	B-Tree/AVL Tree Disk Performance Comparison										 //
// Author:		Adam Savel																		 //
// Date:		Apr 23, 2018																	 //
//===============================================================================================//

#pragma once
#include "dataStructure.h";

class None : public dataStructure
{
public:
	None() { return; };
	~None() { return; };

	//	All the public methods defined here simply return back to the user nothing.  This class is
	// only used as a control group to set a baseline for comparing the other data structures.
	void insert(char*) { return; };
	void list() { return; };
	int getHeight() { return 0; };
	double getLoadingFactor() { return 0; };
	int getTotalNodes() { return 0; };
	int getFileSize() { return 0; };
	int getTotalReads() { return 0; };
	int getTotalWrites() { return 0; };
};

