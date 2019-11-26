//=======================================================================================
// Name        : Test.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 28/03/2019
// Description : Huffman tree encoder - a compression algorithm used to compress English
//               language text files, turning a sequence of ASCII characters into
//				 a compressed bit stream - written in C++, Ansi-style
//=======================================================================================

#define CATCH_CONFIG_MAIN

#include <fstream>
#include "catch.hpp"
#include "HuffmanTree.h"

using namespace std;

// unit tests

TEST_CASE("TESTING COMPRESSION:") {

	DPLKYL002::HuffmanTree tree;
	typedef DPLKYL002::HuffmanTree::HuffmanNode nodeType;

	unordered_map<char, unsigned int> map;
	unordered_map<char, string> codeTable;

	priority_queue<nodeType, vector<nodeType>, DPLKYL002::HuffmanTree::Compare> priorityQueue;

	string inputFileName = "unit_tests/test1.txt";

	SECTION("TESTING createMap:"){

	tree.createMap(map, inputFileName);

	SECTION("Check character found:") {

		REQUIRE(map.find(' ') != map.end()); // found
		REQUIRE(map.find('s') != map.end());// found
		REQUIRE(map.find('p') != map.end());// found
		REQUIRE(map.find('K') == map.end());// not found (case sensitive)
		REQUIRE(map.find('o') == map.end());// not found

	}

	SECTION("Check character frequency updated:") {

		REQUIRE(map['s'] == 5); // updated
		REQUIRE(map[' '] == 4);// updated
		REQUIRE(map['k'] == 1);// not updated

	}

	SECTION("Check map correct size:") {

		REQUIRE(map.size() == 17); // correct size
		REQUIRE(map.size() != 1);// incorrect size
		REQUIRE(map.size() != 0);// incorrect size

	}

}

	SECTION("TESTING createPriorityQueue:"){

	SECTION("Check priority queue correct size:") {

		tree.createPriorityQueue(priorityQueue, map);
		REQUIRE(priorityQueue.size() == 0); // correct size
		REQUIRE(priorityQueue.size()!= 1);// incorrect size

	}

	SECTION("Check map correct size:") {

		tree.createPriorityQueue(priorityQueue, map);
		REQUIRE(map.size() == 0); // correct size
		REQUIRE(map.size()!= 1);// incorrect size

	}

	SECTION("Check map and priority queue have the equal size:") {

		tree.createPriorityQueue(priorityQueue, map);
		REQUIRE(map.size() == priorityQueue.size()); // equal size


	}

}

	SECTION("TESTING buildHuffmanTree:"){

	SECTION("Check root node frequency equal to number of characters in input text file:") {

		tree.createMap(map, inputFileName);
		tree.createPriorityQueue(priorityQueue, map);

		DPLKYL002::HuffmanTree::HuffmanNode huffmanNode(tree.buildHuffmanTree(priorityQueue));
		unsigned int charSum = 0;
		for(const auto &n:map) charSum += n.second;
		REQUIRE(huffmanNode.getFrequency() == charSum);

	}

}

}

TEST_CASE("TESTING DECOMPRESSION:") {

	SECTION("Check output decompressed file identical to original input text file (test2.txt):"){

	DPLKYL002::HuffmanTree tree;

	string inputFileName = "unit_tests/test2.txt";
	string outputFileName = "unit_tests/output2";

	tree.compress(inputFileName, outputFileName);
	tree.decompress(outputFileName, inputFileName + "_decompressed");

	string iFile, oFile, line;

	ifstream inputFile(inputFileName.c_str());

	while(!inputFile.eof()) {

		inputFile >> line;
		iFile += line;

	}

	inputFile.close();

	ifstream outputFile((inputFileName + "_decompressed").c_str());

	while(!outputFile.eof()) {

		outputFile >> line;
		oFile += line;

	}

	outputFile.close();

	REQUIRE(iFile == oFile);

}
	SECTION("Check output decompressed file identical to original input text file (test3.txt):"){

		DPLKYL002::HuffmanTree tree;

		string inputFileName = "unit_tests/test3.txt";
		string outputFileName = "unit_tests/output3";

		tree.compress(inputFileName, outputFileName);
		tree.decompress(outputFileName, inputFileName + "_decompressed");

		string iFile, oFile, line;

		ifstream inputFile(inputFileName.c_str());

		while(!inputFile.eof()) {

			inputFile >> line;
			iFile += line;

		}

		inputFile.close();

		ifstream outputFile((inputFileName + "_decompressed").c_str());

		while(!outputFile.eof()) {

			outputFile >> line;
			oFile += line;

		}

		outputFile.close();

		REQUIRE(iFile == oFile);

	}

	SECTION("Check output decompressed file identical to original input text file (test4.txt):"){

		DPLKYL002::HuffmanTree tree;

		string inputFileName = "unit_tests/test4.txt";
		string outputFileName = "unit_tests/output4";

		tree.compress(inputFileName, outputFileName);
		tree.decompress(outputFileName, inputFileName + "_decompressed");

		string iFile, oFile, line;

		ifstream inputFile(inputFileName.c_str());

		while(!inputFile.eof()) {

			inputFile >> line;
			iFile += line;

		}

		inputFile.close();

		ifstream outputFile((inputFileName + "_decompressed").c_str());

		while(!outputFile.eof()) {

			outputFile >> line;
			oFile += line;

		}

		outputFile.close();

		REQUIRE(iFile == oFile);

	}

}
