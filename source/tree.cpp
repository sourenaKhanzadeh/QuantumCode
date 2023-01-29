#include "tree.hpp"
#include "scan.hpp"
#include <iostream>

struct ASTNode *newASTNode(int op, ASTNode * left, ASTNode * right, int intvalue){
    struct ASTNode *n = new ASTNode;

    if(n == NULL){
        std::cout << "Out of memory" << std::endl;
        exit(1);
    }

    n->op = op;
    n->left = left;
    n->right = right;
    n->intvalue = intvalue;
    return n;
}

struct ASTNode *newASTLeaf(int op, int intvalue){
    return newASTNode(op, NULL, NULL, intvalue);
}

struct ASTNode * newASTUnary(int op, struct ASTNode * left, int intvalue){
    return newASTNode(op, left, NULL, intvalue);
}

int arithop(int tok){
    switch (tok){
        case T_PLUS:
            return A_ADD;
        case T_MINUS:
            return A_SUBTRACT;
        case T_STAR:
            return A_MULTIPLY;
        case T_SLASH:
            return A_DIVIDE;
        default:
            std::cerr << "Unknown error in arithop() on line " << Scan::Line << std::endl;
            exit(1);
    }
}

static struct ASTNode *primary(){
    ASTNode *n;
    Scan *s = new Scan();

    switch (Scan::Token.token)
    {
    case T_INTLIT:
        n = newASTLeaf(A_INTLIT, Scan::Token.intvalue);
        s->scan(&Scan::Token);
        delete s;
        return n;
    
    default:
        std::cerr << "syntax error on line " << Scan::Line << std::endl;
        exit(1);
    }
}

struct ASTNode * binexpr(){
    ASTNode *n, *left, *right;
    int nodetype;
    Scan * s = new Scan();

    left = primary();

    if(Scan::Token.token == T_EOF)
        return left;

    nodetype = arithop(Scan::Token.token);
    s->scan(&Scan::Token);

    right = binexpr();

    n = newASTNode(nodetype, left, right , 0);

    return n;   
}


int interpretAST(struct ASTNode *n) {
    int leftval, rightval;

    if(n->left)
        leftval = interpretAST(n->left);
    if(n->right)
        rightval = interpretAST(n->right);
    
    switch (n->op)
    {
    case A_ADD:
        return leftval + rightval;
    case A_SUBTRACT:
        return leftval - rightval;
    case A_MULTIPLY:
        return leftval * rightval;
    case A_DIVIDE:
        return leftval / rightval;
    case A_INTLIT:
        return n->intvalue;    
    default:
        std::cerr << "Unknown AST operator " << n->op << std::endl;
        exit(1);
    }
}