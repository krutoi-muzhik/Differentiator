#pragma once

#include "../MathTree/include/mathtree.h"

tree_t *Differentiate (tree_t *tree);
tree_t TreeCopy (tree_t *oldtree);
branch_t *BranchCopy (branch_t *oldbranch);
branch_t *BranchCopy_ (branch_t *oldbranch, branch_t *parent)
branch_t *BranchDiff (branch_t *oldbranch);
branch_t *BranchDiff_ (branch_t *oldbranch, branch_t *parent;