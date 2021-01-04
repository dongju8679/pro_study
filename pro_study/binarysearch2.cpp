#include <iostream>

#define MAX_NUM 1<<20

int N;
int in[MAX_NUM];
int tmp[MAX_NUM];

int heap[MAX_NUM];
int heapSize = 0;

int gen_input(int N) {
	int ret = 0;	
	for (int i = 0; i < N; i++) {
		in[i] = rand() % 90;
	}
	return ret;
}

int show_input(int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		std::cout << "in[" << i << "] = " << in[i] << std::endl;
	}
	return ret;
}

int show_heap(int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		std::cout << "in[" << i << "] = " << heap[i] << std::endl;
	}
	return ret;
}

void heapInit(void)
{
	heapSize = 0;
}

int heapPush(int value)
{
	if (heapSize + 1 > MAX_NUM)
	{
		printf("queue is full!");
		return 0;
	}
	heap[heapSize] = value;
	int current = heapSize;
	while (current > 0 && heap[current] < heap[(current - 1) / 2])
	{
		int temp = heap[(current - 1) / 2];
		heap[(current - 1) / 2] = heap[current];
		heap[current] = temp;
		current = (current - 1) / 2;
	}
	heapSize = heapSize + 1;
	return 1;
}

int binarySearch(int* arr, int low, int high, int target)
{
	int ret = 0;
	int mid;
	std::cout << "low = " << low << ", high = " << high << std::endl;
	if (low > high)
	{	
		std::cout << "low = " << low << ", high = " << high << std::endl;
		return -1;
	}	

	mid = (low + high) / 2;
	std::cout << "1, low = " << low << ", high = " << high << ", mid = " << mid << std::endl;
	std::cout << "target = " << target << ", arr[mid] = " << arr[mid] << std::endl;

	if (target < arr[mid])
	{
		std::cout << "2, low = " << low << ", high = " << high << ", mid = " << mid << std::endl;
		binarySearch(arr, low, mid - 1, target);
	}
	else if (arr[mid] < target)
	{
		std::cout << "3, low = " << low << ", high = " << high << ", mid = " << mid << std::endl;
		binarySearch(arr, mid + 1, high, target);
	}
	else
	{
		ret = mid;
		return ret;
	}
}

int binarytry(int in[], int s, int e, int target) {
	int ret = 0;
	int m;
	while (s <= e) {
		m = (s + e) / 2;
		if (target < in[m]) {
			if (m == 0) return m;
			if (target > in[m - 1]) return m;
			e = m - 1;
		}
		else if (target > in[m]) {
			if (m == e) return m + 1;
			if (target < in[m + 1]) return m + 1;
			s = m + 1;
		}
	}
	return ret;
}

int check_condition(int* arr, int i, int j) {
	int ret = 0;
	if (arr[i] < arr[j]) {
		ret = 1;
	}
	return ret;
}

void merge_sort(int* arr, int start, int end) {
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

int main() {
	int ret = 0;
	std::cout << "start binarysearch2" << std::endl;
	clock_t start, end;

	N = MAX_NUM;
	start = clock();
	gen_input(N);
	end = clock();
	std::cout << "gen_input, elapsed time = " << end - start << std::endl;
	//show_input(N);
	start = clock();
	heapInit();
	for (int i = 0; i < N; i++)
	{
		int value = in[i];
		heapPush(value);
	}
	end = clock();
	std::cout << "after heapPush, elapsed time = " << end - start << std::endl;
	//show_heap(N);
	
	int low = 0;
	int high = N - 1;
	int target = 20;	
	start = clock();
	merge_sort(in, low, high);
	end = clock();
	std::cout << "merge_sort, elapsed time = " << end - start << std::endl;
	//int pos = binarySearch(heap, low, high, target);
	start = clock();
	int pos = binarytry(heap, low, high, target);
	end = clock();
	std::cout << "pos = " << pos << ", heap[pos] = " << heap[pos] << ", binarytry, elapsed time = " << end - start << std::endl;	

	return ret;
}