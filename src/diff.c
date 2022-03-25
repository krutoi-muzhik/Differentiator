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

int Const (branch_t *branch) {
	switch (branch->type) {
		case NUM:
			return 1;
		case VAR:
			return 0;
		case BINAR:
			return (Const (branch->left) && Const (branch->right));
		case UNAR:
			return Const (branch->left);
		default:
			printf ("unknown branch type\n");
	}
	return -1;
}

int Func (branch_t *branch) {
	switch (branch->type) {
		case NUM:
			return 0;
		case VAR:
			return 1;
		case UNAR:
			return Func (branch->left);
		case BINAR:
			return (Func (branch->left) || Func (branch->right));
	}
	return -1;
}
