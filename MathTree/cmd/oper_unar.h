#define LEFT branch->left

#define OPERAND Count (LEFT)

#define L BranchCopy (oldbranch->left)
#define dL BranchDiff (oldbranch->left)
#define ADD_(right, left) Branch_ (ADD, BINAR, right, left)
#define SUB_(right, left) Branch_ (SUB, BINAR, right, left)
#define MUL_(right, left) Branch_ (MUL, BINAR, right, left)
#define DIV_(right, left) Branch_ (DIV, BINAR, right, left)
#define POW_(right, left) Branch_ (POW, BINAR, right, left)
#define LOG_(right, left) Branch_ (LOG, BINAR, right, left)
#define MINUS_(branch) SUB_ (Branch_ (0, NUM, NULL, NULL), branch)
#define SQUARE_(branch) POW_ (branch, Branch (2, NUM, NULL, NULL))
#define RAD_(branch) POW (branch, Branch_ (0.5, NUM, NULL, NULL))
#define LN_(left) Branch_ (LN, UNAR, left, NULL)
#define SIN_(left) Branch_ (SIN, UNAR, left, NULL)
#define COS_(left) Branch_ (COS, UNAR, left, NULL)
#define SH_(branch) Branch_ (SH, UNAR, branch, NULL)
#define CH_(branch) Branch_ (CH, UNAR, branch, NULL)

DEF_UNAR (SIN, "sin", {
	return sin (OPERAND);
}, {
	return MUL_ (dL, COS_ (L));
})

DEF_UNAR (COS, "cos", {
	return cos (OPERAND);
}, {
	return MINUS (MUL_ (dL, SIN_ (L)));
})

DEF_UNAR (TAN, "tan", {
	return tan (OPERAND);
}, {
	return MINUS (dL, SQUARE_ (COS_ (L)));
})

DEF_UNAR (COT, "cot", {
	return 1 / tan (OPERAND);
}, {
	MINUS_ (MUL_ (ADD (SQUARE_ (L)), Branch_ (1, NUM, NULL, NULL)), dL);
})

DEF_UNAR (ASIN, "asin", {
	return asin (OPERAND);
}, {
	return DIV_ (dL, RAD_ (SUB_ (Branch_ (1, NUM, NULL, NULL), SQUARE_ (L))));
})

DEF_UNAR (ACOS, "acos", {
	return acos (OPERAND);
}, {
	return MINUS_ (DIV_ (dL, RAD_ (SUB_ (Branch_ (1, NUM, NULL, NULL), SQUARE_ (L)))));
})

DEF_UNAR (ATAN, "atan", {
	return atan (OPERAND);
}, {
	return DIV_ (dL, ADD_ (SQUARE_ (L)), Branch_ (1, NUM, NULL, NULL));
})

DEF_UNAR (ACOT, "acot", {
	return M_PI / 2 - atan (OPERAND);
}, {
	return MINUS_ (DIV_ (dL, ADD_ (SQUARE_ (L)), Branch_ (1, NUM, NULL, NULL)))
})

DEF_UNAR (SH, "sh", {
	return sinh (OPERAND);
}, {
	return MUL_ (dL, CH_ (L));
})

DEF_UNAR (CH, "ch", {
	return cosh (OPERAND);
}, {
	return MUL_ (dL, SH_ (L));
})

DEF_UNAR (TANH, "tanh", {
	return tanh (OPERAND);
}, {
	return DIV_ (dL, SQUARE_ (CH_ (L)));
})

DEF_UNAR (COTH, "coth", {
	return 1 / tanh (OPERAND);
}, {
	return MINUS_ (DIV_ (dL, SQUARE_ (SH_ (L))));
})

DEF_UNAR (ASH, "ash", {
	return asinh (OPERAND);
})

DEF_UNAR (ACH, "ach", {
	return acosh (OPERAND);
})

DEF_UNAR (ATANH, "atgan", {
	return atanh (OPERAND);
})

// DEF_UNAR (ACOTH, "acoth", {
// 	return 															//??????????????????????????????????????
// })

DEF_UNAR (EXP, "exp", {
	return exp (OPERAND);
})
DEF_UNAR (SQRT, "sqrt", {
	return sqrt (OPERAND);
})

DEF_UNAR (LN, "ln", {
	return log (OPERAND);
})

DEF_UNAR (LG, "lg", {
	return log10 (OPERAND);
})

DEF_UNAR (ABS, "abs", {
	return fabs (OPERAND);
})

DEF_UNAR (FACT, "fact", {
	double result = 1;
	for (ssize_t i = 0; i < OPERAND; i++) {
		result *= i;
	}
	return result;
})

#undef OPERAND
#undef LEFT