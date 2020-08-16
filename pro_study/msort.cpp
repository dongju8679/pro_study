#include <iostream>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 10

int A[MAX_N];
int tmp[MAX_N];

void msort(int A[], int start, int end);

int set_input(int in_A[]) {
	int ret = 0;
#if 0
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 99);

	for (int i = 0; i < 5; i++) {
		std::cout << "random_number = " << dis(gen) << std::endl;
	}
#endif
	srand(time(NULL));
#if 0
	for (auto i : A) {
		A[i] = rand() % 10;
		std::cout << "" << A[i] << std::endl;
	}
#endif
	for (int i = 0; i < MAX_N; i++) {
		A[i] = rand() % 10;
		printf("A[%d] = %d\n", i, A[i]);
	}

	return ret;
}

int print_array(int array[]) {
	int ret = 0;
	std::cout << "start print_array" << std::endl;
	for (int i = 0; i < MAX_N; i++) {
		printf("array[%d] = %d\n", i, array[i]);
	}
	std::cout << "end print_array" << std::endl;
	return ret;
}

int main() {
	int ret = 0;
	set_input(A);
	print_array(A);

	msort(A, 0, 9);
	print_array(A);

	return ret;
}

void msort(int A[], int start, int end) {
	if (start >= end) {
		return;
	}

	int i;
	int j;
	int k;
	int middle;
	middle = (start + end) / 2;
	i = start;
	j = middle + 1;
	k = i;
	msort(A, start, middle);
	msort(A, middle + 1, end);
	
	while (i <= middle && j <= end) {
		if (A[i] < A[j]) {
			tmp[k++] = A[i++];
		}
		else {
			tmp[k++] = A[j++];
		}
	}
	while (i <= middle) {
		tmp[k++] = A[i++];
	}
	while (j <= end) {
		tmp[k++] = A[j++];
	}
	
	for (k = start; k <= end; k++) {
		A[k] = tmp[k];
	}	
}