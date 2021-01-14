#include <iostream>

#define MAX_NAME_LEN (7)
#define MAX_NUMTYPE (5)
#define MAX_TYPE_LEN (4)
#define MAX_SECTION (100)
#define MAX_NAME (50000)
#define MAX_TYPE (500)
#define MAX_BOOK (50000)
#define MOD_NAME (MAX_NAME - 1)
#define MOD_TYPE (MAX_TYPE - 1)
int my_strcpy(char* dst, char* src);
int my_strlen(char* str);
int my_strcmp(char* str1, char* str2);

int N;
struct book_t {
	char mName[MAX_NAME_LEN];
	int mNumType;
	char mTypes[MAX_NUMTYPE][MAX_TYPE_LEN];
	int mSection;
}book[MAX_BOOK];
int book_cur;
book_t* book_alloc() {
	return &book[book_cur++];
}

struct list_head {
	list_head* prev;
	list_head* next;
}section_head[MAX_SECTION], name_head[MAX_NAME], type_head[MAX_TYPE];

struct list_t {
	list_head list_entry;
	unsigned int nhash;
	unsigned int thash;
	book_t* pb;
}section[MAX_BOOK], name[MAX_NAME], type[MAX_TYPE * 5];
int section_cur, name_cur, type_cur;
list_t* section_alloc() {
	return &section[section_cur++];
}
list_t* name_alloc() {
	return &name[name_cur++];
}
list_t* type_alloc() {
	return &type[type_cur++];
}

unsigned int name_hash(const char* str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
	{
		hash = ((((hash << 5) + hash) + c) + MOD_NAME) & MOD_NAME;
	}
	return hash;
}

unsigned int type_hash(const char* str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
	{
		hash = ((((hash << 5) + hash) + c) + MOD_TYPE) & MOD_TYPE;
	}
	return hash;
}

void list_init(list_head* head) {
	head->next = head;
	head->prev = head;
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
	int N = nsection;
	section_cur = 0;
	name_cur = 0;
	type_cur = 0;
	for (int i = 0; i < nsection; i++) {
		list_init(&section_head[i]);
	}
	for (int i = 0; i < MAX_NAME; i++) {
		list_init(&name_head[i]);
	}
	for (int i = 0; i < MAX_TYPE; i++) {
		list_init(&type_head[i]);
	}
}
int add_book(char* mName, int mNumType, char Types[MAX_NUMTYPE][MAX_TYPE_LEN], int mSection) {
	int ret = 0;

	std::cout << "add_book, mName = " << mName << std::endl;	

	return ret;
}

int main() {
	int ret = 0;
	int N_Section = 3;
	init_data(N_Section);
	char tName[MAX_NAME_LEN] = "wiedki";
	char tTypes[MAX_NUMTYPE][MAX_TYPE_LEN] = { "ro", "hi" };
	add_book(tName, 2, tTypes, 1);

	std::cout << "start book_section_type_name1" << std::endl;

	return ret;
}

int my_strcpy(char* dst, char* src) {
	int ret = 0;
	int i = 0;
	while (1) {
		if (src[i] == '\0') {
			break;
		}
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	ret = i;
	return ret;
}

int my_strcmp(char* str1, char* str2) {
	int ret = 0;
	int i = 0;
	while (1) {
		if (str1[i] == '\0' || str2[i] == '\0') {
			break;
		}
		if (str1[i] != str2[i]) {
			ret = str1[i] - str2[i];
			break;

		}
		else if (str1[i] == str2[i]) {
			ret = 0;
		}
		i++;
	}
	return ret;
}

int my_strlen(char* str) {
	int ret = 0;
	int i = 0;
	while (1) {
		if (str[i] == '\0') {
			break;
		}
		i++;
	}
	ret = i;
	return ret;
}