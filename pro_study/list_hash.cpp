#include <iostream>

#define MAX_N 10
#define MAX_STRING 100
#define MAX_DATA 100

class data {
	public:
		data *prev;
		data *next;
		int idx;
		int val;
		char name[MAX_STRING];
	private:
};
data dd[MAX_DATA];

data head[MAX_N];
data *phead[MAX_N];

int N;

int main(int argc, char *argv[]) {
	int ret = 0;
	std::cout << "start list_hash2" << std::endl;
	N = MAX_N;
	init();
	return ret;
}

int init(void) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		phead[i] = &head[i];
	}
	return ret;
}

int print_head(int idx) {
	int ret = 0;
	data *tmp = 0;
	data *fhead = phead[idx];
	for (tmp = fhead->next; tmp != fhead; tmp = tmp->next) {
		std::cout << "" << tmp->val << std::endl;
	}
	return ret;
}

int add_item(int val, char *str) {
	int ret = 0;


	return ret;
}

void list_add(data *head, data *list) {
	list->next = head->next;
	list->prev = head;
	head->next->prev = list;
	head->next = list;
}

void list_del(data *list) {
	list->next->prev = list->prev;
	list->prev->next = list->next;
	list->next = list;
	list->prev = list;
}

int my_strcpy(char *dst, char *src) {
	int ret = 0;


	return ret;
}

int my_strcmp(char *str1, char *str2) {

}

int my_strlen(char *str) {
	int ret = 0;
	int i = 0;

	while (1) {
		if (str[i] == '\0') {
			break;
		}
		str++;
		i++;
	}
	ret = i;
	return ret;
}
