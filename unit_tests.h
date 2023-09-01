/*
 *  unit_tests.h
 *  Sam Miller
 *  11/07/2022
 *
 *  CS 15 Zap
 *
 *  Purpose: Unit testing my functions to ensure that they work properly
 *
 */


#ifndef __UNIT_TESTS_H__
#define __UNIT_TESTS_H__

// #include "phaseOne.h"
#include "HuffmanCoder.h"
// #include "BinaryIO.h"
#include "HuffmanTreeNode.h"
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


// first count frequency test
// void count_freq_test() 
// {
//     int frequency[256] = {0};
//     string s = "asdfasdfasdf";
//     std::istringstream is(s);
//     count_freqs(is, frequency);
//     //assert(count_freqs(is) == "Frequency :\na : 3\nd : 3\nf : 3\ns : 3");
// }

// void count_freq_whiteSpace() 
// {
//     int frequency[256] = {0};
//     string s = "       ";
//     std::istringstream is(s);
//     count_freqs(is, frequency);
// }

// void count_freq_TwoWords() 
// {
//     int frequency[256] = {0};
//     string s = "Two Words";
//     std::istringstream is(s);
//     count_freqs(is, frequency);
// }

// void count_CapVsLowerCase() 
// {
//     int frequency[256] = {0};
//     string s = "TtWwSs";
//     std::istringstream is(s);
//     count_freqs(is, frequency);
// }

// void count_LongStressTest() 
// {
//     int frequency[256] = {0};
//     string s = "asdfasdfaergergdskjfgnasldkfgnsaoeirhgtpwoiafg;glaksdnv;falks";
//     std::istringstream is(s);
//     count_freqs(is, frequency);
// }

// void count_newLine() 
// {
//     int frequency[256] = {0};
//     string s = "hi hi\nhi";
//     std::istringstream is(s);
//     count_freqs(is, frequency);
// }

// void count_SpecExample()
// {
//     int frequency[256] = {0};
//     string s = "BaNana";
//     istringstream is(s);
//     count_freqs(is, frequency);
//     //assert(s == "B:  1\na:  3\nN:  1\nn:  1\n");
// }

// void testTree()
// {
//     //six leaves nodes
//     HuffmanTreeNode a('a', 4);
//     HuffmanTreeNode b('b', 3);
//     HuffmanTreeNode c('c', 1);
//     HuffmanTreeNode d('d', 1);
//     HuffmanTreeNode e('e', 2);
//     HuffmanTreeNode f('f', 2);
//     //five internal nodes
//     HuffmanTreeNode g('\0', 7, &a, &b);
//     HuffmanTreeNode h('\0', 4, &e, &f);
//     HuffmanTreeNode i('\0', 2, &c, &d);
//     HuffmanTreeNode j('\0', 11, &g, &h);
//     //root
//     HuffmanTreeNode k('\0', 13, &j, &i);
//     string p = serialize_tree(&k);
//     assert(p == "IIILaLbILeLfILcLd");
// }

// void testTreeTwo()
// {
//     //3 leaf nodes
//     HuffmanTreeNode a('a', 3);
//     HuffmanTreeNode b('b', 1);
//     HuffmanTreeNode c('n', 2);

//     //one internal node
//     HuffmanTreeNode d('\0', 3, &b, &c);

//     //root
//     HuffmanTreeNode e('\0', 6, &d, &a);
    
//     //testing
//     string p = serialize_tree(&e);
//     //cout << p << endl; 
//     assert(p == "IILbLnLa");
// }

void test_deserialize()
{
    string x = "IILbLnLa";
    string y = serialize_tree(deserialize_tree(x));
    assert("IILbLnLa" == serialize_tree(deserialize_tree(y)));
}

void test_buildTree()
{
    int frequency[256] = {0};
    string s = "BaNana";
    istringstream is(s);
    count_freqs(is, frequency);
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, NodeComparator> my_pq;
    string x = "IILbLnLa";
    build_tree(frequency, my_pq);

}

void test_encoder()
{
    string input = "BaNana";
    string output = "";
    HuffmanCoder hi;
    hi.encoder(input, output);
}

void test_encoder_tw0Characters()
{
    string input = "xo";
    string output = "";
    HuffmanCoder hi;
    hi.encoder(input, output);
}

void specTestEncoder()
{
    string input = "aaaaabbbbbfffcdeee";
    string output = "";
    HuffmanCoder hi;
    hi.encoder(input, output);
}

#endif