#include <iostream>

#define MAX_IN (1<<10)
#define MAX_STR (10)
#define MAX_NAME (5)
#define MAX_ARR (10)
#define MAX_SIZE (MAX_ARR)
#define MAX_LIST (MAX_ARR)

typedef unsigned int u32;

#if 1
unsigned long myhash(const char* str);
void heapInit(void);
int heapPush(int value);
int heapPop(int* value);
int my_strlen(char* str);
int my_strcmp(const char* strA, const char* strB);
int my_strcpy(char* dst, const char* src);
int heap[MAX_SIZE];
int heapSize = 0;
int tempHeap[MAX_SIZE];
char name_data[MAX_NAME][MAX_STR];
char hash_table[MAX_NAME][MAX_STR];
#endif

int N;
struct in_t {
	int idx;
	int val;
	char name[MAX_STR];
}in[MAX_IN];

struct arr_t {
	int idx;
	int val;
	char name[MAX_STR];
}arr[MAX_ARR];
int cur_arr;
arr_t* alloc_arr() {
	return &arr[cur_arr];
}

struct list_head {
	list_head* prev;
	list_head* next;
}name_head[MAX_NAME];

struct list_t {
	list_head list_entry;
	int arr_idx;
}list[MAX_LIST];
int cur_list;
list_t* alloc_list() {
	return &list[cur_list++];
}

void list_init(list_head* head) {
	head->prev = head;
	head->next = head;
}

void list_add(list_head* head, list_head* list) {
	list->prev = head;
	list->next = head->next;
	head->next->prev = list;
	head->next = list;
}

void list_add_tail(list_head* head, list_head* list) {
	list->next = head;
	list->prev = head->prev;
	head->prev->next = list;
	head->prev = list;
}

void list_del(list_head* list) {
	list->prev->next = list->next;
	list->next->prev = list->prev;
	list->prev = list;
	list->next = list;
}

void for_each_list_safe(list_head* head) {
	list_head* tmp;
	list_head* n;
	int cnt = 0;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {
		cnt++;
	}
}

int check_max_list(arr_t* target, arr_t* for_arr) {
	int ret = 0;
	//arr_t* arr_obj = &arr[arr_idx];
	//arr_t* target_obj = (arr_t*)target;
	if (target->val > for_arr->val) {
		ret = 1;
	}
	else if (target->val == for_arr->val) {
		if (target->idx < for_arr->idx) {
			ret = 1;
		}
	}
	return ret;
}

list_head* find_pos_prev(list_head* head, arr_t* target) {
	list_head* ret = head;
	list_head* tmp;
	list_head* n;
	for (tmp = head->next, n = tmp->next; tmp != head->next; tmp = n, n = n->next) {
		list_t* list_d = (list_t*)tmp;
		int arr_idx = list_d->arr_idx;
		arr_t* for_arr = &arr[arr_idx];
		if (check_max_list(target, for_arr) == 1) {
			ret = tmp->prev;
			break;
		}
	}
	return ret;
}

int gen_input() {
	int ret = 0;
	std::cout << "start gen_input" << std::endl;
	for (int i = 0; i < N; i++) {
		in[i].idx = i;
		in[i].val = rand() % 30;
		int test_name = rand() % MAX_NAME;
		my_strcpy(in[i].name, name_data[test_name]);		
		printf("in[%d], idx(%d), val(%d), name(%s/%d)\n", i, in[i].idx, in[i].val, in[i].name, test_name);
	}
	std::cout << "end gen_input" << std::endl;
	return ret;
}

int gen_name() {
	int ret = 0;
	for (int i = 0; i < MAX_NAME; i++) {
		for (int j = 0; j < MAX_STR; j++) {
			name_data[i][j] = char(rand() % 26 + 97);
		}
		name_data[i][MAX_STR - 1] = '\0';
	}
	return ret;
}

int add_arr(int in_idx) {
	int ret = 0;
	arr_t* arr_obj = alloc_arr();
	arr_obj->idx = in[in_idx].idx;
	arr_obj->val = in[in_idx].val;
	my_strcpy(arr_obj->name, in[in_idx].name);
	printf("cur_arr(%d), arr_obj, idx(%d), val(%d), name(%s)\n", cur_arr, arr_obj->idx, arr_obj->val, arr_obj->name);
	cur_arr++;
	return ret;
}

int init_case() {
	int ret = 0;
	for (int i = 0; i < MAX_NAME; i++) {
		hash_table[i][0] = '\0';
	}
	for (int i = 0; i < MAX_NAME; i++) {
		u32 hash = myhash(in[i].name);		
		printf("myhash, hash(%u), name(%s)\n", hash, in[i].name);
		while (1) {
			if (hash_table[hash][0] == '\0') {
				my_strcpy(hash_table[hash], in[i].name);
				break;
			}
			else {
				if (my_strcmp(hash_table[hash], in[i].name) == 0) {
					break;
				}
			}
			printf("find_hash, hash(%u), name(%s)\n", hash, in[i].name);
			hash = (hash + 7) % MAX_NAME;
		}		
	}
#if 1
	for (int i = 0; i < MAX_NAME; i++) {
		printf("hash_table[%d] = %s\n", i, hash_table[i]);
	}
#endif
	return ret;
}

int add_list(int i) {
	int ret = 0;

	return ret;
}

int main() {
	int ret = 0;
	N = 10;
	cur_arr = 0;
	cur_list = 0;
	gen_name();
	gen_input();
	init_case();
	for (int i = 0; i < N; i++) {
		add_arr(i);
	}

	for (int i = 0; i < N; i++) {
		add_list(i);
	}

	for (int i = 0; i < N; i++) {
		heapPush(arr[i].idx);
		printf("heapPush, arr[%d].idx = %d, val = %d\n", i, arr[i].idx, arr[arr[i].idx].val);		
	}

	for (int i = 0; i < N; i++) {		
		heapPop(&tempHeap[i]);
		printf("tempHeap[%d], idx(%d), val(%d)\n", i, tempHeap[i], arr[tempHeap[i]].val);
	}

	std::cout << "start list_hash_heap_t01" << std::endl;

	return ret;
}

#if 1
unsigned long myhash(const char* str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_NAME;
	}
	//std::cout << "myhash = " << hash << std::endl;
	return hash % MAX_NAME;
}

void heapInit(void)
{
	heapSize = 0;
}

int check_max_heap(int i, int j) {
	int ret = 0;
	int idx_i = heap[i];
	int idx_j = heap[j];
	arr_t* arr_i = &arr[idx_i];
	arr_t* arr_j = &arr[idx_j];
	if (arr_i->val > arr_j->val) {
		ret = 1;
	}
	else if (arr_i->val == arr_j->val) {
		if (arr_i->idx < arr_j->idx) {
			ret = 1;
		}
	}
	return ret;
}

int heapPush(int value)
{
	if (heapSize + 1 > MAX_SIZE)
	{
		printf("queue is full!");
		return 0;
	}
	heap[heapSize] = value;
	int current = heapSize;
	//while (current > 0 && heap[current] < heap[(current - 1) / 2])
	while (current > 0 && check_max_heap(current, (current - 1) / 2) == 1)
	{
		int temp = heap[(current - 1) / 2];
		heap[(current - 1) / 2] = heap[current];
		heap[current] = temp;
		current = (current - 1) / 2;
	}
	heapSize = heapSize + 1;
	return 1;
}

int heapPop(int* value)
{
	if (heapSize <= 0)
	{
		return -1;
	}
	*value = heap[0];
	heapSize = heapSize - 1;
	heap[0] = heap[heapSize];
	int current = 0;
	while (current * 2 + 1 < heapSize)
	{
		int child;
		if (current * 2 + 2 == heapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			//child = heap[current * 2 + 1] < heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
			if (check_max_heap(current * 2 + 1, current * 2 + 2) == 1) {
				child = current * 2 + 1;
			}
			else {
				child = current * 2 + 2;
			}
		}
		//if (heap[current] < heap[child])
		if (check_max_heap(current, child) == 1)
		{
			break;
		}
		int temp = heap[current];
		heap[current] = heap[child];
		heap[child] = temp;
		current = child;
	}
	return 1;
}

int printHeap() {
	int ret = 0;
	std::cout << "printHeap, cur_arr = " << cur_arr << std::endl;
	for (int i = 0; i < cur_arr; i++) {
		printf("heap[%d] = %d\n", i, heap[i]);
	}
	return ret;
}
int my_strlen(char* str) {
	int ret = 0;
	char* ptr = str;
	//std::cout << "ptr + 1 = " << ptr + 1<< std::endl;
	while (*ptr != '\0') {
		//printf("before ret = %d, *ptr = %c\n", ret, *ptr);
		ret = ret + 1;
		//printf("after ret = %d, *ptr = %c\n", ret);
		ptr++;
	}
	return ret;
}

int my_strcpy(char* dst, const char* src) {
	int ret = 0;
	//char *ptr = src;
	while (1) {
		//printf("before src = %c, dst = %c\n", *src, *dst);
		if (*src == '\0') {
			break;
		}
		*dst = *src;
		//printf("after src = %c, dst = %c\n", *src, *dst);
		dst++;
		src++;
		ret++;
	}
	*dst = '\0';
	return ret;
}

int my_strcmp(const char* strA, const char* strB) {
	int ret = 0;
	while (1) {
		if (*strA == '\0' || *strB == '\0') {
			break;
		}
		if (*strA == *strB) {
			ret = 0;
		}
		else if (*strA > *strB) {
			ret = 1;
			break;
		}
		else if (*strA < *strB) {
			ret = -1;
			break;
		}
		strA++;
		strB++;
	}
	return ret;
}
#endif