#include <iostream>

#define MAX_N 10

int A[MAX_N];
int N;

int set_input(int A[]) {
	int ret = 0;

	for (int i = 0; i < N; i++) {
		A[i] = rand() % 10;
		//printf("a[i] = %d\n", A[i]);
	}
	return ret;
}

int print_array(int A[]) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		printf("A[%d] = %d\n", i, A[i]);
	}
	return ret;
}

int main() {
	int ret = 0;
	N = MAX_N;
	set_input(A);
	std::cout << "start qsort1" << std::endl;
	print_array(A);
	qsort();

	return ret;
}