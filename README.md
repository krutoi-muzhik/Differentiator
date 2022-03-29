# Introduction

As the name of the programm implies, it is designed to calculate the derivative of any function you want.

# Run

To compile clone the repo and use "make diff"

Write the function you want to differentiate in file "input.txt"

Use "make run" to run the programm, and the derivative will be written in "differetiate.txt"

After all use "make clean" to delete all object and executable files 

# Implementation


## Calculate

The big part of programm is my library of tree for math expressions. You can see it's implementation in my project [Calculator](https://github.com/krutoi-muzhik/Calculator)

## Differentiate

The kernel of programm is function BranchDiff_ that works recursively

```C
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
```

As you can see, this function use DSL and include "oper_unar.h" or "oper_binar.h", where the instructions are contained. I use DSL so as not to clog the code with about 20 extra "if" or "switch - case" instructions for every operator we can face in our math expression

Here is an example of instructions for operation "multiply" from "oper_binar.h":

```C
DEF_BINAR (MUL, '*', {
	return Count (branch->left) * Count (branch->right);
}, {
	return ADD_ (MUL_ (dL, R), MUL_ (L, dR));
})
```

The first block of code is for calculator, to calculate the containment of tree branches below and multiply them.

The second block of code is used by differentiator to use derivatives of left and right branches and join them using math rules, that everybody knows.

MUL_ and ADD_ instructions are defined as:

```C
#define L BranchCopy (oldbranch->left)
#define R BranchCopy (oldbranch->right)
#define dR BranchDiff_ (oldbranch->right)
#define dL BranchDiff_ (oldbranch->left)
#define ADD_(right, left) Branch_ (ADD, BINAR, right, left)
#define SUB_(right, left) Branch_ (SUB, BINAR, right, left)
#define MUL_(right, left) Branch_ (MUL, BINAR, right, left)
#define DIV_(right, left) Branch_ (DIV, BINAR, right, left)
#define POW_(right, left) Branch_ (POW, BINAR, right, left)
#define LOG_(right, left) Branch_ (LOG, BINAR, right, left)
#define LN_(left) Branch_ (LN, UNAR, left, NULL)
```

## Simplify

The last step is simplifying the expression. The function BranchSimple is designed specially for that.

For example in this way it simplifies the branch with operation "multiply"

```C
case MUL:
	if (IsConst (branch->right)) {
		double res = Count (branch->right);
		if (IsEqual (0, res)) {
			RecursiveDestruct (branch->left);
			return branch->right;
		}
		if (IsEqual (1, res)) {
			RecursiveDestruct (branch->right);
			return branch->left;
		}
	}
	if (IsConst (branch->left)) {
		double res = Count (branch->left);
		if (IsEqual (0, res)) {
			RecursiveDestruct (branch->right);
			return branch->left;
		}
		if (IsEqual (1, res)) {
			RecursiveDestruct (branch->left);
			return branch->right;
		}
	}
	break;
```

If The branch is multiplicated by zero, it becomes zero, and can be destruted, and if it is multiplicated by one, it saves it's own value, and the branch equal to one can be destructed.

# Example

The primary expression is  f(x) = 2 * x - 3 - x ^ 3 - sin (x) + cos (2 * x) * x

The differentiated is f'(x) = 0.000 * x + 2.000 * 1.000 - 0.000 - x ^ 3.000 * (0.000 * ln (x) + 1.000 * 3.000 / x) - 1.000 * cos (x) + -1.000 * (0.000 * x + 2.000 * 1.000) * sin (2.000 * x) * x + cos (2.000 * x) * 1.000

And after simplifying we get f'(x) = 2 - x ^ 3 * 3 / x - cos (x) + -1 * 2 * sin (2 * x) * x + cos (2 * x)

And using GraphViz dump we can see the tree:

Primary:

![primary](https://github.com/krutoi-muzhik/Differentiator/blob/main/graphviz/primary.png)

After differentiating:

![Unsimplified](https://github.com/krutoi-muzhik/Differentiator/blob/main/graphviz/deffer.png)

After simplifying:

![Simplified](https://github.com/krutoi-muzhik/Differentiator/blob/main/graphviz/simple.png)
