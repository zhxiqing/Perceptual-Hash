#pragma once
#include <vector>
#include "Distance.h"

class ContainerRank
{
public:
	ContainerRank();
	ContainerRank(int a);
	~ContainerRank();
	inline void pushBack(std::vector<std::vector<Distance> * > d) { this->container.push_back(d); };
	inline std::vector<std::vector<Distance> * >& getVecDis(int i) { return this->container.at(i); };
private :
	std::vector<std::vector<std::vector<Distance> * >> container;
};

