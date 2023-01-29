#ifndef  TREE_HPP
#define  TREE_HPP


enum {
    A_ADD,
    A_SUBTRACT,
    A_MULTIPLY,
    A_DIVIDE,
    A_INTLIT
};

struct ASTNode{
    int op;
    ASTNode *left;
    ASTNode *right;
    int intvalue;
};

struct ASTNode *newASTNode(int op, struct ASTNode *left, struct ASTNode *right);
struct ASTNode *newASTLeaf(int op, int intvalue);
struct ASTNode *newASTUnary(int op, struct ASTNode *left, int intvalue);

int arithop(int tok);

static struct ASTNode * primary();
struct ASTNode *binexpr();

int interpretAST(struct ASTNode *n);


#endif