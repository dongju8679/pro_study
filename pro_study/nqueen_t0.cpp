#include <iostream>

#define MAX_N (13 + 10)

struct pos_t {
	int x;
	int y;
};

int cnt = 0;
int N;
pos_t queen[MAX_N];

int tot = 0;
pos_t solve[MAX_N * MAX_N][MAX_N];

int possible_way(int y, int x) {
	//std::cout << "start possible_way, cnt = " << cnt << ", y = " << y << ", x = " << x << std::endl;
	if (cnt == 0) {
		return 1;
	}
	for (int i = 0; i < cnt; i++) {
		//std::cout << "check, queen.y = " << queen[i].y << ", queen.x = " << queen[i].x << std::endl;
	}
	
	int ret = 1;
	pos_t cur;
	cur.y = y;
	cur.x = x;
	
	while (1) {
		if (cur.y > N or cur.x > N) {			
			break;
		}
		if (cur.y < 1 or cur.x < 1) {			
			break;
		}
		for (int k = 0; k < cnt; k++) {
			if (cur.y == queen[k].y && cur.x == queen[k].x) {
				return 0;
			}
		}		
		cur.x = cur.x + 1;
	}
	cur.y = y;
	cur.x = x;
	while (1) {
		if (cur.y > N or cur.x > N) {
			break;
		}
		if (cur.y < 1 or cur.x < 1) {
			break;
		}
		for (int k = 0; k < cnt; k++) {			
			//std::cout << "compare, cur.y = " << cur.y << ", q.y = " << queen[k].y << ", cur.x = " << cur.x << ", q.x = " << queen[k].x << std::endl;
			if (cur.y == queen[k].y && cur.x == queen[k].x) {				
				return 0;
			}
		}
		cur.x = cur.x - 1;
	}
	cur.y = y;
	cur.x = x;
	while (1) {
		if (cur.y > N or cur.x > N) {
			break;
		}
		if (cur.y < 1 or cur.x < 1) {
			break;
		}
		for (int k = 0; k < cnt; k++) {			
			if (cur.y == queen[k].y && cur.x == queen[k].x) {
				return 0;
			}
		}
		cur.y = cur.y + 1;
	}
	cur.y = y;
	cur.x = x;
	while (1) {
		if (cur.y > N or cur.x > N) {
			break;
		}
		if (cur.y < 1 or cur.x < 1) {
			break;
		}
		for (int k = 0; k < cnt; k++) {			
			if (cur.y == queen[k].y && cur.x == queen[k].x) {
				return 0;
			}
		}
		cur.y = cur.y - 1;
	}
	cur.y = y;
	cur.x = x;
	while (1) {
		if (cur.y > N or cur.x > N) {
			break;
		}
		if (cur.y < 1 or cur.x < 1) {
			break;
		}
		for (int k = 0; k < cnt; k++) {			
			if (cur.y == queen[k].y && cur.x == queen[k].x) {
				return 0;
			}
		}
		cur.x = cur.x + 1;
		cur.y = cur.y + 1;
	}
	cur.y = y;
	cur.x = x;
	while (1) {
		if (cur.y > N or cur.x > N) {
			break;
		}
		if (cur.y < 1 or cur.x < 1) {
			break;
		}
		for (int k = 0; k < cnt; k++) {			
			if (cur.y == queen[k].y && cur.x == queen[k].x) {
				return 0;
			}
		}
		cur.x = cur.x - 1;
		cur.y = cur.y - 1;
	}
	cur.y = y;
	cur.x = x;
	while (1) {
		if (cur.y > N or cur.x > N) {
			break;
		}
		if (cur.y < 1 or cur.x < 1) {
			break;
		}
		for (int k = 0; k < cnt; k++) {
			if (cur.y == queen[k].y && cur.x == queen[k].x) {
				return 0;
			}
		}
		cur.x = cur.x - 1;
		cur.y = cur.y + 1;
	}
	cur.y = y;
	cur.x = x;
	while (1) {
		if (cur.y > N or cur.x > N) {
			break;
		}
		if (cur.y < 1 or cur.x < 1) {
			break;
		}
		for (int k = 0; k < cnt; k++) {
			if (cur.y == queen[k].y && cur.x == queen[k].x) {
				return 0;
			}
		}
		cur.x = cur.x + 1;
		cur.y = cur.y - 1;
	}
	return ret;
}

void nqueen(pos_t pos) {
	int ret = 0;
	//std::cout << "start nqueen, pos.y = " << pos.y << ", x= " << pos.x << std::endl;
	for (int i = 0; i < cnt; i++) {
		//std::cout << "cur q, y = " << queen[i].y << ", cur q, x = " << queen[i].x << std::endl;
	}
	if (cnt == N) {
		tot++;
#if 0	
		for (int i = 0; i < cnt; i++) {
			//std::cout << "tot = " << tot << ", y = " << queen[i].y << ", x = " << queen[i].x << std::endl;
			if (1) {				
				solve[tot][i].y = queen[i].y;
				solve[tot][i].x = queen[i].x;
			}				
		}
#endif
		return;
	}
	
	//for (int j = pos.y; j <= N; j++) {
		//for (int i = pos.x; i <= N; i++) {
	int j = pos.y;
	int i = pos.x;
	while (1) {		
		//std::cout << "pos, j = " << j << ", i = " << i << std::endl;
		//std::cout << "cnt = " << cnt << std::endl;	
		int check_possible = 0;
		if (possible_way(j, i) == 0)
		{
			//std::cout << "possible, continue, j = " << j << ", i = " << i << std::endl;
			check_possible = 1;
			goto end;
		}
		queen[cnt].y = j;
		queen[cnt].x = i;
		//std::cout << "add queen, cnt= " << cnt << ", q0.y = " << queen[cnt].y << ", q0.x = " << queen[cnt].x << std::endl;
		cnt++;	

		pos_t new_pos;
		new_pos.y = j;
		new_pos.x = i;
		nqueen(new_pos);
		cnt--;
		
	end:
		if (i == N) {
			j++;
			i = 1;
		}
		else {
			i++;
		}	
		if (j == N + 1) {
			break;
		}			
	}	
	return;
}

int main() {
	int ret = 0;
	std::cin >> N;

	//std::cout << "start nqueen_t0" << std::endl;
	pos_t s = { 1, 1 };
	nqueen(s);

	std::cout << tot << std::endl;

	return ret;
}