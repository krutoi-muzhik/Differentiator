#include "../include/mathtree.h"
#include <math.h>


#define MicroConst 0.0001

int IsEqual (double a, double b) {
	if (fabs (a - b) <= MicroConst) return 1;
	return 0;
}

branch_t *Branch (data_t data, branch_t *left, branch_t *right) {
	branch_t *branch = calloc (1, sizeof (branch_t));
	branch->data = data;
	branch->left = left;
	branch->right = right;
	return branch;
}

branch_t *Branch_ (data_t data, branch_type_t type, branch_t *left, branch_t *right) {
	branch_t *branch = Branch (data, left, right);
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

tree_t *TreeConstruct () {
	tree_t *tree = calloc (1, sizeof (tree_t));
	tree->root = Branch (POISON, NULL, NULL);
	tree->size = 0;
	return tree;
}

void TreeDestruct (tree_t *tree) {
	RecursiveDestruct (tree->root);
	tree->root = NULL;
	tree->size = 0;
	free (tree);
	return;
}

#define Out(func) fprintf (graph, "\tpeak%p [label = \"%s\"];\n", branch, func); break;

void Graph (FILE *graph, branch_t *branch) {
	switch (branch->type) {
		case BINAR:
			switch ((int) branch->data) {
				case ADD:	Out("+")
				case SUB:	Out("-")
				case MUL:	Out("*")
				case DIV:	Out("/")
				case POW:	Out("^")
				case LOG:	Out("log")
			}
			break;
		case UNAR:
			switch ((int) branch->data) {
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
				default: printf ("unknown oper %.3lf\n", branch->data);
			}
			break;
		case VAR:
			fprintf (graph, "\tpeak%p [label = \"%c\" shape = box];\n", branch, (int) branch->data);
			break;
		case NUM:
			fprintf (graph, "\tpeak%p [label = \"%.3lf\" shape = box];\n", branch, branch->data);
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

#undef Out

void GVDump (const char *pathname, tree_t *tree) {
	FILE *graph = fopen (pathname, "w");
	branch_t *branch = tree->root;
	fprintf (graph, "digraph TREE {\n\n");
	Graph (graph, branch);
	fprintf (graph, "}\n");
	fclose (graph);
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
				count_											\
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

double Calculate (tree_t *tree) {
	double cnt = Count (tree->root);
	printf ("%.3lf\n", cnt);
	return cnt;
}

#define skipspace while (isspace (buf[len])) len++;

#define skiptill(c) while (buf[len] != c) len++;

size_t GetLow (char *buf, branch_t **branch) {
	if (buf[0] == '(')
		return GetBracket (buf, branch);
	if (isalpha (buf[0])) {
		// printf ("%c is alpha\n", buf[0]);
		size_t len = 0;
		while (isalpha (buf[len])) len++;
		skipspace

		if (buf[len] == '(')
			return GetFunc (buf, *branch);
		return GetVar (buf, *branch);
	}
	return GetNum (buf, *branch);
}

size_t GetBracket (char *buf, branch_t **branch) {
	size_t len = 0;
	skiptill ('(')
	len ++;
	len += GetAddSub (buf + len, branch);
	skiptill (')')
	len ++;
	return len;
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
		*current = Branch_ (buf[len], BINAR, *current, NULL);

		len++;
		skipspace
		(*current)->right = Branch (POISON, NULL, NULL);
		len += GetLog (buf + len, &(*current)->right);

		skipspace
	}
	return len;
}

size_t GetAddSub (char *buf, branch_t **current) {
	size_t len = 0;
	skipspace
	len += GetMulDiv (buf + len, current);
	skipspace

	while ((buf[len] == '+') || (buf[len] == '-')) {
		*current = Branch_ (buf[len], BINAR, *current, NULL);

		len++;
		skipspace
		(*current)->right = Branch (POISON, NULL, NULL);
		len += GetMulDiv (buf + len, &((*current)->right));

		skipspace
	}
	return len;
}

size_t GetPow (char *buf, branch_t **current) {
	size_t len = 0;
	skipspace
	len += GetLow (buf + len, current);
	skipspace

	if (buf[len] == '^') {
		*current = Branch_ ('^', BINAR, *current, NULL);

		len++;
		skipspace
		(*current)->right = Branch (POISON, NULL, NULL);
		len += GetLow (buf + len, &(*current)->right);

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
		*current = Branch_ (LOG, BINAR, *current, NULL);

		len += 3;
		skipspace
		(*current)->right = Branch (POISON, NULL, NULL);
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
			current->left = Branch (POISON, NULL, NULL);			\
			len += GetAddSub (buf + len, &(current->left));		\
		}															\
	}																// end of define

	#include "../cmd/oper_unar.h"
	#undef DEF_UNAR

	free (func);
	skiptill (')')
	len++;
	return len;

}

#undef skiptill
#undef skipspace

int isoper (char c) {
	if ((c == SUB) || (c == ADD) || (c == POW) || (c == DIV) || (c == MUL))
		return 1;
	return 0;
}

tree_t *Input (const char *pathname) {
	tree_t *tree = TreeConstruct ();
	FILE *inp = fopen (pathname, "r+");
	char buf[BUF_SIZE];
	size_t len = 0;
	size_t nread = fread (buf, sizeof (char), BUF_SIZE, inp);
	fclose (inp);
	branch_t *tmp = Branch (POISON, NULL, NULL);

	len = GetAddSub (buf, &tmp);
	tree->root = tmp;
	// printf ("nread = %ld, len = %ld\n", nread, len);

	return tree;
}

void BranchOut (FILE *out, branch_t *branch) {
	switch (branch->type) {
		case NUM:
			fprintf (out, "%.3lf", branch->data);
			break;

		case BINAR:
			if (Prior (branch->left) > Prior (branch)) {
				fprintf (out, "(");
				BranchOut (out, branch->left);
				fprintf (out, ")");
			} else BranchOut (out, branch->left);

			if (IsEqual (branch->data, LOG))
				fprintf (out, " log ");
			else
				fprintf (out, " %c ", (int) branch->data);
			
			if (Prior (branch->right) > Prior (branch)) {
				fprintf (out, "(");
				BranchOut (out, branch->right);
				fprintf (out, ")");
			} else BranchOut (out, branch->right);
			break;

		case UNAR:
			#define DEF_UNAR(oper_num, oper, calc_, diff_) {	\
				if (branch->data == oper_num) {					\
					fprintf (out, "%s (", oper);				\
					BranchOut (out, branch->left);				\
					fprintf (out, ")");						\
				}												\
			}													// end of define
			#include "../cmd/oper_unar.h"
			#undef DEF_UNAR
			break;

		case VAR:
			fprintf (out, "%c", (int) branch->data);
			break;

		default:
			printf ("unknown branch type\n");
	}
	return;
}

void TreeOut (const char *pathname, tree_t* tree) {
	FILE *out = fopen (pathname, "w");
	BranchOut (out, tree->root);
	fclose (out);
	return;
}

int Prior (branch_t *branch) {
	switch (branch->type) {
		case NUM: return 0;
		case VAR: return 0;
		case UNAR: return 1;
		case BINAR:
			switch ((int) branch->data) {
				case POW: return 2;
				case LOG: return 3;
				case MUL: return 4;
				case DIV: return 4;
				case ADD: return 5;
				case SUB: return 5;
				default: printf ("unknown binar operator %.3lf\n", branch->data); return UNKNOWN_OPER;
			}
		default: printf ("unknown branch type\n"); return UNKNOWN_TYPE;
	}
}