DEF_BINAR (PLUS, '+', {
	return Count (branch->left) + Count (branch->right);
}, {
	newbranch->type = BINAR;
	newbranch->data = PLUS;
	newbranch->left = BranchDiff_ (oldbranch->left, newbranch);
	newbranch->right = BranchDiff (oldbranch->right, newbranch);
})

DEF_BINAR (MINUS, '-', {
	return Count (branch->left) - Count (branch->right);
}, {
	newbranch->type = BINAR;
	newbranch->data = MINUS;
	newbranch->left = BranchDiff (oldbranch->left, newbranch);
	newbranch->right = BranchDiff (oldbranch->right, newbranch);
	return newbranch;
})

DEF_BINAR (MUL, '*', {
	return Count (branch->left) * Count (branch->right);
}, {
	newbranch->type = BINAR;
	newbranch->data = PLUS;

	newbranch->left = Branch_ (newbranch, MUL, BINAR);
	newbranch->left->left = BranchDiff_ (oldbranch->left, newbranch->left);
	newbranch->left->right = BranchCopy_ (oldbranch->right, newbranch->left);

	newbranch->right = Branch_ (newbranch, MUL, BINAR);
	newbranch->right->left = BranchCopy_ (oldbranch->left, newbranch->right);
	newbranch->right->right = BranchDiff_ (oldbranch->right, newbranch->right);

	return newbranch;
})

DEF_BINAR (DIV, '/', {
	return Count (branch->left) / Count (branch->right);
}, {
	newbranch->type = BINAR;
	newbranch->data = DIV;

	newbranch->right = Branch_ (newbranch, POW, BINAR);
	newbranch->right->left = BranchCopy_ (oldbranch->right, newbranch->right);
	newbranch->right->right = Branch_ (newbranch->right, 2, NUM);

	newbranch->left = Branch_ (newbranch, MINUS, BINAR);

	newbranch->left->left = Branch_ (newbranch->left, MUL, BINAR);
	newbranch->left->left->left = BranchDiff_ (oldbranch->left, newbranch->left->left);
	newbranch->left->left->right = BranchCopy_ (oldbranch->right, newbranch->left->left);

	newbranch->left->right = Branch_ (newbranch->left, NUL, BINAR);
	newbranch->left->right->left = BranchCopy_ (oldbranch->left, newbranch->left->right);
	newbranch->left->right->right = BranchDiff_ (oldbranch->right, newbranch->left->right);

	return newbranch;
})

DEF_BINAR (POW, '^', {
	return powf (Count (branch->left), Count (branch->right));
}, {

})

DEF_BINAR (LOG, "log", {
	return log (Count (branch->right)) / log (Count (branch->left));
}, {

})