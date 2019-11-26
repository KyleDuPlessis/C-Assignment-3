//=======================================================================================
// Name        : HuffmanTree.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 28/03/2019
// Description : Huffman tree encoder - a compression algorithm used to compress English
//               language text files, turning a sequence of ASCII characters into
//				 a compressed bit stream - written in C++, Ansi-style
//=======================================================================================

#include "HuffmanTree.h"

#include <bitset>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void DPLKYL002::HuffmanTree::compress(string inputFileName,
		string outputFileName) {

	typedef HuffmanTree::HuffmanNode nodeType;
	HuffmanTree tree;

	unordered_map<char, unsigned int> map;
	unordered_map<char, string> codeTableMap;

	priority_queue<nodeType, vector<nodeType>, HuffmanTree::Compare> priorityQueue;

	tree.createMap(map, inputFileName);
	tree.createPriorityQueue(priorityQueue, map);

	HuffmanTree::HuffmanNode node(tree.buildHuffmanTree(priorityQueue));
	tree.buildCodeTable(node, codeTableMap, "");
	tree.createCodeTableFile(outputFileName, codeTableMap);

	string bitStringCode = tree.getBitStringCode(inputFileName, codeTableMap);
	tree.createCompressedInputFile(outputFileName, bitStringCode);
	tree.createBinaryFile(outputFileName, bitStringCode);

}

void DPLKYL002::HuffmanTree::createMap(HuffmanTree::mapType map,
		string inputFileName) {

	// create a map to store <key / letter, value / frequency> elements

	ifstream inputFile(inputFileName.c_str());

	if (!inputFile) {

		cout << "Unable to open: " << inputFileName << endl;

		return;

	}

	char letter;

	while (inputFile.get(letter)) {

		// if new letter, add to map
		if (map.find(letter) == map.end()) {

			map.insert( { letter, 1 });

		}
		// else if old letter, update its frequency
		else {

			map[letter] += 1;

		}

	}

	inputFile.close();

}

void DPLKYL002::HuffmanTree::createPriorityQueue(
		HuffmanTree::queueType priorityQueue, HuffmanTree::mapType map) {

	/*Create a priority queue containing HuffmanNode elements (nodes)
	  where the HuffmanNode elements are ordered by the frequency of element A
	  being greater than or equal to the frequency of element B
	  */

	// for each <key / letter, value / frequency> element stored in the map
	for (const auto& node : map) {

		// create a HuffmanNode element, and add it to the priority queue
		priorityQueue.push(HuffmanTree::HuffmanNode(node.first, node.second));

	}

}

DPLKYL002::HuffmanTree::HuffmanNode DPLKYL002::HuffmanTree::buildHuffmanTree(
		HuffmanTree::queueType priorityQueue) {

	// while the number of HuffmanNode elements in the priority queue is greater than 1
	while (priorityQueue.size() > 1) {

		// smaller nodes are inserted as left child
		shared_ptr<HuffmanTree::HuffmanNode> left(
				new HuffmanTree::HuffmanNode(priorityQueue.top()));

		priorityQueue.pop();

		// larger nodes are inserted as right child
		shared_ptr<HuffmanTree::HuffmanNode> right(
				new HuffmanTree::HuffmanNode(priorityQueue.top()));

		priorityQueue.pop();

		unsigned int frequency = left->getFrequency() + right->getFrequency();

		/*Choose the two nodes with the smallest letter frequency and create a new internal
		  parent node which has these two nodes as its left and right children.
		  The new node (an internal node) has no letter associated with it, only a frequency.
		  This frequency is the sum of the frequencies of its two children.
		  Insert this new node in to the priority queue.
		  */

		HuffmanTree::HuffmanNode newNode = HuffmanTree::HuffmanNode('\0',
				frequency);

		newNode.leftLink = move(left);
		newNode.rightLink = move(right);

		priorityQueue.push(newNode);

	}

	HuffmanTree::HuffmanNode huffmanNode(priorityQueue.top());

	return huffmanNode;

}

// "code table": this is a mapping that gives a bit string code for each letter in your alphabet
void DPLKYL002::HuffmanTree::buildCodeTable(nodeType node, codeType map,
		string bitStringCode) {

	// create a map to store <key / letter, value / bit string code> elements
	// if leaf node encountered, add to map
	if (node.leftLink == nullptr) {

		map.insert( { node.getLetter(), bitStringCode });
		return;

	}

	// else if
	else { // else if left and right child

		/*When traversing the tree, add a "0" if branching left and add "1" if branching right.*/
		string branchLeft = bitStringCode + "0";
		string branchRight = bitStringCode + "1";

		HuffmanTree::buildCodeTable(*(node.leftLink), map, branchLeft);
		HuffmanTree::buildCodeTable(*(node.rightLink), map, branchRight);

	}

}

// output file (code table file)
void DPLKYL002::HuffmanTree::createCodeTableFile(string outputFileName,
		codeType map) {

	ofstream outputFile((outputFileName + ".hdr").c_str());

	if (outputFile.is_open()) {

		/*The header should have a field count at the top and a field for every character
		 (consisting of the character and its code representation).
		 */

		for (const auto &node : map) {

			outputFile << node.first << endl;
			outputFile << node.second << endl;

		}

		outputFile.close();

	}

}

string DPLKYL002::HuffmanTree::getBitStringCode(string inputFileName,
		codeType map) {

	/*To compress your ASCII text file, take each character, in turn,
	 finding its bit string code and write this into the output buffer.
	 This "buffer" can just be a std::string which you
	 append characters/strings to.
	 */

	ifstream inputFile(inputFileName.c_str());

	if (!inputFile) {

		cout << "Unable to open: " << inputFileName << endl;
		return "";

	}

	string bitStringCode;
	char letter;

	while (inputFile.get(letter)) {

		bitStringCode += map[letter];

	}

	inputFile.close();

	return bitStringCode;

}

// output file (compressed input file)
void DPLKYL002::HuffmanTree::createCompressedInputFile(string outputFileName,
		string bitStringCode) {

	// create the compressed input English (ASCII) text file
	ofstream outputFile(outputFileName.c_str());

	if (outputFile.is_open()) {

		/*first line - bit string code length
		  second line - bit string code
		  */

		outputFile << bitStringCode.size(); // bit string code length
		outputFile << endl;
		outputFile << bitStringCode; // bit string code

		outputFile.close();

	}

}

// extra credit (convert to bit stream)
// output file (binary file)
void DPLKYL002::HuffmanTree::createBinaryFile(string outputFileName,
		string bitStringCode) {

	/*Convert your bits into an actual bit stream and store
	  this in a byte array that is large enough; this should be written to disk as a binary
	  file with a single int as header which lists the number of bits in the file. You can
	  work out number of bytes to read from this.
	  */

	ofstream outputFile((outputFileName + ".bin").c_str(), ios::binary);

	const unsigned char * letter =
			(const unsigned char *) bitStringCode.c_str();

	if (outputFile.is_open()) {

		int bitStringCodeLength = bitStringCode.size(); // bit string code length

		char endBitStringCode = '\n'; // end of bit string code

		outputFile.write(reinterpret_cast<const char *>(&bitStringCodeLength),
				sizeof(int));

		outputFile.write(&endBitStringCode, 1);

		// convert bits into an actual bit stream
		for (int i = 0; i < bitStringCodeLength; i += 8) {

			bitset<8> byteArr = 0; // byte array

			for (int k = i; k < i + 8; k++) {

				bool test = (*(letter + k) == '1' ? true : false);

				byteArr |= (test ? 1 : 0) << 7 - (k - i);

			}

			outputFile.write((const char *) &byteArr, 1);

		}

		outputFile.close();

	}

}

// extra credit (read in and unpack bitstream)
// output file ()
void DPLKYL002::HuffmanTree::decompress(string inputFileName,
		string outputFileName) {

	unordered_map<string, string> map;

	ifstream inputFile((inputFileName + ".hdr").c_str()); // code table file

	if (!inputFile) {

		cout << "Unable to open: " << inputFileName + ".hdr" << endl;
		return;

	}

	/*The header has a field count at the top and a field for every character
	 (consisting of the character and its code representation).
	 */

	while (!inputFile.eof()) {

		string fieldCount, line;

		getline(inputFile, fieldCount, '\n');
		getline(inputFile, line, '\n');

		if (line == "") {

			getline(inputFile, line, '\n');
			map.insert( { line, "\n" });

		} else {

			map.insert( { line, fieldCount });

		}

	}

	inputFile.close();

	// convert input binary file to bit stream
	inputFile.open((inputFileName + ".bin").c_str(), ios::binary); // binary file

	if (!inputFile) {

		cout << "Unable to open: " << inputFileName + ".bin" << endl;
		return;

	}

	int numBits, numBytes;
	char letter;

	inputFile.read(reinterpret_cast<char *>(&numBits), sizeof(int));

	/*To compute the actual packed file size in bytes (approximately) you can compute:
	 (Nbits/8) + (Nbits%8 ? 1 : 0) using integer arithmetic. This accommodates
	 extra padding bits needed to deal with output bit stream sizes that are not a power
	 of 2.
	 */

	numBytes = (numBits / 8) + (numBits % 8 ? 1 : 0);

	inputFile.read(&letter, 1);

	bitset<8> * byteArr = new bitset<8> [numBytes];

	for (int i = 0; i < numBytes; i++) {

		inputFile.read((char *) &byteArr[i], 1);

	}

	inputFile.close();

	// convert bit stream to bit string code
	string bitStringCode, individualBit;

	for (int j = 0; j < numBytes; j++) {

		for (int i = 7; i > -1; i--) {

			bitset<8> tempArr;

			tempArr = byteArr[j] & (bitset<8> ) 1 << i; // extract individual bit at position j in byte array
			tempArr = tempArr >> i;

			individualBit = (tempArr == 1 ? '1' : '0');
			bitStringCode += individualBit;

		}

	}

	delete[] byteArr;

	// decode bit string code
	string decodedbitStringCode, line;

	for (int k = 0; k < bitStringCode.size(); k++) {

		string letter = bitStringCode.substr(k, 1);
		line += letter;

		if (map.find(line) != map.end()) {

			decodedbitStringCode += map[line];
			line = "";

		}
		if (k == numBits) {

			break;

		}
	}

	// write out letters to output file
	ofstream outputFile(outputFileName.c_str());

	while (outputFile.is_open()) {

		outputFile << decodedbitStringCode;
		outputFile.close();

	}

}
