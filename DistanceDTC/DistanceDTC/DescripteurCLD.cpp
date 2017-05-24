#include "DescripteurCLD.h"
#include<iostream>



DescripteurCLD::DescripteurCLD()
{
	this->desCb = new std::vector<int>();
	this->desCr = new std::vector<int>();
	this->desY = new std::vector<int>();
}


DescripteurCLD::~DescripteurCLD()
{
	
}
bool DescripteurCLD::compare(std::vector<int> a, int b) {
	std::vector<int> * tmp = this->desCb;
	if (b == 0)
		tmp = this->desCb;
	else if (b == 1)
		tmp = this->desCr;
	else if (b == 2)
		tmp = this->desY;

	for (size_t i = 0; i < tmp->size(); i++)
		if (a[i] != tmp->at(i))
			return false;

	return true;
}


void DescripteurCLD::pushBack(int a, int type) {
	switch (type) {
		case 1:
			this->desCb->push_back(a);
			break;
		case 2:
			this->desCr->push_back(a);
			break;
		case 3:
			this->desY->push_back(a);
			break;
	}
}


double DescripteurCLD::calculDistance(DescripteurCLD b) {
	double sum = 0;
	double sum1 = 0;
	double sum2 = 0;
	double sum3 = 0;
	//std::cout << b.desY->size() << "  ok  " << this->desY->size();
	for (int i = 0; i < b.desY->size() ; i++) 
		sum += (this->desY->at(i) - b.desY->at(i))*(this->desY->at(i) - b.desY->at(i));
	
	sum1 = sqrt(sum);
	sum = 0;
	for (int i = 0; i < this->desCr->size(); i++) 
		sum += (this->desCr->at(i) - b.desCr->at(i))*(this->desCr->at(i) - b.desCr->at(i));
	
	sum2 = sqrt(sum);
	sum = 0;
	for (int i = 0; i < this->desCb->size(); i++) 
		sum += (this->desCb->at(i) - b.desCb->at(i))*(this->desCb->at(i) - b.desCb->at(i));
	
	sum3 = sqrt(sum);
	//std::cout << (sum1 + sum2 + sum3) << std::endl;
	return (sum1 + sum2 + sum3);
}
