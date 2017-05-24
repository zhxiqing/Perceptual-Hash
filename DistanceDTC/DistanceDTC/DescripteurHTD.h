#include <vector>
#include<iostream>
#include<fstream>
#include<iostream>
#include<sstream>



// class that contains the CLD descriptors 
// to use the implementation calculDistance is needed

class DescripteurHTD 
{
public:
	DescripteurHTD();
	~DescripteurHTD();
	void pushBack(int a);
	double calculDistance(DescripteurHTD b);
	bool compare(std::vector<int> a);

	inline void getSize() { std::cout << this->des->size() << std::endl; }

private :
	std::vector<int> * des ;

};

