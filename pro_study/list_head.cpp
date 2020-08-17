#include <iostream>
#define MAX_N 10
#define MAX_STRING 100

char name_list[MAX_N][MAX_STRING] = {
	"mike", "james", "kokori", "sasaki", "choo"
	,"jim", "john", "stockton", "simmons", "barry"
	//,"kim", "shfsdk", "sano", "miguel", "chiari"
};

class dat {
public:
	dat* prev;
	dat* next;
	int idx;
	int val;
	char name[MAX_STRING];
	int valid;
private:
};

enum class order_t {
	ascending = 0,
	descending = 1,
	max_type = 2
};

int N;
dat head;
dat* phead;
dat in[10];
int cur;

int add_item(int val, char* name);
int add_all_item();
int set_input();
int remove_name(char* str);
int remove_val(int val);
int my_strcmp(char* strA, char* strB);
int my_strcpy(char* dst, char* src);
int my_strlen(char* str);
void list_add(dat* list, dat* new_data);
void list_del(dat* del_data);
int print_input();
int print_list();
int add_item_with_order(order_t ot, int val, char* name);
dat* find_position(order_t dir, int val);

int main() {
	int ret = 0;
	N = MAX_N;

	cur = 0;
	phead = &head;
	phead->prev = &head;
	phead->next = &head;

	set_input();

	print_input();
	add_all_item();
	print_list();

	//add_item(100, "tigris");
	//remove_name("james");

	return ret;
}

int add_all_item() {
	int ret = 0;
	std::cout << std::endl;
	std::cout << "start add_all_item()" << std::endl;

	for (int i = 0; i < N; i++) {
		//add_item(in[i].val, in[i].name);
		//add_item_with_order(order_t::ascending, in[i].val, in[i].name);
		add_item_with_order(order_t::descending, in[i].val, in[i].name);
	}

	return ret;
}


int set_input() {
	int ret = 0;

	for (int i = 0; i < N; i++) {
		in[i].idx = i;
		in[i].val = rand() % 100;
		my_strcpy(&in[i].name[0], &name_list[i][0]);
	}

	return ret;
}

int print_input() {
	int ret = 0;

	for (int i = 0; i < N; i++) {
		std::cout << "idx = " << in[i].idx << ", val = " << in[i].val << ", name = " << in[i].name << std::endl;
	}

	return ret;
}

int print_list() {
	int ret = 0;
	std::cout << std::endl;
	std::cout << "start print_list" << std::endl;
	dat* tmp;
	for (tmp = phead->next; tmp != phead; tmp = tmp->next) {
		ret++;
		std::cout << "idx = " << tmp->idx << ", val = " << tmp->val << ", name = " << tmp->name << std::endl;
		std::cout << "cnt = " << ret << std::endl;
	}
	std::cout << std::endl;
	return ret;
}

int add_item(int val, char *name) {
	int ret = 0;
	dat* new_d = 0;
	new_d = &in[cur];
	std::cout << "cur = " << cur << std::endl;
	cur = cur + 1;
	new_d->val = val;
	std::cout << "val = " << val << ", name = " << name << std::endl;
	my_strcpy(new_d->name, name);
	new_d->valid = 1;
	list_add(phead, new_d);
	return ret;
}

dat* find_position(order_t dir, int val) {
	dat* ret = phead;
	dat* tmp;
	int cnt = 0;
	for (tmp = phead->next; tmp != phead; tmp = tmp->next) {
		cnt++;
		if (dir == order_t::ascending) {
			//std::cout << "tmp->val = " << tmp->val << ", val = " << val << std::endl;
			if (tmp->val >= val) {
				ret = tmp->prev;
				break;
				//std::cout << "tmp->val = " << tmp->val << ", val = " << val << std::endl;
			}
		} else {
			if (tmp->val <= val) {
				ret = tmp->prev;
				break;
			}
		}
	}
	if (cnt == 0) {
		ret = phead;
		std::cout << "this should be called first" << std::endl;
	}
	else {
		if (tmp == phead) {
			ret = phead->prev;
			std::cout << "not found, just add tail" << std::endl;
		}
	}
	return ret;
}

int add_item_with_order(order_t dir, int val, char *name) {
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

	return ret;
}

dat* find_target_name(char *str) {
	dat* ret = 0;
	dat* tmp = 0;

	for (tmp = phead->next; tmp != phead; tmp = tmp->next;) {
		if (my_strcmp(tmp->name, str) == 0) {

		}
	}

	return ret;
}

dat* find_target_val(int name) {
	dat* ret = 0;

	return ret;
}

int remove_name(char *str) {
	int ret = 0;

	dat* target;
	target = find_target_name(str);

	list_del(target);

	return ret;
}

int remove_val(int val) {
	int ret = 0;
	dat* target = 0;
	target = find_target_val(val);

	list_del(target);

	return ret;
}

void list_add(dat *list, dat *new_data) {
	new_data->next = list->next;
	new_data->prev = list;
	list->next->prev = new_data;
	list->next = new_data;
}

void list_del(dat *del_data) {
	del_data->next->prev = del_data->prev;
	del_data->prev->next = del_data->next;
	del_data->next = del_data;
	del_data->prev = del_data;
}

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

int my_strcpy(char* dst, char* src) {
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

int my_strcmp(char* strA, char* strB) {
	int ret = 0;
	while (1) {
		if (*strA == '\0' || *strB == '\0') {
			break;
		}
		if (*strA == *strB) {
			ret = 0;
		}
		else if (*strA > * strB) {
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

#if 1
dat tmp[MAX_N];
dat A[MAX_N];
int check_condition(dat A[], int i, int j) {
	int ret = 0;
	if (A[i].val < A[j].val) {
		ret = 1;
	}
	else if (A[i].val == A[j].val) {
		if (A[i].idx < A[j].idx) {
			ret = 1;
		}
	}
	else {
		ret = 0;
	}
	return ret;
}

void msort(dat A[], int start, int end) {
	if (start >= end) {
		return;
	}
	int middle = (start + end) / 2;
	int i, j, k;
	i = start;
	j = middle + 1;
	k = i;
	msort(A, start, middle);
	msort(A, middle + 1, end);

	while (i <= middle && j <= end) {
		if (check_condition(A, i, j) == 1) {
			tmp[k++] = A[i++];
		}
		else {
			tmp[k++] = A[j++];
		}
	}
	while (i <= middle) {
		tmp[k++] = A[i++];
	}
	while (j <= end) {
		tmp[k++] = A[j++];
	}

	for (k = start; k <= end; k++) {
		A[k] = tmp[k];
	}
} 
#endif