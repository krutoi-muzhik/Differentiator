#include "../include/mathtree.h"
#include <math.h>

branch_t *Branch (branch_t *parent, data_t data) {
	branch_t *branch = calloc (1, sizeof (branch_t));
	branch->data = data;
	branch->parent = parent;
	branch->left = NULL;
	branch->right = NULL;
	return branch;
}

branch_t *Branch_ (branch_t *parent, data_t data, branch_type_t type) {
	branch_t *branch = Branch (parent, data);
	branch->type = type;
	return branch;
}

void RecursiveDestruct (branch_t *branch) {
	if (branch->left != NULL) {
		RecursiveDestruct (branch->left);
		branch->left = NULL;
		// if (branch->left == NULL)
		// 	printf ("\n%d left -> null\n\n", branch->data);
	}
	if (branch->right != NULL) {
		RecursiveDestruct (branch->right);
		branch->right = NULL;
		// if (branch->right == NULL)
		// 	printf ("\n%d right -> null\n\n", branch->data);
	}
	#ifdef DINAMIC_DATA
	free (branch->data);
	#endif

	free (branch);
	return;
}

void TreeConstruct (tree_t *tree) {
	tree->root = Branch (NULL, POISON);
	tree->size = 0;
}

void TreeDestruct (tree_t *tree) {
	RecursiveDestruct (tree->root);
	tree->root = NULL;
	tree->size = 0;
}

#define Out(func) fprintf (graph, "\tpeak%p [label = \"%s\"];\n", branch, func); break;

void Graph (FILE *graph, branch_t *branch) {
	switch (branch->type) {
		case BINAR:
			switch (branch->data) {
				case PLUS:	Out("+")
				case MINUS:	Out("-")
				case MUL:	Out("*")
				case DIV:	Out("/")
				case POW:	Out("^")
				case LOG:	Out("log")
			}
			break;
		case UNAR:
			switch (branch->data) {
				case SIN:	Out("sin")
				case COS:	Out("cos")
				case TAN:	Out("tan")
				case COT:	Out("cot")
				case ASIN:	Out("asin")
				case ACOS:	Out("acos")
				case ATAN:	Out("atan")
				case ACOT:	Out("acot")
				case SH:	Out("sh")
				case CH:	Out("ch")
				case TANH:	Out("tanh")
				case COTH:	Out("coth")
				case ASH:	Out("ash")
				case ACH:	Out("ach")
				case ATANH:	Out("atanh")
				case ACOTH:	Out("acoth")
				case EXP:	Out("exp")
				case SQRT:	Out("sqrt")
				case LN:	Out("ln")
				case LG:	Out("lg")
				case FACT:	Out("fact")
				case ABS:	Out("abs")
				default: printf ("unlnown oper %d\n", branch->data);
			}
			break;
		case VAR:
			fprintf (graph, "\tpeak%p [label = \"%c\" shape = box];\n", branch, branch->data);
			break;
		case NUM:
			fprintf (graph, "\tpeak%p [label = \"%d\" shape = box];\n", branch, branch->data);
			break;
	}

	if (branch->left != NULL) {
		fprintf (graph, "\t\tpeak%p -> peak%p\n", branch, branch->left);
		Graph (graph, branch->left);
	}
	if (branch->right != NULL) {
		fprintf (graph, "\t\tpeak%p -> peak%p\n", branch, branch->right);
		Graph (graph, branch->right);
	}
	return;
}

void GVDump (const char *pathname, tree_t *tree) {
	FILE *graph = fopen (pathname, "w");
	branch_t *branch = tree->root;
	fprintf (graph, "digraph TREE {\n\n");
	Graph (graph, branch);
	fprintf (graph, "}\n");
	fclose (graph);
	return;
}

void InsertBranch (branch_t *parent, size_t dir, data_t data) {
	branch_t *tmp;
	if (dir) {
		tmp = parent->right;
		parent->right = Branch (parent, data);
		parent->right->left = tmp;
	}
	else {
		tmp = parent->left;
		parent->left = Branch (parent, data);
		parent->left->left = tmp;
	}
	return;
}

double Count (branch_t *branch) {
	if (branch->type == BINAR) {
		#define DEF_BINAR(oper_num, oper, count_, diff_) {	\
			if (branch->data == oper_num) {							\
				count_												\
			}														\
		}															// end of define
																	// return is containeed in performance
		#include "../cmd/oper_binar.h"
		#undef DEF_BINAR

	} else if (branch->type == UNAR) {
		#define DEF_UNAR(oper_num, oper, count_, diff_) {		\
			if (branch->data == oper_num) {						\
				diff_											\
			}													\
		}														// end of define
																// return is containeed in performance
		#include "../cmd/oper_unar.h"
		#undef DEF_UNAR
	} else if (branch->type == NUM) {
		return branch->data;
	}
	return 0;
}

void Calculate (tree_t *tree) {
	double cnt = Count (tree->root);
	printf ("%lf\n", cnt);
}

#define skipspace while (isspace (buf[len])) len++;

#define skiptill(c) while (buf[len] != c) len++;

size_t GetLow (char *buf, branch_t *branch) {
	if (isalpha (buf[0])) {
		printf ("%c is alpha\n", buf[0]);
		size_t len = 0;
		while (isalpha (buf[len])) len++;
		skipspace

		if (buf[len] == '(')
			return GetFunc (buf, branch);
		return GetVar (buf, branch);
	}
	return GetNum (buf, branch);
}

size_t GetVar (char *buf, branch_t *branch) {
	size_t len = 0;
	skipspace
	branch->type = VAR;
	branch->data = buf[0];
	len++;
	skipspace
	return len;
}

size_t GetNum (char *buf, branch_t *branch) {
	size_t len = 0;
	branch->type = NUM;
	int num = 0;
	if (buf[len] == '-') {
		len++;
		while (isdigit (buf[len])) {
			num = num * 10 - buf[len] + 48;
			len++;
		}
	} else {
		while (isdigit (buf[len])) {
			num = num * 10 + buf[len] - 48;
			len++;
		}
	}
	branch->data = num;
	while (isspace (buf[len])) len++;
	return len;
}

size_t GetMulDiv (char *buf, branch_t **current) {
	size_t len = 0;
	skipspace
	len += GetLog (buf + len, current);
	skipspace

	while ((buf[len] == '*') || (buf[len] == '/')) {
		(*current)->parent = Branch_ (NULL, buf[len], BINAR);
		(*current)->parent->left = (*current);
		(*current) = (*current)->parent;

		len++;
		skipspace
		(*current)->right = Branch (*current, POISON);
		len += GetLog (buf + len, &(*current)->right);

		skipspace
	}
	return len;
}

size_t GetPlusMinus (char *buf, branch_t **current) {
	size_t len = 0;
	skipspace
	len += GetMulDiv (buf + len, current);
	skipspace

	while ((buf[len] == '+') || (buf[len] == '-')) {
		(*current)->parent = Branch_ (NULL, buf[len], BINAR);
		(*current)->parent->left = (*current);
		(*current) = (*current)->parent;

		len++;
		skipspace
		(*current)->right = Branch (*current, POISON);
		len += GetMulDiv (buf + len, &((*current)->right));

		skipspace
	}
	return len;
}

size_t GetPow (char *buf, branch_t **current) {
	size_t len = 0;
	skipspace
	len += GetLow (buf + len, *current);
	skipspace

	if (buf[len] == '^') {
		(*current)->parent = Branch_ (NULL, '^', BINAR);
		(*current)->parent->left = (*current);
		(*current) = (*current)->parent;

		len++;
		skipspace
		(*current)->right = Branch (*current, POISON);
		len += GetLow (buf + len, (*current)->right);

		skipspace
	}
	return len;
}

size_t GetLog (char *buf, branch_t **current) {
	size_t len = 0;
	skipspace
	len += GetPow (buf + len, current);
	skipspace

	if ((buf[len] == 'l') && (buf[len + 1] == 'o') && (buf[len + 2] == 'g')) {
		(*current)->parent = Branch_ (NULL, LOG, BINAR);
		(*current)->parent->left = (*current);
		(*current) = (*current)->parent;

		len += 3;
		skipspace
		(*current)->right = Branch (*current, POISON);
		len += GetPow (buf + len, &(*current)->right);

		skipspace
	}
	return len;
}

size_t GetFunc (char *buf, branch_t *current) {
	size_t len = 0;
	skipspace

	current->type = UNAR;
	char *func = (char *) calloc (FUNC_LEN, sizeof (char));
	size_t i;
	for (i = 0; isalpha (buf[len]); i++) {
		if (i >= FUNC_LEN) {
			printf ("too long function %s.. \n", func);
			break;
		}
		func[i] = buf[len];
		len++;
	}

	skiptill ('(')
	len++;

	#define DEF_UNAR(oper_num, oper, count_, diff_) {				\
		if (!strcmp (oper, func)) {									\
			current->data = oper_num;								\
			current->left = Branch (current, POISON);				\
			len += GetPlusMinus (buf + len, &(current->left));		\
		}															\
	}																// end of define

	#include "../cmd/oper_unar.h"
	#undef DEF_UNAR

	free (func);
	skiptill (')')
	len++;
	return len;

}

int isoper (char c) {
	if ((c == MINUS) || (c == PLUS) || (c == POW) || (c == DIV) || (c == MUL))
		return 1;
	return 0;
}

tree_t *Input (const char *pathname) {
	tree_t tree;
	TreeConstruct (&tree);
	FILE *inp = fopen (pathname, "r+");
	char buf[BUF_SIZE];
	size_t len = 0;
	size_t nread = fread (buf, sizeof (char), BUF_SIZE, inp);
	fclose (inp);
	branch_t *tmp = Branch (NULL, POISON);

	len = GetPlusMinus (buf, &tmp);
	tree->root = tmp;
	printf ("nread = %ld, len = %ld\n", nread, len);

	return tree;
}

void WriteBase (FILE *out, branch_t *branch) {
	if (branch->type == NUM) {
		fprintf (out, "%d ", branch->data);
		return;
	}
	if (branch->type == BINAR) {
		WriteBase (out, branch->left);
		fprintf (out, "%c ", branch->data);
		WriteBase (out, branch->right);
		return;
	}
	printf ("unknown branch type\n");
	return;
}

void SaveBase (const char *pathname, tree_t* tree) {
	FILE *out = fopen (pathname, "w");
	fprintf (out, "CALCULATOR by krutoi_muzhik crated this base\n\n");
	WriteBase (out, tree->root);
	fclose (out);
	return;
}

