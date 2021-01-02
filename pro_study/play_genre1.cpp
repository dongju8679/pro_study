#include <iostream>

const int MAX_STR_LEN = 10;
const int INPUT_NUM = 1 << 4;
const int MAX_NUM = 1 << 5;
const int gen_list_num = 10;

int my_strlen(char* str);
int my_strcpy(char* dst, char* src);
int my_strcmp(char* strA, char* strB);
int tN;

char genre[10][10] = {"hiphop", "classic", "fpop", "kpop", "britpop", "jazz", "oldpop", "rock", "dance", "jpop"};

struct list_head {
	list_head* prev;
	list_head* next;
}play_list, gen_list[gen_list_num];

struct my_t {
	list_head play_list;
	list_head gen_list;
	int idx;
	int playtime;
	char genre[MAX_STR_LEN];
}a_data[MAX_NUM], mtmp[MAX_NUM];
int a_cur;

my_t* a_alloc() {
	return &(a_data[a_cur++]);
}

const int offsetlist[2] = {0, sizeof(play_list)};

struct input_t {
	int idx;
	int playtime;
	char genre[MAX_STR_LEN];
}in[INPUT_NUM];

void gen_input(int N) {
	srand((unsigned int)time(NULL));	
	for (int i = 0; i < N; i++) {
		in[i].idx = i;
		in[i].playtime = rand() % 20;		
		my_strcpy(in[i].genre, genre[rand() % 10]);
		//std::cout << "in.genre =  = " << in[i].genre << std::endl;
	}
}

int list_init(list_head* head) {
	int ret = 0;
	head->prev = head;
	head->next = head;
	return ret;
}

void list_add(list_head* head, list_head* list) {
	list->prev = head;
	list->next = head->next;
	head->next->prev = list;
	head->next = list;
}

void list_del(list_head* list) {
	list->prev->next = list->next;
	list->next->prev = list->prev;
	list->prev = list;
	list->next = list;
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

int for_each_list_safe(list_head* head, int list_idx) {
	int ret = 0;
	list_head* tmp = 0;
	list_head* n = 0;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {
		my_t* my = reinterpret_cast<my_t *>(tmp - offsetlist[list_idx]);
		//std::cout << "my->idx = " << my->idx << ", playtime = " << my->playtime << ", genre = " << my->genre << std::endl;
		ret++;
	}
	std::cout << "for each list safe cnt = " << ret << std::endl;
	return ret;
}

int push_input(input_t in[]) {
	int ret = 0;
	std::cout << "start push_input" << std::endl;
	for (int i = 0; i < INPUT_NUM; i++) {
		my_t* my = a_alloc();
		my->idx = in[i].idx;
		my->playtime = in[i].playtime;
		my_strcpy(my->genre, in[i].genre);		
	}
	return ret;
}

unsigned int my_hash(const char* str) {
	unsigned int hash = 5381;
	int c;
	while (c = *str++)
	{
		hash = ((((hash << 5) + hash) + c) + (gen_list_num - 1)) & (gen_list_num - 1);
	}
	return hash;
}

unsigned int find_gen_idx(char *str) {
	unsigned int ret = 0;
	for (unsigned int i = 0; i < 10; i++) {
		if (my_strcmp(a_data[i].genre, str)) {
			ret = i;
			break;
		}
	}
	return ret;
}

int push_input_list(input_t in[]) {
	int ret = 0;
	unsigned int gen_idx = 0;
	
	std::cout << "start push_input" << std::endl;
	for (int i = 0; i < INPUT_NUM; i++) {
		my_t* my = a_alloc();
		my->idx = in[i].idx;
		my->playtime = in[i].playtime;
		my_strcpy(my->genre, in[i].genre);
		//gen_idx = my_hash(my->genre);
		gen_idx = find_gen_idx(my->genre);
		list_add(&play_list, &(my->play_list));
		list_add(&gen_list[gen_idx], &(my->gen_list));
	}
	//for_each_list_safe(&play_list, 0);

	return ret;
}

int check_condition(my_t* my, int i, int j) {
	int ret = 0;
	if (my[i].playtime > my[j].playtime) {
		ret = 1;
	}
	else if (my[i].playtime == my[j].playtime) {
		if (my[i].idx > my[i].idx) {
			ret = 1;
		}
	}
	return ret;
}

void merge_sort(my_t* my, int start, int end) {
	if (start >= end) return;
	int middle = (start + end) / 2;
	int i, j, k;
	i = start;
	j = middle + 1;
	k = i;
	merge_sort(my, start, middle);
	merge_sort(my, middle + 1, end);
	while (i <= middle && j <= end) {
		if (check_condition(my, i, j) == 1) {
			mtmp[k++] = my[i++];
		}
		else {
			mtmp[k++] = my[j++];
		}
	}
	while (i <= middle) {
		mtmp[k++] = my[i++];
	}
	while (j <= end) {
		mtmp[k++] = my[j++];
	}
	for (k = start; k <= end; k++) {
		my[k] = mtmp[k];
	}
}

int make_list(my_t* my, int num) {
	int ret = 0;

	std::cout << "start make_list" << std::endl;
	for (int i = 0; i < num; i++) {
		my_t* mmy = &(my[i]);
		unsigned int gen_idx = find_gen_idx(mmy->genre);		
		list_add(&play_list, &(mmy->play_list));
		list_add(&gen_list[gen_idx], &(mmy->gen_list));
	}

	return ret;
}

int insert_list(input_t *in) {
	int ret = 0;

	my_t* my = a_alloc();
	my->idx = in->idx;
	my->playtime = in->playtime;
	my_strcpy(my->genre, in->genre);
	unsigned int gen_idx = find_gen_idx(my->genre);
	list_add(&play_list, &(my->play_list));
	list_add(&gen_list[gen_idx], &(my->gen_list));

	return ret;
}

int binarysearch(my_t* arr, int low, int high, int target) {
	int ret = 0;
	int mid;
	if (low > high)
	{		
		return -1;
	}
	mid = (low + high) / 2;
	if (target < arr[mid].idx)
	{
		binarysearch(arr, low, mid - 1, target);
	}
	else if (arr[mid].idx < target)
	{
		binarysearch(arr, mid + 1, high, target);
	}
	else
	{
		ret = mid;		
		goto errorexit;		
	}
errorexit:
	return ret;
}

int update_playtime(int idx, int playtime) {
	int ret = 0;
	int start = 0;
	int end = INPUT_NUM + 1 - 1;
	int target = idx;

	int new_idx = binarysearch(a_data, start, end, target);
	a_data[new_idx].playtime += playtime;

	return ret;
}

int show_array(int num) {
	int ret = 0;
	for (int i = 0; i < num; i++) {		
		std::cout << "idx = " << a_data[i].idx << ", genre = " << a_data[i].genre << ", playtime = " << a_data[i].playtime << std::endl;
	}
	return ret;
}

int main() {
	int ret = 0;
	clock_t start, end;

	int N = MAX_NUM;
	tN = N;
	a_cur = 0;
	std::cout << "start play and genre!" << std::endl;

	start = clock();

	list_init(&play_list);	
	for (int i = 0; i < gen_list_num; i++) {
		list_init(&(gen_list[i]));
	}	
	gen_input(INPUT_NUM);
	push_input(in);
	//push_input_list(in);
	merge_sort(a_data, 0, INPUT_NUM - 1);
	make_list(a_data, INPUT_NUM);

	int ii = 1;
	input_t add0 = { INPUT_NUM  + ii, 15, "hiphop"};
	insert_list(&add0);
	merge_sort(a_data, 0, INPUT_NUM);
	show_array(INPUT_NUM);
	update_playtime(2, 20);
	std::cout << "after show_array" << std::endl;
	show_array(INPUT_NUM);

	end = clock();
	std::cout << "elasped time = " << end - start << std::endl;

	return ret;
}