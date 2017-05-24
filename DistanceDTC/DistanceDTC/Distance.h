#pragma once
#include <vector>
#include<iostream>
#include <iomanip>



 class  Distance
{
public:
	bool operator<(Distance const & b);
	Distance(int id,double value);					
	~Distance();
	void printValue();
	friend std::ostream& operator<< (std::ostream& stream, const Distance& r);
	inline double getValue() { return value; }
	inline int getidImg() { return idImg; }
	inline void setValue(double a) { this->value = a; }

private :
	double value;
	int idImg;
};


