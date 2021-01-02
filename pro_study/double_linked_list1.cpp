#include <iostream>

#define MAX_NUM 100
#define MAX_STR_LEN 10
#define TEST_IN 10

int my_strlen(char* str);
int my_strcpy(char* dst, char* src);
int my_strcmp(char* strA, char* strB);

struct input_test {
    int data;
    char name[MAX_STR_LEN];
};
input_test in[TEST_IN];

struct list_head {
	list_head* prev;
	list_head* next;
};

struct my_data {
    list_head gen_list;
    list_head play_list;
	int idx;
	int data;
	char name[MAX_STR_LEN];	
};

list_head gen_head;
list_head play_head;

const int offset_list[2] = { 0, sizeof(gen_head) };

my_data data[MAX_NUM];
int data_cur = 0;

my_data* my_data_alloc() {
    my_data* ret = 0;
    ret = &data[data_cur++];    
    return ret;
}

void list_init(list_head* head) {
    head->next = head;
    head->prev = head;
}

void list_add(list_head* head, list_head* data) {
	data->prev = head;
	data->next = head->next;
	head->next->prev = data;
	head->next = data;
}

void list_del(list_head* data) {
    data->next->prev = data->prev;
    data->prev->next = data->next;
    data->next = data;
    data->prev = data;
}

int remove_list(int del_data);

int gen_input() {
    int ret = 0;
    srand((unsigned int)time(NULL));

    for (int j = 0; j < TEST_IN; j++) {
        int a = rand() % 10;
        char name[10];
        for (int i = 0; i < 9; i++) {
            name[i] = static_cast<char>(97 + rand() % 26);
        }
        name[9] = '\0';
        in[j].data = a;
		my_strcpy(in[j].name, name);
        //std::cout << "data = " << a <<  ", name = " << name << std::endl;
    }   

    return ret;
}

int add_input(int data, char* name) {
	int ret = 0;
	int* ptr = 0;
	my_data* item = my_data_alloc();
	item->data = data;
	my_strcpy(item->name, name);
	list_add(&gen_head, &(item->gen_list));
	//std::cout << "&(item->gen_list) = " << &(item->gen_list) << std::endl;
	//std::cout << "&(item->data) = " << &(item->data) << std::endl;
	return ret;
}

int for_each_list(list_head* head, int list_idx) {
	int ret = 0;
	list_head* tmp = 0;
	for (tmp = head->next; tmp != head; tmp = tmp->next) {
		my_data* mdata = 0;
		mdata = reinterpret_cast<my_data*>(tmp - offset_list[list_idx]);
		std::cout << "mdata->data = " << mdata->data << std::endl;
		//std::cout << "mdata->name = " << mdata->name << std::endl;
		ret++;
	}
	return ret;
}

int for_each_list_safe(list_head* head, int list_idx) {
	list_head* tmp = 0;
	list_head* n = 0;
	int ret = 0;
	my_data* mdata = 0;
	
	for (tmp = head->next, n = tmp->next; tmp != head; tmp = n, n = n->next) {		
		ret++;
		mdata = reinterpret_cast<my_data*>(tmp - offset_list[list_idx]);
		std::cout << "mdata->data = " << mdata->data << std::endl;
	}
	return ret;
}

int main() {
	int ret = 0;
	std::cout << "start main" << std::endl;
	list_init(&gen_head);
	list_init(&play_head);
	data_cur = 0;

	char temp_char[10] = "checklist";
	char a1[] = "eidkajkd";
	char a2[] = "dskfjsh";

	//std::cout << "offset_list0 = " << offset_list[0] << std::endl;
	//std::cout << "offset_list1 = " << offset_list[1] << std::endl;

    gen_input();
	for (auto val:in) {
		add_input(val.data, val.name);
	}
	add_input(10, temp_char);
	add_input(8, a1);
	add_input(7, a2);

	int cnt1 = for_each_list(&gen_head, 0);
	for_each_list(&play_head, 1);
	std::cout << "cnt1 = " << cnt1 << std::endl;	
	int cnt2 = remove_list(3);
	std::cout << "cnt2 = " << cnt2 << std::endl;	
	for_each_list_safe(&gen_head, 0);

	return ret;
}

int remove_list(int del_data) {
	int ret = 0;
	list_head* tmp = 0;
	list_head* n = 0;

	int cnt = 0;
	int cnt2 = 0;
	std::cout << "del_data, " << del_data << " below will be removed" << std::endl;

	for (tmp = (&gen_head)->next, n = tmp->next; tmp != &gen_head; tmp = n, n = n->next) {
		std::cout << "tmp = " << tmp << ", n = " << n << std::endl;
		cnt++;
		//my_data* mydata = reinterpret_cast<my_data*>(tmp - offset_list[0]);
		my_data* mydata = (my_data *)(tmp - offset_list[0]);
		if (mydata->data < del_data) {
			std::cout << "mydata = " << mydata->data << ", del_data = " << del_data << std::endl;
			list_del(tmp);
			cnt2++;
		}
	}
	ret = cnt2;
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
