#include <iostream>
#include <time.h>
#include <random>

#define MAX_STRING 100
#define MAX_N 10
#define MAX_HEAD 10

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
private:
	
};

dat in[MAX_N];
dat tmp[MAX_N];
int N;

dat head[MAX_HEAD];
dat* phead[MAX_HEAD];

int set_input(dat array[]);
int my_strlen(char* str);
int my_strcpy(char* dst, char* src);
int my_strcmp(char* strA, char* strB);

int main(int argc, char *argv[]) {
	int ret = 0;
	std::cout << "start msort_hash" << std::endl;
	N = MAX_N;
	init(in);
	set_input(in);
	return ret;
}

int init(dat array[]) {
	int ret = 0;
	for (int i = 0; i < MAX_HEAD; i++) {
		phead[i] = &head[i];
		phead[i]->prev = &head[i];
		phead[i]->next = &head[i];
	}
	for (int i = 0; i < N; i++) {
		array[i].idx = -1;
		array[i].val = -1;
		array[i].name[0] = '\0';
	}
	return ret;
}

int set_input(dat array[]) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		array[i].idx = i;
		array[i].val = rand() % 10;
		my_strcpy(array[i].name, &name_list[i][0]);
	}
	return ret;
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
