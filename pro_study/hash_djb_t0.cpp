#include <iostream>
#define MAX_NUM_DATA (1 << 12)
#define MAX_STR_LEN 10
#define MAX_TABLE (1 << 12)
#define MOD  (MAX_TABLE - 1)

int my_strlen(char* str);
int my_strcpy(char* dst, char* src);
int my_strcmp(char* strA, char* strB);

char arr[MAX_NUM_DATA][MAX_STR_LEN];
unsigned int arr2[MAX_NUM_DATA];

int N;
int map[MAX_NUM_DATA][MAX_NUM_DATA];

unsigned int djb2_t0(char *str) {
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

unsigned int djb2_t1(char* str) {
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
	{
		hash = ((((hash << 5) + hash) + c) + MOD) & MOD;
	}
	return hash;
}

int show_arr(int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		std::cout << "arr[i] = " << arr[i] << std::endl;
	}
	return ret;
}

int show_arr2(int N) {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		std::cout << "arr2[i] = " << arr2[i] << std::endl;
	}
	return ret;
}

int main() {
	int ret = 0;
	clock_t start, end;
	std::cout << "start hash_djb2_t0" << std::endl;
	N = MAX_NUM_DATA;
	for (int i = 0; i < MAX_NUM_DATA; i++) {		
		char name[MAX_STR_LEN];
		for (int j = 0; j < MAX_STR_LEN; j++) {
			name[j] = static_cast<char>(97 + rand() % 26);
		}
		name[MAX_STR_LEN - 1] = '\0';
		my_strcpy(arr[i], name);
	}

	//show_arr(N);
	
	start = clock();
	for (int i = 0; i < N; i++) {
		//unsigned int my_hash = djb2_t0(arr[i]);
		unsigned int my_hash = djb2_t1(arr[i]);
		arr2[i] = my_hash;
	}
	end = clock();
	std::cout << "elapsed time = " << end - start << std::endl;
	//show_arr2(N);
	int conflict_cnt = 0;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (arr2[i] == arr2[j]) {
				if (i == j) continue;
				if (map[i][j] == 1) continue;
				if (map[j][i] == 1) continue;
				conflict_cnt++;
				map[i][j] = 1;				
				map[j][i] = 1;
			}
		}
	}
	std::cout << "conflict_cnt = " << conflict_cnt << std::endl;

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