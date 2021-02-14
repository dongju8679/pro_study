#include <iostream>
#define MAX_NUM (1<<2)
#define MAX_STR (10)

struct in_t {
	int idx;
	int val;
	char name[MAX_STR];
}in[MAX_NUM];

int N;
int heap[MAX_NUM];
int maxn;
inline void SWAP(int a, int b) {
	int temp = heap[a];
	heap[a] = heap[b];
	heap[b] = temp;
}

void push(int cnt) {
	heap[++maxn] = cnt;
	std::cout << "initial maxn = " << maxn << std::endl;
	std::cout << "push, cnt = " << cnt << std::endl;
	register int C = maxn, P = C / 2;
	while (P > 0) {
		if (heap[C] < heap[P]) {
			SWAP(C, P);
			C = P;
			P = C / 2;
		}
		else break;
	}
}

int pop() {
	int ret = heap[1];
	heap[1] = heap[maxn--];
	register int P = 1, L = 2, R = 3, C;
	while (L <= maxn) {
		if (R > maxn) C = L;
		else C = (heap[L] < heap[R]) ? L : R;
		if (heap[C] < heap[P]) {
			SWAP(C, P);
			P = C; L = P * 2; R = L + 1;
		}
		else break;
	}
	return ret;
}

int gen_input() {
	int ret = 0;

	std::cout << "gen_input" << std::endl;
	for (int i = 0; i < MAX_NUM; i++) {
		in[i].idx = i;
		in[i].val = rand() % 30;
		std::cout << "idx = " << in[i].idx << ", val = " << in[i].val << std::endl;
	}

	return ret;
}

int main() {
	int ans = 0;
	std::cout << "start heap_t0" << std::endl;
	gen_input();
	//printf("%d\n", ans);

	for (int i = 0; i < MAX_NUM; i++) {
		push(in[i].val);
	}
	
	return 0;
}