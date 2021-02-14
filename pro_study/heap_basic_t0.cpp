#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define MAX_NUM (1<<2)
#define MAX_HEAP (MAX_NUM * 2)

struct in_t {
	int idx;
	int val;
}in[MAX_NUM];

int N;
int heap[MAX_HEAP]; // minimum heap
int maxn; // last heap index
inline void SWAP(int a, int b) {
	int temp = heap[a];
	heap[a] = heap[b];
	heap[b] = temp;
}

void push(int cnt) {
	heap[++maxn] = cnt;
	int C = maxn;
	int P = C / 2;
	printf("C(%d), P(%d)\n", C, P);
	while (P > 0) {
		if (heap[C] < heap[P]) {
			SWAP(C, P);
			C = P; P = C / 2;
			printf("swap, C(%d), P(%d)\n", C, P);
		}
		else break; // if normal, finish
	}
}

int print_heap() {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		printf("heap[%d] = %d\n", i, heap[i]);
	}
	return ret;
}

int pop() {
	int ret = heap[1]; heap[1] = heap[maxn--]; // complete binary tree, last node is bought as 1 node
	int P = 1, L = 2, R = 3, C;
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

void InputData() {
#if 1
	register int i; int cnt;
	scanf("%d", &N);
	maxn = 0; // init priority queue
	for (i = 1; i <= N; i++) {
		scanf("%d", &cnt);
		in[i].val = cnt;
		printf("in[i].val = %d\n", in[i].val);
		//push(cnt);
	}
#else
	for (int i = 0; i < N; i++) {
		in[i].idx = i;
		in[i].val = rand() % 30;
		//push(in[i].val);
	}
#endif
}

int main() {
	int ret = 0;
	freopen("input.txt", "r", stdin);
	InputData();
	print_heap();

	for (int i = 0; i < N; i++) {
		push(in[i].val);
	}
	

	return ret;
}