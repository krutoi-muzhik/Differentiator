#include "include/diff.h"
#include "MathTree/include/mathtree.h"

int main () {
	tree_t tree;
	TreeConstruct (&tree);
	Input ("input.txt", &tree);

	GVDump ("graphviz/graph.gv", &tree);
	exit (EXIT_SUCCESS);
}