/***
* Shyam Kishan
* WordFrequency.cpp
* takes two files as input and output.
***/ 

#include <iostream>
#include <fstream>
#include <cstring>
#include <set>
#include "Dictionary.h"
using namespace std;

// lower()
// Converts all chars in word to lower case.
void lower(string& word){
   for (int i=0; word[i] != '\0'; i++) {
      word[i] = std::tolower(static_cast<unsigned char>(word[i]));
   }
}

int main(int argc, char * argv[]){
    size_t begin, end, len;
    ifstream in;
    ofstream out;
    string line;
    string tokenBuffer;
    string token;
    string delim = " \t\n\r\\\"',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789"; 

    Dictionary D;

   // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

   // open files for reading and writing
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    while (getline(in, line)){
        len = line.length();
        begin = min(line.find_first_not_of(delim, 0), len);
        end   = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end-begin);
        lower(token);

        while (token != ""){
            lower(token);
            if (!D.contains(token)){
                D.setValue(token, 1);
            } else if (D.contains(token)){
                int freq = D.getValue(token);
                freq++;
                D.setValue(token, freq);
            }
            begin = min(line.find_first_not_of(delim, end+1), len);
            end   = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end-begin);
        }
    }

    out << D << endl;

    // close files 
    in.close();
    out.close();
    
    return(EXIT_SUCCESS);
}