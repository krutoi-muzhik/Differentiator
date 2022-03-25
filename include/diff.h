#pragma once

#include "../MathTree/include/mathtree.h"

enum REPEAT {
	NSIMPLE = 3
};

tree_t *Differentiate (tree_t *tree);
tree_t TreeCopy (tree_t *oldtree);
branch_t *BranchCopy (branch_t *oldbranch);
branch_t *BranchDiff_ (branch_t *oldbranch);
int IsConst (branch_t *branch);
int IsFunc (branch_t *branch);
void Simplify (tree_t *tree);
branch_t *BranchSimple (branch_t *branch);