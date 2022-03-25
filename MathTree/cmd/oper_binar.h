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

DEF_BINAR (ADD, '+', {
	return Count (branch->left) + Count (branch->right);
}, {
	return ADD_ (dL, dR);
})

DEF_BINAR (SUB, '-', {
	return Count (branch->left) - Count (branch->right);
}, {
	return SUB_ (dL, dR);
})

DEF_BINAR (MUL, '*', {
	return Count (branch->left) * Count (branch->right);
}, {
	return ADD_ (MUL_ (dL, R), MUL_ (L, dR));
})

DEF_BINAR (DIV, '/', {
	return Count (branch->left) / Count (branch->right);
}, {
	return DIV_ (SUB_ (MUL_ (dL, R), MUL_ (L, dR)), POW_ (R, Branch_ (2, NUM, NULL, NULL)));
})

DEF_BINAR (POW, '^', {
	return powf (Count (branch->left), Count (branch->right));
}, {
	return MUL_ (POW_ (L, R), ADD_ (MUL_ (dR, LN_ (L)), DIV_ (MUL_ (dL, R), L)));
})

DEF_BINAR (LOG, "log", {
	return log (Count (branch->right)) / log (Count (branch->left));
}, {
	return ADD_ (DIV_ (dR, MUL_ (R, LN_ (L))), DIV_ (LN_ (R), MUL_ (L, POW_ (LN_ (L), Branch_ (2, NUM, NULL, NULL)))));
})

#undef L
#undef R
#undef dL
#undef dR
#undef LOG_
#undef POW_
#undef ADD_
#undef SUB_
#undef MUL_
#undef DIV_
#undef LN_
