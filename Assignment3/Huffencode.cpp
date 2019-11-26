//=======================================================================================
// Name        : Huffencode.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 28/03/2019
// Description : Huffman tree encoder - a compression algorithm used to compress English
//               language text files, turning a sequence of ASCII characters into
//				 a compressed bit stream - written in C++, Ansi-style
//=======================================================================================

#include <string>
#include <iostream>

#include "HuffmanTree.h"

using namespace std;

// main function
int main(int argc, char * argv[]) { // argc and argv values passed into main

	// argc - number of all items on command line
	// argv array - contains simple C-strings for each of these items
	// argv[0] is always the application name, and argv[1] the first argument

	// if number of items on command line is less than 3
	if (argc < 4) {

		cout << "Incorrect arguments!" << endl;

		return 0;

	}

	string inputFileName = string(argv[2]); // an input English (ASCII) text file
	string outputFileName = string(argv[3]); // an output compressed "bitstream"

	DPLKYL002::HuffmanTree tree;

	tree.compress(inputFileName, outputFileName);
	tree.decompress(outputFileName, "decompressed_" + inputFileName);

	return 0;

}
