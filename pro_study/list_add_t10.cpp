#include <iostream>

#define MAX_LIST (1<<2)
#define MAX_STR (10)
#define MAX_DATA (1<<2)
#define MAX_IN (1<<10)



int N;
struct data_t {
	int idx;
	int val;
	char name[MAX_STR];
}data[MAX_DATA];

struct in_t {
	int idx;
	int val;
	char name[MAX_STR];
}in[MAX_IN];

struct list_head {
	list_head* prev;
	list_head* next;
}gen_head;

struct list_t {
	list_head list_entry;
	int data_idx;
}list[MAX_LIST];

void list_init(list_head* head) {
	head->prev = head;
	head->next = head;
}

void list_add(list_head* head, list_head* list) {
	list->prev = head;
	list->next = head->next;
	head->next->prev = list;
	head->next = list;
}

void list_add_tail(list_head* head, list_head* list) {
	list->next = head;
	list->prev = head->prev;
	head->prev->next = list;
	head->prev = list;
}

void list_del(list_head* list) {
	list->prev->next = list->next;
	list->next->prev = list->prev;
	list->prev = list;
	list->next = list;
}

void for_each_list_safe(list_head* head) {
	list_head* tmp;
	list_head* n;
	int cnt = 0;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {
		cnt++;
	}
}

list_head* find_pos(list_head* head, data_t* target) {
	list_head* ret = head;
	list_head* tmp;
	list_head* n;

	list_t* list_obj;

	data_t* obj;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {
		list_obj = (list_t*)tmp;
		int idx = list_obj->data_idx;
		data_t* dd = &data[idx];
		
		if (target->val > dd->val) {
			ret = tmp->prev;
			break;
		}
	}

	return ret;
}

int gen_input() {
	int ret = 0;

	for (int i = 0; i < N; i++) {
		in[i].idx = i;
		in[i].val = rand() % 30;
		for (int j = 0; j < MAX_STR; j++) {
			in[i].name[j] = char(rand() % 26 + 97);
		}
		in[i].name[MAX_STR - 1] = '\0';
	}

	return ret;
}

int main() {
	int ret = 0;
	std::cout << "start list_add_t10" << std::endl;
	N = 10;
	gen_input();

	return ret;
}