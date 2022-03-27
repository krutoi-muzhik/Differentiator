#include "include/diff.h"
#include "MathTree/include/mathtree.h"

void FullInOut (const char *inpath, const char *outpath);

int main () {

	FullInOut ("input.txt", "differentiate.txt");

	exit (EXIT_SUCCESS);
}

void FullInOut (const char *inpath, const char *outpath) {
	FILE *out = fopen (outpath, "w");

	tree_t *tree = Input (inpath);
	GVDump ("graphviz/undiff.gv", tree);
	fprintf (out, "Thanks for using DIFFERENTIATOR by krutoi muzhik \nf(x) = ");
	BranchOut (out, tree->root);
	fprintf (out, "\n");

	tree_t *difftree = Differentiate (tree);
	GVDump ("graphviz/diff.gv", difftree);
	fprintf (out, "f\'(x) = ");
	BranchOut (out, difftree->root);
	fprintf (out, "\n");

	Simplify (difftree);
	GVDump ("graphviz/simple.gv", difftree);
	fprintf (out, "ufter simplifying:\n= ");
	BranchOut (out, difftree->root);
	fprintf (out, "\n");
}