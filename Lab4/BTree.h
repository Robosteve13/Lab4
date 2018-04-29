//===============================================================================================//
//	Btree.h - 																					 //
//																								 //
//	This file defines the structs, functions, and variables to be used in the B-Tree data		 //
// structure.  A B-Tree is a tree data structure like a BST.  However, it contains more than one //
// key (BSTs are actually B-Tree's with only one key).  Another difference is that the new nodes //
// are made by 'popping' them out of the top of the tree.  In this way, each leaf node remains at//
// the same height.																				 //
//																								 //
// Class:		EECS 2510 Nonlinear Data Structures												 //
// Project #4:	B-Tree/AVL Tree Disk Performance Comparison										 //
// Author:		Adam Savel																		 //
// Date:		Apr 23, 2018																	 //
//===============================================================================================//

#pragma once
#include "dataStructure.h"
#include <fstream>

#define BRANCHING_FACTOR 10

class BTree : public dataStructure
{
public:
	BTree();
	~BTree();

	// <See 'dataStructure.h' for greater details involving the public functions.>
	void insert(char*);
	void list();
	int getHeight();
	double getLoadingFactor();
	int getTotalNodes();
	int getFileSize();
	int getTotalReads();
	int getTotalWrites();

private:
	int nodeCount;				//	Needed Class-level variable are declared here.
	int readCount;				//
	int writeCount;				//
	std::fstream fileStream;	//

	//	Unlike a tree with only one key, B-Trees contain multiple keys.  For the B-Tree, structures
	// called BTData nodes are used.  Each contain a key (of 50 characters) and a count correspding
	// to that key.
	struct BTData
	{
		char key[50];			//	Because of the increased amount of parameters to set when
		int count = 0;			// creating nodes, default values are pre-set.
	};

	//	A BTNode needs to contain it's index (location in the disk), an identifier for whether or
	// not it is a leaf, a count of the number of keys it contains, an array of keys, and a an
	// array containing the locations of the children nodes as integers.
	struct BTNode
	{
		int index = NULL;
		bool leaf = true;
		int keyCount = 0;

		//	The code for B-Trees is all 1 indexed.  Because of this, one needs to be added to the
		//	sizes of each array to make room (as they are 0 indexed).
		BTData keys[2 * BRANCHING_FACTOR - 1 + 1];
		int children[2 * BRANCHING_FACTOR + 1];
	};

	BTNode rootNode;			//	Because the root node of a B-Tree will always be in memory, we
								// can declare the object here.
	int rootID;					//	An integer that holds the location of the root node on the disk

	//	As this is a disk based data structure, there needs to be a way of reading nodes off of the
	// disk.  This function takes an integer as a parameter and returns the data at that location
	// as a B-Tree node.
	BTNode diskRead(int);

	//	Likewise, there needs to be a way of writing data to the disk.  This function takes a node
	// and writes it to the disk.
	void diskWrite(BTNode&);

	//	For balancing, B-Trees utilize a split.  In a split, the current node is split into two.
	// Half of the keys stay in the current node, the other half go to the new node.  Finally a 
	// third node is made as the parent of the other two and the middle key from the original node
	// is placed in this root node.
	void splitChild(BTNode&, int);

	//	This function is called if the current node is found to not be entirely full.  It then
	// inserts the given char string into the proper place in the node.
	void insertNonFull(BTNode&, char*);

	//	For debugging purposes, this function traverses the B-Tree recursivly and prints out every
	// key to the console along with its count.
	void IOTraverse(BTNode);

	//	In order to calculate the loading factor, the number of keys in use needs to be found.  The
	// best way to do this is recursively. This function reads in a node and returns the key count
	// of the current node in addition to all of it's childrens key counts.
	int tGetKeyCount(BTNode);
};