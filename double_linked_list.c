#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 노드 디자인
typedef struct _Node 
{
	int value;
	struct _Node* prev;
	struct _Node* next;
} 
Node;

// 리스트 메타 정보 컨테이너
typedef struct _DList 
{
	int id;
	int size;
	Node* head;
	Node* tail;
}
DList;

// ADT
Node* new_node(int value);
void init_list(DList* plist);
void insert(DList* plist, Node* node);
void update(DList* plist, int index, Node* node);
void remove_by_index(DList* plist, int index);
Node* get_or_null(DList* plist, int index);

// 함수 구현

Node* new_node(int value) 
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = value;
	node->prev = NULL;
	node->next = NULL;

	return node;
}

void init_list(DList* plist) 
{
	static int next_id = 1;
	plist->id = next_id;
	plist->size = 0;
	plist->head = NULL;
	plist->tail = NULL;
	++next_id;
}

void insert(DList *plist, Node* node) 
{
	assert(plist != NULL && node != NULL);

	if (plist->head == NULL) 
	{
		plist->head = node;
		plist->tail = node;
	}
	else
    {
		plist->tail->next = node;
		node->prev = plist->tail;
		plist->tail = node;
	}
	plist->size++;
}

Node* get_node_for_back(Node* target, int index) 
{
	assert(target != NULL);

	for (int i = 0; i < index; ++i) 
	{
		if (target->prev == NULL) 
		{
			break;
		}
		target = target->prev;
	}
	return target;
}

Node* get_node_for_fwd(Node* target, int index) 
{
	assert(target != NULL);

	for (int i = 0; i < index; ++i) 
	{
		if (target->next == NULL) 
		{
			break;
		}
		target = target->next;
	}
	return target;
}

Node* get_or_null(DList* plist, int index) 
{
	assert(plist != NULL);

	if (plist->size <= 0 && plist->size < index) {
		return NULL;
	}
	if(plist->size / 2 < index)
	{
		return get_node_for_back(plist->tail, plist->size - index - 1);
	}
	return get_node_for_fwd(plist->head, index);
}

void delete_node_on_list(DList* plist, Node* target)
{
	free(target);
	plist->size--;
}
void remove_by_index(DList* plist, int index) 
{
	assert(plist != NULL);

	Node* dtarget = get_or_null(plist, index);

	if (dtarget == NULL) 
	{
		printf("delete target is null..\n");
		return;
	}

	if (dtarget == plist->head && dtarget == plist->tail)
	{
		printf("list is clear\n");
		delete_node_on_list(plist, dtarget);
		return;
	}

	if (dtarget->prev == NULL) 
	{
		printf("delete target is first node\n");
		plist->head = dtarget->next;
		plist->head->prev = NULL;
		delete_node_on_list(plist, dtarget);
		return;
	}

	if (dtarget->next == NULL) 
	{
		printf("delete target is last node\n");
		plist->tail = dtarget->prev;
		plist->tail->next = NULL;
		delete_node_on_list(plist, dtarget);
		return;
	}
	printf("[%d] node deleted\n", index);
	dtarget->prev->next = dtarget->next;
	dtarget->next->prev = dtarget->prev;
	delete_node_on_list(plist, dtarget);
}

void update(DList* plist, int index, Node* node)
{
	assert(plist != NULL && node != NULL);

	Node* utarget = get_or_null(plist, index);

	if (utarget == NULL) 
	{
		printf("update target is null..\n");
		return; // 비정상 처리
	}

	node->next = utarget->next;
	node->prev = utarget->prev;
	utarget->next->prev = node;
	utarget->prev->next = node;
	free(utarget);
}
int main() 
{

	// 1. 변수 준비
	DList list1;
	Node* node1, *node2, *node3;

	// 2. 초기화 및 변수 할당
	init_list(&list1);
	node1 = new_node(10);
	node2 = new_node(20);
	node3 = new_node(30);
	
	// 3. insert 수행
	insert(&list1, node1);
	insert(&list1, node2);
	insert(&list1, node3);

	// 4. get 수행
	Node* node4 = get_or_null(&list1, 0);
	Node* node5 = get_or_null(&list1, 1);
	Node* node6 = get_or_null(&list1, 2);

	//printf("%d %d %d", node4->value, node5->value, node6->value);
	//5. 전체 출력
	for (int i = 0; i < list1.size; i++)
	{
		printf("%d ", get_or_null(&list1, i)->value);
	}
	printf("\n");
	remove_by_index(&list1, 1);

	for (int i = 0; i < list1.size; i++)
	{
		printf("%d ", get_or_null(&list1, i)->value);
	}

	printf("\n");
	insert(&list1, new_node(40));
	insert(&list1, new_node(50));
	insert(&list1, new_node(60));

	for (int i = 0; i < list1.size; i++)
	{
		printf("%d ", get_or_null(&list1, i)->value);
	}
	printf("\n");
	update(&list1, 2, new_node(100));

	for (int i = 0; i < list1.size; i++)
	{
		printf("%d ", get_or_null(&list1, i)->value);
	}

	printf("\n");
	//update(NULL, 1, new_node(300));
	remove_by_index(&list1, 0);

	for (int i = 0; i < list1.size; i++)
	{
		printf("%d ", get_or_null(&list1, i)->value);
	}
	printf("\n");

	remove_by_index(&list1, 3);
	remove_by_index(&list1, 1);
	remove_by_index(&list1, 0);
	remove_by_index(&list1, 0);

	//printf("%d\n", get_or_null(&list1, 0)->value);

	return 0;
}