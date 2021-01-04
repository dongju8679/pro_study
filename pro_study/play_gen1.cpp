#include <iostream>

#define MAX_NUM (1<<15) //30000

struct in_t {
	int idx;
	int playtime;
	int genre;
}in[MAX_NUM];

int N;

struct list_head {
	list_head* prev;
	list_head* next;
}play_head, gen_head[6];

struct dat_t {
	list_head play_list;
	list_head gen_list;
	int idx;
	int playtime;
	int genre;
}arr[MAX_NUM], tmp[MAX_NUM];

enum {
	play_list_enum = 0,
	gen_list_enum = 1,
	max_num_list_enum = 2
};

int offsetoflist[max_num_list_enum] = {0, sizeof(list_head)};

#if 0
int alloc_cur;
dat_t* my_alloc() {
	return &arr[alloc_cur++];
}
#endif

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
		//std::cout << "in[" << i << "] = " << in[i].idx << "/" << in[i].playtime << "/" << in[i].genre << std::endl;
	}
	return ret;
}

int init_data(in_t* in, dat_t* arr, int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		arr[i].idx = in[i].idx;
		arr[i].playtime = in[i].playtime;
		arr[i].genre = in[i].genre;
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

int show_arr(dat_t* arr, int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		std::cout << "arr[" << i << "] = " << arr[i].idx << "/" << arr[i].playtime << "/" << arr[i].genre << std::endl;
	}
	return ret;
}

int make_play_list(dat_t* arr, int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		dat_t* dat = &arr[i];
		list_add_tail(&play_head, &(dat->play_list));
	}
	return ret;
}

int make_gen_list(dat_t* arr, int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		dat_t* dat = &arr[i];
		//std::cout << "dat = " << dat << std::endl;
		int gen_head_idx = dat->genre;
		//std::cout << "gen_head_idx = " << gen_head_idx  << ", idx = " << dat->idx << ", playtime = " << dat->playtime << std::endl;		
		list_add_tail(&gen_head[gen_head_idx], &(dat->gen_list));
	}
	return ret;
}

int for_each_list_safe(list_head* head, int list_idx) {
	int ret = 0;
	list_head* tmp = 0;
	list_head* n = 0;
	int cnt = 0;
	std::cout << "for_each_list_safe, list_idx" << list_idx << std::endl;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {		
		dat_t* arr = reinterpret_cast<dat_t*>((char*)tmp - (char*)offsetoflist[list_idx]);
		std::cout << "arr[" << cnt << "] = " << arr->idx << "/" << arr->playtime << "/" << arr->genre << std::endl;
		cnt++;
	}
	return ret;
}

int main() {
	int ret = 0;
	std::cout << "start play_gen1" << std::endl;
	clock_t start, end;

	N = MAX_NUM;
	start = clock();
	gen_input(N);
	end = clock();
	std::cout << "gen_input, elapsed time = " << end - start << std::endl;
	//alloc_cur = 0;
	list_init(&play_head);
	for (int i = 0; i < N; i++) {
		list_init(&gen_head[i]);
	}	
	
	start = clock();
	init_data(in, arr, N);
	end = clock();
	std::cout << "init_data, elapsed time = " << end - start << std::endl;
	//show_arr(arr, N);
	start = clock();
	merge_sort_play(arr, 0, N-1);
	end = clock();
	std::cout << "merge_sort_play, elapsed time = " << end - start << std::endl;
	//show_arr(arr, N);

	start = clock();
	make_play_list(arr, N);
	//for_each_list_safe(&play_head, play_list_enum);
	end = clock();
	std::cout << "make_play_list, elapsed time = " << end - start << std::endl;

	start = clock();
	merge_sort_gen(arr, 0, N - 1);
	end = clock();
	std::cout << "merge_sort_gen, elapsed time = " << end - start << std::endl;
	//show_arr(arr, N);

	start = clock();
	make_gen_list(arr, N);
	end = clock();
	std::cout << "make_gen_list, elapsed time = " << end - start << std::endl;
#if 0
	for (int i = 0; i < 6; i++) {
		for_each_list_safe(&gen_head[i], gen_list_enum);
	}
#endif

	return ret;
}