#pragma once
#include<fstream>
#include<iostream>
#include<sstream>       // string stream
#include <vector>
#include <map>
#include <utility>      // std::pair, std::make_pair
#include <string>
#include "DescripteurHTD.h"
#include "DescripteurCLD.h"
#include "Distance.h"
#include "RankPerImg.h"


class SubRankCmp
{
public:
	SubRankCmp( std::string nameFile);
	void extractSubRank(std::string nameFile);
	void compare(std::string outputFile, const  RankPerImg & r, int nbImg, int inter );
	double compareReversed(std::ofstream & myfile, std::string outputFile, const RankPerImg & rank, int nbImg );
	void printRank();

	~SubRankCmp();
private:
	
	std::map<int, std::vector<int>> subRank;
	std::map<int, std::vector<int>> notInSub;
	std::map<int, std::vector<int>> notInActual;


};

