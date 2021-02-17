#include <iostream>
#include <map>
#include <vector>

int main() {
	int ret = 0;

	std::vector<int> myvector(3, 100);
	for (auto aa:myvector) {
		std::cout << "aa = " << aa << std::endl;
	}
	std::vector<int>::iterator it;

	it = myvector.begin();
	std::cout << "check01, *it = " << *it << std::endl;
	it = myvector.insert(it, 200);
	for (auto aa22:myvector) {
		std::cout << "aa22 = " << aa22 << std::endl;

	}
	std::cout << "check02, *it = " << *it << std::endl;

	myvector.insert(it, 2, 300);
	for (auto aa2:myvector) {
		std::cout << "aa2 = " << aa2 << std::endl;
	}

	it = myvector.begin();

	std::vector<int> anothervector(2, 400);
	myvector.insert(it + 2, anothervector.begin(), anothervector.end());

	int myarray[] = {501, 502, 503};
	myvector.insert(myvector.begin(), myarray, myarray + 3);
	std::cout << "myvector contains:";
	for (it = myvector.begin(); it < myvector.end(); it++)	{
		std::cout << " " << *it;
	}
	
	std::cout << std::endl;

	std::cout << "start map_t3" << std::endl;
	std::map<int, std::string> m1;
	std::vector<int> a1;	

	return ret;
}