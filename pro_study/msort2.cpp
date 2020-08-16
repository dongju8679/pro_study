#include <iostream>
#include <random>
#include <time.h>
#include <stdlib.h>

#define MAX_STRING 100
#define MAX_N 10

int N;

class dat_t {
public:
	dat_t* prev;
	dat_t* next;
	int idx;
	int val;
	char name[MAX_STRING];
private:
};

dat_t dat[MAX_N];
dat_t tmp[MAX_N];

int set_input(dat_t in_array[]);
int my_strcmp(char* strA, char* strB);
int my_strlen(char* str);
int my_strcpy(char* dst, char* src);
int initialize();
int print_array(dat_t array[]);
void msort(dat_t A[], int start, int end);

int main(int argc, char *argv[]) {
	int ret = 0;
	std::cout << "start main" << std::endl;
	N = MAX_N;

	initialize();

	set_input(dat);
	print_array(dat);

	int start_idx = 0;
	int end_idx = N - 1;

	msort(dat, start_idx, end_idx);
	print_array(dat);

	return ret;
}

int check_condition(dat_t A[], int i, int j) {
	int ret = 0;
	if (A[i].val < A[j].val) {
		ret = 1;
	} else if (A[i].val == A[j].val) {
		if (A[i].idx < A[j].idx) {
			ret = 1;
		}		
	} else {
		ret = 0;
	}
	return ret;
}

void msort(dat_t A[], int start, int end) {
	if (start >= end) {
		return;
	}
	int middle = (start + end) / 2;
	int i, j, k;
	i = start;
	j = middle + 1;
	k = i;
	msort(A, start, middle);
	msort(A, middle + 1, end);

	while (i <= middle && j <= end) {
		if (check_condition(A, i, j) == 1) {
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

int print_array(dat_t array[]) {
	int ret = 0;
	std::cout << std::endl;

	for (int i = 0; i < N; i++) {
		std::cout << "idx = " << array[i].idx << ", val = " << array[i].val << std::endl;
	}
	return ret;
}

int initialize() {
	int ret = 0;
	

	return ret;
}

int set_input(dat_t in_array[]) {

	int ret = 0;
	srand(unsigned int(time(NULL)));	

	for (int i = 0; i < N; i++) {
		in_array[i].idx = i;
		in_array[i].val = rand() % 10;
		//in_array[i].name = ;
	}	

	return ret;
}

int my_strlen(char* str) {
	int ret = 0;
	char* ptr = str;
	//std::cout << "ptr + 1 = " << ptr + 1<< std::endl;
#if 1
	while (*ptr != '\0') {
		//printf("before ret = %d, *ptr = %c\n", ret, *ptr);
		ret = ret + 1;
		//printf("after ret = %d, *ptr = %c\n", ret);
		ptr++;
	}
#endif
	return ret;
}

int my_strcpy(char* dst, char* src) {
	int ret = 0;
	//char *ptr = src;

	while (1) {
		//printf("before src = %c, dst = %c\n", *src, *dst);
		if (*src == '\0') {
			break;
		}
		*dst = *src;
		//printf("after src = %c, dst = %c\n", *src, *dst);
		dst++;
		src++;
		ret++;
	}
	*dst = '\0';
	return ret;
}

int my_strcmp(char* strA, char* strB) {
	int ret = 0;
	while (1) {
		if (*strA == '\0' || *strB == '\0') {
			break;
		}
		if (*strA == *strB) {
			ret = 0;
		}
		else if (*strA > * strB) {
			ret = 1;
			break;
		}
		else if (*strA < *strB) {
			ret = -1;
			break;
		}
		strA++;
		strB++;
	}
	return ret;
}