#include "RankPerImg.h"





// write the result of a rank in a file called name
void writeRankOnFile(std::string name, RankPerImg rank) {
	std::ofstream myfile;
	myfile.open(name);
	myfile << "IDimg ,";
	for (size_t i = 0; i < 10; i++)
	{
		myfile << " rank " << i << "," << " distance " << i << ",";
	}
	myfile << std::endl;
	myfile << rank;
	myfile.close();
}




RankPerImg::RankPerImg(std::string name){
	this->nameRank = name;
	this->ranks =  std::vector<std::vector<Distance>*>();
	this->normed = false;
}

RankPerImg::RankPerImg(std::vector<std::vector<Distance> * >  &r) {
	this->ranks = r;
}


RankPerImg::RankPerImg(){
	this->ranks =  std::vector<std::vector<Distance>*>();
	this->normed = false;
}


RankPerImg::~RankPerImg(){
	//for (size_t i = 0; i < this->ranks->size(); i++)
//		free(this->ranks->at(i));
//	free(this->ranks);
	this->normed = false;

}


void RankPerImg::sortRanks(){
	for (size_t i = 0; i < this->ranks.size(); i++)
		std::sort(this->ranks.at(i)->begin(), this->ranks.at(i)->end());
}

void RankPerImg::pushBack(std::vector<Distance> * vec) {
	this->ranks.push_back(vec);
}
void RankPerImg::printValue() {
	for (size_t i = 0; i < this->ranks.size(); i++)
	{
		std::cout << "Classement " << i << std::endl;
		for (size_t j = 0; j < this->ranks.at(i)->size(); j++)
		{
			this->ranks.at(i)->at(j).printValue();
		}
	}
}


std::ostream& operator<< (std::ostream& stream, const RankPerImg& r) {

	for (size_t i = 0; i < r.ranks.size(); i++)
	{
		stream << i  ;
		for (size_t j = 0; j < r.ranks.at(i)->size() && j<10 ; j++)
		{
			stream << "," << r.ranks.at(i)->at(j);
		}
		stream << std::endl;
	}
	

	return stream;
}



void RankPerImg::normalisation() {

	if (this->normed)
		return;
	
	double sum,moy,eccart,tmp;
	
	std::vector<Distance> * data;
	for (size_t t = 0; t < ranks.size(); t++)
	{
		sum = 0;
		moy = 0;
		eccart = 0;

		data = ranks.at(t);
		for (size_t i = 0; i < data->size(); i++)
			sum += data->at(i).getValue();
		//std::cout << "sum " << sum;
		moy = sum / data->size();
		//std::cout << " moy " << moy;

		sum = 0;
		for (size_t i = 0; i < data->size(); i++)
			sum += (moy - data->at(i).getValue())*(moy - data->at(i).getValue());
		sum /= data->size();
		eccart = sqrt(sum);
		//std::cout << " eccart " << eccart;
		//std::cout << " value : " << eccart;

		for (size_t i = 0; i < data->size(); i++) {
			tmp = data->at(i).getValue();
			//std::cout << tmp << " / " << (tmp - moy) / eccart << std::endl;

			data->at(i).setValue((tmp - moy) / eccart);
			//std::cout << tmp << " / " << data->at(i).getValue() << std::endl;

		}
		//std::cout << std::endl;
		//system("pause");

	}
	this->normed = true;
	
}



// get a rank CLD and a rank HTD NOT SORTED then create a hybrid rank and write it on file name 
// if we sort them we have to search the matching distance for each image comparaison in all ranks 

void RankPerImg::outputrankHybrid(RankPerImg CLD, RankPerImg HTD, int nbimg, std::vector<std::vector<Distance> * > &container,double ratio) {
	int disCLD;
	int disHTD;


	// change that to change the weight of each distance 

	// just to be sure everything is working
	CLD.printSize();
	HTD.printSize();

	double ratioCLD = (ratio/10);
	double ratioHTD = 1 - (ratio/10);

	// normalisation of the disances
	
	CLD.normalisation();
	HTD.normalisation();
	
	

	for (size_t i = 0; i < nbimg; i++)
	{
		std::vector<Distance> * vecDis = new std::vector<Distance>();
		for (size_t j = 0; j < nbimg - 1; j++)
		{
			if (CLD.getId(i, j) != HTD.getId(i, j))
				std::cout << " ho shit " << CLD.getId(i, j) << " " << HTD.getId(i, j) << std::endl;

			// add the new distance in the vector
			vecDis->push_back(Distance(CLD.getId(i, j), CLD.getValue(i, j)*ratioCLD + ratioHTD*HTD.getValue(i, j)));

		}
		// sort and add the new vector into the rank
		std::sort(vecDis->begin(), vecDis->end());
		this->pushBack(vecDis);
		container.push_back(vecDis);
	}
	// write the rank  in the output file
	//writeRankOnFile(name, *(this));

}


int RankPerImg::getId(int x,int y) const{ 
	return ranks.at(x)->at(y).getidImg(); 
}


bool RankPerImg::inRank(int img, int nb,int id) const{
	//std::cout << "ok" << std::endl;
	for (size_t i = 0; i < nb; i++)
		if (this->ranks.at(img)->at(i).getidImg() == id)
			return true;

	return false;
}

int RankPerImg::getSumDistance() {
	int a = 0;
	for (size_t i = 0; i < this->ranks.size(); i++)

		for (int j = 0; j < this->ranks[i]->size(); j++)
			a += this->ranks[i]->at(j).getValue();

	return a;
	
}

