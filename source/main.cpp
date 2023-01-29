#include "scan.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char **argv){
    Scan *s = new Scan();
    struct token t;
    int tok;
    if(argc != 2){
        std::cout << "Usage: scan <filename>" << std::endl;
        return 1;
    }
    s->Infile = new std::ifstream(argv[1]);
    if(!s->Infile->is_open()){
        std::cout << "Could not open file " << argv[1] << std::endl;
        return 1;
    }
    s->scanfile();

    delete s;

    return 0;
}