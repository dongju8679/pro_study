#include <iostream>

#define MAX_NUM (1<<20)
#define MAX_NUM_IN (MAX_NUM * 2)
#define MAX_STR (10)

struct in_t {
	int idx;
	int val;
	char name[MAX_STR];
}in[MAX_NUM_IN];

int N;
struct arr_t {
	int idx;
	int val;
	char name[MAX_STR];
}a[MAX_NUM_IN], tmpa[MAX_NUM_IN], tmpb[MAX_NUM_IN];

struct list_head {
	list_head* prev;
	list_head* next;
}play_head;

struct list_t {
	list_head list_entry;
	int idx;
	int val;
	char name[MAX_STR];
}list[MAX_NUM_IN],tmpc[MAX_NUM_IN];
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

int for_each_list_safe(list_head* head) {
	std::cout << "start for_each_list_safe" << std::endl;
	list_head* tmp = 0;
	list_head* n = 0;
	int cnt = 0;
	list_t* list = 0;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {		
		list = reinterpret_cast<list_t*>(tmp);
		std::cout << "list, cnt = " << cnt << ", idx = " << list->idx << ", val = " << list->val << std::endl;;
		cnt++;		
	}
	return cnt;
}

int check_msort_list(int i, int j) {
	int ret = 0;
	if (list[i].val < list[j].val) {
		ret = 1;
	}
	else if (list[i].val == list[j].val) {
		if (list[i].idx > list[j].idx) {
			ret = 1;
		}
	}
	return ret;
}

void msort_list(int s, int e) {
	if (s >= e) return;
	int m = (s + e) / 2;
	int i, j, k;
	i = s;
	j = m + 1;
	k = i;
	msort_list(s, m);
	msort_list(m + 1, e);
	while (i <= m && j <= e) {
		if (check_msort_list(i, j) == 1) {
			tmpc[k++] = list[i++];
		}
		else {
			tmpc[k++] = list[j++];
		}
	}
	while (i <= m) {
		tmpc[k++] = list[i++];
	}
	while (j <= e) {
		tmpc[k++] = list[j++];
	}
	for (int k = s; k <= e; k++) {
		list[k] = tmpc[k];
	}
}

int check_msort(int i, int j) {
	int ret = 0;
	if (a[i].val < a[j].val) {
		ret = 1;
	}
	else if (a[i].val == a[j].val) {
		if (a[i].idx > a[j].idx) {
			ret = 1;
		}
	}
	return ret;
}

int make_list() {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		list[i].idx = in[i].idx;
		list[i].val = in[i].val;
	}
	return ret;
}

int make_list2() {
	int ret = 0;
	list_head* head = &play_head;
	for (int i = 0; i < N; i++) {
		list_t* list_data = alloc_list();
		list_add_tail(head, &list_data->list_entry);
	}
	return ret;
}

int check_list1(list_t* target, list_t* list) {
	int ret = 0;

	if (target->val < list->val) {
		ret = 1;
	}
	else if (target->val == list->val) {
		if (target->idx > list->idx) {
			ret = 1;
		}
	}
	return ret;
}

list_head* find_pos(list_t* target) {
	list_head* pos = 0;
	list_head* tmp = 0;
	list_head* n = 0;
	list_head* head = &play_head;
	list_t* list = 0;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {
		list = reinterpret_cast<list_t*>(tmp);
		if (check_list1(target, list) == 1) {
			pos = tmp->prev;
			break;
		}
		pos = tmp;
	}
	return pos;
}

int add_list(int N) {
	int ret = 0;
	list_head* pos = &play_head;
	list_t* target = alloc_list();
	target->idx = in[N - 1].idx;
	target->val = in[N - 1].val;
	pos = find_pos(target);
	list_add(pos, &target->list_entry);
	return ret;
}

void msort(int s, int e) {
	if (s >= e) return;
	int m = (s + e) / 2;
	int i, j, k;
	i = s;
	j = m + 1;
	k = i;
	msort(s, m);
	msort(m + 1, e);
	while (i <= m && j <= e) {
		if (check_msort(i, j) == 1) {
			tmpa[k++] = a[i++];
		}
		else {
			tmpa[k++] = a[j++];
		}
	}
	while (i <= m) {
		tmpa[k++] = a[i++];
	}
	while (j <= e) {
		tmpa[k++] = a[j++];
	}
	for (int k = s; k <= e; k++) {
		a[k] = tmpa[k];
	}
}

int gen_input() {
	int ret = 0;
	for (int i = 0; i < MAX_NUM_IN; i++) {
		in[i].idx = i;
		in[i].val = rand() % 30;
	}
	return ret;
}

int print_input() {
	int ret = 0;
	std::cout << "print_input" << std::endl;
	for (int i = 0; i < MAX_NUM_IN; i++) {
		std::cout << "in, i = " << i << ", idx = " << in[i].idx << ", val = " << in[i].val << std::endl;
	}
	return ret;
}

int make_a(int i) {
	int ret = 0;
	arr_t* a_ = &a[i];
	a_->idx = in[i].idx;
	a_->val = in[i].val;
	return ret;
}

int print_a() {
	int ret = 0;
	std::cout << "print_msort()" << std::endl;
	for (int i = 0; i < N; i++) {
		std::cout << "a, i = " << i << ", idx = " << a[i].idx << ", val = " << a[i].val << std::endl;
	}
	return ret;
}
int print_list() {
	int ret = 0;
	std::cout << "print_list()" << std::endl;
	for (int i = 0; i < N; i++) {
		std::cout << "list, i = " << i << ", idx = " << list[i].idx << ", val = " << list[i].val << std::endl;
	}
	return ret;
}

int check_binary(int m, arr_t* target) {
	int ret = 0;
	if (target->val < a[m].val) {
		ret = 1;
	}
	else if (target->val == a[m].val) {
		if (target->idx > a[m].idx) {
			ret = 1;
		}
	}
	return ret;
}

int binary_try(int s, int e, arr_t* target) {
	int ret = 0;
	int m = 0;
	while (s <= e) {
		m = (s + e) / 2;
		if (check_binary(m, target) == 1) {
			if (m == s) return m;
			if (check_binary(m - 1, target) != 1) return m;
			e = m - 1;
		}
		else if (check_binary(m, target) != 1) {
			if (m == e) return m + 1;
			if (check_binary(m + 1, target) == 1) return m + 1;
			s = m + 1;
		}
	}
	return ret;
}
int find_pos(arr_t* arr) {
	int ret = 0;
	int s = 0;
	int e = N - 2;
	//std::cout << "e = " << e << std::endl;
	ret = binary_try(s, e, arr);
	return ret;
}

int add_binary_try(arr_t* target) {
	int ret = 0;
	int pos = 0;
#if 0
	if (cur_a == 0) {
		arr_t* a = alloc_a();
		a->idx = in[i].idx;
		a->val = in[i].val;
		//std::cout << "cur_music = " << cur_music << std::endl;
		return cur_music;
	}
	arr_t* a = alloc_music();
	//std::cout << "i = " << i << ", add_binary_try, cur_music = " << cur_music << std::endl;
	a->idx = in[i].idx;
	a->val = in[i].val;
	//std::cout << "a, idx = " << a->idx << ", val = " << a->val << std::endl;
#endif
	pos = find_pos(target);
	//std::cout << "pos = " << pos << std::endl;

	arr_t tmp0;
	tmp0 = a[pos];
	a[pos] = a[N - 1];
	int k = 0;
	for (int i = pos + 1; i <= N - 2; i++) {
		tmpb[k] = a[i];
		k++;
	}
	k = 0;
	for (int i = pos + 2; i <= N - 1; i++) {
		a[i] = tmpb[k];
		k++;
	}
	a[pos + 1] = tmp0;

	ret = N;
	return ret;
}

int check_insertion(arr_t temp, int j) {
	int ret = 0;
	if (temp.val < a[j].val) {
		ret = 1;
	}
	else if (temp.val == a[j].val) {
		if (temp.idx > a[j].idx) {
			ret = 1;
		}
	}
	return ret;
}

void insertionSort(void)
{
	arr_t temp;
	int i;
	int j;

	for (i = 1; i < N; i++)
	{
		temp = a[i];
		j = i - 1;
		
		while ((check_insertion(temp, j)) && (j >= 0))
		{
			a[j + 1] = a[j];
			j = j - 1;
		}
		a[j + 1] = temp;
	}
}

int main() {
	int ret = 0;
	clock_t start, end;

	std::cout << "start sort_compare1" << std::endl;
	start = clock();
	gen_input();
	end = clock();
	std::cout << "after gen_input, elapsed_time = " << end - start << std::endl;
	//print_input();
	N = MAX_NUM;
	for (int i = 0; i < MAX_NUM_IN; i++) {
		make_a(i);
	}
	
	start = clock();
	msort(0, N-1);
	end = clock();
	std::cout << "after msort(), elapsed_time = " << end - start << std::endl;
	//print_a();	
#if 0	
	N = N + 1;
	start = clock();
	msort(0, N-1);
	end = clock();
	std::cout << "after msort1(), elapsed_time = " << end - start << std::endl;
	//print_a();
#endif
#if 1
	N++;
	start = clock();
	add_binary_try(&a[N-1]);
	end = clock();
	std::cout << "after binary_add1(), elapsed_time = " << end - start << std::endl;
	//print_a();
#endif
#if 0
	N++;
	start = clock();
	insertionSort();
	end = clock();
	std::cout << "after insertionSort(), elapsed_time = " << end - start << std::endl;
	//print_a();
#endif
#if 0
	cur_list = 0;
	list_init(&play_head);
	make_list();
	msort_list(0, N - 1);
	start = clock();
	make_list2();
	end = clock();
	std::cout << "after make_list2(), elapsed_time = " << end - start << std::endl;
	//for_each_list_safe(&play_head);
	N = N + 1;
	add_list(N);
	//for_each_list_safe(&play_head);
	//print_list();
#endif

	return ret;
}