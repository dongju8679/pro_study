#include <iostream>

#define MAX_SIZE (1<<20)
#define MAX_STR 10

int N;
struct arr_t {
	int idx;
	int val;
	char name[MAX_STR];
}in[MAX_SIZE], a[MAX_SIZE];
int cur_a;
arr_t* alloc_a() {
	return &a[cur_a++];
}

arr_t heap[MAX_SIZE];
int heapSize = 0;

void heapInit(void)
{
	heapSize = 0;
}

int check_heap_right_large(int a, int b) {
	int ret = 0;
	if (heap[a].val < heap[b].val) {
		ret = 1;
	}
	else if (heap[a].val == heap[b].val) {
		if (heap[a].idx > heap[b].idx) {
			ret = 1;
		}
	}
	return ret;
}

int heapPush(arr_t value)
{
	if (heapSize + 1 > MAX_SIZE)
	{
		printf("queue is full!");
		return 0;
	}
	heap[heapSize] = value;
	int current = heapSize;
	//while (current > 0 && heap[current] < heap[(current - 1) / 2])
	while (current > 0 && (check_heap_right_large(current, (current - 1) / 2) == 1))
	{
		arr_t temp = heap[(current - 1) / 2];
		heap[(current - 1) / 2] = heap[current];
		heap[current] = temp;
		current = (current - 1) / 2;
	}
	heapSize = heapSize + 1;
	return 1;
}

int heapPop(arr_t* value)
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
			//child = heap[current * 2 + 1] < heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
			child = check_heap_right_large(current * 2 + 1, current * 2 + 2) ? current * 2 + 1 : current * 2 + 2;
		}
		//if (heap[current] < heap[child])
		if (check_heap_right_large(current, child))
		{
			break;
		}
		arr_t temp = heap[current];
		heap[current] = heap[child];
		heap[child] = temp;
		current = child;
	}
	return 1;
}

int gen_input() {
	int ret = 0;
	std::cout << "gen_input()" << std::endl;
	for (int i = 0; i < N; i++) {
		in[i].idx = i;
		in[i].val = rand() % 30;
		//std::cout << "in.val = " << in[i].val << std::endl;
	}
	return ret;
}

int main(int argc, char* argv[])
{
	N = MAX_SIZE;
	heapInit();
	gen_input();
	clock_t start, end;
	start = clock();
	for (int i = 0; i < N; i++)
	{	
		heapPush(in[i]);
		//std::cout << "push, in[i].idx = " << in[i].idx << ", val = " << in[i].val << std::endl;
	}
	for (int i = 0; i < N; i++)
	{
		int value;
		heapPop(&in[i]);
		//std::cout << "pop, in[i].idx = " << in[i].idx << ", val = " << in[i].val << std::endl;
	}
	end = clock();
	std::cout << "after heap(), elapsed time = " << end - start << std::endl;
	return 0;
}