/*
 * Sam Miller
 * CS15
 * 11/07/2022
 * 
 * Purpose - Interace of PhaseOne functions: frequency counter, serialize
 *           and deserialize. Ultimately will be used to build a program that
 *           compresses and decompresses files. 
 */

#ifndef __PHASEONE_H__
#define __PHASEONE_H__

#include "HuffmanTreeNode.h"
#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;


void count_freqs(std::istream &text,int *frequency);
HuffmanTreeNode* build_tree(int *ascii, priority_queue<HuffmanTreeNode*,\
vector<HuffmanTreeNode*>, NodeComparator> my_pq);
string serialize_tree(HuffmanTreeNode *root);
HuffmanTreeNode *deserialize_tree(std::string serial_tree); 
HuffmanTreeNode *deserialize_helper(string &input); 
HuffmanTreeNode *makeNode(char one, char two);
string generate_BinaryString(istream &text, vector<string> ascii);




#endif