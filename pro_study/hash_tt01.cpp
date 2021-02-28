#include <iostream>
#define MAX_IN (1<<2)
#define MAX_STR (4)
#define MAX_HASH (1<<4)
#define MAX_LIST (1<<4)
#define MAX_TABLE (MAX_IN)

int N;
typedef unsigned int u32;

struct in_t {
	int idx;
	int val;
	char name[MAX_STR];
}in[MAX_IN];

struct list_t {
	int idx;
	int val;
	char name[MAX_STR];
	u32 hash;
}list[MAX_LIST];



struct list_head {
	list_head* prev;
	list_head* next;
}hash_head[MAX_HASH];

void list_init(list_head* head) {
	head->prev = head;
	head->next = head;
}

int gen_input() {
	int ret = 0;

	for (int i = 0; i < N; i++) {
		in[i].idx = i;
		in[i].val = rand() % 30;
		for (int j = 0; j < 3; j++) {
			in[i].name[j] = char(rand() % 26 + 97);
		}
		std::cout << "in[i].name = " << in[i].name << std::endl;
	}

	return ret;
}

unsigned long myhash(const char* str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

int main() {
	int ret = 0;
	std::cout << "start hash_tt01" << std::endl;
	N = MAX_IN;	
	char B = 'a';	
	std::cout << "B = " << B << std::endl;
	std::cout << "int(B) = " << int(B) << std::endl;

#if 0
	for (int i = 0; i < 10; i++) {
		std::cout << "test val = " << char(rand() % 26 + 97) << std::endl;
	}
#endif

	gen_input();	

	for (int i = 0; i < MAX_IN; i++) {
		

	}

	return ret;
}