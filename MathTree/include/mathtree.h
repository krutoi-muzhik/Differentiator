#ifndef TREE_H

#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define POISON 0xBEEBA

typedef int data_t;

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
	struct branch *parent;
	branch_type_t type;
} branch_t;

typedef struct tree {
	branch_t *root;
	size_t size;
} tree_t;

typedef enum ERRORS {
	NICE_TREE,
	INVALID_SIZE
} tree_error_t;

size_t GetNum (char *buf, branch_t *branch);
size_t GetPlus (char *buf, branch_t **current);
int isoper (char c);
double Count (branch_t *branch);
void Calculate (tree_t *tree);
void Input (const char *pathname, tree_t *tree);
void WriteBase (FILE *out, branch_t *branch);
void SaveBase (const char *pathname, tree_t* tree);
size_t GetPow (char *buf, branch_t **current);
size_t GetLog (char *buf, branch_t **current);
size_t GetLow (char *buf, branch_t *branch);
size_t GetFunc (char *buf, branch_t *current);
size_t GetVar (char *buf, branch_t *branch);
branch_t *Branch (branch_t *parent, data_t data);
branch_t *Branch_ (branch_t *parent, data_t data, branch_type_t type);
void RecursiveDestruct (branch_t *branch);
void TreeConstruct (tree_t *tree);
void TreeDestruct (tree_t *tree);
void Graph (FILE *graph, branch_t *branch);
void GVDump (const char *pathname, tree_t *tree);
void InsertBranch (branch_t *parent, size_t dir, data_t data);

enum SIZES {
	BUF_SIZE = 1024,
	FUNC_LEN = 5
};

enum BINARS {
	PLUS = '+',
	MINUS = '-',
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