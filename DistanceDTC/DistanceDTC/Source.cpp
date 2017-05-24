#include<fstream>
#include<iostream>
#include<sstream>       // string stream
#include <vector>
#include <utility>      // std::pair, std::make_pair
#include <string>
#include <cstdio>
#include <ctime>

#include "ContainerRank.h"
#include "Distance.h"
#include "RankPerImg.h"
#include "SubRankCmp.h"

void writeRankOnFile(std::string name, RankPerImg rank);


// write a ank on standard input
void writeRank( RankPerImg rank) {
	
	std::cout << "IDimg ,";
	for (size_t i = 0; i < 5; i++)
	{
		std::cout << " rank " << i << "," << " distance " << i << ",";
	}
	std::cout << std::endl;
	std::cout << rank;
}


// extract the HTD descriptor from the file called name file
std::vector<DescripteurHTD >extractDescripteurHTD(std::string nameFile) {

	std::vector<DescripteurHTD > vecDes;
	std::string temp,number;
	std::fstream read;
	std::stringstream sstr;
	read.open(nameFile, std::ios::in);

	// simple verification
	if (!read.is_open()) {
		std::cout << "File error!" << std::endl;
		exit(EXIT_FAILURE);
	}

	// get line by line
	while (getline(read, temp)) {

		vecDes.push_back( *(new DescripteurHTD()));

		// we use stringstream to separate the numbers in the string
		sstr << temp;
		while (sstr >> number)
			vecDes.at(vecDes.size()-1).pushBack(std::atoi(number.c_str()));
		sstr.clear();
	}

	return vecDes;

}


// extract the CLD descriptor from the file called name file
std::vector<DescripteurCLD >extractDescripteurCLD(std::string nameFile) {

	std::vector<DescripteurCLD > vecDes;
	std::string temp, number;
	std::fstream read;
	std::stringstream sstr;
	read.open(nameFile, std::ios::in);

	if (!read.is_open()) {
		std::cout << "File error!" << std::endl;
		exit(EXIT_FAILURE);
	}

	while (getline(read, temp)) {
		vecDes.push_back(*(new DescripteurCLD()));

		// get line CB
		sstr << temp;
		while (sstr >> number)
			vecDes.back().pushBack(std::atoi(number.c_str()),1);
		sstr.clear();

		// get line CR
		getline(read, temp);
		sstr << temp;
		while (sstr >> number)
			vecDes.at(vecDes.size() - 1).pushBack(std::atoi(number.c_str()),2);
		sstr.clear();

		// get line Y
		getline(read, temp);
		sstr << temp;
		while (sstr >> number)
			vecDes.at(vecDes.size() - 1).pushBack(std::atoi(number.c_str()), 3);
		sstr.clear();

	}

	return vecDes;

}


// get the vector of descriptor return the rank NOT SORTED  of the descriptor
template<typename T>
RankPerImg outputRank(std::vector<T> des) {
	T curr;
	RankPerImg rank("lol");
	for (size_t i = 0; i < des.size(); i++)
	{
		// we create a new vector conatining all the distance between an image A and the rest of the collection
		std::vector<Distance> * vecDis = new std::vector<Distance>();
		curr = des[i];
		for (size_t j = 0; j < des.size(); j++)
		{
			if (j != i) {
				vecDis->push_back(Distance(j, curr.calculDistance(des[j])));
				// add the new distance into the vector
			}
		}
		// add the new vector into the rank
		rank.pushBack(vecDis);
	}
	
	
	return rank;
}


// Template instanciation
template RankPerImg outputRank<DescripteurCLD>( std::vector<DescripteurCLD> des);
template RankPerImg outputRank<DescripteurHTD>( std::vector<DescripteurHTD> des);



bool testUnitaire() {

	std::ofstream HTDcreate, CLDcreate;
	std::vector<int> vecData;


	// création des fichiers de descripteurs

	HTDcreate.open("testHTD.txt");
	CLDcreate.open("testCLD.txt");

	// remplissage des fichiers

	for (int i = 0; i < 5; i++)
		HTDcreate << "10 20 30 40" << std::endl;

	for (int i = 0; i < 5; i++)
		for (size_t i = 0; i < 3; i++)
			CLDcreate << "10 20 30 40 " << std::endl;

	HTDcreate.close();
	CLDcreate.close();

	// extraction des descripteurs

	std::vector<DescripteurHTD> vecHTD = extractDescripteurHTD("testHTD.txt");
	std::vector<DescripteurCLD> vecCLD = extractDescripteurCLD("testCLD.txt");

	// création d'un vecteur à comparer avec le résultat de l'extraction

	for (size_t i = 0; i < 4; i++)
		vecData.push_back(10 * (i + 1));

	for (int i = 0; i < 5; i++) {

		if (!vecHTD[i].compare(vecData)) {
			std::cout << "step 1 " << std::endl;
			return false;

		}

		for (size_t j = 0; j < 3; j++)
			if (!vecCLD[i].compare(vecData, j)) {
				std::cout << "step 2 " << std::endl;
				return false;
			}
	}

	// calcul des distances

	RankPerImg rankHTD = outputRank(vecHTD);
	RankPerImg rankCLD = outputRank(vecCLD);

	// verification de la somme des distances soit bien égale à 0

	if (rankCLD.getSumDistance() != 0 || rankHTD.getSumDistance() != 0) {
		std::cout << "step 3 " << std::endl;
		return false;
	}

	return true;

}





int main() {
	/*
	if (testUnitaire())
		std::cout << "ok" << std::endl;
	*/
	
	std::string nameInput = "ImageXiqing";
	std::string nameOutput = "BDD-";
	std::string subjectFile = "ressemblance";
	std::string subjectOuputFile = "FullBaseXiqing";

	// nbratio is the number of distance's rank  we will be using
	// each rank has a different ratio CLD/HTD
	double nb_ratio = 11;

	double tmpResult, duration;

	std::clock_t start;

	


	RankPerImg tmp;
	ContainerRank data(nb_ratio);

	start = std::clock();

	// get the descriptors OF THE SAME COLLECTION OF IMAGE 
	std::vector<DescripteurHTD> vecHTD= extractDescripteurHTD(nameInput+"HTD.txt");
	std::vector<DescripteurCLD> vecCLD = extractDescripteurCLD(nameInput+"CLD.txt");

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Time extract step : " << duration  << std::endl;


	// this class is a basic container to store the results
	std::vector<std::pair<std::string, double>> dataResult;

	
	start = std::clock();

	// get the distance rank
	// output rank is the function that extract the descriptor and process the distance between each one of them

	RankPerImg rankHTD = outputRank(vecHTD);
	RankPerImg rankCLD = outputRank(vecCLD);


	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Time calculation distance step : " << duration << std::endl;


	duration = 0.0;


	// get the hybrid distance rank 
	// we stock the data in a double vector of Distance inside Container Rank
	for (double i  = 0; i <nb_ratio; i++)
	{
		
		start = std::clock();

		tmp.outputrankHybrid(rankCLD, rankHTD, vecHTD.size(), data.getVecDis(i),i);

		// this line writes every rank in a separated file

		//writeRankOnFile(std::to_string(int(i))+"_test.csv", RankPerImg(data.getVecDis(i)));

		duration += (std::clock() - start) / (double)CLOCKS_PER_SEC;
	}

	std::cout << "Mean  time first step : " << duration/nb_ratio << std::endl;
		 
	// sort the original rank
	// DONT USE THIS FUNCTION BEFORE outputrankHybrid
	rankHTD.sortRanks();
	rankCLD.sortRanks();
	
	// write the original rank (only HTD or only CLD / ratio of 0 or 1 in a hybrid rank ) on two files
	// OBSOLETE was just for starting test
	writeRankOnFile(nameOutput + "HTD.csv", rankHTD);
	writeRankOnFile(nameOutput + "CLD.csv", rankCLD);


	// get the human classification 
	SubRankCmp compare (subjectFile + ".txt");


	// print just to test
	compare.printRank();

	// ofstream for the final result in CSV 
	std::ofstream myfile , resultFile;

	myfile.open(subjectOuputFile + ".csv");

	// a file that contains only the average and not the detailed data
	resultFile.open("ResultFinal.csv");



	// for each ratio of CLD/HTD
	for (int i = 0; i < 11; i++)

		// for each number of image we want to compare between the human's and program's classification
		for (int x = 1; x < 11; x++) {

			tmpResult = compare.compareReversed(myfile, "ratio CLD / HTD : " + std::to_string(i * 10) + "% number img used  " + std::to_string(x), RankPerImg(data.getVecDis(i)), x);
			dataResult.push_back(std::pair<std::string, double>("ratio CLD / HTD : " + std::to_string(i * 10) + "% number img used  " + std::to_string(x), tmpResult));
		}

	// write the average on the other file 
	for (size_t i = 0; i < dataResult.size(); i++)
		resultFile << dataResult[i].first << "," << dataResult[i].second << std::endl;

	resultFile.close();
	myfile.close();
	
	system("pause");
	
	return 0 ;

}

