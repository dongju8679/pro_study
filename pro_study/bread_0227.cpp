#include <iostream>

#define MAX_IN (1<<20)
#define MAX_STR (20)
#define MAX_TABLE (1<<10)
#define MAX_BREAD (100)
#define MAX_NUM_ADDBREAD (40000)
#define MAX_SIZE (MAX_NUM_ADDBREAD)

int N;
typedef unsigned int u32;
int my_strlen(char* str);
int my_strcmp(const char* strA, const char* strB);
int my_strcpy(char* dst, const char* src);

char hash_table[MAX_BREAD][MAX_STR];
int decay[MAX_BREAD];

int heap[MAX_BREAD][MAX_NUM_ADDBREAD];
int heapSize[MAX_BREAD];

struct init_t {
	char bName[MAX_STR];
	int decay;
}init_data[MAX_IN];

struct bread_t {
	int tStamp;
	int mFresh;
	char bName[MAX_STR];
	int decayed;
}bread[MAX_NUM_ADDBREAD];
int cur_bread;
bread_t* alloc_bread() {
	return &bread[cur_bread];
}

void heapInit(void)
{
	for (int i = 0; i < N; i++) {
		heapSize[i] = 0;
	}	
}

int check_max(int idx, int i, int j) {
	int ret = 0;
	int ii = heap[idx][i];
	int jj = heap[idx][j];
	bread_t* bread_i = &bread[ii];
	bread_t* bread_j = &bread[jj];
	if (bread_i->mFresh > bread_j->mFresh) {
		ret = 1;
	}
	else if (bread_i->mFresh == bread_j->mFresh) {
		if (bread_i->tStamp > bread_j->tStamp) {
			ret = 1;
		}
	}
	return ret;
}

int heapPush(int idx, int value)
{
	if (heapSize[idx] + 1 > MAX_SIZE)
	{
		printf("queue is full!");
		return 0;
	}

	heap[idx][heapSize[idx]] = value;

	int current = heapSize[idx];
	//while (current > 0 && heap[current] < heap[(current - 1) / 2])
	while (current > 0 && check_max(idx, current, (current - 1) / 2) == 1)
	{
		int temp = heap[idx][(current - 1) / 2];
		heap[idx][(current - 1) / 2] = heap[idx][current];
		heap[idx][current] = temp;
		current = (current - 1) / 2;
	}

	heapSize[idx] = heapSize[idx] + 1;

	return 1;
}

int heapPop(int idx, int* value)
{
	if (heapSize[idx] <= 0)
	{
		return -1;
	}

	*value = heap[idx][0];
	heapSize[idx] = heapSize[idx] - 1;

	heap[idx][0] = heap[idx][heapSize[idx]];

	int current = 0;
	while (current * 2 + 1 < heapSize[idx])
	{
		int child;
		if (current * 2 + 2 == heapSize[idx])
		{
			child = current * 2 + 1;
		}
		else
		{
			//child = heap[current * 2 + 1] < heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
			if (check_max(idx, current * 2 + 1, current * 2 + 2) == 1) {
				child = current * 2 + 1;
			}
			else {
				child = current * 2 + 2;
			}			
		}

		//if (heap[current] < heap[child])
		if (check_max(idx, current, child) == 1)
		{
			break;
		}

		int temp = heap[idx][current];
		heap[idx][current] = heap[idx][child];
		heap[idx][child] = temp;

		current = child;
	}
	return 1;
}

unsigned long myhash(const char* str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_BREAD;
	}
	//std::cout << "myhash = " << hash << std::endl;
	return hash % N;
}

int gen_init() {
	int ret = 0;
	//printf("start input_gen\n");
	for (int i = 0; i < N; i++) {
		//std::cout << "check input_gen" << std::endl;
		//init_data[i].tStamp = 1 + (rand() % 10000);
		//init_data[i].mFresh = 91 + (rand() % 10);
		init_data[i].decay = 1 + (rand() % 20);
		for (int j = 0; j < 15; j++) {
			init_data[i].bName[j] = char(rand() % 26 + 97);
		}
		init_data[i].bName[14] = '\0';
		printf("bName(%s), decay(%d)\n", init_data[i].bName, init_data[i].decay);
	}
	return ret;
}

int get_hashidx(const char bName[]) {
	int ret = 0;
	u32 hash = myhash(bName);
	int idx = 0;
	int check_cnt1 = 0;
	std::cout << "addbread, hash = " << hash << std::endl;
	while (1) {
		if (my_strcmp(hash_table[hash], bName) == 0) {
			idx = hash;
			break;
		}
		check_cnt1++;
		hash = (hash + 7) % N;
	}
	ret = idx;
	return ret;
}

int addBread(int tStamp, int mFresh, const char bName[], int mCnt) {
	int ret = 0;
	printf("addbread, bName(%s)\n", bName);
	bread_t* new_bread = alloc_bread();
	new_bread->tStamp = tStamp;
	new_bread->mFresh = mFresh;
	my_strcpy(new_bread->bName, bName);
	int idx = get_hashidx(bName);	
	heapPush(idx, cur_bread);
	cur_bread++;
	return ret;
}

int init() {
	int ret = 0;
	std::cout << "start init" << std::endl;	
	cur_bread = 0;
	for (int i = 0; i < N; i++) {
		hash_table[i][0] = '\0';
	}
	int check_cnt = 0;
	for (int i = 0; i < N; i ++) {
		u32 hash0 = myhash(init_data[i].bName);
		//printf("hash0 = %u, N = %d\n", hash0, N);
		while (1) {
			if (hash_table[hash0][0] == '\0') {
				//printf("copy, hash0(%u)\n", hash0);
				my_strcpy(hash_table[hash0], init_data[i].bName);
				//printf("bName(%s), hash_table[hash0] = %s\n", init_data[i].bName, hash_table[hash0]);
				decay[hash0] = init_data[i].decay;
				break;
			}
			check_cnt++;
			//printf("1st hash0(%u)\n", hash0);
#if 0
			hash0 = (hash0 + 1);
			if (hash0 >= N) hash0 = hash0 - N;
#else
			hash0 = (hash0 + 7) % N;
#endif
			//printf("dongju, N = %d\n", N);
			//printf("2nd hash0(%u)\n", hash0);
		}		
	}
	printf("check_cnt(%d)\n", check_cnt);
#if 1
	for (int i = 0; i < N; i++) {
		printf("hash_table[i] = %s, decay[i] = %d\n", hash_table[i], decay[i]);		
	}
#endif
	return ret;
}

int init2() {
	int ret = 0;
	std::cout << "start init" << std::endl;
	for (int i = 0; i < N; i++) {
		hash_table[i][0] = '\0';
	}
	int check_cnt = 0;
	for (int i = 0; i < N; i++) {
		u32 hash0 = myhash(init_data[i].bName);
		//printf("hash0 = %u, N = %d\n", hash0, N);

		if (hash_table[hash0][0] == '\0') {
			//printf("copy, hash0(%u)\n", hash0);
			my_strcpy(hash_table[hash0], init_data[i].bName);
			//printf("bName(%s), hash_table[hash0] = %s\n", init_data[i].bName, hash_table[hash0]);
			decay[hash0] = init_data[i].decay;
		}
	}
	return ret;
}

int printHeap() {
	int ret = 0;

	for (int idx = 0; idx < N; idx++) {
		for (int i = 0; i < heapSize[idx]; i++) {
			printf("heap[%d][%d] = %d\n", idx, i, heap[idx][i]);
		}		
	}

	return ret;
}

int buyBread(int tStamp, const char bName[], int mCnt) {
	int ret = 0;

	return ret;
}

int buySector() {
	int ret = 0;

	return ret;
}

int main() {
	int ret = 0;	
	//clock_t start, end;
	std::cout << "start bread_0227" << std::endl;
	//srand((unsigned int)time(0));
	N = 10;	
	gen_init();
	//start = clock();
	init();
	//end = clock();
	//printf("init, elapsed time = %u\n", end - start);
	addBread(10, 91, init_data[0].bName, 3);	
	addBread(20, 99, init_data[1].bName, 1);
	addBread(30, 99, init_data[2].bName, 3);
	addBread(10, 98, init_data[0].bName, 3);
	for (int i = 0; i < N; i++) {
		printf("heapSize[%d] = %d\n", i, heapSize[i]);
	}
	printHeap();
#if 0
	int check11 = 0;
	heapPop(0, &check11);
	std::cout << "check11 = " << check11 << std::endl;
	printf("heapSize[0] = %d\n", heapSize[0]);
#endif

	ret = buyBread(730, init_data[0].bName, 3);
	std::cout << "ret, buyBread() = " << ret << std::endl;
	buySector();

	return ret;
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

