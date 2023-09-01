/*
 * Sam Miller
 * CS15
 * 11/13/2022
 * 
 * Purpose - Interace of HuffmanCoder Class: This class has the capability of
 *           encoding a file and decoding a file. 
 */

#ifndef HUFFMANCODER_H
#define HUFFMANCODER_H

#include "BinaryIO.h"
#include "phaseOne.h"
#include "HuffmanTreeNode.h"
#include <iostream>
#include <string>
#include <istream>
#include <vector>
using namespace std;

class HuffmanCoder{
    public:
        void encoder(string input_file, string output_file);
        void decoder(string input_file, string output_file);  
    private:
        void characterCodes(HuffmanTreeNode *root, string path, vector<string> &ascii);
        void stringDecoder(HuffmanTreeNode *root, string *decodedString, string BinaryString);
        void deleteTree(HuffmanTreeNode *root);
};

#endif