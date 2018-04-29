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
	//	In order to test the performance of disk based tree insertions, the following public
	// methods are necessary.  Insert, of course, to insert a given key into the data structure.
	// The other functions return performance data collected during insertion.
public:
	//	The purpose of this lab is to test the performance of disk based insertions from with
	// different data structures.  It would follow, then, that a public function for inserting
	// items into the structure would be necessary.  Insert() takes a char array as input (which
	// is what will be used as the key for each node).  Nothing is returned.
	virtual void insert(char*) = 0;

	//	Mostly for debugging purposes, the list() function is to be implemented.  It goes through
	// the data structure, displaying each nodes key in order.  Nothing is returned to the user.
	// The list is printed to the console.
	virtual void list() = 0;
	
	//	In order to get information regarding the height of the tree implemented, the function
	// 'getHeight()' is to be implemented.  This function is to return the height of the data
	// structure to the user.
	virtual int getHeight() = 0;
	
	//	One of the performance metrics in which the B-Trees in this lab are to be measured is by
	// how full each of it's nodes are.  The loading factor for AVL trees will always be 100%.
	// The function is to return a double which is a percentage of how full the data structure is.
	virtual double getLoadingFactor() = 0;
	
	//	The total number of nodes per data structure is also to be used as a performance metric for
	// comparing each of the data structures.  This method is to return the number of nodes within
	// the currernt data structure.
	virtual int getTotalNodes() = 0;

	//	The amount of space each structure takes up will also be used as a performance metric. When
	// this function is called, it returns the size (in KiloBytes) the size of the file produced by
	// the data structure.
	virtual int getFileSize() = 0;
	
	//	In order to obtain the total number of reads performed throughout the series of insertions,
	// the following function is to be implemented.  It returns to the user the total number of
	// reads performed on the disk thus far.
	virtual int getTotalReads() = 0;
	
	//	In order to obtain the total number of writes performed throughout the series of insertions,
	// the following function is to be implemented.  It returns to the user the total number of
	// writes performed on the disk thus far.
	virtual int getTotalWrites() = 0;
};
