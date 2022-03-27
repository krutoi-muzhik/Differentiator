#ifndef MATHTREE_H

#define MATHTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define POISON 0xBEEBA

typedef double data_t;

typedef enum TYPES {
	BINAR,
	NUM,
	UNAR,
	VAR
} branch_type_t;

typedef struct branch {
	data_t data;
	struct branch *right;
	struct branch *left;
	branch_type_t type;
} branch_t;

typedef struct tree {
	branch_t *root;
	size_t size;
} tree_t;

typedef enum TREE_ERRORS {
	NICE_TREE,
	INVALID_SIZE
} tree_error_t;

enum BRANCH_ERRORS {
	UNKNOWN_TYPE = -1,
	UNKNOWN_OPER = -2
};

int IsEqual (double a, double b);

branch_t *Branch (data_t data, branch_t *left, branch_t *right);
branch_t *Branch_ (data_t data, branch_type_t type, branch_t *left, branch_t *right);
void RecursiveDestruct (branch_t *branch);
tree_t *TreeConstruct ();
void TreeDestruct (tree_t *tree);

size_t GetNum (char *buf, branch_t *branch);
size_t GetAddSub (char *buf, branch_t **current);
size_t GetPow (char *buf, branch_t **current);
size_t GetLog (char *buf, branch_t **current);
size_t GetLow (char *buf, branch_t **branch);
size_t GetFunc (char *buf, branch_t *current);
size_t GetVar (char *buf, branch_t *branch);
size_t GetMulDiv (char *buf, branch_t **current);
size_t GetBracket (char *buf, branch_t **branch);

int isoper (char c);

double Count (branch_t *branch);
double Calculate (tree_t *tree);

tree_t *Input (const char *pathname);
void BranchOut (FILE *out, branch_t *branch);
void TreeOut (const char *pathname, tree_t* tree);
void Graph (FILE *graph, branch_t *branch);
void GVDump (const char *pathname, tree_t *tree);
int Prior (branch_t *branch);

enum SIZES {
	BUF_SIZE = 1024,
	FUNC_LEN = 5
};

enum BINARS {
	ADD = '+',
	SUB = '-',
	POW = '^',
	MUL = '*',
	DIV = '/',
	LOG = 0
};

enum OPERS {
	SIN = 1,
	COS = 2,
	TAN = 3,
	COT = 4,
	ASIN = 5,
	ACOS = 6,
	ATAN = 7,
	ACOT = 8,
	SH = 9,
	CH = 10,
	TANH = 11,
	COTH = 12,
	ASH = 13,
	ACH = 14,
	ATANH = 15,
	ACOTH = 16,
	EXP = 17,
	SQRT = 18,
	LN = 19,
	LG = 20,
	FACT = 21,
	ABS = 22
};

#endif