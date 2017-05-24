#include "SubRankCmp.h"



SubRankCmp::SubRankCmp( std::string nameFile)
{
	
	this->notInSub = std::map<int, std::vector<int>>();
	this->notInActual = std::map<int, std::vector<int>>();
	this->subRank = std::map<int, std::vector<int>>();
	this->extractSubRank(nameFile);

}


SubRankCmp::~SubRankCmp()
{
}


void SubRankCmp::extractSubRank(std::string nameFile) {

	std::string temp, number, id;
	std::fstream read;
	std::stringstream sstr;
	std::pair<int, std::vector<int>> pa;
	read.open(nameFile, std::ios::in);

	// simple verification
	if (!read.is_open()) {
		std::cout << "File error!" << std::endl;
		exit(EXIT_FAILURE);
	}

	// get line by line
	while (getline(read, temp)) {

		// we use stringstream to separate the numbers in the string
		sstr << temp;

		// we get the id of the image 
		sstr >> id ;
		pa = std::pair<int, std::vector<int>>(std::atoi(id.c_str()), std::vector<int>());
		//std::cout << "ID : " << id <<" ";

		// then the ranking of the distances between her and the collection
		while (sstr >> number) {
			pa.second.push_back(std::atoi(number.c_str()));
			//std::cout << number << "  ";
		}
		//std::cout << std::endl;
		// then insert the pair inside the map
		this->subRank.insert(pa);
		sstr.clear();
	}


}


void SubRankCmp::printRank() {

	for (auto const &ent1 : this->subRank) {
		std::cout << "ID :: " << ent1.first << " rank :: ";

		for (size_t j = 0; j < ent1.second.size(); j++)
			std::cout << ent1.second.at(j) << " | ";

		std::cout << std::endl;

	}

}

void SubRankCmp::compare(std::string outputFile, const RankPerImg & rank,int nbImg=-1,int inter=-1) {

	double id, sizeR , interCompare ;
	double percent;
	std::vector<int> r;
	std::vector<int> notInS;
	std::ofstream myfile;
	myfile.open(outputFile);
	

	for (auto const &ent1 : this->subRank) {

		id = ent1.first;
		myfile << "IDimg ," << id ;

		if (nbImg < 0)
			sizeR = ent1.second.size();
		else
			sizeR = nbImg;

		if (inter < 0)
			interCompare = ent1.second.size();
		else
			interCompare = inter;

		for (size_t j = 0; j < sizeR; j++)
			if (!rank.inRank(id, interCompare, ent1.second.at(j)) )
				notInS.push_back(ent1.second.at(j));

		//std::cout << "percent" << (sizeR - notInS.size())/sizeR << "  ";
		percent = ((sizeR - notInS.size()) / sizeR) * 100;
		myfile << ", percent found, " << percent << " % ," << "List not found : ";

		for (size_t i = 0; i < notInS.size(); i++)
			myfile << "," << notInS.at(i) ;

		myfile << " , List : ";
		for (size_t i = 0; i < sizeR; i++)
		{
			myfile << "," << rank.getId(id,i) ;
		}
		
		myfile << std::endl;
		notInS.clear();

	}

	
	myfile.close();




}


// we take the first nbImg distance of each line of the rank
// if those distances belongs to Img in the subjective classification then it's good
// we then do the average (image in the classication /  total )  
double  SubRankCmp::compareReversed(std::ofstream & myfile,std::string outputFile, const RankPerImg & rank,int nbImg=-1) {

	double id, sizeR;
	double percent;
	double percentsum = 0;
	int img;
	std::vector<int> r;
	std::vector<int> notInS;
	
	myfile << outputFile;
	myfile << std::endl;
	
	// we get the human classification for each img
	for (auto const &ent1 : this->subRank) {

		// get the name of the image we are working with 
		id = ent1.first;
		myfile << id;

		if (nbImg < 0 && ent1.second.size() > nbImg)
			sizeR = ent1.second.size() / 2;
		else
			sizeR = nbImg;

		for (size_t j = 0; j < sizeR; j++) {

			// we get the img name of the sizeR img closest to the Id img 

			img = rank.getId(id, j);

			// if it's not in it we put in a list of id that we didn't found
			if (!(std::find(ent1.second.begin(), ent1.second.end(), img) != ent1.second.end()))
				notInS.push_back(img);
		}
			


		// average for one img
		percent = ((sizeR - notInS.size()) / sizeR) * 100;

		// sum of the average in the classfication
		percentsum += percent;
		myfile << "," << percent << ","<< "List not found : ";

		
		for (size_t i = 0; i < notInS.size(); i++)
			myfile << "," << notInS.at(i);

		myfile << " , List used : ";
		for (size_t i = 0; i < sizeR; i++)
		{
			myfile << "," << rank.getId(id, i);
		}
		
		myfile << std::endl;
		
		notInS.clear();

	}
	// the average of the classification
	myfile << "Average  ," << percentsum / subRank.size() ;
	myfile << std::endl;
	myfile << std::endl;

	return (percentsum / subRank.size());


}