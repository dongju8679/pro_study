#include <iostream>

#define MAX_N (10)
#define MAX_M (10)
#define MAX_Q (100*100)

int N;
int M;
char b[MAX_N][MAX_M];
int f;
int r;

int chk[MAX_N][MAX_N][MAX_N][MAX_N];

struct q_t {
	int wx;
	int wy;
	int bx;
	int by;
	int cnt;
}q[MAX_Q];

int push(int wx, int wy, int bx, int by, int cnt) {
	int ret = 0;
	if (b[wy][wx] == '#' || b[by][bx] == '#') {
		return 0;
	}
	if (b[wy][wx] == 'O' || b[by][bx] == 'O') {
		return 0;
	}
	if (chk[wy][wx][by][bx] == 1) {
		return 0;
	}

	q[f].wx = wx;
	q[f].wy = wy;
	q[f].bx = bx;
	q[f].by = by;
	q[f].cnt = cnt;
	f++;
	chk[wy][wx][by][bx] = 1;
	return ret;
}

q_t pop() {
	q_t ret = {};
	ret.wy = q[r].wy;
	ret.wx = q[r].wx;
	ret.by = q[r].by;
	ret.bx = q[r].bx;
	ret.cnt = q[r].cnt;
	r++;
	return ret;
}

int bfs(int wx, int wy, int bx, int by) {
	push(wx, wy, bx, by, 0);
	while (f>r) {
		q_t dat = pop();
		for (int i = 0; i < 4; i++) {			
			q_t new_dat = dat;
			while (1) {
				if (b[new_dat.wy - 1][wx] == 'O') {
					break;
				}
				else if (b[new_dat.wy - 1][wx] == '#') {

				}
				if (b[new_dat.by - 1][wx] == 'O') {
					break;
				}
				if (b[new_dat.wy - 1][wx] == '#') {
					break;
				}
				if (b[new_dat.by - 1][wx] == '#') {
					break;
				}
				new_dat.wy = new_dat.wy - 1;
				new_dat.by = new_dat.by - 1;
			}

		}


	}
	return 0;
}

int main() {
	int ret = 0;
	
	std::cin >> N;
	std::cin >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			std::cin >> b[i][j];
		}
	}

#if 0
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			std::cout << b[i][j];
		}
		std::cout << std::endl;
	}
#endif
	int wx, wy, bx, by;
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (b[i][j] == 'W') {
				wx = j;
				wy = i;
				cnt++;
				if (cnt == 2) {
					goto start;
				}
			}
			else if (b[i][j] == 'B') {
				bx = j;
				by = i;
				cnt++;
				if (cnt == 2) {
					goto start;
				}
			}
		}
	}
start:
	std::cout << "wx = " << wx << ", wy = " << wy << ", bx = " << bx << ", by = " << by << std::endl;
	f = r = 0;
	bfs(wx, wy, bx, by);

	return ret;
}