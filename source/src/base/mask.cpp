#include "headers/mask.h"

//on n'affiche pas les warning du flag -Weffc++ car sinon on a un warning de type : warning: ‘Mask::mask’ should be initialized in the member initialization list
//qui complique l'initialisation et l'utilisation de vector sans être pertinenent étant donné que vector a deja un constructeur par defaut
#pragma GCC diagnostic ignored "-Weffc++"

Mask::Mask(Shape s, int order) {
	shape=s;
	this->order=order;
	cornerX=0;
	cornerY=0;
	int size;
	switch(s) {
		case Shape::SQUARE:	size=order*order;
						break;
		default:			size=order;
						break;
	}
	mask.assign(size,vector<int>(2));
	generate();
}

vector< vector<int> > Mask::getMask() {return mask;}


void Mask::transform(ImagePNG* img, void (&f)(ImagePNG*, int, int)) {
	for (int i=0; i<(signed)mask.size(); i++) {
		if (mask[i][0] < (signed)img->getHeight() && mask[i][0] >=0 && mask[i][1] < (signed)img->getWidth() && mask[i][1] >= 0)
			(*f)(img, mask[i][0], mask[i][1]);
	}
}

void Mask::fill(ImagePNG* img, Color* c) {
	#pragma omp parallel for schedule(static) num_threads(Data::NB_THREADS)
	for (int i=0; i<(signed)mask.size(); i++) {
		if (mask[i][0] < (signed)img->getHeight() && mask[i][0] >=0 && mask[i][1] < (signed)img->getWidth() && mask[i][1] >= 0)
			c->fill(img, mask[i][0], mask[i][1]);
	}
}

int Mask::moveTo(ImagePNG* img, int i, int j) {
	if (i >= (signed)img->getHeight() || i< -order +1 || j>= (signed)img->getWidth() || j<-order+1) return -1;
	else {
		cornerX=i;
		cornerY=j;
		generate();
		return 1;
	}
}

int Mask::moveToNext(ImagePNG* img) {
	int newCornerX = cornerX;
	int newCornerY = cornerY + 1;
	
	if (newCornerY >= (signed)img->getWidth()) {
		newCornerY = 0;
		newCornerX += 1;
	}
	
	if (newCornerX >= (signed)img->getHeight()) return -1;
	
	cornerX = newCornerX;
	cornerY = newCornerY;
	return generate();
}

int Mask::generate() {
	switch(shape) {
		case Shape::SQUARE:	return generateSQUARE();
						break;
		case Shape::ROW:		return generateROW();
						break;
		case Shape::COLUMN:	return generateCOLUMN();
						break;
		default:			return -1;
						break;
	}
}

int Mask::generateSQUARE() {
	int count=0;
	for(int i = 0; i<order; i += 1)
	{
		for (int j = 0; j < order; j += 1)
		{
			mask[count][0]=cornerX+i;
			mask[count][1]=cornerY+j;
			count++;
		}
	}
	return 1;
}

int Mask::generateROW() {
	for(int i = 0; i<order; i += 1)
	{
		mask[i][0]=cornerX;
		mask[i][1]=cornerY+i;
	}
	return 1;
}

int Mask::generateCOLUMN() {
	for(int i = 0; i<order; i += 1)
	{
		mask[i][0]=cornerX+i;
		mask[i][1]=cornerY;
	}
	return 1;
}
