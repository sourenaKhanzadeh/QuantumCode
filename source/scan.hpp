#ifndef SCAN_HPP
#define SCAN_HPP
#include <string>
#include <fstream>



struct token{
    int token;
    int intvalue;
};

enum{
    T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_EOF
};

class Scan{
    public:
        Scan();
        ~Scan();
        int scan(struct token *t);
        static int next();
        static void putback(int c);
        static int skipwhite();
        static int scanint(int c);
        static int chrpos(std::string s, int c);
        static int Line;
        static int Putback;
        static struct token Token;
        static std::ifstream *Infile;
        void scanfile();
};




#endif // SCAN_HPP