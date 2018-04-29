//===============================================================================================//
//	AVL.h											 											 //
//																								 //
//	This header file defines the structs, functions, and class level variables needed for an AVL //
// tree.  An AVL tree is a type of balanced Binary Search Tree.  It implements a new property to //
// each node in the tree called the 'balance factor'.  This factor is set depending on the		 //
// lopsided-ness of the node's children subtrees.  When this factor exceeds preset limitations	 //
// (in this case |1|) the nodes causing the imbalance are shifted in rotations.					 //
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
	int root;					//	Unlike ram based data structures, the root is now an integer
								// that holds the location on the disk of the root node.

	int	nodeCount;				//	Needed class-level variables are declared here.
	int writeCount;				//	
	int readCount;				//
	std::fstream fileStream;	//	The file stream is declared here.

	//	An AVL node needs to contain a left right child 'pointer', in this case an int defining the
	// location on the disk of the child node.  Much like a BST, an AVL node also needs a key and
	// a count of that key.  Unlike a BST, an AVL node also needs a variable for keeping track of 
	// the balance factor.

	struct AVLNode
	{
		int leftChild = NULL;
		int rightChild = NULL;
		char key[50];
		int count = 1;
		char bF = 0;
	};

	//	There needs to be some way of reading nodes from the disk.  This method is given an integer
	// corresponding to a location on the disk.  It then returns the data stored at that location
	// as an AVL node.
	AVLNode diskRead(int);

	//	Likewise, there needs to be some way of writing nodes to the disk.  This method is given
	// both an AVL node and an integer.  The AVL node will then be written to the disk at the 
	// location specified by the integer.
	void diskWrite(AVLNode, int);

	//	For debugging purposes, this method is to be implemented.  When called, it traverses the 
	// tree, displaying every key in value order.
	void inOrderDisplay(AVLNode);

	//	In order to obtain the height of the tree, a traversal is to be used.  This function then
	// allows for a recursive traversal.  It returns an integer which is the subtree's (which it
	// just traversed) height in the tree.  In this way, when the first call returns, the height
	// of the full tree will be given.  This method is to be called by the corresponding public
	// function for security purposes.
	int tGetHeight(AVLNode);
};

