#include <iostream>
#include "vector.h"

int main(int argc, char* argv[]) {
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.dump(std::cout);
}
	
