#include "include/diff.h"
#include "MathTree/include/mathtree.h"

int main () {
	tree_t *tree = Input ("input.txt");
	GVDump ("graphviz/old.gv", tree);

	tree_t *newtree = Differentiate (tree);
	GVDump ("graphviz/new.gv", newtree);

	exit (EXIT_SUCCESS);
}