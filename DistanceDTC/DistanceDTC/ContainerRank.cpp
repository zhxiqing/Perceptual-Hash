#include "ContainerRank.h"



ContainerRank::ContainerRank()
{
}

ContainerRank::ContainerRank(int a) {
	for (size_t i = 0; i < a; i++)
		this->container.push_back(std::vector<std::vector<Distance> * >());
}

ContainerRank::~ContainerRank()
{
}
