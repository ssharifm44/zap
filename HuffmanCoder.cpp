/*
 * Sam Miller
 * CS15
 * 11/13/2022
 * 
 * Purpose - The implementation of my HuffmanCoder Class. This file includes
 *           the functionality of encoding and decoding files. 
 */

#include "BinaryIO.h"
#include "HuffmanCoder.h"
#include "phaseOne.h"
#include "HuffmanTreeNode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <istream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <ostream>
using namespace std;




/*
 * name:      encoder()
 * purpose:   compresses files
 * arguments: (string input_file, string output_file)
 * returns:   none
 * effects:   compresses file into huffman tree
 */
void HuffmanCoder::encoder(string input_file, string output_file)
{
    ifstream is;                // opening file
    is.open(input_file);
    if (not is.is_open()) {     // checking if program can open file
        throw runtime_error("Unable to open file " + input_file);
    }  
    bool isEmpty = is.peek() == EOF;
    if (isEmpty) {              // checking for empty file
        throw runtime_error("Cannot zap an empty file!");
    }        
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>,\
    NodeComparator> my_pq;              // declaring priority queue

    int frequency[256] = {0};           // storing frequencies
    count_freqs(is, frequency);
    is.clear();                         // resetting stringstream
    is.seekg(0, std::ios::beg);
                                        // building tree
    HuffmanTreeNode *root = build_tree(frequency, my_pq);
    vector<string> ascii(256, "\0");    // initalize storage to null
    characterCodes(root, "", ascii);    // store paths

    string binaryString = generate_BinaryString(is, ascii);
    string serialized = serialize_tree(root);  // storing serialized tree
    BinaryIO a;                         // building compressed file
    a.writeFile(output_file, serialized, binaryString);  
    cout << "Success! Encoded given text using " << binaryString.length() << \
        " bits.\n";
    deleteTree(root);
    is.close();                         // close file
}

/*
 * name:      decoder()
 * purpose:   decompresses files
 * arguments: (string input_file, string output_file)
 * returns:   none
 * effects:   decompresses file from huffman tree
 */
void HuffmanCoder::decoder(string input_file, string output_file)
{
    BinaryIO a;
    vector<string>decoded = a.readFile(input_file);
    string serialize_tree = decoded[0]; 
    string encoded_text = decoded[1];
    // building tree and returning root
    HuffmanTreeNode *root = deserialize_tree(serialize_tree);
    string final = "";
    stringDecoder(root, &final, encoded_text);
    ofstream ostream;               // saving file
    ostream.open(output_file);
    ostream << final;
    deleteTree(root);               // free memory
    ostream.close();
}

void HuffmanCoder::stringDecoder(HuffmanTreeNode *root, string *decodedString, string BinaryString)
{
    unsigned int counter = 0;
    HuffmanTreeNode *temp = root;
    while (counter != BinaryString.length()) {
        if (BinaryString[counter] == '0') {
            temp = temp->get_left();
        }
        if (BinaryString[counter] == '1') {
            temp = temp->get_right();      
        }
        if (temp->isLeaf()) {   
            *decodedString += temp->get_val();  // updating string in encoder
            if  (counter + 1 != BinaryString.length()) {
                temp = root; // sets the node pointer back to root of tree
            }
        }
        counter++;           // increasing counter to traverse string   
    }    
        if (!temp->isLeaf()) {
            throw runtime_error("Encoding did not match Huffman tree.");
            deleteTree(root);
        }                    // checking program terminates at a leaf
}

/*
 * name:      characterCodes()
 * purpose:   creates binary pathes in string form
 * arguments: (HuffmanTreeNode *root, string path, string ascii[])
 * returns:   none
 * effects:   creates huffman string that represents node's path
 */
void HuffmanCoder::characterCodes(HuffmanTreeNode *root, string path, vector<string> &ascii) 
{
    if (root->isLeaf()) { // putting string into array
        ascii[int(root->get_val())] = path;
    }  
    else {                // building binary pathes
        characterCodes(root->get_left(), path + "0", ascii);
        characterCodes(root->get_right(), path + "1", ascii);
    }
}

/*
 * name:      deleteTree()
 * purpose:   frees nodes of tree
 * arguments: (HuffmanTreeNode *root)
 * returns:   none
 * effects:   frees nodes on tree to prevent memory leaks
 */
void HuffmanCoder::deleteTree(HuffmanTreeNode *root) {
    if (root == nullptr) { return; }
    deleteTree(root->get_left());
    deleteTree(root->get_right());
    delete root;
} 



