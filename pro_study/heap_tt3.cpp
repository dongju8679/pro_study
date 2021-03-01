#include <iostream>
#define MAX_SIZE (100)
#define MAX_STR (20)
#define MAX_IN (1<<10)
#define MAX_DATA (100)
#define MAX_LIST (100)

int my_strlen(char* str);
int my_strcmp(const char* strA, const char* strB);
int my_strcpy(char* dst, const char* src);

int N;
int heap[MAX_SIZE];
int heapSize = 0;
int gCnt;

int cur_maxheap;
int tempHeap[MAX_SIZE];

struct in_t {
	int idx;
	int val;
	char name[MAX_STR];
}in[MAX_IN];

struct arr_t {
	int idx;
	int val;
	char name[MAX_STR];
}arr[MAX_DATA];
int cur_arr;

arr_t* alloc_arr() {
	return &arr[cur_arr++];
}

struct list_t {
	int idx;
	int val;
	char name[MAX_STR];
}list[MAX_LIST];

int gen_input() {
	int ret = 0;
	printf("start gen_input\n");
	for (int i = 0; i < N; i++) {
		in[i].idx = i;
		in[i].val = rand() % 30;
		for (int j = 0; j < MAX_STR; j++) {
			in[i].name[j] = char(rand() % 26 + 97);
		}
		in[i].name[MAX_STR-1] = '\0';
		std::cout << "in[i].val = " << in[i].val << std::endl;
	}
	std::cout << "end gen_input\n" << std::endl;

	return ret;
}

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

int printHeap() {
	int ret = 0;
	std::cout << "printHeap, cur_arr = " << cur_arr << std::endl;
	for (int i = 0; i < cur_arr; i++) {
		printf("heap[%d] = %d\n", i, heap[i]);
	}
	return ret;
}

int add_arr(int cnt) {
	int ret = 0;
	arr_t* arr = alloc_arr();
	arr->idx = in[cnt].idx;
	arr->val = in[cnt].val;
	my_strcpy(arr->name, in[cnt].name);
	printf("add_arr, cur_arr(%d)\n", cur_arr);
	return ret;
}

int main(int argc, char* argv[])
{
	N = 10;
	gCnt = 0;
	cur_maxheap = 0;
	cur_arr = 0;
	gen_input();
	heapInit();
	
	//add_arr(gCnt);
	//gCnt++;
	for (int i = 0; i < 10; i++) {
		add_arr(i);
	}	
	
	std::cout << "before heap_push, check cur_arr = " << cur_arr << std::endl;
	printf("before push heapSize = %d\n", heapSize);
	for (int i = 0; i < cur_arr; i++) {
		heapPush(arr[i].val);
		printf("push val(%d), heapSize(%d)\n", arr[i].val, heapSize);
		cur_maxheap++;
	}
	printHeap();
	printf("before tempheap, pop heapSize = %d, cur_maxheap = %d, N(%d)\n", heapSize, cur_maxheap, N);
#if 0
	for (int i = 0; i < cur_maxheap; i++) {
		heapPop(&tempHeap[i]);
		printf("tempHeap[%d] = %d, heapSize(%d)\n", i, tempHeap[i], heapSize);
	}
	printf("after heapSize = %d\n", heapSize);
	printHeap();
#endif
	
#if 1
	printf("before pop heapSize = %d\n", heapSize);
	for (int i = 0; i < N; i++)
	{
		int value;
		heapPop(&value);
		printf("pop val(%d), heapSize(%d)\n", value, heapSize);		
	}
#endif
	return 0;
}

#if 1
int my_strlen(char* str) {
	int ret = 0;
	char* ptr = str;
	//std::cout << "ptr + 1 = " << ptr + 1<< std::endl;
	while (*ptr != '\0') {
		//printf("before ret = %d, *ptr = %c\n", ret, *ptr);
		ret = ret + 1;
		//printf("after ret = %d, *ptr = %c\n", ret);
		ptr++;
	}
	return ret;
}

int my_strcpy(char* dst, const char* src) {
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

int my_strcmp(const char* strA, const char* strB) {
	int ret = 0;
	while (1) {
		if (*strA == '\0' || *strB == '\0') {
			break;
		}
		if (*strA == *strB) {
			ret = 0;
		}
		else if (*strA > *strB) {
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
#endif
