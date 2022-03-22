#ifndef MATHIO_H

#define MATHIO_H

#include "../include/tree.h"
#include <ctype.h>
#include <math.h>

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
size_t GetNF (char *buf, branch_t *branch);
size_t GetFunc (char *buf, branch_t *current);

#endif