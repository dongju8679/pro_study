#include <iostream>

#define MAX_NUM (1<<3) //30000

struct dat_t {
	int idx;
	int playtime;
	int genre;
}in[MAX_NUM];

int N;

struct list_head {
	list_head* prev;
	list_head* next;
}play_head, gen_head[6];

struct play_t {
	list_head play_list;	
	int idx;
	int playtime;
	int genre;	
}play[MAX_NUM + 10], ptmp[MAX_NUM + 10];
int play_cur;
play_t* play_alloc() {
	return &play[play_cur++];
}

struct gen_t {
	list_head gen_list;
	int idx;
	int playtime;
	int genre;
}gen[MAX_NUM + 10], gtmp[MAX_NUM + 10];
int gen_cur;
gen_t* gen_alloc() {
	return &gen[gen_cur++];
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

int gen_input(int N) {
	int ret = 0;
	std::cout << "start gen_input" << std::endl;
	for (int i = 0; i < N; i++) {
		in[i].idx = i;
		in[i].playtime = rand() % 30;
		in[i].genre = rand() % 6;
		std::cout << "in[" << i << "] = " << in[i].idx << "/" << in[i].playtime << "/" << in[i].genre << std::endl;
	}
	return ret;
}

int init_data(dat_t* in, int N) {
	int ret = 0;	
	for (int i = 0; i < N; i++) {	
		play_t* play = play_alloc();
		gen_t* gen = gen_alloc();
		play->idx = in[i].idx;
		play->playtime = in[i].playtime;
		play->genre = in[i].genre;
		gen->idx = in[i].idx;
		gen->playtime = in[i].playtime;
		gen->genre = in[i].genre;
	}
	return ret;
}

int check_condition_play(int i, int j) {
	int ret = 0;
	if (play[i].playtime > play[j].playtime) {
		ret = 1;
	}
	else if (play[i].playtime == play[j].playtime) {
		if (play[i].idx < play[j].idx) {
			ret = 1;
		}
	}
	return ret;
}

int check_condition_gen(int i, int j) {
	int ret = 0;
	if (gen[i].genre < gen[j].genre) {
		ret = 1;
	}
	else if (gen[i].genre == gen[j].genre) {
		if (gen[i].playtime > gen[j].playtime) {
			ret = 1;
		}
	}
	return ret;
}

void merge_sort_gen(int start, int end) {
	if (start >= end) return;
	int middle = (start + end) / 2;
	int i, j, k;
	i = start;
	j = middle + 1;
	k = i;
	merge_sort_gen(start, middle);
	merge_sort_gen(middle + 1, end);
	while (i <= middle && j <= end) {
		if (check_condition_gen(i, j) == 1) {
			gtmp[k++] = gen[i++];
		}
		else {
			gtmp[k++] = gen[j++];
		}
	}
	while (i <= middle) {
		gtmp[k++] = gen[i++];
	}
	while (j <= end) {
		gtmp[k++] = gen[j++];
	}
	for (k = start; k <= end; k++) {
		gen[k] = gtmp[k];
	}
}

void merge_sort_play(int start, int end) {
	if (start >= end) return;
	int middle = (start + end) / 2;
	int i, j, k;
	i = start;
	j = middle + 1;
	k = i;
	merge_sort_play(start, middle);
	merge_sort_play(middle + 1, end);
	while (i <= middle && j <= end) {
		if (check_condition_play(i, j) == 1) {
			ptmp[k++] = play[i++];
		}
		else {
			ptmp[k++] = play[j++];
		}
	}
	while (i <= middle) {
		ptmp[k++] = play[i++];
	}
	while (j <= end) {
		ptmp[k++] = play[j++];
	}
	for (k = start; k <= end; k++) {
		play[k] = ptmp[k];
	}
}

int show_play(int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		std::cout << "play[" << i << "] = " << play[i].idx << "/" << play[i].playtime << "/" << play[i].genre << std::endl;		
	}
	return ret;
}

int show_gen(int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		std::cout << "gen[" << i << "] = " << gen[i].idx << "/" << gen[i].playtime << "/" << gen[i].genre << std::endl;
	}
	return ret;
}

int make_play_list(int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		play_t* dat = &play[i];
		//std::cout << "play = " << dat << std::endl;
		list_add_tail(&play_head, &(dat->play_list));
	}
	return ret;
}

int make_gen_list(int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		gen_t* dat = &gen[i];		
		int gen_head_idx = dat->genre;
		//std::cout << "gen_head_idx = " << gen_head_idx << std::endl;
		list_add_tail(&gen_head[gen_head_idx], &(dat->gen_list));
	}
	return ret;
}

int for_each_list_safe_play(list_head* head) {
	int ret = 0;
	list_head* tmp = 0;
	list_head* n = 0;
	int cnt = 0;	
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {		
		play_t* play = (play_t*)tmp;
		//std::cout << "tmp = " << tmp << std::endl;
		std::cout << "play[" << cnt << "] = " << play->idx << "/" << play->playtime << "/" << play->genre << std::endl;
		cnt++;
	}
	return ret;
}

int for_each_list_safe_gen(list_head* head) {
	int ret = 0;
	list_head* tmp = 0;
	list_head* n = 0;
	int cnt = 0;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {
		gen_t* gen = (gen_t*)tmp;
		std::cout << "gen[" << cnt << "] = " << gen->idx << "/" << gen->playtime << "/" << gen->genre << std::endl;
		cnt++;
	}
	return ret;
}

int binarytry(int target) {
	int ret = 0;
	int s = 0;
	int e = N - 1;
	int m = 0;
	while (s <= e) {
		m = (s + e) / 2;
		if (target < play[m].idx) {
			std::cout << "1m = " << m << std::endl;
			if (m == 0) return m;
			if (target > play[m - 1].idx) return m;
			e = m - 1;
		}
		else if (target > play[m].idx) {
			std::cout << "2m = " << m << std::endl;
			if (m == e) return m + 1;
			if (target < play[m + 1].idx) return m + 1;
			s = m + 1;
		}
		else {
			std::cout << "m = " << m << std::endl;
			return m;
		}
	}
	return ret;
}

int check_playtime(play_t* play, int target) {
	int ret = 0;
	if (target > play->playtime) {
		ret = 1;
	}
	else if (target == play->playtime) {
		if (play->idx > 0) {
			ret = 1;
		}
	}
	return ret;
}

list_head* find_pos(list_head* head, int target) {
	list_head* ret = head;

	list_head* tmp = 0;
	list_head* n = 0;
	play_t* play_l = 0;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {
		play_l = reinterpret_cast<play_t*>(tmp);
		if (check_playtime(play_l, target) == 1) {
			ret = tmp->prev;
			break;
		}
	}
	return ret;
}

int update_gen_playtime(int id, int playtime, int genre) {
	int ret = 0;	

	list_head* tmp = 0;
	list_head* n = 0;
	list_head* head = &gen_head[genre];
	gen_t* gen_l = 0;
	int cnt = 0;
	int target = 0;
	list_head* list_old = 0;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {
		gen_l = (gen_t*)tmp;
		std::cout << "gen_l->idx = " << gen_l->idx << std::endl;
		if (gen_l->idx == id) {
			gen_l->playtime += playtime;
			target = gen_l->playtime;
			list_old = tmp;
			std::cout << "gen_l->playtime = " << gen_l->playtime << std::endl;
			break;
		}
		cnt++;
	}
	list_head* pos = find_pos(head, target);
	gen_t* gen_new = gen_alloc();
	gen_new->idx = id;
	gen_new->playtime = target;
	gen_new->genre = genre;
	list_add(pos, &(gen_new->gen_list));
	//list_del(&(play_old->play_list));
	list_del(list_old);
	return ret;
}

int update_playtime(int id, int playtime) {
	int ret = 0;
	//int pos = binarytry(id);
	//std::cout << "pos = " << pos << std::endl;
	list_head* tmp = 0;
	list_head* n = 0;
	list_head* head = &play_head;
	play_t* play_l = 0;
	int cnt = 0;
	int genre = 0;
	int target = 0;
	list_head* list_old = 0;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {		
		play_l = (play_t*)tmp;
		std::cout << "play_l->idx = " << play_l->idx << std::endl;
		if (play_l->idx == id) {
			play_l->playtime += playtime;
			genre = play_l->genre;
			target = play_l->playtime;
			list_old = tmp;
			std::cout << "play_l->playtime = " << play_l->playtime << std::endl;
			break;
		}		
		cnt++;
	}
	list_head* pos = find_pos(head, target);
	play_t* play_new = play_alloc();
	play_new->idx = id;
	play_new->playtime = target;
	play_new->genre = genre;
	list_add(pos, &(play_new->play_list));
	//list_del(&(play_old->play_list));
	list_del(list_old);

	update_gen_playtime(id, playtime, genre);	
	return ret;
}

int get_cnt_list(list_head* head) {
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

int check_play_list(dat_t* target, dat_t* arr) {
	int ret = 0;
	if (target->playtime > arr->playtime) {
		ret = 1;
	}
	else if (target->playtime == arr->playtime) {
		if (target->idx < arr->idx) {
			ret = 1;
		}
	}
	return ret;
}

#if 0
list_head* find_pos(dat_t* target) {
	list_head* ret = &play_head;
	list_head* head = &play_head;
	list_head* tmp = 0;
	list_head* n = 0;
	if (get_cnt_list(&play_head) == 0) return ret;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {	

		if (check_play_list(target, arr) == 1) {
			ret = tmp->prev;
			break;
		}
		ret = tmp;
	}
	return ret;
}

int make_sort_play_list(dat_t* arr, int N) {
	int ret = 0;

	for (int i = 0; i < N; i++) {
		dat_t* target = &arr[i];
		list_head* pos = find_pos(target);
		//list_add(pos, &(target->play_list));
	}
	return ret;
}
#endif

int main() {
	int ret = 0;
	std::cout << "start play_gen5" << std::endl;
	clock_t start, end;

	N = MAX_NUM;
	start = clock();
	gen_input(N);
	end = clock();
	std::cout << "gen_input, elapsed time = " << end - start << std::endl;
	
	list_init(&play_head);
	for (int i = 0; i < N; i++) {
		list_init(&gen_head[i]);
	}
	play_cur = 0;
	gen_cur = 0;

	start = clock();
	init_data(in, N);
	end = clock();
	std::cout << "init_data, elapsed time = " << end - start << std::endl;
	show_play(N);
	show_gen(N);

	start = clock();
	merge_sort_play(0, N-1);
	end = clock();
	std::cout << "merge_sort_play, elapsed time = " << end - start << std::endl;
	show_play(N);

	start = clock();
	make_play_list(N);
	end = clock();
	std::cout << "make_play_list, elapsed time = " << end - start << std::endl;
	for_each_list_safe_play(&play_head);

	start = clock();
	merge_sort_gen(0, N - 1);
	end = clock();
	std::cout << "merge_sort_gen, elapsed time = " << end - start << std::endl;
	show_gen(N);

	start = clock();
	make_gen_list(N);
	end = clock();
	std::cout << "make_gen_list, elapsed time = " << end - start << std::endl;	

#if 1
	start = clock();
	for (int i = 0; i < 6; i++) {
		//std::cout << "for_each_list_safe_gen" << i << std::endl;
		for_each_list_safe_gen(&gen_head[i]);
	}	
	end = clock();
	std::cout << "for_each_list_safe, elapsed time = " << end - start << std::endl;
#endif

#if 1
	start = clock();
	int up_idx = 2;
	int add_playtime = 10;
	update_playtime(up_idx, add_playtime);
	end = clock();
	std::cout << "update_playtime, elapsed time = " << end - start << std::endl;
	for_each_list_safe_play(&play_head);
#endif

#if 1
	start = clock();
	for (int i = 0; i < 6; i++) {
		//std::cout << "for_each_list_safe_gen" << i << std::endl;
		for_each_list_safe_gen(&gen_head[i]);
	}
	end = clock();
	std::cout << "for_each_list_safe, elapsed time = " << end - start << std::endl;
#endif

	return ret;
}