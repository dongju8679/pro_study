#include <iostream>

#define MAX_N (5)

int N, M;

int val[MAX_N];
int cnt = 0;
int chk[7] = {0};

#if 1
int dice1() {
	int ret = 0;	
	if (cnt == N) {
		for (int i = 0; i < cnt; i++) {
			std::cout << val[i] << " ";
		}		
		std::cout << std::endl;
		return 0;
	}	
	for (int i = 1; i <= 6; i++) {
		val[cnt] = i;
		cnt++;
		dice1();
		cnt--;
	}	
	return ret;	
}

int dice2(int prev) {
	int ret = 0;
	if (cnt == N) {
		for (int i = 0; i < cnt; i++) {
			std::cout << val[i] << " ";
		}
		std::cout << std::endl;
		return 0;
	}
	for (int i = prev; i <= 6; i++) {
		val[cnt] = i;
		cnt++;
		chk[i] = 1;
		dice2(i);
		cnt--;
		chk[i] = 0;
	}
	return ret;
}

int dice3() {
	int ret = 0;
	if (cnt == N) {
		for (int i = 0; i < cnt; i++) {
			std::cout << val[i] << " ";
		}
		std::cout << std::endl;
		return 0;
	}
	for (int i = 1; i <= 6; i++) {
		if (chk[i] == 1) {
			continue;
		}
		val[cnt] = i;
		cnt++;
		chk[i] = 1;
		dice3();
		cnt--;
		chk[i] = 0;
	}
	return ret;
}	
#endif

int main() {
	int ret = 0;
	std::cin >> N;
	std::cin >> M;
	//std::cout << "N = " << N << ", M = " << M << std::endl;
	if (M == 1) {
		dice1();
	}
	if (M == 2) {
		int init = 1;
		dice2(init);
	}
	if (M == 3) {
		dice3();
	}
	
	//std::cout << "start dice_t1" << std::endl;

	return ret;
}