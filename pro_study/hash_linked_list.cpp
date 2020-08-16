#include <iostream>
#define MAX_STRING 100
#define MAX_N 10
#define MAX_HEAD 10

class dat {
public:
	dat* prev;
	dat* next;
	int idx;
	int val;
	char name[MAX_STRING];
private:
};

dat in[MAX_N];
dat head[MAX_HEAD];
dat* phead[MAX_HEAD];

int main(int argc, char *argv[]) {
	int ret = 0;

	std::cout << "start main" << std::endl;

	for (int i = 0; i < MAX_HEAD; i++) {
		phead[i] = &head[i];
		phead[i]->prev = &head[i];
		phead[i]->next = &head[i];
	}

	return ret;
}

int find_head(int idx) {
	int ret = 0;

	return ret;
}

int add_item(int idx, int val, char *str) {
	int pos_head = find_head(idx);
	dat* tmp_phead = phead[pos_head];
	dat* new_data = my_alloc_data(); // cur++
	list_add(tmp_phead, new_data);

}


