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

#include "stdafx.h"
#include <iostream>
#include "AVL.h"
#include <fstream>

#define _CRT_SECURE_NO_WARNINGS

AVL::AVL()
{
	AVL::root = NULL;
	AVL::fileStream.open("AVLTree.data", std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
}

AVL::~AVL()
{
	AVL::fileStream.close();
}

void AVL::insert(char* key)
{
	AVLNode node1, node2, node3;
	int Y, A, B, F, P, Q, C = NULL, CL, CR;
	int d, cmp;
	

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
	A = P = root;

	// A is last node with a balance factor > or < 0
	// F is A's parent
	while (P != NULL)
	{
		node2 = diskRead(P);
		cmp = strcmp(key, node2.key);

		if (cmp == 0)
		{
			node2.count++;
			diskWrite(node2, P);
			return;
		}
		
		if (node2.bF != 0) 
		{
			A = P;
			F = Q;
		}
		
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

	node1;
	strcpy_s(node1.key, key);
	nodeCount++;
	diskWrite(node1, nodeCount);
	Y = nodeCount;

	node3 = diskRead(Q);

	if (strcmp(key, node3.key) < 0)	node3.leftChild = nodeCount;
	else							node3.rightChild = nodeCount;

	diskWrite(node3, Q);
	node3 = diskRead(A);

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

	while (P != Y)
	{
		node2 = diskRead(P);
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

	node2 = diskRead(B);

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

	if (d == 1)
	{
		if (node2.bF == 1)
		{
			node3.leftChild = node2.rightChild;
			node2.rightChild = A;
			node2.bF = 0;
			node3.bF = 0;
		}
		else
		{
			C = node2.rightChild;
			diskWrite(node1, Y);
			node1 = diskRead(C);
			CL = node1.leftChild;
			CR = node1.rightChild;
			
			node3.leftChild = CR;
			node2.rightChild = CL;
			node1.leftChild = B;
			node1.rightChild = A;

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
			node3.rightChild = node2.leftChild;
			node2.leftChild = A;
			node2.bF = 0;
			node3.bF = 0;
		}
		else
		{
			//if (AVL::root != NULL) AVL::prettyPrint(0, false, AVL::root);
			C = node2.leftChild;
			diskWrite(node1, Y);
			node1 = diskRead(C);
			CL = node1.leftChild;
			CR = node1.rightChild;

			node3.rightChild = CL;
			node2.leftChild = CR;
			node1.leftChild = A;
			node1.rightChild = B;

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

			node1.bF = 0;
			diskWrite(node2, B);
			diskWrite(node1, C);
			B = C;
			node2 = node1;
		}
	}

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

	if (B != C)
	{
		diskWrite(node1, Y);
	}
	node1 = diskRead(F);

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

 	if (B != C)
	{
		diskWrite(node1, Y);
	}
	diskWrite(node2, B);
	diskWrite(node3, A);
	return;
}

void AVL::list()
{
	AVL::inOrderDisplay(diskRead(root));
	return;
}

int AVL::getHeight()
{
	return AVL::tGetHeight(diskRead(root));
}

int AVL::getDistinctKeys()
{
	return nodeCount;
}

int AVL::getTotalKeys()
{
	return AVL::tGetTotalKeys(diskRead(root));
}

void AVL::inOrderDisplay(AVLNode node)
{
	if (node.leftChild != NULL) AVL::inOrderDisplay(diskRead(node.leftChild));
	std::cout << node.key << " " << node.count << std::endl;
	if (node.rightChild != NULL) AVL::inOrderDisplay(diskRead(node.rightChild));
}

int AVL::tGetHeight(AVLNode node)
{
	if (&node == NULL) return 0;

	int leftHeight = 0;
	int rightHeight = 0;

	if (node.leftChild != NULL) leftHeight = AVL::tGetHeight(diskRead(node.leftChild));
	if (node.rightChild != NULL) rightHeight = AVL::tGetHeight(diskRead(node.rightChild));

	if (leftHeight >= rightHeight) return leftHeight + 1;
	return rightHeight + 1;
}

int AVL::tGetTotalKeys(AVLNode node)
{
	if (&node == NULL) return -1;

	int leftNodes = 0;
	int rightNodes = 0;

	if (node.leftChild != NULL) leftNodes = AVL::tGetTotalKeys(diskRead(node.leftChild));
	if (node.rightChild != NULL) rightNodes = AVL::tGetTotalKeys(diskRead(node.rightChild));

	return leftNodes + rightNodes + node.count;
}

int AVL::getTotalReads()
{
	return 0;
}

int AVL::getTotalWrites()
{
	return 0;
}

AVL::AVLNode AVL::diskRead(int nodeInd)
{
	AVLNode loadedNode = AVLNode();

	fileStream.seekg((nodeInd - 1) * sizeof(loadedNode));
	fileStream.read((char*)&loadedNode, sizeof(loadedNode));

	return loadedNode;
}

void AVL::diskWrite(AVL::AVLNode node, int nodeInd)
{
	if (nodeInd < 0) return;
	fileStream.seekp((nodeInd - 1) * sizeof(node));
	fileStream.write((char*)&node, sizeof(node));
	return;
}