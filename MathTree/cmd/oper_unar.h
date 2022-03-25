#define LEFT branch->left

#define OPERAND Count (LEFT)

#define L BranchCopy (oldbranch->left)
#define dL BranchDiff_ (oldbranch->left)
#define ADD_(right, left) Branch_ (ADD, BINAR, right, left)
#define SUB_(right, left) Branch_ (SUB, BINAR, right, left)
#define MUL_(right, left) Branch_ (MUL, BINAR, right, left)
#define DIV_(right, left) Branch_ (DIV, BINAR, right, left)
#define POW_(right, left) Branch_ (POW, BINAR, right, left)
#define LOG_(right, left) Branch_ (LOG, BINAR, right, left)
#define MINUS_(branch) MUL_ (Branch_ (-1, NUM, NULL, NULL), branch)
#define SQUARE_(branch) POW_ (branch, Branch_ (2, NUM, NULL, NULL))
#define SQRT_(branch) POW_ (branch, DIV_ (Branch_ (1, NUM, NULL, NULL), Branch_ (2, NUM, NULL, NULL)))
#define LN_(left) Branch_ (LN, UNAR, left, NULL)
#define SIN_(left) Branch_ (SIN, UNAR, left, NULL)
#define COS_(left) Branch_ (COS, UNAR, left, NULL)
#define SH_(branch) Branch_ (SH, UNAR, branch, NULL)
#define CH_(branch) Branch_ (CH, UNAR, branch, NULL)
#define EXP_(branch) Branch_ (EXP, UNAR, branch, NULL)

DEF_UNAR (SIN, "sin", {
	return sin (OPERAND);
}, {
	return MUL_ (dL, COS_ (L));
})

DEF_UNAR (COS, "cos", {
	return cos (OPERAND);
}, {
	return MINUS_ (MUL_ (dL, SIN_ (L)));
})

DEF_UNAR (TAN, "tan", {
	return tan (OPERAND);
}, {
	return DIV_ (dL, SQUARE_ (COS_ (L)));
})

DEF_UNAR (COT, "cot", {
	return 1 / tan (OPERAND);
}, {
	return MINUS_ (MUL_ (ADD_ (SQUARE_ (L), Branch_ (1, NUM, NULL, NULL)), dL));
})

DEF_UNAR (ASIN, "asin", {
	return asin (OPERAND);
}, {
	return DIV_ (dL, SQRT_ (SUB_ (Branch_ (1, NUM, NULL, NULL), SQUARE_ (L))));
})

DEF_UNAR (ACOS, "acos", {
	return acos (OPERAND);
}, {
	return MINUS_ (DIV_ (dL, SQRT_ (SUB_ (Branch_ (1, NUM, NULL, NULL), SQUARE_ (L)))));
})

DEF_UNAR (ATAN, "atan", {
	return atan (OPERAND);
}, {
	return DIV_ (dL, ADD_ (SQUARE_ (L), Branch_ (1, NUM, NULL, NULL)));
})

DEF_UNAR (ACOT, "acot", {
	return M_PI / 2 - atan (OPERAND);
}, {
	return MINUS_ (DIV_ (dL, ADD_ (SQUARE_ (L), Branch_ (1, NUM, NULL, NULL))));
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
}, {
	return DIV_ (dL, SQRT_ (ADD_ (SQUARE_ (L), Branch_ (1, NUM, NULL, NULL))));
})

DEF_UNAR (ACH, "ach", {
	return acosh (OPERAND);
}, {
	return DIV_ (dL, SQRT_ (SUB_ (SQUARE_ (L), Branch_ (1, NUM, NULL, NULL))));
})

DEF_UNAR (ATANH, "atgan", {
	return atanh (OPERAND);
}, {
	return DIV_ (dL, SUB_ (Branch_ (1, NUM, NULL, NULL), SQUARE_ (L)));
})

// DEF_UNAR (ACOTH, "acoth", {
// 	return 															//??????????????????????????????????????
// })

DEF_UNAR (EXP, "exp", {
	return exp (OPERAND);
}, {
	return MUL_ (dL, EXP_ (L));
})

DEF_UNAR (SQRT, "sqrt", {
	return sqrt (OPERAND);
}, {
	return DIV_ (dL, MUL_ (Branch_ (2, NUM, NULL, NULL), SQRT_ (L)));
})

DEF_UNAR (LN, "ln", {
	return log (OPERAND);
}, {
	return DIV_ (dL, L);
})

DEF_UNAR (LG, "lg", {
	return log10 (OPERAND);
}, {
	return DIV_ (dL, MUL_ (LN_ (Branch_ (10, NUM, NULL, NULL)), L));
})

DEF_UNAR (ABS, "abs", {
	return fabs (OPERAND);
}, {
	return NULL;
})

DEF_UNAR (FACT, "fact", {
	double result = 1;
	for (ssize_t i = 0; i < OPERAND; i++) {
		result *= i;
	}
	return result;
}, {
	return NULL;
})

#undef OPERAND
#undef LEFT

#undef L
#undef dL
#undef ADD_
#undef SUB_
#undef MUL_
#undef DIV_
#undef POW_
#undef LOG_
#undef MINUS_
#undef SQUARE_
#undef SQRT_
#undef LN_
#undef SIN_
#undef COS_
#undef SH_
#undef CH_
#undef EXP_