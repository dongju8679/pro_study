#include <iostream>

#define MAX_SIZE (1<<18)

int heap[MAX_SIZE];
int heapSize = 0;
int in[MAX_SIZE], out[MAX_SIZE], arr[MAX_SIZE], tmp[MAX_SIZE], input[MAX_SIZE];
int N;

void heapInit(void)
{
	heapSize = 0;
}

int heapPush(int value)
{
	if (heapSize + 1 > MAX_SIZE)
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

int heapPop(int* value)
{
	if (heapSize <= 0)
	{
		return -1;
	}

	*value = heap[0];
	heapSize = heapSize - 1;

	heap[0] = heap[heapSize];

	int current = 0;
	while (current * 2 + 1 < heapSize)
	{
		int child;
		if (current * 2 + 2 == heapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			child = heap[current * 2 + 1] < heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
		}

		if (heap[current] < heap[child])
		{
			break;
		}

		int temp = heap[current];
		heap[current] = heap[child];
		heap[child] = temp;

		current = child;
	}
	return 1;
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
		if (arr[i] < arr[j]) {
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

void insertionSort(void)
{
	int temp;
	int i;
	int j;

	for (i = 1; i < N; i++)
	{
		temp = input[i];
		j = i - 1;

		while ((temp < input[j]) && (j >= 0))
		{
			input[j + 1] = input[j];
			j = j - 1;
		}
		input[j + 1] = temp;
	}
}
void quickSort(int first, int last)
{
	int pivot;
	int i;
	int j;
	int temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (input[i] <= input[pivot] && i < last)
			{
				i++;
			}
			while (input[j] > input[pivot])
			{
				j--;
			}
			if (i < j)
			{
				temp = input[i];
				input[i] = input[j];
				input[j] = temp;
			}
		}

		temp = input[pivot];
		input[pivot] = input[j];
		input[j] = temp;

		quickSort(first, j - 1);
		quickSort(j + 1, last);
	}
}

int main(int argc, char* argv[])
{	
	N = MAX_SIZE;

	for (int i = 0; i < N; i++) {
		in[i] = rand() % 20;
		input[i] = rand() % 20;
	}

	clock_t start, end;
	start = clock();
	heapInit();
	for (int i = 0; i < N; i++)
	{	
		heapPush(in[i]);
		//std::cout << "heap = " << heap[i] << std::endl;
	}
#if 0
	end = clock();
	std::cout << "heap push, elapsed time = " << end - start << std::endl;
	start = clock();
#endif
	for (int i = 0; i < N; i++)
	{
		heapPop(&out[i]);
		//std::cout << "out = " << out[i] << std::endl;
	}
	end = clock();
	std::cout << "heap pop, elapsed time = " << end - start << std::endl;

	start = clock();
	merge_sort(arr, 0, N-1);
	end = clock();
	std::cout << "merge_sort, elapsed time = " << end - start << std::endl;	

	return 0;
}