#include <iostream>
#define MAX_IN (1<<2)
#define MAX_STR (4)
#define MAX_HASH (1<<4)
#define MAX_LIST (1<<4)

int N;

struct in_t {
	int idx;
	int val;
	char name[MAX_STR];
}in[MAX_IN];

struct list_t {

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


int main() {
	int ret = 0;
	std::cout << "start hash_tt01" << std::endl;
	N = MAX_IN;
	char A = '10';
	char B = 'a';
	std::cout << "A = " << A << std::endl;
	std::cout << "B = " << B << std::endl;
	std::cout << "int(B) = " << int(B) << std::endl;

#if 0
	for (int i = 0; i < 10; i++) {
		std::cout << "test val = " << char(rand() % 26 + 97) << std::endl;
	}
#endif

	gen_input();

	

	return ret;
}