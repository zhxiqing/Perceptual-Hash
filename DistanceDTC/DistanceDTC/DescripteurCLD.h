#pragma once
#include<iostream>
#include<fstream>
#include<iostream>
#include<sstream>
#include <vector>


// class that contains the CLD descriptors 
// to use the implementation calculDistance is needed

class DescripteurCLD
{
public:
	DescripteurCLD();
	~DescripteurCLD();
	void pushBack(int a, int type);
	double calculDistance(DescripteurCLD b);
	bool compare(std::vector<int> a, int b);
	inline void getSize() { std::cout << this->desCb->size() << "  " << this->desCr->size() << "  " << this->desY->size() << std::endl; }

private :
	std::vector<int> * desY;
	std::vector<int> * desCr;
	std::vector<int> * desCb;
};

