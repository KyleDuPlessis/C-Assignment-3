//=======================================================================================
// Name        : HuffmanTree.h
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 28/03/2019
// Description : Huffman tree encoder - a compression algorithm used to compress English
//               language text files, turning a sequence of ASCII characters into
//				 a compressed bit stream - written in C++, Ansi-style
//=======================================================================================

#include <queue>
#include <memory>
#include <unordered_map>

#ifndef LIBS_HUFFMANTREE_H
#define LIBS_HUFFMANNTREE_H

using namespace std;

namespace DPLKYL002 {

// manages the tree and has methods to compress data, build a Huffman tree etc
class HuffmanTree {

public:

	// represents the tree nodes in the underlying Huffman tree (which is a simple binary tree)
	class HuffmanNode {

	private:
		char letter;
		unsigned int frequency;

	public:

		// represents the left / right links for tree nodes as well as the root of the tree in HuffmanTree class
		shared_ptr<HuffmanNode> leftLink;
		shared_ptr<HuffmanNode> rightLink;


		HuffmanNode() = delete;

		// constructor defined to use the specified smart pointers to manage memory above
		HuffmanNode(char c, unsigned int f) :
				letter(c), frequency(f) {

			leftLink = nullptr;
			rightLink = nullptr;

		}

		HuffmanNode(const HuffmanNode & huffmanNode) {

			this->letter = huffmanNode.letter;
			this->frequency = huffmanNode.frequency;
			this->leftLink = huffmanNode.leftLink;
			this->rightLink = huffmanNode.rightLink;

		}

		char getLetter(void) const {

			return this->letter;

		}

		unsigned int getFrequency(void) const {

			return this->frequency;

		}
	};

	class Compare {
	public:

		// a binary function predicate

		/*This function (which can be a free function) will be used by the priority queue to decide how to order its
		  HuffmanNode elements.
		  */

		/*the HuffmanNode elements are ordered by the frequency of element A
		  being greater than or equal to the frequency of element B
		  */

		bool operator()(const HuffmanNode nodeA, const HuffmanNode nodeB) {

			return (nodeA.getFrequency() >= nodeB.getFrequency() ? true : false);

		}
	};


		/*Prior to constructing the huffman encoding tree you have to count the number of
		  occurrences of each letter in the file. To store these frequencies you can use a
		  std::unordered_map with keys of type character and values of integer type
		  */

		/*You should use a std::priority_queue<HuffmanNode> data structure to assist you in the building the tree.
		  A priority queue returns the next largest or smallest item, depending on how you
		  have set it up. This is required to decide which tree nodes to aggregate as you build
		  your tree.
		  */

		typedef unordered_map<char, unsigned int> & mapType;
		typedef unordered_map<char, string> & codeType;
		typedef HuffmanTree::HuffmanNode nodeType;
		typedef priority_queue<nodeType, vector<nodeType>, HuffmanTree::Compare> & queueType;

		// functions
		void compress(string inputFileName, string outputFileName);

		void createMap(HuffmanTree::mapType map, string inputFileName);
		void createPriorityQueue(HuffmanTree::queueType priorityQueue, HuffmanTree::mapType map);
		HuffmanTree::HuffmanNode buildHuffmanTree(HuffmanTree::queueType priorityQueue);

		void buildCodeTable(nodeType node, codeType map, string bitStringCode);
		void createCodeTableFile(string outputFileName, codeType map);

		string getBitStringCode(string inputFileName, codeType map);
		void createCompressedInputFile(string outputFileName, string bitStringCode);
		void createBinaryFile(string outputFileName, string bitStringCode);

		void decompress(string inputBinaryFileName, string outputFileName);



};

}

#endif
