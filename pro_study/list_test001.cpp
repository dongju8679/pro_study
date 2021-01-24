#include <iostream>

#define MAX_NUM (1<<12)
#define USE_NUM (1<<2)
#define MAX_STR (10)

struct in_t {
	int idx;
	int val;
}in[MAX_NUM];

int N;
struct list_head {
	list_head* prev;
	list_head* next;
}book_head;

struct list_t {
	list_head list_entry;
	int idx;
	int val;
	char name[MAX_STR];
}book[MAX_NUM];
int cur_book;
list_t* alloc_book() {
	//std::cout << "cur_book = " << cur_book << std::endl;
	return &book[cur_book++];
}

struct arr_t {
	int idx;
	int val;
	char name[MAX_STR];
}music[MAX_NUM], tmp[MAX_NUM], b[MAX_NUM], tmp1[MAX_NUM];
int cur_music;
arr_t* alloc_music() {
	return &music[cur_music++];
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
	head->next = list;
}

void list_del(list_head* list) {
	list->prev->next = list->next;
	list->next->prev = list->prev;
	list->prev = list;
	list->next = list;
}

int for_each_list_safe(list_head* head) {
	int ret = 0;
	list_head* tmp = 0;
	list_head* n = 0;
	int cnt = 0;
	list_t* book = 0;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {
		book = reinterpret_cast<list_t*>(tmp);
		//std::cout << "book, idx = " << book->idx << ", val = " << book->val << std::endl;
		b[cnt].idx = book->idx;
		b[cnt].val = book->val;
		cnt++;
	}
	ret = cnt;
	//std::cout << "cnt = " << cnt << std::endl;
	return ret;
}

int gen_input(int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		in[i].idx = i;
		in[i].val = rand() % 30;
	}
	return ret;
}
int print_in(int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		std::cout << "i = " << i << ", idx = " << in[i].idx << ", val = " << in[i].val << std::endl;
	}
	return ret;
}

int print_book(int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		std::cout << "i = " << i << ", idx = " << book[i].idx << ", val = " << book[i].val << std::endl;
	}
	return ret;
}

int get_list_cnt(list_head* head) {
	int ret = 0;
	list_head* tmp = 0;
	list_head* n = 0;
	int cnt = 0;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {
		cnt++;
	}
	ret = cnt;
	return ret;
}

int check_book(list_t* target, list_t* book) {
	int ret = 0;
	//std::cout << "target->val = " << target->val << ", book->val = " << book->val << std::endl;
	if (target->val < book->val) {
		ret = 1;
	}
#if 1
	else if (target->val == book->val) {
		if (target->idx > book->idx) {
			ret = 1;
		}
	}
#endif
	return ret;
}

list_head* find_pos(list_head* head, list_t* target) {
	list_head* tmp = 0;
	list_head* n = 0;
	list_head* pos = 0;
	int cnt = get_list_cnt(head);
	if (cnt == 0) return head;
	//std::cout << "find_pos, pos = " << pos << std::endl;
	list_t* book = 0;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {
		book = reinterpret_cast<list_t*>(tmp);
		if (check_book(target, book) == 1) {
			pos = tmp->prev;
			return pos;
		}
		pos = tmp;
	}
	return pos;
}

int add_book(int i) {
	int ret = 0;
	list_head* pos = 0;	
	list_t* book = alloc_book();
	book->idx = in[i].idx;
	book->val = in[i].val;
	//std::cout << "add_book, i = " << i << ", book->val = " << book->val << std::endl;
	pos = find_pos(&book_head, book);
	//std::cout << "pos = " << pos << std::endl;
	list_add(pos, &book->list_entry);
	return ret;
}

int check_msort(int i, int j) {
	int ret = 0;
	if (music[i].val < music[j].val) {
		ret = 1;
	}
	else if (music[i].val == music[j].val) {
		if (music[i].idx > music[j].idx) {
			ret = 1;
		}
	}
	return ret;
}

void msort(int s, int e) {
	if (s>=e) return;
	int m = (s + e) / 2;
	int i, j, k;
	i = s;
	j = m + 1;
	k = i;
	msort(s, m);
	msort(m+1, e);
	while (i <= m && j <= e) {
		if (check_msort(i, j) == 1) {
			tmp[k++] = music[i++];
		}
		else {
			tmp[k++] = music[j++];
		}
	}
	while (i <= m) {
		tmp[k++] = music[i++];
	}
	while (j <= e) {
		tmp[k++] = music[j++];
	}
	for (k = s; k <= e; k++) {
		music[k] = tmp[k];
	}
}

int make_arr(int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		arr_t* a = alloc_music();
		a->idx = in[i].idx;
		a->val = in[i].val;
	}
	return ret;
}

int print_arr(int N) {
	int ret = 0;
	std::cout << "start print_arr" << std::endl;
	for (int i = 0; i < N; i++) {
		std::cout << "i = " << i << ", idx = " << music[i].idx << ", val = " << music[i].val << std::endl;
	}
	return ret;
}

int check_binary(int m, arr_t* target) {
	int ret = 0;
	if (target->val < music[m].val) {
		ret = 1;
	}
	else if (target->val == music[m].val) {
		if (target->idx > music[m].idx) {
			ret = 1;
		}
	}
	return ret;
}

int binary_try(int s, int e, arr_t* target) {
	int ret = 0;
	int m = 0;
	while (s<=e) {
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
	int e = cur_music - 2;
	//std::cout << "e = " << e << std::endl;
	ret = binary_try(s, e, arr);
	return ret;
}

int add_binary_try(int i) {
	int ret = 0;
	int pos = 0;
	if (cur_music == 0) {
		arr_t* a = alloc_music();
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
	pos = find_pos(a);
	//std::cout << "pos = " << pos << std::endl;

	arr_t tmp0;
	tmp0 = music[pos];
	music[pos] = music[cur_music - 1];		
	int k = 0;
	for (int i = pos + 1; i <= cur_music - 2;i++) {
		tmp[k] = music[i];
		k++;
	}	
	k = 0;
	for (int i = pos + 2; i <= cur_music - 1; i++) {
		music[i] = tmp[k];
		k++;
	}
	music[pos+1] = tmp0;

	ret = cur_music;
	return ret;
}

int main() {
	int ret = 0;
	clock_t start, end;
	N = MAX_NUM;
	std::cout << "start list_test001, N = " << MAX_NUM << std::endl;
	list_init(&book_head);
	cur_book = 0;

	gen_input(N);
	//print_in(N);
	start = clock();
	for (int i = 0; i < N; i++) {
		//std::cout << "add_book, i = " << i << std::endl;
		add_book(i);
	}
	end = clock();
	std::cout << "after add_book, elapsed_time = " << end - start << std::endl;
	for_each_list_safe(&book_head);

	make_arr(N);
	//print_arr(N);
	start = clock();
	msort(0, N-1);
	end = clock();
	std::cout << "after msort, elapsed_time = " << end - start << std::endl;
	//print_arr(N);

	for (int i = 0; i < N; i++) {
		tmp1[i] = music[i];
	}
	//print_arr(N);
	//std::cout << "cur_music = " << cur_music << std::endl;

	cur_music = 0;
#if 1
	start = clock();
	for (int i = 0; i < N; i++) {
		add_binary_try(i);
	}	
	end = clock();
	std::cout << "after add_binary_try, elapsed_time = " << end - start << std::endl;
	//print_arr(N);
#endif
	int cnt = 0;
	start = clock();
	for (int i = 0; i < N; i++) {
		if (music[i].val != tmp1[i].val) {
			std::cout << "i = " << i << ", music, val = " << music[i].val << ", tmp1 val = " << tmp1[i].val << std::endl;
			cnt++;
		}
	}
	end = clock();
	std::cout << "after, bitmatching, elapsedtime = " << end - start << ", cnt = " << cnt << std::endl;

	return ret;
}