//===============================================================================================//
//	Trees.cpp - Conatins the entry point of the trees program.									 //
//																								 //
//	This file is the entry point of the program written for Project #4, the study of B-Trees.	 //
// the goal of this project is to compare the performance of two nonlinear data structures that  //
// are disk based.  These two structures are AVL Trees and B-Trees.								 //
//																								 //
//	This is accomplished by reading through a number of files of varying sizes, storing each	 //
// individual word into either a B-Tree or AVL Tree which is, in turn, stored on the disk. There //
// are several performance metrics which are reported and recorded to an excel file.  These		 //
// include the number of times a node is read from a file, the number of times a node is written //
// to a file, and the time to read through the entire file.										 //
//																								 //
// Class:		EECS 2510 Nonlinear Data Structures												 //
// Project #4:	B-Tree/AVL Tree Disk Performance Comparison										 //
// Author:		Adam Savel																		 //
// Date:		Apr 23, 2018																	 //
//===============================================================================================//

#include "stdafx.h"					//
#include "BTree.h"
#include "AVL.h"					//	AVL Header file
#include "None.h"					//	A 'NONE' Data structure as control metric
#include <iostream>					//	Console I/O
#include <fstream>					//	File I/O
#include <ctime>					//	Time
#define _CRT_SECURE_NO_WARNINGS

//	Easy-access file path for general case runs
#define INPUT_FILE "C:\\Users\\Adam\\Desktop\\TestFiles\\All.txt"

//	Easy-access file paths for the thorough testing for the report
#define INPUT_FILE1 "C:\\Users\\Adam\\Desktop\\TestFiles\\Green Eggs and Ham.txt"
#define INPUT_FILE2 "C:\\Users\\Adam\\Desktop\\TestFiles\\A Bee Movie Script.txt"
#define INPUT_FILE3 "C:\\Users\\Adam\\Desktop\\TestFiles\\Hamlet.txt"
#define INPUT_FILE4 "C:\\Users\\Adam\\Desktop\\TestFiles\\To Kill a Mockingbird - Harper Lee.txt"
#define INPUT_FILE5 "C:\\Users\\Adam\\Desktop\\TestFiles\\The Hunchback of Notre Dame - Hugo.txt"
#define INPUT_FILE6 "C:\\Users\\Adam\\Desktop\\TestFiles\\Anna Karenina - Tolstoy.txt"
#define INPUT_FILE7 "C:\\Users\\Adam\\Desktop\\TestFiles\\War and Peace.txt"
#define INPUT_FILE8 "C:\\Users\\Adam\\Desktop\\TestFiles\\King James Bible.txt"
#define INPUT_FILE9 "C:\\Users\\Adam\\Desktop\\TestFiles\\Shakespeare.txt"
#define INPUT_FILE10 "C:\\Users\\Adam\\Desktop\\TestFiles\\Green Eggs and Ham.txt"

//	Output file path for data collection
#define OUTPUT_FILE "C:\\Users\\Adam\\Desktop\\TestFiles\\OutputBTBF10.csv"

//	In order to make running the different data structure tests easier and more readable, an enum
// is used as the selector for each data structure.
enum DATA_STRUCTURE
{
	NONE = 0,
	AVLTree,
	BT
};

void heightChecker(DATA_STRUCTURE);
void fileParser(DATA_STRUCTURE, const char*, int);
void writeToFile(std::ofstream& output);
void performanceChecker(DATA_STRUCTURE);

//	So that the data could be saved into the file in the correct order, several arrays are used as
// an intermediary or temporary storage point.  Once the ten runs have been made for the given data
// structure, the data in each of the arrays is saved to the output file.  In this way, the data
// for each structure is kept together and maintains readability.

const char *files[] = { INPUT_FILE1, INPUT_FILE2, INPUT_FILE3, INPUT_FILE4, INPUT_FILE5, INPUT_FILE6, INPUT_FILE7, INPUT_FILE8, INPUT_FILE9, INPUT_FILE10 };
int heights[10];
double loadingFactors[10];
int totalNodes[10];
int fileSizes[10];
int totalReads[10];
int totalWrites[10];
double times[10];

std::clock_t start;
std::clock_t end;

int main()
{
	//	main() - defines the entry point of the 'trees' program.  From main, the appropriate data
	// structure test can be run.  There are three tests currently programmed.  A height checker
	// tool, a performance checker which tests each data structure ten times, and a single-use file
	// parser.

	char c;

	//	Uncomment to run the height checker.
	//	Mainly used for DEBUG purposes.
	//heightChecker(AVLTree);
	//heightChecker(BT);

	//	Uncomment to run the complete performance checker.
	//performanceChecker(BT);
	//performanceChecker(AVLTree);

	//  Uncomment to run single-use file parser with specified input file.
	//fileParser(NONE, INPUT_FILE, 0);
	//fileParser(AVLTree, INPUT_FILE, 0);
	fileParser(BT, INPUT_FILE, 0);

	//	Prevents program from closing immediately so that run data can be viewed.
	std::cout << "\n\nPress to exit continue program.\n"; std::cin.get(c);
	return 0;
}

void heightChecker(DATA_STRUCTURE ds)
{
	//	heightChecker() - basic insertion test for a given data structure.  Takes a single 
	// parameter which defines the data structure to be used.  This method outputs the results to
	// the console which include a list of all the words, height, word counts, comparisons, pointer
	// updates, and any other updates.

	dataStructure* testStructure;

	//	chari instantiator taken directly from assignment document.
	char chari[10];
	for (int i = 0; i<10; i++) chari[i] = '\0';

	//	Switch statement with a case for each of the data structure types.  For each case,
	// instantiate the appropriate data structure object, print out the data structure name, and
	// insert 3000 different characters.  Code for the 'for loops' taken directly from assignment
	// document modified only to be compatible with written functions.

	switch (ds)
	{
	case BT:
		testStructure = new BTree();
		for (int i = 1001; i <= 2000; i++) // insert 2000 strings in BT
		{
			sprintf_s(chari, "%4i", i);
			testStructure->insert(chari);
		}
		break;
	case AVLTree:
		testStructure = new AVL();
		for (int i = 1001; i <= 3000; i++) // insert 2000 strings in AVL
		{
			sprintf_s(chari, "%4i", i);
			testStructure->insert(chari);
		}
		break;
	case NONE:						//	In the case that the user selects 'NONE' as the data
	default:						// structure, return with no data.
		return;
		break;
	}

	//	Listing used for DEBUG purposes.  Uncomment to view.
	//testStructure->list();

	//	Output the run results.
	std::cout << "Height: " << testStructure->getHeight() << std::endl;
	std::cout << "Loading Factor: " << testStructure->getLoadingFactor() << std::endl;
	std::cout << "Total Nodes: " << testStructure->getTotalNodes() << std::endl;
	std::cout << "File Size: " << testStructure->getFileSize() << " kBytes" << std::endl;
	std::cout << "Total Reads: " << testStructure->getTotalReads() << std::endl;
	std::cout << "Total Writes: " << testStructure->getTotalWrites() << std::endl;
}

void fileParser(DATA_STRUCTURE ds, const char* inputFile, int arrayPos)
{
	//	fileParser() - reads a given input file, inserting each word into the data structure
	// specified.  Takes 3 parameters:
	//
	//	'DATA_STRUCTURE ds'		- specifies the data structure to use.
	//	'const char* inputFile' - specifies the file path of the file to be parsed.
	//	'int arrayPos'			- determines where to store the retrieved data in the data arrays.
	//
	// The function first instantiates the appropriate data structure.  It then opens the given
	// input file, parsing it into individual words.  Each word then gets inserted into the data
	// structure.  This process of reading the file, parsing, and inserting is timed.  Finally, run
	// data is saved in the data arrays and output to the console.

	char c;
	dataStructure* testStructure;

	//	Switch statement to instantiate the specified data structure.  For the 'NONE' and default
	// case, an object containing only empty functions is instantiated.  In this way, the same code
	// can be used for every run, thus reducing variability in results.

	switch (ds)
	{
	case AVLTree:
		testStructure = new AVL();
		break;
	case BT:
		testStructure = new BTree();
		break;
	case NONE:
	default:
		testStructure = new None();
		break;
	}

	//  The parsing code shown below is copied directly from the assignment sheet.  The differences
	// include a typo fix for the while loop, start and end time measurements, and a generic
	// 'dataStructure' insert to allow reuse of the same code for each test run.

	char chari[50]; // assumes no word is longer than 49 characters
	memset(chari, 0, 50); // zero the word buffer
	int iPtr;
	bool IsDelimiter = false, WasDelimiter = false;
	std::ifstream inFile;
	inFile.open(inputFile, std::ios::binary);
	if (inFile.fail())
	{
		std::cout << inputFile << std::endl;
		std::cout << "Unable to open input file\n\n"
			<< "Program Exiting\n\nPress ENTER to exit\n";
		std::cin.get(c);
		exit(1);
	}
	start = std::clock();
	iPtr = 0;
	inFile.get(c); // priming read
	while (!inFile.eof())
	{
		IsDelimiter = (c == ' ' || c == 10 || c == 13 || c == 9 || c == '.' || c == ',' ||
			c == '!' || c == ';' || c == ':' || c == '(' || c == ')' || c == '?' ||
			c == '-');
		if (IsDelimiter && !WasDelimiter) // if THIS character IS a delimiter, and the
										  // last character WASN’T, it’s the end of a word
		{
			WasDelimiter = true;
			testStructure->insert(chari);
			memset(chari, 0, 50); // zero the word buffer
			iPtr = 0;
		}
		else if (!IsDelimiter) // if this isn’t a delimiter, keep going
		{
			chari[iPtr] = c;
			iPtr++;
		}
		else if (IsDelimiter && WasDelimiter)
		{
			// Do nothing -- two consecutive delimiters.
		}
		WasDelimiter = IsDelimiter; // for the NEXT iteration
		inFile.get(c);
	}
	end = std::clock();
	inFile.close();

	//	Listing used for DEBUG purposes.  Uncomment to view.
	//testStructure->list();

	//	Once the file has been completely read, save the data to an array and output the result to
	// the console.

	heights[arrayPos] = testStructure->getHeight();
	loadingFactors[arrayPos] = testStructure->getLoadingFactor();
	totalNodes[arrayPos] = testStructure->getTotalNodes();
	fileSizes[arrayPos] = testStructure->getFileSize();
	totalReads[arrayPos] = testStructure->getTotalReads();
	totalWrites[arrayPos] = testStructure->getTotalWrites();
	times[arrayPos] = (end - start) / 1000.0;

	std::cout << inputFile << std::endl;
	std::cout << "Height: " << heights[arrayPos] << std::endl;
	std::cout << "Loading Factor: " << loadingFactors[arrayPos] << std::endl;
	std::cout << "Total Nodes: " << totalNodes[arrayPos] << std::endl;
	std::cout << "File Size: " << fileSizes[arrayPos] << " kBytes" << std::endl;
	std::cout << "Total Reads: " << totalReads[arrayPos] << std::endl;
	std::cout << "Total Writes: " << totalWrites[arrayPos] << std::endl;
	std::cout << "Time: " << times[arrayPos] << "s" << std::endl;
	std::cout << std::endl;
}

void writeToFile(std::ofstream &output)
{
	//	writeToTile() - writes the data from the data arrays into the specified output file.  Takes
	// a single parameter:
	//
	//	'ofstream &output' - specifies the output file path for the data.
	//
	//	Each group of code outputs a header followed by the data in one of the data arrays formatted
	// to be read as a csv file.

	//	First Line: File header
	//	Second Line: 'for' loop to iterate through data array
	//	Third Line: Output newline for formatting

	//	Outputs file names.
	output << "File Name" << ",";
	for (int i = 0; i < 10; i++) output << files[i] << ",";
	output << std::endl;

	//	Outputs data structure heights.
	output << "Height" << ",";
	for (int i = 0; i < 10; i++) output << heights[i] << ",";
	output << std::endl;

	output << "Loading Factor" << ",";
	for (int i = 0; i < 10; i++) output << loadingFactors[i] << ",";
	output << std::endl;

	output << "Total Nodes" << ",";
	for (int i = 0; i < 10; i++) output << totalNodes[i] << ",";
	output << std::endl;

	output << "File Size" << ",";
	for (int i = 0; i < 10; i++) output << fileSizes[i] << ",";
	output << std::endl;

	output << "Total Reads" << ",";
	for (int i = 0; i < 10; i++) output << totalReads[i] << ",";
	output << std::endl;

	output << "Total Writes" << ",";
	for (int i = 0; i < 10; i++) output << totalWrites[i] << ",";
	output << std::endl;

	//	Outputs the time to run insertion loop.
	output << "Time to Run" << ",";
	for (int i = 0; i < 10; i++) output << times[i] << ",";
	output << std::endl;

	output << std::endl;
}

void performanceChecker(DATA_STRUCTURE ds)
{
	//	performanceChecker() - runs a thorough insertion test for each data structure including a
	// blank run to gather base run times.
	//
	//	An insertion test is run with ten different files per data structure.  The resulting data
	// is then output to an output file.

	//	First Line: Output data structure name as header to output file.
	//	Second Line: Output data structure name to console.
	//
	//	Third Line: 'for' loop to run the 'fileParser()' using each file.
	//
	//	Fourth Line: Output a newline to console for formatting.
	//	Fifth Line: Write the run data to the output file.

	std::ofstream outputFile(OUTPUT_FILE);

	outputFile << "None_1" << std::endl;
	std::cout << "No Tree" << std::endl;

	for (int i = 0; i < 10; i++) fileParser(NONE, files[i], i);

	std::cout << "" << std::endl;
	writeToFile(outputFile);

	if (ds == BT)
	{
		outputFile << "B-Tree" << std::endl;
		std::cout << "B-Tree" << std::endl;

		for (int i = 0; i < 10; i++) fileParser(BT, files[i], i);

		std::cout << "" << std::endl;
		writeToFile(outputFile);
	}
	else if (ds == AVLTree)
	{
		outputFile << "AVL" << std::endl;
		std::cout << "AVL" << std::endl;

		for (int i = 0; i < 10; i++) fileParser(AVLTree, files[i], i);

		std::cout << "" << std::endl;
		writeToFile(outputFile);
	}

	outputFile << "None_2" << std::endl;
	std::cout << "No Tree" << std::endl;

	for (int i = 0; i < 10; i++) fileParser(NONE, files[i], i);

	std::cout << "" << std::endl;
	writeToFile(outputFile);

	outputFile.close();
}