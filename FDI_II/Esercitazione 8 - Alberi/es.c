#include "tree_int.h"

/* ES 1-2 */
Node * BstInsert(const ElemType *e, Node *t) {
	if (IsEmptyTree(t)) {
		return CreateRootTree(e, CreateEmptyTree(), CreateEmptyTree());
	}
	else if (ElemCompare(e, GetRootValueTree(t)) <= 0) {
		return CreateRootTree(GetRootValueTree(t), BstInsert(e, LeftTree(t)), RightTree(t));
	}
	else {
		return CreateRootTree(GetRootValueTree(t), LeftTree(t), BstInsert(e, RightTree(t)));
	}
}

/* ES 3 */
void CountDominantResolver(const Node *t, int * count) {
	if (IsEmptyTree(t) || IsLeafTree(t))
		return;
	int l = 0, r = 0;
	if (LeftTree(t))
		l = LeftTree(t)->value;
	if (RightTree(t))
		r = RightTree(t)->value;

	if (t->value > l + r)
		(*count)++;
	CountDominantResolver(LeftTree(t), count);
	CountDominantResolver(RightTree(t), count);
}

int CountDominant(const Node*t) {
	int count = 0;
	CountDominantResolver(t, &count);
	return count;
}

/* ES 4 */
const ElemType * BstTreeMax(const Node *n) {
	if (IsEmptyTree(n))
		return NULL;

	const Node * tmp = n;
	const ElemType * max = &tmp->value;
	while (!IsEmptyTree(tmp)) {
		max = &tmp->value;
		tmp = RightTree(tmp);
	}
	return max;
}

/* ES 5 */
void backtracking_max_search(const Node *t, const ElemType ** max) {
	if (IsEmptyTree(t))
		return;

	if (ElemCompare(GetRootValueTree(t), *max) > 0)
		*max = GetRootValueTree(t);
	backtracking_max_search(LeftTree(t), max);
	backtracking_max_search(RightTree(t), max);
}

const ElemType * MaxTree(const Node * n) {
	if (IsEmptyTree(n))
		return NULL;

	const ElemType * max = GetRootValueTree(n);
	backtracking_max_search(n, &max);
	return max;
}

/* ES 6 */
const ElemType * BstTreeMin(const Node *n) {
	if (IsEmptyTree(n))
		return NULL;

	const Node * tmp = n;
	const ElemType * min = &tmp->value;
	while (!IsEmptyTree(tmp)) {
		min = &tmp->value;
		tmp = LeftTree(tmp);
	}
	return min;
}

/* ES 7 */
void backtracking_min_search(const Node *t, const ElemType ** min) {
	if (IsEmptyTree(t))
		return;

	if (ElemCompare(GetRootValueTree(t), *min) < 0)
		*min = GetRootValueTree(t);
	backtracking_min_search(LeftTree(t), min);
	backtracking_min_search(RightTree(t), min);
}

const ElemType * MinTree(const Node * n) {
	if (IsEmptyTree(n))
		return NULL;

	const ElemType * min = GetRootValueTree(n);
	backtracking_min_search(n, &min);
	return min;
}

/* ES 8 */
Node * DeleteBstNode(Node * t, const ElemType * key) {
	if (IsEmptyTree(t)) {
		return NULL;
	}
	// Get pl, pr
	Node * pl = CreateEmptyTree(), * pr=CreateEmptyTree(), * start = t;
	while (GetRootValueTree(t) != key && !IsEmptyTree(t)) {
		if (ElemCompare(key, GetRootValueTree(t)) < 0) {
			pl = t;
			pr = CreateEmptyTree();
			t = LeftTree(t);
		}
		else {
			pr = t;
			pl = CreateEmptyTree();
			t = RightTree(t);
		}
	}
	
	Node * next = CreateEmptyTree();

	// Caso foglia
	if (IsLeafTree(t)) {
		if (!IsEmptyTree(pl))
			pl->left = next;
		else
			pr->right = next;
	}

	// caso unico figlio
	if (!IsEmptyTree(LeftTree(t)) && IsEmptyTree(RightTree(t)))
		next = RightTree(t);
	else if (IsEmptyTree(LeftTree(t)) && !IsEmptyTree(RightTree(t)))
		next = LeftTree(t);
	if (!IsEmptyTree(pl))
		pl->left = next;
	else
		pr->right = next;

	// caso due figli
	if (!IsEmptyTree(LeftTree(t)) && !IsEmptyTree(RightTree(t))) {
		//prendiamo il minimo maggiore del padre
		pr = t;
		pl = CreateEmptyTree();
		next = RightTree(t);
		if (!IsEmptyTree(next)) {
			while (!IsEmptyTree(LeftTree(t))) {
				pr = CreateEmptyTree();
				pl = next;
				next = LeftTree(next);
			}
		}
		t->value = next->value;
		next = CreateEmptyTree();
	}
	if (!IsEmptyTree(pl))
		pl->left = next;
	else
		pr->right = next;

	return start;
}

int main(void) {

	return 0;
}