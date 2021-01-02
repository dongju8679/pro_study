#include <iostream>
#define SHOW 1

#define MAX_NUM_DATA 1 << 2
#define MAX_STR_LEN 10

int my_strlen(char* str);
int my_strcpy(char* dst, char* src);
int my_strcmp(char* strA, char* strB);

struct in_data {
	int val;
	char name[MAX_STR_LEN];
}in_d[MAX_NUM_DATA];

struct my_data {
	int idx;
	int val;
	char name[MAX_STR_LEN];

}my_d[MAX_NUM_DATA], tmp[MAX_NUM_DATA];

int check_condition(my_data* arr, int i, int j) {
	int ret = 0;
	if (arr[i].val < arr[j].val) {
		ret = 1;
	}
	else if (arr[i].val == arr[j].val) {
		if (arr[i].idx < arr[j].idx) {
			ret = 1;
		}
	}
	return ret;
}

int check_condition_idx(my_data* arr, int i, int j) {
	int ret = 0;
	if (arr[i].idx < arr[j].idx) {
		ret = 1;
	}	
	return ret;
}

void merge_sort(my_data* arr, int start, int end) {
	if (start >= end) return;
	int middle = (start + end) / 2;
	int i, j, k;
	i = start;
	j = middle + 1;
	k = i;
	merge_sort(arr, start, middle);
	merge_sort(arr, middle+1, end);
	while (i <= middle && j <= end) {
		if (check_condition(arr, i, j) == 1) {
			tmp[k++] = arr[i++];
		}
		else {
			tmp[k++] = arr[j++];
		}
	}
	while (i <= middle) {
		tmp[k++] = arr[i++];
	}
	while (j <= end) {
		tmp[k++] = arr[j++];
	}
	for (k = start; k <= end; k++) {
		arr[k] = tmp[k];
	}
}

void merge_sort_idx(my_data* arr, int start, int end) {
	if (start >= end) return;
	int middle = (start + end) / 2;
	int i, j, k;
	i = start;
	j = middle + 1;
	k = i;
	merge_sort_idx(arr, start, middle);
	merge_sort_idx(arr, middle + 1, end);
	while (i <= middle && j <= end) {
		if (check_condition_idx(arr, i, j) == 1) {
			tmp[k++] = arr[i++];
		}
		else {
			tmp[k++] = arr[j++];
		}
	}
	while (i <= middle) {
		tmp[k++] = arr[i++];
	}
	while (j <= end) {
		tmp[k++] = arr[j++];
	}
	for (k = start; k <= end; k++) {
		arr[k] = tmp[k];
	}
}

int binarysearch(my_data* arr, int low, int high, int target) {
	int ret = 0;
	int mid;
	if (low > high)
	{		
		return -1;
	}
	mid = (low + high) / 2;
	if (target < arr[mid].idx)
	{
		//std::cout << "mid0 = " << mid << std::endl;
		binarysearch(arr, low, mid - 1, target);
	}
	else if (arr[mid].idx < target)
	{
		//std::cout << "mid1 = " << mid << std::endl;
		binarysearch(arr, mid + 1, high, target);
	}
	else
	{		
		//std::cout << "mid2 = " << mid << std::endl;
		ret = mid;
		return ret;		
	}	
}

int normalsearch(my_data* arr, int low, int high, int target) {
	int ret = 0;
	for (int i = low; i <= high; i++) {
		if (arr[i].idx == target) {
			ret = i;
			return ret;
		}
	}
}

int show_arr(my_data* arr) {
	int ret = 0;
	for (int i = 0; i < MAX_NUM_DATA; i++) {
		std::cout << "idx = " << arr[i].idx << ", val = " << arr[i].val << ", name = " << arr[i].name << std::endl;
	}
	return ret;
}

int check_insert1(my_data* arr, int i, int j) {
	int ret = 0;
	if (arr[i].val < arr[j].val) {
		ret = 1;
	}
	else if (arr[i].val == arr[j].val) {
		if (arr[i].idx < arr[j].idx) {
			ret = 1;
		}
	}
	return ret;
}

void insertionSort(my_data* arr, int start, int end)
{
	my_data temp = {};
	int i;
	int j;
	for (i = start + 1; i <= end; i++)
	{
		temp = arr[i];
		j = i - 1;

		//while ((temp < arr[j].val) && (j >= 0))
		while ((check_insert1(arr, i, j) == 1) && (j >= 0))
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = temp;
	}
}

int main() {
	int ret = 0;
	int N = MAX_NUM_DATA;
	clock_t start, end;
	
	std::cout << "start binarysearch0" << std::endl;
	for (int i = 0; i < MAX_NUM_DATA; i++) {		
		in_d[i].val = rand() % 50;
		char name[MAX_STR_LEN];
		for (int j = 0; j < MAX_STR_LEN; j++) {
			name[j] = static_cast<char>(97 + rand() % 26);
		}		
		name[MAX_STR_LEN - 1] = '\0';
		my_strcpy(in_d[i].name, name);
	}	

	for (int i = 0; i < MAX_NUM_DATA; i++) {
		my_d[i].idx = i;
		my_d[i].val = in_d[i].val;
		my_strcpy(my_d[i].name, in_d[i].name);
	}
#ifdef SHOW
	show_arr(my_d);
#endif

	//merge_sort(my_d, 0, MAX_NUM_DATA - 1);
#if 0
	start = clock();
	merge_sort_idx(my_d, 0, N - 2);
	end = clock();
	std::cout << "after merge_sort_idx0, elapsed time = " << end - start << std::endl;
#endif

	start = clock();
	//merge_sort_idx(my_d, 0, N - 1);
	//merge_sort(my_d, 0, N - 1);
	merge_sort(my_d, 0, N - 2);
	end = clock();
	std::cout << "after merge_sort_idx1, elapsed time = " << end - start << std::endl;

	start = clock();
	int target_idx = 3;
#if 0
	merge_sort_idx(my_d, 0, N - 1);
	int new_idx = binarysearch(my_d, 0, N - 1, target_idx);	
#else
	int new_idx = normalsearch(my_d, 0, N - 1, target_idx);	
#endif
	end = clock();
	std::cout << "after search, elapsed time = " << end - start << std::endl;
	std::cout << "new_idx = " << new_idx << std::endl;	

#if 0
	start = clock();
	merge_sort(my_d, 0, N - 2);
	end = clock();
	std::cout << "after merge_sort, elapsed time = " << end - start << std::endl;

	start = clock();
	merge_sort(my_d, 0, N - 1);
	end = clock();
	std::cout << "after merge_sort, elapsed time = " << end - start << std::endl;
#endif

#ifdef SHOW	
	show_arr(my_d);
#endif
	start = clock();
#if 0
	merge_sort(my_d, 0, N - 1);
#else
	insertionSort(my_d, 0, N - 1);
#endif
	end = clock();
	std::cout << "after sort2, elapsed time = " << end - start << std::endl;

#ifdef SHOW	
	show_arr(my_d);
#endif

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