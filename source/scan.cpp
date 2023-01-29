#include "scan.hpp"
#include <iostream>


int Scan::Line = 1;
int Scan::Putback = 0;
std::ifstream *Scan::Infile = NULL;
struct token Scan::Token = {T_EOF, -1};

Scan::Scan(){

}

Scan::~Scan(){
}

int Scan::scan(struct token *t){
    int c;
    c = skipwhite();
    if(c == EOF){
        return EOF;
    }

    switch (c)
    {
    case '+':
        t->token = T_PLUS;
        break;
    case '-':
        t->token = T_MINUS;
        break;
    case '*':
        t->token = T_STAR;
        break;
    case '/':
        t->token = T_SLASH;
        break;
    default:
        if(isdigit(c)){
            t->token = T_INTLIT;
            t->intvalue = scanint(c);
            return t->token;
        }
        std::cout << "Unrecognised character on line " << Line << std::endl;
        exit(1);
        break;
    }


    return t->token;
}


int Scan::next(){
    int c;
    if(Putback){
        c = Putback;
        Putback = 0;
        return c;
    }
    c = Infile->get();
    if('\n' == c)
        Line++;
    return c;
}

void Scan::putback(int c){
    Scan::Putback = c;
}

int Scan::skipwhite(){
    int c;
    c = next();
    while(isspace(c)){
        c = next();
    }
    return c;
}

int Scan::scanint(int c){
    int k;
    k = c - '0';
    c = next();
    while(isdigit(c)){
        k = k * 10 + c - '0';
        c = next();
    }
    putback(c);
    return k;
}

int Scan::chrpos(std::string s, int c){
    int i;
    for(i = 0; i < s.length(); i++){
        if(s[i] == c)
            return i;
    }
    return -1;
}

void Scan::scanfile(){
    struct token t;
    int tok;
    while((tok = scan(&t)) != EOF){
        switch (tok)
        {
        case T_PLUS:
            std::cout << "Plus" << std::endl;
            break;
        case T_MINUS:
            std::cout << "Minus" << std::endl;
            break;
        case T_STAR:
            std::cout << "Star" << std::endl;
            break;
        case T_SLASH:
            std::cout << "Slash" << std::endl;
            break;
        case T_INTLIT:
            std::cout << "Intlit " << t.intvalue << std::endl;
            break;
        default:
            std::cout << "Unrecognised token on line " << Line << std::endl;
            exit(1);
            break;
        }
    }
}