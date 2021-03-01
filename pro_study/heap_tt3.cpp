#include <iostream>
#define MAX_SIZE (100)
#define MAX_STR (20)
#define MAX_IN (1<<10)

int N;
int heap[MAX_SIZE];
int heapSize = 0;

struct in_t {
	int idx;
	int val;
	char name[MAX_STR];
}in[MAX_IN];

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

int gen_input() {
	int ret = 0;

	for (int i = 0; i < N; i++) {
		in[i].idx = i;
		in[i].val = rand() % 30;
		std::cout << "in[i].val = " << in[i].val << std::endl;
	}

	return ret;
}

int main(int argc, char* argv[])
{
	N = 10;
	gen_input();

	heapInit();

	for (int i = 0; i < N; i++) {
		heapPush(in[i].val);
	}

	for (int i = 0; i < N; i++)
	{
		int value;
		heapPop(&value);
		printf("%d ", value);
	}

	return 0;
}


