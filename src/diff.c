#include "../include/diff.h"

tree_t *Differentiate (tree_t *tree) {
	tree_t *newtree = calloc (1, sizeof (tree_t));
	newtree->root = BranchDiff_ (tree->root);
	newtree->size = 0;
	return newtree;
}

tree_t TreeCopy (tree_t *oldtree) {
	tree_t newtree;
	TreeConstruct (&newtree);
	newtree.root = BranchCopy (oldtree->root);
	newtree.size = oldtree->size;
	return newtree;
}

branch_t *BranchCopy (branch_t *oldbranch) {
	branch_t *newbranch = Branch_ (oldbranch->data, oldbranch->type, NULL, NULL);
	if (oldbranch->left != NULL)
		newbranch->left = BranchCopy (oldbranch->left);
	if (oldbranch->right != NULL)
		newbranch->right = BranchCopy (oldbranch->right);
	return newbranch;
}

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

int IsConst (branch_t *branch) {
	switch (branch->type) {
		case NUM:
			return 1;
		case VAR:
			return 0;
		case BINAR:
			return (IsConst (branch->left) && IsConst (branch->right));
		case UNAR:
			return IsConst (branch->left);
		default:
			printf ("unknown branch type\n");
	}
	return -1;
}

int IsFunc (branch_t *branch) {
	switch (branch->type) {
		case NUM:
			return 0;
		case VAR:
			return 1;
		case UNAR:
			return IsFunc (branch->left);
		case BINAR:
			return (IsFunc (branch->left) || IsFunc (branch->right));
	}
	return -1;
}

void Simplify (tree_t *tree) {
	tree->root = BranchSimple (tree->root);
	return;
}

#define MUL_(right, left) Branch_ (MUL, BINAR, right, left)
#define MINUS_(branch) MUL_ (Branch_ (-1, NUM, NULL, NULL), branch)

branch_t *BranchSimple (branch_t *branch) {
	if ((branch->type == NUM) || (branch->type == VAR))
		return branch;

	if (IsConst (branch)) {
		branch_t *cnt = Branch_ (Count (branch), NUM, NULL, NULL);
		RecursiveDestruct (branch);
		return cnt;
	}

	if (branch->type == UNAR) {
		branch->left = BranchSimple (branch->left);
		return branch;
	}

	if (branch->type == BINAR) {
		branch->right = BranchSimple (branch->right);
		branch->left = BranchSimple (branch->left);

		switch ((int) branch->data) {
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
			case DIV:
				if (IsConst (branch->right)) {
					double res = Count (branch->right);
					if (IsEqual (0, res)) {
						printf ("division by zero detected alaarma\n");
						return branch;
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
				}
				break;
			case ADD:
				if (IsConst (branch->right)) {
					double res = Count (branch->right);
					if (IsEqual (0, res)) {
						RecursiveDestruct (branch->right);
						return branch->left;
					}
				}
				if (IsConst (branch->left)) {
					double res = Count (branch->left);
					if (IsEqual (0, res)) {
						RecursiveDestruct (branch->left);
						return branch->right;
					}
				}
				break;
			case SUB:
				if (IsConst (branch->right)) {
					double res = Count (branch->right);
					if (IsEqual (0, res)) {
						RecursiveDestruct (branch->right);
						return branch->left;
					}
				}
				if (IsConst (branch->left)) {
					double res = Count (branch->left);
					if (IsEqual (0, res)) {
						RecursiveDestruct (branch->left);
						return MINUS_ (branch->right);
					}
				}
				break;
			default:
				return branch;
		}
	}

	if (branch->type == UNAR) {
		branch->left = BranchSimple (branch->left);
		return branch;
	}
	return branch;
}

#undef MINUS_
#undef MUL_
