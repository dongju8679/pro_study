#include <iostream>

#define MAX_NUM (1<<3) //30000

int N;

struct list_head {
	list_head* prev;
	list_head* next;
}play_head, gen_head[6];

struct dat_t {
	int idx;
	int playtime;
	int genre;
}in[MAX_NUM], arr[MAX_NUM], tmp[MAX_NUM];

struct play_t {
	list_head play_list;
	dat_t* dat;
}play[MAX_NUM], ptmp[MAX_NUM];

struct gen_t {
	list_head gen_list;
	dat_t* dat;
}gen[MAX_NUM], gtmp[MAX_NUM];

enum {
	play_list_enum = 0,
	gen_list_enum = 1,
	max_num_list_enum = 2
};

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
	std::cout << "start gen_input1" << std::endl;
	for (int i = 0; i < N; i++) {
		in[i].idx = i;
		in[i].playtime = rand() % 30;
		in[i].genre = rand() % 6;		
		std::cout << "in idx = " << in[i].idx << ", playtime = " << in[i].playtime << ", genre = " << in[i].genre << std::endl;
	}
	return ret;
}

int init_data(dat_t* in, dat_t* arr, int N) {
	int ret = 0;	
	play_t* play_l;
	gen_t* gen_l;
	for (int i = 0; i < N; i++) {
		arr[i].idx = in[i].idx;		
		arr[i].playtime = in[i].playtime;
		arr[i].genre = in[i].genre;	
		play_l = &play[i];
		std::cout << "play_l = " << play_l << std::endl;
		play_l->dat = &arr[i];
		std::cout << "play_l->dat = " << play_l->dat << std::endl;
		gen_l = &gen[i];		
		gen_l->dat = &arr[i];
	}
	return ret;
}

int check_condition_play(dat_t* arr, int i, int j) {
	int ret = 0;
	if (arr[i].playtime > arr[j].playtime) {
		ret = 1;
	}
	else if (arr[i].playtime == arr[j].playtime) {
		if (arr[i].idx < arr[j].idx) {
			ret = 1;
		}
	}
	return ret;
}

int check_condition_gen(dat_t* arr, int i, int j) {
	int ret = 0;
	if (arr[i].genre < arr[j].genre) {
		ret = 1;
	}
	else if (arr[i].genre == arr[j].genre) {
		if (arr[i].playtime > arr[j].playtime) {
			ret = 1;
		}
	}
	return ret;
}

void merge_sort_gen(dat_t* arr, int start, int end) {
	if (start >= end) return;
	int middle = (start + end) / 2;
	int i, j, k;
	i = start;
	j = middle + 1;
	k = i;
	merge_sort_gen(arr, start, middle);
	merge_sort_gen(arr, middle + 1, end);
	while (i <= middle && j <= end) {
		if (check_condition_gen(arr, i, j) == 1) {
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

void merge_sort_play(dat_t* arr, int start, int end) {
	if (start >= end) return;
	int middle = (start + end) / 2;
	int i, j, k;
	i = start;
	j = middle + 1;
	k = i;
	merge_sort_play(arr, start, middle);
	merge_sort_play(arr, middle + 1, end);
	while (i <= middle && j <= end) {
		if (check_condition_play(arr, i, j) == 1) {
			tmp[k++] = arr[i++];
			ptmp[k++] = play[i++];			
		}
		else {
			tmp[k++] = arr[j++];
			ptmp[k++] = play[j++];			
		}
	}
	while (i <= middle) {
		tmp[k++] = arr[i++];
		ptmp[k++] = play[i++];		
	}
	while (j <= end) {
		tmp[k++] = arr[j++];
		ptmp[k++] = play[j++];		
	}
	for (k = start; k <= end; k++) {
		arr[k] = tmp[k];
		play[k] = ptmp[k];		
	}
}

int show_arr(dat_t* arr, int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		std::cout << "&arr[i] = " << &arr[i] << std::endl;
		std::cout << "arr[" << i << "] = " << arr[i].idx << "/" << arr[i].playtime << "/" << arr[i].genre << std::endl;
	}
	return ret;
}

int make_play_list(int N) {
	int ret = 0;
	play_t* target = 0;
	for (int i = 0; i < N; i++) {
		target = &play[i];
		std::cout << "target = " << target << std::endl;
		std::cout << "target->dat = " << target->dat << std::endl;
		list_add_tail(&play_head, &(target->play_list));
	}	
	return ret;
}

int make_gen_list(dat_t* arr, int N) {
	int ret = 0;
	gen_t* target = 0;
	int gen_head_idx = 0;
	for (int i = 0; i < N; i++) {				
		target = &gen[i];
		gen_head_idx = target->dat->idx;
		//std::cout << "gen_head_idx = " << gen_head_idx  << ", idx = " << dat->idx << ", playtime = " << dat->playtime << std::endl;		
		list_add_tail(&gen_head[gen_head_idx], &(target->gen_list));
	}
	return ret;
}

int for_each_list_safe(list_head* head) {
	int ret = 0;
	list_head* tmp = 0;
	list_head* n = 0;	
	int cnt = 0;
	play_t* target = 0;
	std::cout << "for_each_list_safe, head = " << head << std::endl;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {	
		std::cout << "tmp = " << tmp << std::endl;
		target = reinterpret_cast<play_t*>(tmp);
		dat_t* arr = target->dat;
		std::cout << "arr = " << arr << std::endl;
#if 1
		//std::cout << "arr[" << cnt << "] = " << arr->idx << "/" << arr->playtime << "/" << arr->genre << std::endl;
		cnt++;
#endif
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
		if (target < arr[m].idx) {
			std::cout << "1m = " << m << std::endl;
			if (m == 0) return m;
			if (target > arr[m - 1].idx) return m;
			e = m - 1;
		}
		else if (target > arr[m].idx) {
			std::cout << "2m = " << m << std::endl;
			if (m == e) return m + 1;
			if (target < arr[m + 1].idx) return m + 1;
			s = m + 1;
		}
		else {
			std::cout << "m = " << m << std::endl;
			return m;
		}
	}
	return ret;
}

int update_playtime(int id, int playtime) {
	int ret = 0;
	//int pos = binarytry(id);
	//std::cout << "" << pos << std::endl;
	list_head* tmp = 0;
	list_head* n = 0;
	list_head* head = &play_head;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {		
		play_t* play_l = (play_t*)tmp;
		dat_t* dat = play_l->dat;
		if (dat->idx == id) {
			std::cout << "dat->idx = " << dat->idx << std::endl;
			dat->playtime += playtime;
			break;
		}
	}
	return ret;
}

int main() {
	int ret = 0;
	std::cout << "start play_gen1" << std::endl;
	clock_t start, end;
#if 1
	list_init(&play_head);
	for (int i = 0; i < N; i++) {
		list_init(&gen_head[i]);
	}
#endif
	N = MAX_NUM;
	start = clock();
	gen_input(N);
	end = clock();
	std::cout << "gen_input, elapsed time = " << end - start << std::endl;
#if 1
	start = clock();
	init_data(in, arr, N);
	end = clock();
	std::cout << "init_data, elapsed time = " << end - start << std::endl;
	show_arr(arr, N);
#endif
#if 0
	start = clock();
	merge_sort_play(arr, 0, N - 1);
	end = clock();
	std::cout << "merge_sort_play, elapsed time = " << end - start << std::endl;
	show_arr(arr, N);
#endif

	start = clock();		
	make_play_list(N);		
	for_each_list_safe(&play_head);
	end = clock();
	std::cout << "make_play_list, elapsed time = " << end - start << std::endl;
#if 0

	start = clock();
	merge_sort_gen(arr, 0, N - 1);
	end = clock();
	std::cout << "merge_sort_gen, elapsed time = " << end - start << std::endl;
	show_arr(arr, N);

	start = clock();
	make_gen_list(arr, N);
	end = clock();
	std::cout << "make_gen_list, elapsed time = " << end - start << std::endl;
#if 1
	for (int i = 0; i < 6; i++) {
		std::cout << "gen_head" << i << std::endl;
		for_each_list_safe(&gen_head[i], gen_list_enum);
	}
#endif	
	show_arr(arr, N);
	std::cout << "before foreachplay_head" << std::endl;
	for_each_list_safe(&play_head, play_list_enum);
	std::cout << "before update_playtime" << std::endl;
	update_playtime(0, 10);
	std::cout << "after update_playtime" << std::endl;
	show_arr(arr, N);
#endif

	return ret;
}