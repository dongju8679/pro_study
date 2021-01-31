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


int possible_way(int y, int x) {
	std::cout << "start possible_way, cnt = " << cnt << ", y = " << y << ", x = " << x << std::endl;
	if (cnt == 0) {
		return 1;
	}
	for (int i = 0; i < cnt; i++) {
		std::cout << "check, queen.y = " << queen[i].y << ", queen.x = " << queen[i].x << std::endl;
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
	return ret;
}

int nqueen(pos_t pos) {
	int ret = 0;
	//std::cout << "start nqueen, pos.y = " << pos.y << ", x= " << pos.x << std::endl;
	for (int i = 0; i <= cnt; i++) {
		std::cout << "cur q, y = " << queen[i].y << ", cur q, x = " << queen[i].x << std::endl;

	}
	if (cnt == N) {
		tot = tot + 1;
		ret = tot;
		//std::cout << "tot = " << tot << std::endl;
		for (int i = 0; i < cnt; i++) {
			//std::cout << "y = " << queen[cnt].y << ", x = " << queen[cnt].x << std::endl;
		}
		//std::cout << "ret = " << ret << std::endl;
		return ret;
	}
	
	for (int j = pos.y; j <= N; j++) {
		for (int i = pos.x; i <= N; i++) {
			std::cout << "pos, j = " << j << ", i = " << i << std::endl;
			//std::cout << "cnt = " << cnt << std::endl;				
			if (possible_way(j, i) == 0)
			{
				std::cout << "possible, continue, y = " << j << ", x = " << i << std::endl;
				continue;
			}			
			queen[cnt].y = j;
			queen[cnt].x = i;
			std::cout << "add queen, cnt= " << cnt << ", q0.y = " << queen[cnt].y << ", q0.x = " << queen[cnt].x << std::endl;
			for (int i = 0; i < cnt; i++) {
				//std::cout << "q.y = " << queen[cnt].y << ", q.x = " << queen[cnt].x << std::endl;
			}
			cnt++;
			pos_t new_pos;
			new_pos.y = j;
			new_pos.x = i;
			
			std::cout << "before nqeen" << std::endl;
			nqueen(new_pos);
			cnt--;			
		}		
	}
	ret = -1;
	return ret;
}

int main() {
	int ret = 0;
	std::cin >> N;

	//std::cout << "start nqueen_t0" << std::endl;
	pos_t s = { 1, 1 };

	std::cout << "" << nqueen(s) << std::endl;

	return ret;
}