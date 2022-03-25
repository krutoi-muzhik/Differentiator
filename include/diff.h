#pragma once

#include "../MathTree/include/mathtree.h"

tree_t *Differentiate (tree_t *tree);
tree_t TreeCopy (tree_t *oldtree);
branch_t *BranchCopy (branch_t *oldbranch);
branch_t *BranchDiff_ (branch_t *oldbranch);
int Const (branch_t *branch);
int Func (branch_t *branch);