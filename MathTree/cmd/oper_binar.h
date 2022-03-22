DEF_BINAR (PLUS, '+', 1, {
	return Count (branch->left) + Count (branch->right);
})

DEF_BINAR (MINUS, '-', 1, {
	return Count (branch->left) - Count (branch->right);
})

DEF_BINAR (MUL, '*', 2, {
	return Count (branch->left) * Count (branch->right);
})

DEF_BINAR (DIV, '/', 2, {
	return Count (branch->left) / Count (branch->right);
})

DEF_BINAR (POW, '^', 3, {
	return powf (Count (branch->left), Count (branch->right));
})

DEF_BINAR (LOG, "log", 2, {
	return log (Count (branch->right)) / log (Count (branch->left));
})