#include <iostream>
//#include <time.h>

#define MAX_HASH 10
#define MAX_STRING 100
#define MAX_N 100

class dat {
	public:
		dat *prev;
		dat *next;
		int idx;
		int val;
		char name[MAX_STRING];
	private:
};
dat dd[MAX_N];
int cur;
dat head[MAX_HASH];
dat *phead[MAX_HASH];

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
dat *my_alloc(void);
int my_strcpy(char *dst, char *src);
int my_strcmp(char *str1, char *str2);
int my_strlen(char *str);
int print_input(void);

int main(int argc, char *argv[]) {
	int ret = 0;
	std::cout << "start list_hash2" << std::endl;
	N = 25;
	init();
	gen_input();

	print_input();

	return ret;
}

int print_input(void) {
	int ret = 0;

	for (int i = 0; i < N; i++) {
		std::cout << "i = " << i  << ", val = " << input[i].val << ", name = " << input[i].name << std::endl;
	}

	return ret;
}

int gen_input(void) {
	int ret = 0;

	for (int i = 0; i < MAX_N; i++) {
		input[i].val = rand() % 10;
		my_strcpy(input[i].name, input_name[i]);
	}

	return ret;
}

int init(void) {
	int ret = 0;
	for (int i = 0; i < MAX_HASH; i++) {
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

dat *my_alloc(void) {
	dat *ret = 0;
	ret = &dd[cur];
	std::cout << "current alloc index = " << cur << std::endl;
	cur++;
	std::cout << "alloc count = " << cur << std::endl;
	return ret;
}


int print_head(int idx) {
	int ret = 0;
	dat *tmp = 0;
	dat *fhead = phead[idx];
	for (tmp = fhead->next; tmp != fhead; tmp = tmp->next) {
		std::cout << "" << tmp->val << std::endl;
	}
	return ret;
}

int add_item(int val, char *str) {
	int ret = 0;


	return ret;
}

void list_add(dat *head, dat *list) {
	list->next = head->next;
	list->prev = head;
	head->next->prev = list;
	head->next = list;
}

void list_del(dat *list) {
	list->next->prev = list->prev;
	list->prev->next = list->next;
	list->next = list;
	list->prev = list;
}

#if 1
int my_strcpy(char *dst, char *src) {
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

int my_strcmp(char *str1, char *str2) {
	int ret = 0;
	int i = 0;

	while (1) {
		if (str1[i] == '\0' || str2[i] == '\0')  {
			break;
		}
#if 0
		if (str1[i] > str2[i]) {
			ret = 1;
			break;
		} else if (str1[i] < str2[i]) {
			ret = -1;
			break;
		}
#else
		if (str1[i] != str2[i]) {
			ret = str1[i] - str2[i];
			break;
#endif
		} else if (str1[i] == str2[i]) {
			ret = 0;
		}
		i++;
	}
	return ret;
}

int my_strlen(char *str) {
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
