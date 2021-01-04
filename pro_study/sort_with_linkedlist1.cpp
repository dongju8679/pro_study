#include <iostream>

#define MERGE 1

#define MAX_NUM (1<<3)
#define MAX_STR_LEN 10
#define GEN_LIST_NUM 5

int my_strlen(char* str);
int my_strcpy(char* dst, char* src);
int my_strcmp(char* strA, char* strB);

int N;
int heapSize = 0;

struct list_head {
	list_head* prev;
	list_head* next;
}play_head, gen_head[GEN_LIST_NUM];

struct input_t {	
	int val;
	char name[MAX_STR_LEN];
};

struct my_data {
	list_head play_list;
	list_head gen_list;
	int idx;
	int val;
	char name[MAX_STR_LEN];
}arr[MAX_NUM + 10]; 
#ifdef MERGE
my_data tmp[MAX_NUM + 10];
#endif
int my_cur;

my_data* my_alloc() {
	//std::cout << "my_cur = " << my_cur << std::endl;
	return &arr[my_cur++];
}

enum {
	play_list_enum = 0,
	gen_list_enum = 1,
	MAX_NUM_LIST_ENUM = 2
};

int offset_of_list[MAX_NUM_LIST_ENUM] = { 0, sizeof(list_head) };

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
	list->prev = head->prev;
	list->next = head;
	head->prev->next = list;
	head->prev = list;
}

void list_del(list_head* list) {
	list->prev->next = list->next;
	list->next->prev = list->prev;
	list->prev = list;
	list->next = list;
}

int for_each_list_safe(list_head* head, int list_enum) {
	int ret = 0;
	list_head* tmp = 0;
	list_head* n = 0;
	std::cout << "start for_each_list_safe" << std::endl;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next ) {
		my_data* arr = reinterpret_cast<my_data *>(tmp - offset_of_list[list_enum]);
		std::cout << "arr->idx = " << arr->idx << ", arr->val = " << arr->val << ", arr->name = " << arr->name << std::endl;
	}
	return ret;
}

#ifdef MERGE
int check_condition(my_data* arr, int i, int j) {
	int ret = 0;
	if (arr[i].val < arr[j].val) {
		ret = 1;
	}
	else if (arr[i].val == arr[j].val) {
		if (arr[i].idx < arr[j].idx) {
			ret = 1;
		}
	}
	return ret;
}

void merge_sort(my_data* arr, int start, int end) {
	if (start >= end) return;
	int middle = (start + end) / 2;
	int i, j, k;
	i = start;
	j = middle + 1;
	k = i;
	merge_sort(arr, start, middle);
	merge_sort(arr, middle + 1, end);
	while (i <= middle && j <= end) {
		if (check_condition(arr, i, j) == 1) {
			tmp[k++] = arr[i++];
		}
		else {
			tmp[k++] = arr[j++];
		}
	}
	while (i <= middle) {
		tmp[k++] = arr[i++];
	}
	while (j <= end) {
		tmp[k++] = arr[j++];
	}
	for (k = start; k <= end; k++) {
		arr[k] = tmp[k];
	}
}
#endif

#if 1
int gen_input(my_data in[], int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		in[i].idx = i;
		in[i].val = rand() % 30;
		char name[MAX_STR_LEN];
		for (int j = 0; j < MAX_STR_LEN - 1; j++) {			
			name[j] = static_cast<char>((rand() % 26) + 97);			
		}
		name[MAX_STR_LEN - 1] = '\0';
		my_strcpy(in[i].name, name);
	}
	return ret;
}
#endif

int show_in(input_t* in, int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		std::cout << "in.val = " << in[i].val << ", in.name = " << in[i].name << std::endl;
	}
	return ret;
}

int make_array(input_t* in, my_data* arr, int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		arr[i].idx = i;
		arr[i].val = in[i].val;
		my_strcpy(arr[i].name, in[i].name);
	}
	return ret;
}

int show_arr(my_data* arr, int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		std::cout << "arr.idx = " << arr[i].idx << ", arr.val = " << arr[i].val << ", arr.name = " << arr[i].name << std::endl;
	}
	return ret;
}

int make_list(list_head* head, my_data* arr, int N) {
	int ret = 0;
	my_data* data = 0;
	for (int i = 0; i < N; i++) {
		data = my_alloc();
		//list_add(head, &(data->play_list));
		list_add_tail(head, &(data->play_list));
	}
	return ret;
}

int binarysearch(my_data* arr, int low, int high, int target) {
	int ret = 0;
	int mid;
	if (low > high)
	{
		return -1;
	}
	mid = (low + high) / 2;
	if (target < arr[mid].idx)
	{
		//std::cout << "mid0 = " << mid << std::endl;
		binarysearch(arr, low, mid - 1, target);
	}
	else if (arr[mid].idx < target)
	{
		//std::cout << "mid1 = " << mid << std::endl;
		binarysearch(arr, mid + 1, high, target);
	}
	else
	{
		//std::cout << "mid2 = " << mid << std::endl;
		ret = mid;
		return ret;
	}
}

int binarytry(my_data* arr, int start, int end, int target) {
	int ret = 0;
	int middle = 0;
	
	while (start <= end) {
		middle = (start + end) / 2;
		if (target < arr[middle].val) {
			if (middle == 0) return middle;
			if (target > arr[middle - 1].val) return middle;
			end = middle - 1;
		}
		else if (target > arr[middle].val) {
			if (middle == end) return middle + 1;
			if (target < arr[middle + 1].val) return middle + 1;
			start = middle + 1;
		}
		else {
			return middle;
		}
	}
	return ret;
}

list_head* find_list_pos (list_head* head, int pos){
	list_head* ret = 0;
	list_head* tmp = 0;
	list_head* n = 0;
	int cnt = 1;
	if (pos == 0) return head;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {
		//std::cout << "cnt = " << cnt << std::endl;
		if (pos == cnt) {
			ret = tmp;
			//std::cout << "head = " << head << std::endl;
			//std::cout << "tmp = " << tmp << std::endl;
			return ret;
		}
		cnt++;
	}
	return ret;
}

int push_data(my_data* arr, int low, int high) {
	int ret = 0;
	int idx = MAX_NUM;
	//int val = rand() % 30;
	int val = 25;
	char name[MAX_STR_LEN] = "chciejkdi";
#if 0
	for (int i = 0; i < MAX_STR_LEN - 1; i++) {
		name[i] = static_cast<char>((rand() % 26) + 97);
	}
	name[MAX_STR_LEN - 1] = '\0';
#endif
	my_data* data = my_alloc();
	data->idx = idx;
	data->val = val;
	my_strcpy(data->name, name);
	//char* ptr = data->name;
	//ptr = name;
	//std::cout << "new data->name = " << data->name << std::endl;	
	//int pos = binarysearch(arr, low, high, target);
	int target = val;
	std::cout << "low = " << low << ", high = " << high << ", target = " << target << std::endl;
	int pos = binarytry(arr, low, high, target);
	std::cout << "binarytry, pos = " << pos << std::endl;
#if 1
	list_head* new_list_pos = find_list_pos(&play_head, pos);	
	list_add(new_list_pos, &(data->play_list));
#if 0
	my_data* t0 = 0;
	list_head* t1 = &(data->play_list);
	list_head* t2 = t1->next;
	t0 = reinterpret_cast<my_data*>(t2 - offset_of_list[0]);
	std::cout << "t0->name = " <<  t0->name << std::endl;
#endif
	
#endif
	//list_add(&play_head, &(data->play_list));
	return ret;
}

void heapInit(void)
{
	heapSize = 0;
}

int check_heap(my_data * arr, int current) {
	int ret = 0;
	if (arr[current].val < arr[(current - 1)/ 2].val) {

	}

	return ret;
}

int heapPush(my_data arr[], int i)
{
	if (heapSize + 1 > MAX_NUM)
	{		
		return 0;
	}
	arr[heapSize] = arr[i];
	int current = heapSize;
	//while (current > 0 && arr[current].val < arr[(current - 1) / 2].val)
	while (current > 0 && (check_heap(arr, current) == 1))
	{
		my_data temp = arr[(current - 1) / 2];
		arr[(current - 1) / 2] = arr[current];
		arr[current] = temp;
		current = (current - 1) / 2;
	}
	heapSize = heapSize + 1;
	return 1;
}

int main() {
	int ret = 0;
	std::cout << "start sort_with_linkedlist" << std::endl;
	N = MAX_NUM;
	my_cur = 0;
	list_init(&play_head);
	for (int i = 0; i < GEN_LIST_NUM; i++) {
		list_init(&(gen_head[i]));
	}
	clock_t start, end;
	int start_idx = 0;
	int end_idx = MAX_NUM;

	start = clock();
	gen_input(arr, N);
	end = clock();
	std::cout << "gen_input, elapsed time = " << end - start << std::endl;
	//show_in(in, N);

#if 0
	start = clock();
	make_array(in, arr, N);
	end = clock();
	std::cout << "make_array, elapsed time = " << end - start << std::endl;
#endif

	start = clock();
#ifdef MERGE
	merge_sort(arr, start_idx, end_idx - 1);
#else
	heapInit();
	for (int i = 0; i < N; i++)
	{
		//int value = arr[i].val;
		heapPush(arr, i);
	}
#endif
	end = clock();
	std::cout << "merge_sort, elapsed time = " << end - start << std::endl;
	show_arr(arr, N);

	start = clock();
	make_list(&play_head, arr, N);
	end = clock();
	std::cout << "make_list, elapsed time = " << end - start << std::endl;
	for_each_list_safe(&play_head, play_list_enum);

	start = clock();
	push_data(arr, 0, N - 1);
	end = clock();
	std::cout << "push_data, elapsed time = " << end - start << std::endl;
	for_each_list_safe(&play_head, play_list_enum);

	return ret;
}

int my_strcpy(char* dst, char* src) {
	int ret = 0;
	int i = 0;
	while (1) {
		if (src[i] == '\0') {
			break;
		}
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	ret = i;
	return ret;
}

int my_strcmp(char* str1, char* str2) {
	int ret = 0;
	int i = 0;
	while (1) {
		if (str1[i] == '\0' || str2[i] == '\0') {
			break;
		}
		if (str1[i] != str2[i]) {
			ret = str1[i] - str2[i];
			break;

		}
		else if (str1[i] == str2[i]) {
			ret = 0;
		}
		i++;
	}
	return ret;
}

int my_strlen(char* str) {
	int ret = 0;
	int i = 0;
	while (1) {
		if (str[i] == '\0') {
			break;
		}
		i++;
	}
	ret = i;
	return ret;
}