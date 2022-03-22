#include "../io/mathio.h"

#define LEFT branch->left

#define OPERAND Count (LEFT)

DEF_UNAR (SIN, "sin", {
	return sin (OPERAND);
})

DEF_UNAR (COS, "cos", {
	return cos (OPERAND);
})

DEF_UNAR (TAN, "tan", {
	return tan (OPERAND);
})

DEF_UNAR (COT, "cot", {
	return 1 / tan (OPERAND);
})

DEF_UNAR (ASIN, "asin", {
	return asin (OPERAND);
})

DEF_UNAR (ACOS, "acos", {
	return acos (OPERAND);
})

DEF_UNAR (ATAN, "atan", {
	return atan (OPERAND);
})

DEF_UNAR (ACOT, "acot", {
	return M_PI / 2 - atan (OPERAND);
})

DEF_UNAR (SH, "sh", {
	return sinh (OPERAND);
})

DEF_UNAR (CH, "ch", {
	return cosh (OPERAND);
})

DEF_UNAR (TANH, "tanh", {
	return tanh (OPERAND);
})

DEF_UNAR (COTH, "coth", {
	return 1 / tanh (OPERAND);
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