/***
* Shyam Kishan
* Words.cpp
***/

#include <iostream>
#include <fstream>
#include <cstring>
#include <set>
#include "Dictionary.h"
using namespace std;
#define MAX_LEN 300


int main(int argc, char* argv[]){
    size_t begin, end, len;
    ifstream in;
    ofstream out;
    string line;
    string tokenBuffer;
    string token;
    string delim = " \t\n\r\\\"',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789"; 

    Dictionary D;
    valType insertionOrder = 0;

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

        while (token != ""){
            if (!D.contains(token)){
                D.setValue(token, insertionOrder);
                insertionOrder ++;
            }
            begin = min(line.find_first_not_of(delim, end+1), len);
            end   = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end-begin);
        }
    }

    string s = "(";

    D.begin();
    int counter = 0;
    while(counter < D.size()){
        if (D.size() - counter == 1){
            s += std::to_string(D.currentVal()) + ")\n";
            break;
        }
        s += std::to_string(D.currentVal()) + ", ";
        D.next();
        counter++;
    }

    out << s << endl;
    out << D.to_string2() << endl;

    // close files 
    in.close();
    out.close();
    
    return(EXIT_SUCCESS);
}
