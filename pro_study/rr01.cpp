#include <iostream>
#define MAX_NUM (1<<2)
#define MAX_HEAP (MAX_NUM * 2)

int N;
int in[MAX_NUM];
int maxn = 0;
int heap[MAX_HEAP];

int gen_input() {
	int ret = 0;

	for (int i = 0; i < N; i++) {
		in[i] = rand() % 30;
		std::cout << "in = " << in[i] << std::endl;
	}

	return ret;
}

inline int swap(int i, int j) {
	int ret = 0;
	int temp;
	temp = heap[i];
	heap[i] = heap[j];
	heap[j] = temp;
	return ret;
}

int push(int val) {
	int ret = 0;
	heap[++maxn] = val;

	int P, C;
	C = maxn;
	P = C / 2;

	while (P>0) {
		if (heap[C] < heap[P]) {
			swap(C, P);
			C = P;
			P = C / 2;
		}
		else break;
	}

	return ret;
}

int pop() {
	int ret = 0;
	ret = heap[1];
	heap[1] = heap[maxn--];

	int P, L, R, C;
	P = 1;
	L = 2;
	R = 3;

	while (L <= maxn) {
		if (heap[L] < heap[R]) {
			C = L;
		}
		else {
			C = R;
		}
		if (heap[C] < heap[P]) {
			swap(C, P);
			P = C;
			L = 2 * P + 1;
			R = L + 1;
		}
		else break;
	}

	return ret;
}

int main() {
	int ret = 0;
	N = MAX_NUM;

	gen_input();

	return ret;
}