#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	int value;
	int bf;
	struct _Node* left;
	struct _Node* right;
} Node;

Node* groot = NULL;
void print_nodes2(Node* root);

Node* get_new_node(int val) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->value = val;
	new_node->bf = 0;
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}
int is_valid_bf(int bf) {
	if (-1 <= bf && bf <= 1)
	{
		return 1;
	}
	return 0;
}

enum ROTATE_FLAG{
	LL,
	LR,
	RL,
	RR
};

//ROTATE_FLAG get_rotate_rflag(Node* sub_root) {
//	if (sub_root->right->right != NULL)
//	{
//		return RR;
//	}
//	return RL;
//}

int* get_route(Node* root, Node* target) {
	int* route = (int*)malloc(sizeof(int) * 3);
	for (int i = 0; i < 3; i++) {
		if (root->value < target->value) {
			root = root->right;
			route[i] = 1;
		}
		else {
			root = root->left;
			route[i] = 0;
		}
	}
	return route;
}
ROTATE_FLAG get_rotate_flag2(int rotate_flag_value) {
	if (rotate_flag_value == 3) {
		return LL;
	}
	else if (rotate_flag_value == -3) {
		return RR;
	}
	else if (rotate_flag_value == -1) {
		return RL;
	}
	else {
		return LR;
	}

}
ROTATE_FLAG get_rotate_flag(Node* sub_root) {
	if (sub_root->left != NULL)
	{
		if (sub_root->left->left != NULL)
		{
			return LL;
		}
		else if (sub_root->left->right != NULL)
		{
			return LR;
		}
	}
	if (sub_root->right != NULL)
	{
		if (sub_root->right->right != NULL)
		{
			return RR;
		}
		else if (sub_root->right->left != NULL)
		{
			return RL;
		}
	}
}

void rotate_rr(Node* parent, Node* target, int lrflag) {

	Node* node1 = target;
	Node* node2 = target->right;
	Node* node3 = target->right->right;

	node1->right = node2->left;
	node2->left = node1;
	if (target == groot) {
		groot = node2;
	}
	
	node1->bf = 0;
	node2->bf = 0;
	node3->bf = 0;

	if (lrflag == 2) {
		return;
	}

	if (lrflag == 0)
	{
		parent->left = node2;
		parent->bf--;
	}
	else {
		parent->right = node2;
		parent->bf++;
	}
}
void rotate_ll(Node* parent, Node* target, int lrflag) {

	Node* node1 = target;
	Node* node2 = target->left;
	Node* node3 = target->left->left;

	node1->left = node2->right;
	node2->right = node1;
	if (target == groot) {
		groot = node2;
	}
	
	node1->bf = 0;
	node2->bf = 0;
	node3->bf = 0;

	if (lrflag == 2) {
		return;
	}

	if (lrflag == 0)
	{
		parent->left = node2;
		parent->bf--;
	}
	else {
		parent->right = node2;
		parent->bf++;
	}

}

void rotate_rl(Node* parent, Node* target, int lrflag) {

	Node* node1 = target;
	Node* node2 = target->right;
	Node* node3 = target->right->left;

	node1->right = node3;
	node2->left = node3->right;
	node3->right = node2;
	
	rotate_rr(parent, node1, lrflag);
}

void rotate_lr(Node* parent, Node* target, int lrflag) {

	Node* node1 = target;
	Node* node2 = target->left;
	Node* node3 = target->left->right;

	node1->left = node3;
	node2->right = node3->left;
	node3->left = node2;
	
	rotate_ll(parent, node1, lrflag);
}

//Node* get_rotated_root(Node* root, Node* sub_root, ROTATE_FLAG flag)
void rotate(Node* parent, Node* root, ROTATE_FLAG flag, int lrflag)
{
	printf("flag : %d\n", flag);
	Node* rotated_root = NULL;
	if (flag == LL)
	{
		rotate_ll(parent, root, lrflag);
		/*rotated_root = root->left;
		rotated_root->right = root;
		root->left = NULL;*/
	}
	else if (flag == RR)
	{
		rotate_rr(parent, root, lrflag);
		/*rotated_root = root->right;
		rotated_root->left = root;
		root->right = NULL;*/
	}
	else if (flag == LR)
	{
		rotate_lr(parent, root, lrflag);
		/*Node* node1 = root->left->right;
		Node* node2 = root->left;
		root->left = node1;
		node1->left = node2;
		node2->right = NULL;
		rotated_root = get_rotated_root(parent, root, LL, lrflag);*/
	}
	else
	{
		rotate_rl(parent, root, lrflag);
		/*Node* node1 = root->right->left;
		Node* node2 = root->right;
		root->right = node1;
		node1->right = node2;
		node2->left = NULL;
		rotated_root = get_rotated_root(parent, root, RR, lrflag);*/
	}
}

//void rotate_right(Node* root, Node* sub_root) {
//	ROTATE_FLAG flag = get_rotate_flag(sub_root);
//	root->right = get_rotated_root(root, sub_root, flag);
//}
//
//void rotate_left(Node* root, Node* sub_root) {
//	ROTATE_FLAG flag = get_rotate_flag(sub_root);
//	root->left = get_rotated_root(root, sub_root, flag);
//}

int get_left_degree(Node* root, int max_degree, int current_degree)
{
	if (root == NULL) {
		printf("max_degree : %d\n", max_degree);
		return max_degree;
	}
	current_degree++;
	if (current_degree > max_degree) {
		max_degree = current_degree;
	}
	int lmax = get_left_degree(root->left, max_degree, current_degree);
	int rmax = get_left_degree(root->right, max_degree, current_degree);

	if (lmax > rmax) {
		max_degree = lmax;
	}
	else {
		max_degree = rmax;
	}
	//int degree = 0;
	//while (root != NULL) {
	//	if (root->left != NULL) {
	//		root = root->left;
	//	}
	//	else {
	//		root = root->right;
	//	}
	//	degree++;
	//}
	//return degree;
}

Node* get_right_degree(Node* parent, Node* root, int max_degree, int current_degree)
{
	if (root == NULL) {
		printf("max_degree : %d\n", max_degree);
		parent->bf = max_degree;
		return parent;
	}
	current_degree++;
	if (current_degree > root->bf) {
		root->bf = current_degree;
	}
	Node* lnode = get_right_degree(root, root->left, max_degree, current_degree);
	Node* rnode = get_right_degree(root, root->right, max_degree, current_degree);
	 
	if (lnode->bf > rnode->bf) {
		root->bf = lnode->bf;
	}
	else {
		root->bf = rnode->bf;
	}
	/*int degree = 0;

	while (root != NULL) {
		root = root->right;
		degree++;
	}
	return degree;*/
}

int get_bf(Node* root) {
	int left_degree = get_left_degree(root->left, 0, 0);
	//int right_degree = get_right_degree(root->right,0, 0);
	Node* rsub = get_right_degree(root, root->right, 0, 0);
	return left_degree - rsub->bf;
}

void check_bf(Node* parent, Node* root, int lrflag) 
{
	if (root == NULL) {
		return;
	}
	int bf = get_bf(root);
	printf("bf : %d\n", bf);
	printf("is_valid_bf() : %d\n", is_valid_bf(bf));
	if (!is_valid_bf(bf))
	{
		ROTATE_FLAG flag = get_rotate_flag(root);
		rotate(parent, root, flag, lrflag);
		/*else {
			if (bf > 0) {
				rotate(parent, root, flag, 0);
			}
			else {
				rotate(parent, root, flag, 1);
			}
		}*/
	}

	check_bf(root, root->left, 0);
	check_bf(root, root->right, 1);
}

// stack 만들어서 삽입 노드 추적 경로 저장하고 빼면서 인수 조정 -> 리밸런싱
// 삭제는 삭제 대상 찾는 경로 스택에 저자하고 빼면서 인수 조정 -> 리밸런싱

// 역추적 -> 스택에서 하나씩 꺼냄. 좌측에 붙었으면 1을 더하고 우측에 붙었으면 1을 뺀다.

Node* node_stack[100];
int top = 0;
int is_full() {
	if (top == 100) {
		return 1;
	}
	return 0;
}
int is_empty() {
	if (top == 0) {
		return 1;
	}
	return 0;
}

void push_node(Node* node) {
	if (is_full()) {
		return;
	}
	node_stack[top++] = node;
}

Node* pop_node() {
	if (is_empty()) {
		return NULL;
	}
	return node_stack[--top];
}

void clear_stack() {
	top = 0;
}
int abs(int val) {
	if (val < 0) {
		val *= -1;
	}

	return val;

}
char get_rotate_flag3(Node* target) {
	char rotate_flag = 0;
	if (target->left == NULL) {
		target = target->right;
		rotate_flag = rotate_flag | 1 << 3;
	}
	else {
		if (target->right != NULL && abs(target->left->bf) < abs(target->right->bf)) {
			target = target->right;
			rotate_flag = rotate_flag | 1 << 3;
		}
		else {
			target = target->left;
			rotate_flag = rotate_flag | 1 << 2;
		}
	}

	if (target->left == NULL) {
		rotate_flag = rotate_flag | 1 << 1;
	}
	else {
		rotate_flag = rotate_flag | 1 << 0;
		if (target->right != NULL && abs(target->left->bf) < abs(target->right->bf)) {
			target = target->right;
			rotate_flag = rotate_flag | 1 << 1;
		}
	}

	return rotate_flag;
}

ROTATE_FLAG get_rotate_flag4(char rotate_flag) {
	if (rotate_flag == 10) {
		return RR;
	}
	else if (rotate_flag == 9) {
		return RL;
	}
	else if (rotate_flag == 6) {
		return LR;
	}
	else {
		return LL;
	}
}
//void stack_print(Node* root) {
//	clear_stack();
//	push_node(root);
//	while (!is_empty()) {
//		Node* node = pop_node();
//		printf("%d\n", node->value);
//		if (node->right != NULL) {
//			push_node(node->right);
//		}
//		if (node->left != NULL) {
//			push_node(node->left);
//
//		}
//	}
//}
void check_child(Node* node) {
	if (node->left != NULL) {

	}
}
void set_bf(Node* root) {

	Node* node = root;
	clear_stack();
	push_node(node->right);
	while (!is_empty()) {
		if (node->right != NULL) {
			push_node(node->right);
		}
		if (node->left != NULL) {
			push_node(node->left);
		}
		Node* tmp = pop_node();
		node = tmp;
	}
	while (!is_empty()) {
		Node* node = pop_node();
		printf("%d ", node->value);
	}
}
void trace_back() {
	int rotate_flag_value = 0;
	Node* curr = pop_node(); // 회전 대상
	Node* parent = pop_node();// 회전된거 붙일라고
	int lrflag = 0;

	if (curr == NULL) {
		return;
	}
	if (parent == NULL) {
		return;
	}

	while (curr != NULL) {
		lrflag = 0;
		printf("bf : %d\n", curr->bf);
		rotate_flag_value += curr->bf;
		printf("curr->bf : %d\n", curr->bf);
		printf("is_valid_bf() : %d\n", is_valid_bf(curr->bf));
		printf("rotate_flag_value: %d\n", rotate_flag_value);
		if (!is_valid_bf(curr->bf)) {
				
			//ROTATE_FLAG flag = get_rotate_flag2(rotate_flag_value);
			ROTATE_FLAG flag = get_rotate_flag4(get_rotate_flag3(curr));

			if (parent == NULL) {
				lrflag = 2;
			}

			else if (parent->value < curr->value) {
				lrflag = 1;
			}
			rotate(parent, curr, flag, lrflag);
		}

		curr = parent;
		parent = pop_node();
	}
}

int i = 0;
void insert_node(Node* root, Node* new_node)
{
	Node* origin = root;
	Node* parent = NULL;
	int lrflag = 0;
	clear_stack();
	while (root != NULL) {
		push_node(root);
		lrflag = 0;
		parent = root;
		if (root->value < new_node->value)
		{
			root->bf--;
			root = root->right;
			lrflag = 1;
		}
		else
		{
			root->bf++;
			root = root->left;
		}
	}
	if (lrflag == 0) {
		parent->left = new_node;
	}
	else
	{
		parent->right = new_node;
	}
	push_node(new_node);
	trace_back();
	/*printf("=============\n");
	print_nodes2(groot);
	printf("=============\n")*/;

	//check_bf(NULL, origin, lrflag);
}
void print_nodes(Node* root) {
	if (root == NULL) {
		return;
	}

	print_nodes(root->left);
	printf("%d ", root->value);
	print_nodes(root->right);
}
void print_nodes2(Node* root) {
	if (root == NULL) {
		return;
	}

	printf("[bf : %d,  val : %d] ", root->bf, root->value);
	print_nodes2(root->left);
	print_nodes2(root->right);
}

int main() {

	// 1. 이진 탐색 트리이다.
	// 2. 왼쪽, 오른쪽 서브 트리의 높이 차이가 최대 1이다.
	// 3. 높이 차이가 1보다 커지면 회전을 통해 균형을 맞춰 높이 차이를 줄인다.
	// 4. 삽입, 검색, 삭제의 시간 복잡도가 O(log N)이다.

	// BF = hL - hR
	groot = get_new_node(1);
	Node* node2 = get_new_node(24);
	Node* node3 = get_new_node(3);
	Node* node4 = get_new_node(4);
	Node* node5 = get_new_node(15);
	Node* node6 = get_new_node(7);
	Node* node7 = get_new_node(6);
	Node* node8 = get_new_node(18);
	Node* node9 = get_new_node(38);
	Node* node10 = get_new_node(8);
	Node* node11 = get_new_node(12);
	Node* node12 = get_new_node(81);
	Node* node13 = get_new_node(118);
	Node* node14 = get_new_node(33);
	Node* node15 = get_new_node(29);
	Node* node16 = get_new_node(36);
	Node* node17 = get_new_node(5);
	Node* node18 = get_new_node(22);
	Node* node19 = get_new_node(44);
	Node* node20 = get_new_node(313);
	Node* node21 = get_new_node(66);
	Node* node22 = get_new_node(128);

	insert_node(groot, node2);
	insert_node(groot, node3);
	insert_node(groot, node4);
	insert_node(groot, node5);
	set_bf(groot);
	// todo.
	// 회전 케이스를 잘못 찾고 있음.
	// 세개의 노드의 균형인수를 단순히 합하면 안됨. 노드들의 균형인수는 노드 형상에 따라 달라짐.
	// 균형인수를 찾는 규칙을 생각해야함 -> 절대값이 더 큰쪽으로 움직인다.
	/*insert_node(groot, node6);
	insert_node(groot, node7);
	insert_node(groot, node8);
	insert_node(groot, node9);
	insert_node(groot, node10);
	insert_node(groot, node11);*/
	/*printf("%d\n", groot->value);
	printf("%d\n", groot->right->value);
	printf("%d\n", groot->right->right->value);
	printf("%d\n", groot->right->left->value);
	printf("%d\n", groot->right->left->left->value)*/;
	/*insert_node(groot, node12);
	insert_node(groot, node13);
	insert_node(groot, node14);
	insert_node(groot, node15);
	insert_node(groot, node16);
	insert_node(groot, node17);
	insert_node(groot, node18);
	insert_node(groot, node19);
	insert_node(groot, node20);
	insert_node(groot, node21);
	insert_node(groot, node22);
	print_nodes2(groot);*/

	return 0;
}