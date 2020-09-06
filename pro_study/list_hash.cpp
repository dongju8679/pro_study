#include <iostream>
#include <time.h>

#define MAX_STRING 100
#define MAX_N 100
#define MAX_NUM_HASH 10

#define ADD_NO_ORDER

enum class order_t {
	ascending = 0,
	descending = 1,
	no_order = 2,
	max_type = 3
};

class dat {
	public:
		dat* prev;
		dat* next;
		int idx;
		int valid;
		int val;
		char name[MAX_STRING];
	private:
};
dat dd[MAX_N];
int cur;
dat head[MAX_NUM_HASH];
dat* phead[MAX_NUM_HASH];

char input_name[MAX_N][MAX_STRING] = {
	"james", "jordan" , "penny", "aaron", "mike",
	"aime", "kenva" , "jona", "ace", "piss",
	"funy", "samdi" , "jinny", "handk", "choo",
	"kevin", "brad" , "zombid", "amici", "ryu",
	"midkck", "peter" , "jidan", "camero", "mike"
};

class in_t {
	public:
		int val;
		char name[MAX_STRING];
	private:
};

in_t input[MAX_N];

int N;

// functions decalaration
int init(void);
int gen_input(void);
dat* my_alloc(void);
int my_strcpy(char* dst, char* src);
int my_strcmp(char* str1, char* str2);
int my_strlen(char* str);
int print_input(void);
int add_all_item();
#ifdef ADD_NO_ORDER
int add_item(int val, char* str);
#else
int add_item_with_order(order_t ot, int val, char* name);
#endif
int del_item_val(int val);
int del_item_name(char* str);

void list_add(dat* head, dat* list);
void list_del(dat* list);
unsigned long myhash(const char* str);
int print_all_head();
int print_head(int idx);

int main(int argc, char* argv[]) {
	int ret = 0;
	std::cout << "dongju_a01, start list_hash2" << std::endl;
	N = 25;
	init();
	gen_input();
	print_input();
	add_all_item();
	add_item(30, "peterson");

	return ret;
}

int print_input(void) {
	int ret = 0;
	std::cout << "print_input start" << std::endl;
	for (int i = 0; i < N; i++) {
		std::cout << "i = " << i << ", val = " << input[i].val <<
			", name = " << input[i].name << std::endl;
	}
	return ret;
}

int gen_input(void) {
	int ret = 0;
	std::cout << "start gen_input" << std::endl;
	for (int i = 0; i < MAX_N; i++) {
		input[i].val = rand() % 10;
		my_strcpy(input[i].name, input_name[i]);
	}
	return ret;
}

int init(void) {
	int ret = 0;
	for (int i = 0; i < MAX_NUM_HASH; i++) {
		phead[i] = &head[i];
		phead[i] = &head[i];
		phead[i]->prev = phead[i];
		phead[i]->next = phead[i];
	}
	for (int i = 0; i < MAX_N; i++) {
		dd[i].next = &dd[i];
		dd[i].prev = &dd[i];
	}
	cur = 0;

	return ret;
}

dat* my_alloc(void) {
	dat* ret = 0;
	ret = &dd[cur];
	std::cout << "current alloc index = " << cur << std::endl;
	cur++;
	std::cout << "alloc count = " << cur << std::endl;
	return ret;
}

int print_all_head() {
	int ret = 0;
	std::cout << "print_all_head" << std::endl;
	for (int i = 0; i < MAX_NUM_HASH; i++) {
		dat* tmp = 0;
		dat* thead = phead[i];
		for (tmp = thead->next; tmp != thead; tmp = tmp->next) {
			std::cout << "hash num = " << i << ", tmp->val = " << tmp->val << ", tmp->name = " << tmp->name << std::endl;
		}
	}
	return ret;
}

int print_head(int idx) {
	std::cout << "print_head start" << std::endl;
	int ret = 0;
	dat* tmp = 0;
	dat* thead = phead[idx];
	for (tmp = thead->next; tmp != thead; tmp = tmp->next) {
		std::cout << "idx = " << idx << ", val = " << tmp->val << std::endl;
	}
	return ret;
}

int add_all_item(void) {
	std::cout << "start add_all_item()" << std::endl;
	int ret = 0;
	for (int i = 0; i < N; i++) {
#ifdef ADD_NO_ORDER
		std::cout << "ADD_NO_ORDER, add item, input idx = " << i << std::endl;
		add_item(input[i].val, input[i].name);
#else
		add_item_with_order(order_t::descending, input[i].val, input[i].name);
#endif
	}
	print_all_head();
	return ret;
}

#ifdef ADD_NO_ORDER
int add_item(int val, char* str) {
	std::cout << "add_item, val = " << val << ", str = " << str << std::endl;
	int ret = 0;
	int hash_idx = 0;
	dat* thead = 0;
	hash_idx = myhash(str);
	std::cout << "str = " << str << ", hash_idx = " << hash_idx << std::endl;
	thead = phead[hash_idx];

	dat* new_data = my_alloc();
	new_data->val = val;
	my_strcpy(new_data->name, str);
	new_data->valid = 1;

	list_add(thead, new_data);
	return ret;
}
#else
int add_item_with_order(order_t ot, int val, char* name) {
	int ret = 0;
	//std::cout << "add_item_with_order start" << std::endl;

	dat* new_d = 0;
	new_d = &in[cur];
	//std::cout << "cur = " << cur << std::endl;
	cur = cur + 1;
	new_d->val = val;
	//std::cout << "val = " << val << ", name = " << name << std::endl;
	my_strcpy(new_d->name, name);
	new_d->valid = 1;

	dat* pos;
	//std::cout << "dir = "  << static_cast<int>(dir) << ", val = " << val << std::endl;
	pos = find_position(dir, val);
	list_add(pos, new_d);
#if 0
	print_list();
#endif
}
#endif

dat* find_location_by_val(int val) {
	dat *ret = 0;
	std::cout << "find_location_by_val start" << std::endl;
	for (int i = 0; i < MAX_NUM_HASH; i++) {
		dat *tmp = 0;
		dat *thead = phead[i];
		for (tmp = thead->next; tmp != thead; tmp->next) {
			if (val == tmp->val) {
				ret = tmp;
				std::cout << "found location by val = " << tmp->val << ", idx = " << i << std::endl;
			}
		}
	}
	return ret;
}

int del_item_val(int val) {
	int ret = 0;

	dat* del_list = find_location_by_val(val);

	list_del(del_list);
	del_list->valid = 0;

	return ret;
}

int del_item_name(char* str) {
	int ret = 0;

	return ret;
}

void list_add(dat* head, dat* list) {
	list->next = head->next;
	list->prev = head;
	head->next->prev = list;
	head->next = list;
}

void list_del(dat* list) {
	list->next->prev = list->prev;
	list->prev->next = list->next;
	list->next = list;
	list->prev = list;
}

#if 1 // calculate hash
unsigned long myhash(const char* str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++) {
		hash = (((hash << 5) + hash) + c) % MAX_NUM_HASH;
	}
	return hash % MAX_NUM_HASH;
}
#endif

#if 1
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
#if 0
		if (str1[i] > str2[i]) {
			ret = 1;
			break;
		}
		else if (str1[i] < str2[i]) {
			ret = -1;
			break;
		}
#else
		if (str1[i] != str2[i]) {
			ret = str1[i] - str2[i];
			break;
#endif
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
#endif
