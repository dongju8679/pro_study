#include <iostream>

template <typename T1, typename T2>
T2 cast(T1 a) {
	return (T2)a;
}

int main(int argc, char *argv[]) {
	int ret = 0;
	std::cout << "start this" << std::endl;
	std::cout << cast<int, double>(3.4) << std::endl;

	return ret;
}