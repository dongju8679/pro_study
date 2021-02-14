#include <iostream>
#define MAX_NUM (1<<2)
#define MAX_HEAP (MAX_NUM * 2)
#define MAX_STR (10)

int N;
struct in_t {
	int idx;
	int val;
}in[MAX_NUM];

struct data_t {
	int idx;
	int val;
	char name[MAX_STR];
}data[MAX_NUM], heap1[MAX_HEAP];

int gen_input() {
	int ret = 0;
	std::cout << "start gen_input" << std::endl;
	for (int i = 0; i < N; i++) {
		in[i].idx = i;
		in[i].val = rand() % 30;
	}
	return ret;
}

int maxn = 0;

int min_heap1(int i, int j) {
	int ret = 0;
	if (heap1[i].val < heap1[j].val) {
		ret = 1;
	}
	else if (heap1[i].val == heap1[j].val) {
		if (heap1[i].idx > heap1[j].idx) {
			ret = 1;
		}
	}
	return ret;
}

inline int swap_heap1(int i, int j) {
	int ret = 0;
	data_t temp = {};
	temp = heap1[i];
	heap1[i] = heap1[j];
	heap1[j] = temp;
	return ret;	
}

int push_heap1(data_t* data) {
	int ret = 0;
	maxn++;
	heap1[maxn];
	int C = maxn;
	int P = C/2;
	while (P>0) {
		if (min_heap1(C, P) == 1) {
			swap_heap1(C, P);
			C = P; P = C / 2;
		}
		else break;
	}
	return ret;
}

data_t popheap1() {
	data_t ret = heap1[1];	
	heap1[1] = heap1[maxn];
	maxn--;
	int P = 1, L = 2, R = 3, C;
	while (L <= maxn) {
		if (min_heap1(L, R) == 1) {
			C = L;
		}
		else C = R;
		if (min_heap1(C, P) == 1) {
			swap_heap1(C, P);
			P = C, L = P * 2 + 1, R = L + 1;
		}
		else break;
	}

	return ret;
}

int main() {
	int ret = 0;
	N = MAX_NUM;
	std::cout << "start heap_t2" << std::endl;
	gen_input();
	return ret;
}