#include "headers/deblur.h"

ImagePNG* ImageProcess::refImage = new ImagePNG();

Deblur::Deblur(): Command("deblur","","","Deblur"), population() {}

Deblur::~Deblur(){
	for (unsigned int i=0; i<population.size(); i++)
		delete population[i];
}

Deblur::Deblur(Deblur* pDeblur): Command(pDeblur), population(pDeblur->population) {}

Deblur::Deblur(string pStandAlone, string pParameter, string pNormal, string pDescription): Command(pStandAlone,pParameter,pNormal,pDescription), population() {}

Deblur::Deblur(const Deblur &pDeblur) : Command(pDeblur), population() {
	population.clear();
	for (unsigned int i=0; i<pDeblur.population.size(); i++)
		population.push_back(pDeblur.population[i]);
}

const Deblur &Deblur::operator =(const Deblur &pDeblur){
	if ( &pDeblur != this ) {
		standAlone = pDeblur.standAlone;
		parameter = pDeblur.parameter;
		normal = pDeblur.normal;
		description = pDeblur.description;
		for (unsigned int i=0; i<population.size(); i++)
			population[i] = pDeblur.population[i];
	}
	return *this;
}

vector<FilterFitness*> Deblur::getPopulation(){
	return population;
}

bool Deblur::isValid(vector<string> pArgParam){
unused(pArgParam);
if (pArgParam.size() == 0) return true;
else return false;
}

void Deblur::run(vector<string> pArgParam,string input, string output){
	unused(pArgParam);
	ImagePNG* img = new ImagePNG();
	img->load(input);
	double start = Data::get_time();
	img = deblur(img);
	if (Data::CHRONO)	cout << description<<" effectue en " << 1000*(Data::get_time() - start)<<" ms"<<endl;
	img->save(output);
}

ImagePNG* Deblur::deblur(ImagePNG* img) {
	cout << "Generation de l'image de reference ..." << endl;
	createRefImage(ImageProcess::autoShrink(ImageProcess::autoResize(img,testMin(img->getHeight(),img->getWidth()))));
	cout << "Application de l'algorithme genetique ..." << endl;
	FilterFitness* blur = algoGenetique(ImageProcess::autoShrink(ImageProcess::autoResize(img,testMin(img->getHeight(),img->getWidth()))));
	cout << "Application de la deconvolution ..." << endl;
	img = blur->applyDeconvolution(img);
	return img;
}

void Deblur::createRefImage(ImagePNG* img){
	ImageProcess::refImage->load("refImage.png");
	ImageProcess::refImage = ImageProcess::autoResize(ImageProcess::refImage,img->getHeight(),img->getWidth());
}

FilterFitness* Deblur::algoGenetique(ImagePNG* img){
	cout << "Generation de la population ..." << endl;
	generation(img);
		cout << "Le filtre de flou le plus optimal est " << endl;
		bestFilter()->display();
	while (bestFilter()->getAdaptation()<90){
		cout << "Recherche d'un autre filtre plus optimal ..." << endl;
		cout << "Selection par adaptation ..." << endl;
		selectionAdaptation(img);
		cout << "Crossover ..." << endl;
		crossover(img);
		cout << "Mutation ..." << endl;
		mutation(img);
	}
	return bestFilter();
}

void Deblur::allUpdate(const ImagePNG* img){
	for (unsigned int i=0;i<population.size();i++){
		population[i]->update(img);
	}
}

void Deblur::display(){
	for (unsigned int i=0;i<population.size();i++){
		population[i]->display();
	}
}

void Deblur::generation(const ImagePNG* img){
	double randomAngle;
	double randomDistance;
	for (int i=0;i<NB_POPULATION;i++){
		randomAngle = rand()%360-180;
		randomDistance = rand()%MAX_DIST;
		FilterFitness* filter = new FilterFitness((int)randomAngle,(int)randomDistance);
		filter->update(img);
		population.push_back(filter);
	}
}

void Deblur::selectionRandom(const ImagePNG* img){
	int cpt = (int)(population.size()/2);
	vector<FilterFitness*> populationNew;
	double randomAngle;
	double randomDistance;
	int random;
	for (int i=0;i<cpt;i++){
		random = (int)(rand()%population.size());
		populationNew.push_back(population[random]);
		population.erase(population.begin()+random);
	}
	for (int i=0;i<cpt;i++){
		randomAngle = rand()%360-180;
		randomDistance = rand()%MAX_DIST;
		FilterFitness* filter = new FilterFitness((int)randomAngle,(int)randomDistance);
		filter->update(img);
		populationNew.push_back(filter);
	}
	for (unsigned int i=0;i<population.size();i++) population.erase(population.begin());
	population = populationNew;
}

void Deblur::selectionAdaptation(const ImagePNG* img){
	double totalAdaptation = 0;
	double randomAngle;
	double randomDistance;
	int cpt = (int)(population.size()/2);
	vector<FilterFitness*> populationNew;
	for (int j=0;j<cpt;j++){
		totalAdaptation = 0;
		for (unsigned int i=0;i<population.size();i++)
			totalAdaptation += population[i]->getAdaptation();
		int random = (int)(rand()%(int)totalAdaptation);
		int i = 0;
		if (totalAdaptation == 0) i = (int)(rand()%population.size())+1;
		while (random>0){
			random = random-population[i]->getAdaptation();
			i++;
		}
		populationNew.push_back(population[i-1]);
		population.erase(population.begin()+i-1);
	}
	for (int i=0;i<cpt;i++){
		randomAngle = rand()%360-180;
		randomDistance = rand()%MAX_DIST;
		FilterFitness* filter = new FilterFitness((int)randomAngle,(int)randomDistance);
		filter->update(img);
		populationNew.push_back(filter);
	}
	for (unsigned int i=0;i<population.size();i++) population.erase(population.begin());
	population = populationNew;
}

void Deblur::crossover(const ImagePNG* img){
	vector<FilterFitness*> populationNew;
	while (population.size()!=0){
		if (population.size()>1 && rand()%100 <= CROSSOVER){
			int rankFilter = (int)(rand()%(population.size()-1)+1);
			double rankDistance = rand()%100;
			
			double newDistanceA1 = population[0]->getDistance()*rankDistance/100;
			double newDistanceB1 = population[rankFilter]->getDistance()*rankDistance/100;
			double newDistanceA2 = population[0]->getDistance()-newDistanceA1;
			double newDistanceB2 = population[rankFilter]->getDistance()-newDistanceB1;
			
			double newDistanceCI = FilterFitness::getDistI(population[0]->getAngle(),newDistanceA1)+FilterFitness::getDistI(population[rankFilter]->getAngle(),newDistanceB2);
			double newDistanceCJ = FilterFitness::getDistJ(population[0]->getAngle(),newDistanceA1)+FilterFitness::getDistJ(population[rankFilter]->getAngle(),newDistanceB2);
			double newDistanceDI = FilterFitness::getDistI(population[0]->getAngle(),newDistanceA2)+FilterFitness::getDistI(population[rankFilter]->getAngle(),newDistanceB1);
			double newDistanceDJ = FilterFitness::getDistJ(population[0]->getAngle(),newDistanceA2)+FilterFitness::getDistJ(population[rankFilter]->getAngle(),newDistanceB1);
			
			double newDistanceC = sqrt(newDistanceCI*newDistanceCI+newDistanceCJ*newDistanceCJ);
			double newDistanceD = sqrt(newDistanceDI*newDistanceDI+newDistanceDJ*newDistanceDJ);
			
			double newAngleC;
			double newAngleD;
			if (newDistanceC == 0) newAngleC = 0;
			else newAngleC = 180*acos(newDistanceCI/newDistanceC)/M_PI;
			if (newDistanceD == 0) newAngleD = 0;
			else newAngleD = 180*acos(newDistanceDI/newDistanceD)/M_PI;
			
			if (newDistanceCI < 0) newAngleC = -newAngleC;
			if (newDistanceDI < 0) newAngleD = -newAngleD;
			
			FilterFitness* filter1 = new FilterFitness((int)newAngleC, (int)newDistanceC);
			filter1->update(img);
			FilterFitness* filter2 = new FilterFitness((int)newAngleD, (int)newDistanceD);
			filter2->update(img);
			populationNew.push_back(filter1);
			populationNew.push_back(filter2);
			population.erase(population.begin());
			population.erase(population.begin()+rankFilter-1);
		}
		else{
			populationNew.push_back(population[0]);
			population.erase(population.begin());
		}
	}
	population.clear();
	for (unsigned int i=0;i<populationNew.size();i++) population.push_back(populationNew[i]);
}

void Deblur::mutation(const ImagePNG* img){
	double randomAngle;
	double randomDistance;
	for(unsigned int i=0; i<population.size();i++){
		if (rand()%100 <= MUTATION){
			randomAngle = rand()%360;
			randomDistance = rand()%MAX_DIST;
			if (rand()%100 < 50) {
				population[i]->setAngle((int)randomAngle);
				population[i]->update(img);
				}
			else {
				population[i]->setDistance((int)randomDistance);
				population[i]->update(img);
			}
		}
	}
}

FilterFitness* Deblur::bestFilter(){
	if (population.size()==0) return NULL;
	else{
		int rank = 0;
		for (unsigned int i=0;i<population.size();i++){
			if (population[i]->getAdaptation()>population[rank]->getAdaptation()) rank = i;
		}
		return population[rank];
	}
}
