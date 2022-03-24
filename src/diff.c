#include "../include/diff.h"

tree_t *Differentiate (tree_t *tree) {
	tree_t newtree = TreeCopy (tree);

}

tree_t TreeCopy (tree_t *oldtree) {
	tree_t newtree;
	TreeConstruct (&newtree);
	newtree.root = BranchCopy (oldtree->root);
	newtree.size = oldtree->size;
	return newtree;
}

branch_t *BranchCopy (branch_t *oldbranch) {
	branch_t *newbranch = Branch_ (oldbranch->parent, oldbranch->data, oldbranch->type);
	if (oldbranch->left != NULL)
		newbranch->left = BranchCopy (oldbranch->left);
	if (oldbranch->right != NULL)
		newbranch->right = BranchCopy (oldbranch->right);
	return newbranch;
}

branch_t *BranchCopy_ (branch_t *oldbranch, branch_t *parent) {
	branch_t *newbranch = BranchCopy (oldbranch);
	newbranch->parent = parent;
	return newbranch;
}

branch_t *BranchDiff (branch_t *oldbranch) {
	branch_t *newbranch = Branch (NULL, POISON);
	switch (oldbranch->type):
		case NUM:
			newbranch->type = NUM;
			newbranch->data = 0;
			break;
		case VAR:
			newbranch->type = NUM;
			newbranch->data = 1;
			break;
		case BINAR:
			#define DEF_BINAR(oper, oper_num, count_, diff_) {	\
				if (oldbranch->data == oper_num) {				\
					diff_ 										\
				}												\
			}													// end of define
			#include "../MathTree/cmd/oper_binar.h"
			#undef DEF_BINAR
			break;

		case UNAR:
			#define DEF_UNAR(oper, oper_num, count_, diff_) {	\
				if (oldbranch->data = oper_num) {				\
					diff_ 										\
				}												\
			}													// end of define
			#include "../MathTree/cmd/oper_unar.h"
			#undef DEF_UNAR
			break;

		default: printf ("unknown type\n");

	return newbranch;
}

branch_t *BranchDiff_ (branch_t *oldbranch, branch_t *parent) {
	branch_t *newbranch = BranchDiff (oldbranch);
	newbranch->parent = parent;
	return newbranch;
}

int Const (branch_t *branch) {
	switch (branch->type) {
		case NUM:
			return 1;
		case VAR:
			return 0;
		case BUNAR:
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
}
