/*
 * Sam Miller
 * CS15
 * 11/07/2022
 * 
 * Purpose - The implementation of my frequency counter, serializer and
 *           deserializer. This will be used to eventually build a file 
 *           compressor and decompressor. 
 */



#include <iostream>
#include <string>
#include "phaseOne.h"
#include "HuffmanTreeNode.h" 
#include "HuffmanCoder.h"
#include <queue>
#include <vector> 
using namespace std;


/*
 * name:      count_freqs(std::istream &text)
 * purpose:   counts frequency of each char
 * arguments: std::istream &text
 * returns:   none
 * effects:   counts frequency of each char
 */
void count_freqs(istream &text,int *ascii)
{
    char readIn;                // reading input and putting it into a string

    while(text.get(readIn)) {
        ascii [int(readIn)]++;  // keeping track of frequency within the array
    }                           // index value represents ascii value read in
}


/*
 * name:      generate_FinalString(std::istream &text)
 * purpose:   counts frequency of each char
 * arguments: std::istream &text
 * returns:   none
 * effects:   counts frequency of each char
 */
string generate_BinaryString(istream &text, vector<string> ascii)
{
    char readIn;
    string binaryString = "";

    while(text.get(readIn)) {   
       binaryString += ascii[readIn];
    }
    return binaryString;
}

/*
 * name:      build_tree
 * purpose:   builds Huffman tree
 * arguments: (istream &text,int *ascii, priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, NodeComparator> my_pq)
 * returns:   root of tree
 * effects:   used to encode tree
 */
HuffmanTreeNode* build_tree(int *ascii, priority_queue<HuffmanTreeNode*,\
         vector<HuffmanTreeNode*>, NodeComparator> my_pq)
{
    for (int i = 0; i < 256; i++) {
        if (ascii[i] > 0) {
            HuffmanTreeNode* node = new HuffmanTreeNode(char(i), ascii[i]);
            my_pq.push(node);   // Push nodes onto queue
        }
    }
    while (my_pq.size() != 1) { // joining nodes, stop until one node left
        HuffmanTreeNode *first = my_pq.top();
        int firstInt = first->get_freq();
        my_pq.pop();
        HuffmanTreeNode *second = my_pq.top();
        int secondInt = second->get_freq();
        my_pq.pop();
        int total = firstInt + secondInt;
        HuffmanTreeNode* joined = new HuffmanTreeNode('\0', total, first, second);
        my_pq.push(joined);
    }
    //make root
    HuffmanTreeNode *root = my_pq.top();
    return root;
}

/*
 * name:      serialize_tree()
 * purpose:   contstruct to initalize empty stack
 * arguments: HuffmanTreeNode *root
 * returns:   a string that represents the contents of a huffman tree
 * effects:   compressing a huffman tree
 */
std::string serialize_tree(HuffmanTreeNode *root)
{
    string store = "";          
    if (root == nullptr) {              // checking for empty tree
        return store;              
    }
    if (root->isLeaf()) {               // checking if node is a leaf
        store = store + 'L' + root->get_val();
    }
    if (!root->isLeaf()) {              // otherwise, it is an internal node
        store += 'I';
    }   
    if (root->get_left() != nullptr){   //traversing to the next nodes
        store += serialize_tree(root->get_left());
    }
    if (root->get_right() != nullptr){
        store += serialize_tree(root->get_right());
    }
    return store;                       
}

/*
 * name:      deserialize_helper()
 * purpose:   recursive helper
 * arguments: (string &input) 
 * returns:   root of huffman tree
 * effects:   constructs huffman tree
 */
HuffmanTreeNode *deserialize_helper(string &input) 
{
   if (input.size() == 0) {
        return nullptr;                               // empty string
    }
    if (input[0] == 'I') {
        HuffmanTreeNode *topp = new HuffmanTreeNode('\0', 0);
        input = input.substr(1, input.size());
        topp->set_left(deserialize_helper(input));   // making subsequent
        topp->set_right(deserialize_helper(input));  // nodes
        return topp;         
    }
    if (input[0] == 'L') {
        HuffmanTreeNode *topp = new HuffmanTreeNode(input[1], 0);
        input = input.substr(2, input.size());       // making leaf
        return topp;                                 // return root
    }
    return nullptr;
}

/*
 * name:      *deserialize_tree()
 * purpose:   constructs a tree from a serialized string
 * arguments: (string serial_tree)
 * returns:   pointer to root of tree
 * effects:   calls deserialize_helper that is a recursive function
 */
HuffmanTreeNode *deserialize_tree(string serial_tree)
{   
    return deserialize_helper(serial_tree);
} 


