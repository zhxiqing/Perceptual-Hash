#include "DescripteurHTD.h"


DescripteurHTD::DescripteurHTD() {
	this->des = new std::vector<int>;
}



DescripteurHTD::~DescripteurHTD(){
}

void DescripteurHTD::pushBack(int a) {
	this->des->push_back(a);
}

bool DescripteurHTD::compare(std::vector<int> a) {

	for (size_t i = 0; i < a.size(); i++)
		if (a[i] != this->des->at(i))
			return false;

	return true;
}


double DescripteurHTD::calculDistance(DescripteurHTD b) {
	double sum = 0;
	for (size_t i = 0; i < this->des->size(); i++)
		sum += (this->des->at(i) - b.des->at(i))*(this->des->at(i) - b.des->at(i));
	//std::cout << sqrt(sum) << std::endl;

	return sqrt(sum);
}
