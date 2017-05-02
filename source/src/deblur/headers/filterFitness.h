#ifndef FILTERFITNESS_H_
#define FILTERFITNESS_H_
#include <iostream>
#include <algorithm>
#include <math.h>
#include "../../base/headers/filter.h"
#include "imageProcess.h"
#include "fft.h"

using namespace std;

class FilterFitness : public Filter {

public:
	FilterFitness();
	FilterFitness(double a, double d);
	FilterFitness(ImagePNG* img);
	FilterFitness(double a, double d, ImagePNG* img);
	FilterFitness(const FilterFitness &f);
	virtual ~FilterFitness(){};
	virtual void display();
	const FilterFitness &operator =(const FilterFitness &f);
	void update(const ImagePNG* img);
	double getAngle(){return angle;};
	double getDistance(){return distance;};
	double getAdaptation(){return adaptation;};
	void setAngle(double a){angle = a;};
	void setDistance(double d){distance = d;}
	double getDistI();
	double getDistJ();
	static double getDistI(double a, double d){return d*sin(M_PI*a/180);};
	static double getDistJ(double a, double d){return d*cos(M_PI*a/180);};
	ImagePNG* applyDeconvolution(const ImagePNG* img);
private:
	double angle;
	double distance;
	double adaptation;
	double fitness(const ImagePNG* img);
	void convertMatrix();
	void convertMatrix(int size);
};
#endif /* FILTERFITNESS_H_ */
