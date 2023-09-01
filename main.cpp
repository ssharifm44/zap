/*
 * Sam Miller
 * CS15
 * 11/07/2022
 * 
 * Purpose - The purpose of this program is to run Zap. 
 */
 


#include "HuffmanCoder.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
using namespace std;

/*        main()
 *
 *    Purpose: Run the Zap Program
 *  
 * Parameters: none
 * 
 *    Returns: zero - none. 
*/
int main(int argc, char *argv[])
{
    HuffmanCoder a;
     if (argc != 4) {    // output usage error
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile\n";
        return 1;  
    }                   // if command is zap
    else if (strcmp(argv[1],"zap") == 0) {
        a.encoder(argv[2], argv[3]);
    }                   // if commmand is unzap
    else if (strcmp(argv[1],"unzap") == 0) {
        a.decoder(argv[2], argv[3]);
    }
    else {
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile\n"<< endl;
        return 1;  
    }
}