#include <iostream>
#include <time.h>

#define MAX_SIZE 60000
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))
int original[MAX_SIZE];
int list[MAX_SIZE];
int n;
int sorted[MAX_SIZE];

clock_t start;
clock_t finish;
clock_t used_time = 0;

int main(int argc, char *argv[]) {
	int ret = 0;

	return ret;
}

void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left, j = mid + i; k = left;
	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) {
			sorted[k++] = list[i++];

		}

	}


}