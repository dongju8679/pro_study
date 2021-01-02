#include <iostream>
#define MAX_NUM 1<<20
#define MAX_STR_LEN 10

struct my_data {
	int idx;
	int val;
	char name[MAX_STR_LEN];
}in[MAX_NUM], tmp[MAX_NUM];

//int input[MAX_NUM];
int N;

int check_condition(my_data* arr, int i, int j) {
	int ret = 0;
	if (arr[i].val < arr[j].val) {
		ret = 1;
	}
	else if (arr[i].val == arr[j].val) {
		if (arr[i].idx < arr[j].idx) {
			ret = 1;
		}
	}
	return ret;
}

int check_condition_insert(my_data* arr, my_data temp, int j) {
	int ret = 0;
	if (temp.val < arr[j].val) {
		ret = 1;
	}
	else if (temp.val == arr[j].val) {
		if (temp.idx < arr[j].idx) {
			ret = 1;
		}
	}
	return ret;
}

void insertionSort(my_data* in, int start, int num)
{
	my_data temp = {};
	int i;
	int j;	
	for (i = start + 1; i <= num; i++)
	{
		temp = in[i];		
		j = i - 1;		
		while ((check_condition_insert(in, temp, j) == 1) && (j >= 0))
		{		
			in[j + 1] = in[j];
			j = j - 1;
		}		
		in[j + 1] = temp;		
	}
}

int check_condition_idx(my_data* arr, int i, int j) {
	int ret = 0;
	if (arr[i].idx < arr[j].idx) {
		ret = 1;
	}
	return ret;
}

void merge_sort(my_data* arr, int start, int end) {
	if (start >= end) return;
	int middle = (start + end) / 2;
	int i, j, k;
	i = start;
	j = middle + 1;
	k = i;
	merge_sort(arr, start, middle);
	merge_sort(arr, middle + 1, end);
	while (i <= middle && j <= end) {
		if (check_condition(arr, i, j) == 1) {
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

int show_arr(int num) {
	int ret = 0;
	for (int i = 0; i < num; i++) {
		std::cout << "in[i].idx = " << in[i].idx << ", in[i].val = " << in[i].val << std::endl;
	}
	return ret;
}

int main() {
	int ret = 0;
	clock_t start, end;

	N = MAX_NUM;
	for (int i = 0; i < N; i++) {
		in[i].val = rand() % 10;
		in[i].idx = i;
	}
	//show_arr(N);
	start = clock();
	merge_sort(in, 0, N - 2);
	end = clock();
	std::cout << "after mergesort, elapsed time = " << end - start << std::endl;
	//show_arr(N);

	start = clock();
#if 1
	insertionSort(in, 0, N - 1);
	std::cout << "insert sort!" << std::endl;
#else
	merge_sort(in, 0, N - 1);
	std::cout << "merge sort!" << std::endl;
#endif
	end = clock();
	std::cout << "after insertionSort, elapsed time = " << end - start << std::endl;
	//show_arr(N);

	return ret;
}