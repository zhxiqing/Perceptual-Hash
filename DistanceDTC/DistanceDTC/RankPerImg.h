#pragma once
#include<fstream>
#include <vector>
#include <iostream>
#include <string>
#include "Distance.h"
#include <algorithm>    // std::sort


// data structure that contains the distance
// the distances are storaged in a vector of vector of distance 
// since the matrix of distance is symmetric we could remove half of the data 
// but it would make the sorting implementation of ranks way more complicated

class RankPerImg
{
public:
	RankPerImg();
	RankPerImg(std::string name);
	RankPerImg(std::vector<std::vector<Distance> * > & ranks);
	~RankPerImg();
	void sortRanks();
	void pushBack(std::vector<Distance> * d);
	void printValue();
	friend std::ostream& operator<< (std::ostream& stream, const RankPerImg& r);
	inline double getValue(int x, int y) { return ranks.at(x)->at(y).getValue(); }
	int getId(int x, int y) const ;
	bool inRank(int img, int nbImg,int id) const ;
	void normalisation();
	void outputrankHybrid(RankPerImg CLD, RankPerImg HTD,  int nbimg, std::vector<std::vector<Distance> * > &container,double ratio);
	int getSumDistance();
	inline void printSize() { std::cout << "x " << ranks.size() << " y " << ranks.at(0)->size() << std::endl; }
private:
	std::string nameRank;
	std::vector<std::vector<Distance> * >  ranks;
	bool  normed;

};

