//===============================================================================================//
//	AVL.cpp - Contains code definitions for the methods in the AVL class.						 //
//																								 //
//	This file defines the mfunctions of the AVL Tree class.  The main metric to be tested is the //
// insertion.  All metrics it returns to the caller of the public functions are based on the	 //
// insertion.  TTwo functions, 'diskRead' and 'diskWrite', store the nodes of the tree in a file //
// on the disk.  In this way, the performance of an AVL tree data structure based on disk		 //
// storage can be measured and compared to a B-Tree.											 //
//																								 //
// Class:		EECS 2510 Nonlinear Data Structures												 //
// Project #3:	BST/AVL/RBT/SkipList Comparison 												 //
// Author:		Adam Savel																		 //
// Date:		Mar 17, 2018																	 //
//===============================================================================================//

#include "stdafx.h"					//	
#include <iostream>					//	
#include "AVL.h"					//	AVL header file.
#include <fstream>					//	File I/O

#define _CRT_SECURE_NO_WARNINGS

AVL::AVL()
{
	//	AVL() - is the constructor for the AVL tree object.  In it, the initial values and
	// parameters are set.  In this case, the root is set to NULL since the tree is currently
	// empty.  It also opens the file stream to which the tree data will be written which is just a
	// file in the programs directory (kept in the same location where ever the program was
	// executed).

	writeCount = 0;
	readCount = 0;
	AVL::root = NULL;
	AVL::fileStream.open("AVLTree.data", std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
}

AVL::~AVL()
{
}

void AVL::insert(char* key)
{
	//	insert() - The public function that inserts a given character array into the AVL tree.  
	// If the tree is empty, a new root node is created.  Otherwise, the tree is traversed in order
	// to find the appropriate insert location of the new node.  If the key is found to already be
	// contained within the tree, a count parameter is incremented.  Otherwise, a new node is
	// created and attached.  Balance factors are adjusted and any necessary rotations are
	// performed.


	AVLNode node1, node2, node3;			//	Only three nodes will ever needed to be loaded
											// into memory in a single instance.

	int Y, A, B, F, P, Q, C = NULL, CL, CR;	//	Ints to hold node indecies for rotations.
											//	Y - New Node Index
											//	A - Last node with bF != 0
											//	B - first node of unbalanced branch under A
											//	F - A's parent
											//	P - Used for traversal
											//	Q - Follows one node behind P through traversal
											//	C - Child of B
											//	CL - Left child of C
											//	CR - Right child of C

	int d, cmp;								//	d - Balance factor adjustment variable
											//	cmp - Stores the result of a strcmp to reduce the
											// amount of compares needed
	
	//	If there is no root node, create a new node.  Set all the necessary parameters (key, root
	// index, nodecount) and save the node to the file.

	if (AVL::root == NULL)
	{
		node1 = AVLNode();
		strcpy_s(node1.key, key);
		AVL::root = 1;
		diskWrite(node1, root);
		nodeCount++;
		return;
	}

	F = Q = NULL;
	A = P = root;					//	Start P at the root to prepare for traversal.

	//	If there is already a root node, then we must find where in the tree to insert the key
	// provided.  If it is found to be in the tree already, then we increment the count parameter
	// by one.  This can be done by traversing the tree, comparing the given key to the key values
	// of the nodes in the tree.

	while (P != NULL)
	{
		node2 = diskRead(P);			//	Read the current node (P) from the disk.
		readCount++;
		cmp = strcmp(key, node2.key);	//	Get the compare result value.

		//	If cmp == 0, increment count parameter.
		if (cmp == 0)
		{
			node2.count++;
			diskWrite(node2, P);
			return;
		}

		//	If the balance factor of the current node is not equal to 0, then we need to remember
		// this nodes location and its parents location for use later in the rotations.

		if (node2.bF != 0)
		{
			A = P;
			F = Q;
		}

		//  If cmp < 0, go left through the tree.
		//	If cmp > 0, go right throught the tree.
		if (cmp < 0)
		{
			Q = P;
			P = node2.leftChild;
		}
		if (cmp > 0)
		{
			Q = P;
			P = node2.rightChild;
		}
	}

	strcpy_s(node1.key, key);		//	Create and allocate a new node to the disk.
	nodeCount++;					//
	diskWrite(node1, nodeCount);	//
	Y = nodeCount;					//

	node3 = diskRead(Q);			//	Q holds the last node we reached while traversing the tree.
	readCount++;					// Read that node from memory so that it's data can be changed.

	//	Attach the new node as a child to the proper node, maintaining the BST property.
	if (strcmp(key, node3.key) < 0)	node3.leftChild = Y;
	else							node3.rightChild = Y;

	diskWrite(node3, Q);			//	Save changes to the child node.
	node3 = diskRead(A);			//	Read in the node where bF was != 0 (node A).
	readCount++;

	//	Determine whether or not the imbalance occurs in A's left or right subtree.  Set B and P
	// (for iteration) to the root of this subtree.  Set d to the expected change in the balance
	// factor.
	
	if (strcmp(key, node3.key) > 0)
	{
		B = P = node3.rightChild;
		d = -1;
	}
	else
	{
		B = P = node3.leftChild;
		d = 1;
	}

	//	Next, we need to adjust the balance factors following A until we reach the new node
	// inserted.  For each value of P, read the node from the disk.  If we go right, set the 
	// balance factor to -1, otherwise set it to 1.  Save changes and continue down the tree.

	while (P != Y)
	{
		node2 = diskRead(P);
		readCount++;
		if (strcmp(key, node2.key) > 0)
		{
			node2.bF = -1;			
			diskWrite(node2, P);	
			P = node2.rightChild;	
		}
		else
		{
			node2.bF = 1;		
			diskWrite(node2, P);
			P = node2.leftChild;
		}
	}

	//	If adding a new node balances the subtree A or causes it to become unbalanced by |1|, then
	// B's bF can be updated and saved without any rotations needed.

	if (node3.bF == 0)
	{
		node3.bF = d;
		diskWrite(node3, A);
		return;
	}
	
	if (node3.bF == -d)
	{
		node3.bF = 0;
		diskWrite(node3, A);
		return;
	}

	//	If we've made it this far, we need to perform a rotation.  In order to perform a rotation,
	// the nodes at A, B, and C are needed.  Node1 = C, Node2 = B, Node3 = A.  In order to
	// determine the needed rotation, the variable and the balance factor of node B are checked.

	// If d == 1 and B.bF == 1, then the imbalance occured in the left-left node.
	// If d == 1 and B.bF == -1, then the imbalance occured in the left-right node.
	// If d == -1 and B.bF == 1, then the imbalance occured in the right-right node.
	// If d == -1 and B.bF == -1, then the imbalance occured in the right-left node.

	//	After the rotation, F, A's parent, is repointed at the correct node.

	node2 = diskRead(B);
	readCount++;

	if (d == 1)
	{
		if (node2.bF == 1)
		{
			//	Left-left rotation
			// Change the child pointers at A and B to reflect the rotation.  Adjust the bFs at A
			// and B.
			node3.leftChild = node2.rightChild;
			node2.rightChild = A;
			node2.bF = 0;
			node3.bF = 0;
		}
		else
		{
			//	Left-right rotation
			// Adjust the child pointers of nodes A, B, & C to reflect the new post-rotation
			// structure.
			C = node2.rightChild;	//	C is B's right child.
			diskWrite(node1, Y);	//	CL and CR are C's left and right children respectively
			node1 = diskRead(C);
			readCount++;
			CL = node1.leftChild;
			CR = node1.rightChild;
			
			node3.leftChild = CR;
			node2.rightChild = CL;
			node1.leftChild = B;
			node1.rightChild = A;

			//	Set the new bF's at A and B, based on the bF at C.  There are 3 sub-cases.
			switch (node1.bF)
			{
			case -1:
				node3.bF = 0;
				node2.bF = 1;
				break;
			case 0:
				node3.bF = 0;
				node2.bF = 0;
				break;
			case 1:
				node3.bF = -1;
				node2.bF = 0;
				break;
			}

			//	Regardless, C is now balanced.  B is the rood of the now rebalanced subtree.
			node1.bF = 0;
			diskWrite(node2, B);
			diskWrite(node1, C);
			B = C;
			node2 = node1;
		}
	}
	else
	{
		if (node2.bF == -1)
		{
			//	Right-right rotation
			// Change the child pointers at A and B to reflect the rotation.  Adjust the bFs at A
			// and B.
			node3.rightChild = node2.leftChild;
			node2.leftChild = A;
			node2.bF = 0;
			node3.bF = 0;
		}
		else
		{
			//	Right-left rotation
			// Adjust the child pointers of nodes A, B, & C to reflect the new post-rotation
			// structure.
			C = node2.leftChild;	//	C is B's right child.
			diskWrite(node1, Y);	//	CL and CR are C's left and right children respectively
			node1 = diskRead(C);
			readCount++;
			CL = node1.leftChild;
			CR = node1.rightChild;

			node3.rightChild = CL;
			node2.leftChild = CR;
			node1.leftChild = A;
			node1.rightChild = B;

			//	Set the new bF's at A and B, based on the bF at C.  There are 3 sub-cases.
			switch (node1.bF)
			{
			case -1:
				node3.bF = 1;
				node2.bF = 0;
				break;
			case 0:
				node3.bF = 0;
				node2.bF = 0;
				break;
			case 1:
				node3.bF = 0;
				node2.bF = -1;
				break;
			}

			//	Regardless, C is now balanced.  B is the rood of the now rebalanced subtree.
			node1.bF = 0;
			diskWrite(node2, B);
			diskWrite(node1, C);
			B = C;
			node2 = node1;
		}
	}

	// Regardless, the subtree rooted at B has been rebalanced, and needs to
	// be the new child of F.  The original subtree of F had root A.


	if (F == NULL)
	{
		root = B;
		if (B != C)
		{
			diskWrite(node1, Y);
		}
		diskWrite(node2, B);
		diskWrite(node3, A);
		return;
	}

	//	This step was added to save the necessary changes in the event that node Y, which is
	// contained in node1 was not saved.  This occurs when anything other than a right-left or
	// left-rotation is performed and B is set to C.
	if (B != C)
	{
		diskWrite(node1, Y);
	}
	node1 = diskRead(F);
	readCount++;

	// The root of what we rebalanced WAS A; now it’s B.  If the subtree we
	// rebalanced was LEFT of F, then B needs to be left of F;
	// if A was RIGHT of F, then B now needs to be right of F.
	if (A == node1.leftChild)
	{
		diskWrite(node2, B);
		diskWrite(node3, A);
		node1.leftChild = B;
		diskWrite(node1, F);
		return;
	}
	if (A == node1.rightChild)
	{
		diskWrite(node2, B);
		diskWrite(node3, A);
		node1.rightChild = B;
		diskWrite(node1, F);
		return;
	}

	//	As before, node1 needs to be saved in the case a right-left or left-right rotation is not
	// performed.
 	if (B != C)
	{
		diskWrite(node1, Y);
	}

	diskWrite(node2, B);			// Save and exit
	diskWrite(node3, A);
	return;
}

void AVL::list()
{
	//	list() - a public function that displays, in order, every item contained within the tree.
	// This is implemented in a private recursive function that traverses the tree.

	//	Recursive traversal starting at the root.
	AVL::inOrderDisplay(diskRead(root));
	return;
}

int AVL::getHeight()
{
	//	getHeight() - is apublic function that returns the current height of the tree.

	//	Finding the height is done using the recursive function that returns the height of a given
	// node's subtree.  Thus, by starting at the root, the height of the full tree will be returned
	return AVL::tGetHeight(diskRead(root));
}

double AVL::getLoadingFactor()
{
	//	getLoadingFactor() - is a public function that returns the loading factor.  That is, the
	// proportion of available keys to keys in use.  Because there is only one key per node, the
	// loading factor will always be one.

	return 1.00;
}

int AVL::getTotalNodes()
{
	//	getTotalNodes() - is a public function that returns the number of nodes currently within
	// the tree.

	//	Because the number of nodes must be monitored for saving new nodes to the file, the
	// nodeCount-er must be correct for the tree to work properly.  Thus we can just return the
	// nodeCount.
	return nodeCount;
}

int AVL::getFileSize()
{
	//	getFileSize() - is a public function that returns the current file size of the stored tree.

	//	To read the filesize, we just need to read the offset of the last byte in the file.
	fileStream.seekg(0, std::ios::end);		//	Seek to the last byte in the file
	return (fileStream.tellg() / 1024);		//	Return the position value in kiloBytes
}

int AVL::getTotalReads()
{
	//	getTotalReads() - is a public function that returns the number of times a disk read was
	// performed.  Since this is kept track in the code, all that's needed is to return the
	// variable value.
	return readCount;
}

int AVL::getTotalWrites()
{
	//	getTotalWrites() is a public function taht returns the number of times a disk write was
	// performed. Since this is kept track in the code, all that's needed is to return the
	// variable value.
	return writeCount;
}

void AVL::inOrderDisplay(AVLNode node)
{
	//	inOrderDisplay() - is a private function that prints out every key, in value order, into
	// the console.  It does this using recursion.  The function takes a node as a parameter. First
	// it displays the node's left children.  Then it displays the current node's key.  Finally, it
	// displays the node's right children.

	if (node.leftChild != NULL) AVL::inOrderDisplay(diskRead(node.leftChild));
	std::cout << node.key << " " << node.count << std::endl;
	if (node.rightChild != NULL) AVL::inOrderDisplay(diskRead(node.rightChild));
}

int AVL::tGetHeight(AVLNode node)
{
	//	tGetHeight() - is a recursive function that traverses the tree, keeping track of the height
	// of the nodes that is has passed through.

	//	If the function was handed NULL (nothing) return 0 since nothing was here.
	if (&node == NULL) return 0;

	int leftHeight = 0;				//	Initialize the subtree heights.
	int rightHeight = 0;

	//	Recursively get the heights of both the left and right subtrees.
	if (node.leftChild != NULL) leftHeight = AVL::tGetHeight(diskRead(node.leftChild));
	if (node.rightChild != NULL) rightHeight = AVL::tGetHeight(diskRead(node.rightChild));

	//	Return the height of whichever was taller (plus one for the current node).
	if (leftHeight >= rightHeight) return leftHeight + 1;
	return rightHeight + 1;
}

AVL::AVLNode AVL::diskRead(int nodeInd)
{
	//	diskRead() - is a private function that reads the node at the index given and returns the
	// read node.  The input parameter, rather than defining a specific location, specifies an
	// index which is then interpreted as a location by multiplying it by the size of aa AVL node.

	AVLNode loadedNode = AVLNode();

	//	Seek to the specified location.
	fileStream.seekg((nodeInd - 1) * sizeof(loadedNode));

	//	From the location, read the next amount of bytes equal in size the an AVL node.
	fileStream.read((char*)&loadedNode, sizeof(loadedNode));

	return loadedNode;

	//	Note: the reason readCount is not incremented within this function is because other
	// functions than insert utilize the diskRead function.  This would, in turn, mess up the
	// results.
}

void AVL::diskWrite(AVL::AVLNode node, int nodeInd)
{
	//	diskWrite() - is a private function that writes a given node to the index specified in the
	// storage file.  The input parameter, rather than defining a specific location, specifies an
	// index which is then interpreted as a location by multiplying it by the size of aa AVL node.

	if (nodeInd <= 0) return;		//	Safety check
	writeCount++;					//	To keep track of the amount of writes.

	//	Seek to the specified location.
	fileStream.seekp((nodeInd - 1) * sizeof(node));

	//	Write to the file and clear the cache of the file stream.
	fileStream.write((char*)&node, sizeof(node));
	fileStream.flush();
	return;
}