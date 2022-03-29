# Introduction

As the name of the programm implies, it is designed to calculate the derivative of any function you want.

#Implementation

The big part of programm is my library of tree for math expressions. You can see it's implementation in my project [Calculator](https://github.com/krutoi-muzhik/Calculator)

The kernel of programm is function BranchDiff_ that works recursively
'''C
branch_t *BranchDiff_ (branch_t *oldbranch) {
	switch (oldbranch->type) {
		case NUM:
			return Branch_ (0, NUM, NULL, NULL);
		case VAR:
			return Branch_ (1, NUM, NULL, NULL);
		case BINAR:
			#define DEF_BINAR(oper_num, oper, count_, diff_) {	\
				if (oldbranch->data == oper_num) {				\
					diff_ 										\
				}												\
			}													// end of define
			#include "../MathTree/cmd/oper_binar.h"
			#undef DEF_BINAR

		case UNAR:
			#define DEF_UNAR(oper_num, oper, count_, diff_) {	\
				if (oldbranch->data == oper_num) {				\
					diff_ 										\
				}												\
			}													// end of define
			#include "../MathTree/cmd/oper_unar.h"
			#undef DEF_UNAR

		default: printf ("unknown type\n");
	}

	return NULL;
}
'''
