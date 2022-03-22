#include "../include/tree.h"
#include "mathio.h"

#define skipspace while (isspace (buf[len])) len++;

#define skiptill(c) while (buf[len] != c) len++;

size_t GetNF (char *buf, branch_t *branch) {
	if (isalpha (buf[0])) {
		return GetFunc (buf, branch);
	}
	return GetNum (buf, branch);
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
	len += GetNF (buf + len, *current);
	skipspace

	if (buf[len] == '^') {
		(*current)->parent = Branch_ (NULL, '^', BINAR);
		(*current)->parent->left = (*current);
		(*current) = (*current)->parent;

		len++;
		skipspace
		(*current)->right = Branch (*current, POISON);
		len += GetNF (buf + len, (*current)->right);

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

	#define DEF_UNAR(oper_num, oper, performance) {				\
		if (!strcmp (oper, func)) {								\
			current->data = oper_num;							\
			current->left = Branch (current, POISON);			\
			len += GetPlusMinus (buf + len, &(current->left));	\
		}														\
	}															// end of define

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

void Input (const char *pathname, tree_t *tree) {
	FILE *inp = fopen (pathname, "r+");
	char buf[BUF_SIZE];
	size_t len = 0;
	size_t nread = fread (buf, sizeof (char), BUF_SIZE, inp);
	fclose (inp);

	branch_t *tmp = Branch (NULL, POISON);

	len = GetPlusMinus (buf, &tmp);
	tree->root = tmp;
	printf ("nread = %ld, len = %ld\n", nread, len);
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
