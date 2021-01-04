#include <iostream>

#define MAX_NUM 10 //30000

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
	list_head* play_list;
	list_head* gen_list;
	int idx;
	int playtime;
	int genre;
}arr[MAX_NUM];

int alloc_cur;

dat_t* my_alloc() {
	return &arr[alloc_cur++];
}

int list_init(list_head* head) {
	head->prev = head;
	head->next = head;
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

int init_data(in_t* in, dat_t* arr, int N) {
	int ret = 0;

	for (int i = 0; i < N; i++) {
		arr[i].idx = in[i].idx;
		arr[i].playtime = in[i].playtime;
		arr[i].genre = in[i].genre;
	}

	return ret;
}

int main() {
	int ret = 0;

	N = MAX_NUM;

	gen_input(N);
	alloc_cur = 0;
	list_init(&play_head);
	for (int i = 0; i < N; i++) {
		list_init(&gen_head[i]);
	}	
	
	init_data(in, arr, N);

	std::cout << "start play_gen1" << std::endl;

	return ret;
}