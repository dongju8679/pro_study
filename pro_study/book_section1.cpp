#include <iostream>

#define MAX_NAME_LEN (7)
#define MAX_NUMTYPE (5)
#define MAX_TYPE_LEN (4)
#define MAX_SECTION (100)
#define MAX_NAME (50000)
#define MAX_TYPE (500)
#define MAX_BOOK (50000)

struct book_t {
	char mName[MAX_NAME_LEN];
	int mNumType;
	char mTypes[MAX_NUMTYPE][MAX_TYPE_LEN];
	int mSection;
}book[MAX_BOOK];

struct list_head {
	list_head* prev;
	list_head* next;
}section_head[MAX_SECTION], name_head[MAX_NAME], type_head[MAX_TYPE];

struct section_t {
	list_head section_list;
	book_t* pb;
}section[MAX_BOOK];

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
	list->next = list;
	list->prev = list;
}

void for_each_list_safe(list_head* head) {
	list_head* tmp = 0;
	list_head* n = 0;
	int cnt = 0;
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {
		cnt++;
	}
}

void init_data(int nsection) {
	for (int i = 0; i < nsection; i++) {


	}
}

int main() {
	int ret = 0;
	int N_Section = 3;
	init_data(N_Section);

	std::cout << "start book_section_type_name1" << std::endl;

	return ret;
}