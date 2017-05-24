#include "Distance.h"

	

Distance::Distance(int id,double value)
{
	this->idImg = id;
	this->value = value;
}


Distance::~Distance()
{
}

bool Distance::operator<(const Distance  &b) {
	return this->value < b.value;
}

void Distance::printValue() {
	std::cout << "Distance avec " << this->idImg << "  " << this->value << std::endl;
}

std::ostream& operator<< (std::ostream& stream, const Distance& r) {
	//std::cout << std::fixed << std::setw(11) << std::setprecision(3) << r.value << std::endl; 
	stream << r.idImg << "," << std::fixed << std::setw(11) << std::setprecision(3) << r.value;
	return stream;
}