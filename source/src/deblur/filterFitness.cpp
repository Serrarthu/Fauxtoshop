#include "headers/filterFitness.h"

FilterFitness::FilterFitness(): Filter(), angle(0), distance(0), adaptation(0) {
	convertMatrix();
}

FilterFitness::FilterFitness(ImagePNG* img): Filter(), angle(0), distance(0), adaptation(0) {
	convertMatrix();
	update(img);
}

FilterFitness::FilterFitness(double a, double d): angle(a), distance(d), adaptation(0) {
	convertMatrix();
}

FilterFitness::FilterFitness(double a, double d, ImagePNG* img): angle(a), distance(d), adaptation(0) {
	convertMatrix();
	update(img);
}

FilterFitness::FilterFitness(const FilterFitness &f): Filter(f.matrix,f.factor,f.bias), angle(f.angle), distance(f.distance), adaptation(f.adaptation) {
	convertMatrix();
}

const FilterFitness &FilterFitness::operator =(const FilterFitness &f){
	angle = f.angle;
	distance = f.distance;
	matrix = f.matrix;
	factor = f.factor;
	bias = f.bias;
	adaptation = f.adaptation;
	return *this;
}


void FilterFitness::update(const ImagePNG* img){
	convertMatrix();
	fitness(img);
}

double FilterFitness::getDistI(){
	return distance*sin(M_PI*angle/180);
}

double FilterFitness::getDistJ(){
	return distance*cos(M_PI*angle/180);
}

double FilterFitness::fitness(const ImagePNG* img){
	ImagePNG* newImg = new ImagePNG(*img);
	ImagePNG* refImg = new ImagePNG(*ImageProcess::refImage);
	apply(refImg);
	newImg = ImageProcess::cepstre(newImg);
	refImg = ImageProcess::cepstre(refImg);
	adaptation = (int)(100*ImageProcess::compareImages(newImg,refImg)/(255*3*newImg->getHeight()*newImg->getWidth()));
	adaptation = (int)(rand()%90);
	return adaptation;
}

void FilterFitness::display(){
	cout << "Angle = " << angle << "\nDistance = " << distance << "\nFactor = " << factor << "\nBias = " << bias << "\nAdaptation = " << adaptation << endl;
	matrix->display();
}

void FilterFitness::convertMatrix(){

	double distI = getDistI();
	double distJ = getDistJ();
	
	if ((int)abs(distI)<=1 && (int)abs(distJ)<=1){
		matrix = new Matrix(1,1);
		matrix->set(0,0,1);
		factor = 1;
	}
	else{
	int dimension = (int)max(abs(distI),abs(distJ));
	matrix = new Matrix(dimension,dimension);
	
	double iterI = (dimension/2) - (distI/2);
	double iterJ = (dimension/2) - (distJ/2);
	if (iterI<0) iterI = 0;
	if (iterI>=dimension) iterI = dimension-1;
	if (iterJ<0) iterJ = 0;
	if (iterJ>=dimension) iterJ = dimension-1;
	
	factor = 0;
	while ( ( (int)iterI!=(int)((dimension/2) - (distI/2)+distI) || (int)iterJ!=(int)((dimension/2) - (distJ/2)+distJ) ) && 
		(int)iterI>=0 && (int)iterJ>=0 && (int)iterI<dimension && (int)iterJ<dimension ) {
		matrix->set((int)iterI,(int)iterJ,1);
		factor++;
		if (distI>0){
			if (distJ==0 || distI/distJ<-1 || distI/distJ>1 ) iterI++;
			else iterI += abs(distI/distJ);
		}
		else if (distI<0){
			if (distJ==0 || distI/distJ<-1 || distI/distJ>1 ) iterI--;
			else iterI -= abs(distI/distJ);
		}
		if (distJ>0){
			if (distI==0 || distJ/distI<-1 || distJ/distI>1 ) iterJ++;
			else iterJ += abs(distJ/distI);
		}
		else if (distJ<0){
			if (distI==0 || distJ/distI<-1 || distJ/distI>1 ) iterJ--;
			else iterJ -= abs(distJ/distI);
		}
		}
	factor = 1/factor;
	}
	
}

void FilterFitness::convertMatrix(int size){
	double distI = getDistI();
	double distJ = getDistJ();
	
	if (distI<=1 && distI>=-1 && distJ<=1 && distJ>=-1){
		matrix = new Matrix(1,1);
		matrix->set(0,0,1);
		factor = 1;
	}
	else{
	int dimension = size;
	matrix = new Matrix(dimension,dimension);
	
	double iterI = (dimension/2) - (distI/2);
	double iterJ = (dimension/2) - (distJ/2);
	if (iterI<0) iterI = 0;
	if (iterI>=dimension) iterI = dimension-1;
	if (iterJ<0) iterJ = 0;
	if (iterJ>=dimension) iterJ = dimension-1;
	
	factor = 0;
	while ( ( (int)iterI!=(int)((dimension/2) - (distI/2)+distI) || (int)iterJ!=(int)((dimension/2) - (distJ/2)+distJ) ) && 
		(int)iterI>=0 && (int)iterJ>=0 && (int)iterI<dimension && (int)iterJ<dimension ) {
		matrix->set((int)iterI,(int)iterJ,1);
		factor++;
		if (distI>0){
			if (distJ==0 || distI/distJ<-1 || distI/distJ>1 ) iterI++;
			else iterI += abs(distI/distJ);
		}
		else if (distI<0){
			if (distJ==0 || distI/distJ<-1 || distI/distJ>1 ) iterI--;
			else iterI -= abs(distI/distJ);
		}
		if (distJ>0){
			if (distI==0 || distJ/distI<-1 || distJ/distI>1 ) iterJ++;
			else iterJ += abs(distJ/distI);
		}
		else if (distJ<0){
			if (distI==0 || distJ/distI<-1 || distJ/distI>1 ) iterJ--;
			else iterJ -= abs(distJ/distI);
		}
		}
	factor = 1/factor;
	}
}

ImagePNG* FilterFitness::applyDeconvolution(const ImagePNG* img){
	ImagePNG* newImg = new ImagePNG(*img);
	return newImg;
}
