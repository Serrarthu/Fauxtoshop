#include "headers/filter.h"

Filter::Filter (): matrix(), factor(1), bias(0){}

Filter::Filter (Matrix* m, double f, double b): matrix(m), factor(f), bias(b){}

Filter::Filter (double f, double b): matrix(), factor(f), bias(b){}

ImagePNG* Filter::apply(ImagePNG* img){
	#pragma omp parallel for schedule(static) num_threads(Data::NB_THREADS)
	for(int x = 0; x < (signed)img->getHeight(); x++)
	{
		for(int y = 0; y < (signed)img->getWidth(); y++)
		{
			double red = 0.0, green = 0.0, blue = 0.0;
			for(int filterX = 0; filterX < matrix->getColumns(); filterX++)
			{
				for(int filterY = 0; filterY < matrix->getRows(); filterY++)
				{
					int imageX = (int((x + filterX + img->getHeight()))) % (img->getHeight());
					int imageY = (int((y + filterY + img->getWidth()))) % (img->getWidth());
					red += img->red(imageX, imageY) * ((*matrix)(filterX,filterY));
					green += img->green(imageX,imageY) * ((*matrix)(filterX,filterY));
					blue += img->blue(imageX,imageY) *((*matrix)(filterX,filterY));
				}
			}	
			img->red(x,y) = (int)testMin(testMax(factor * red + bias, 0), 255);
			img->green(x,y) = (int)testMin(testMax(factor * green + bias, 0), 255);
			img->blue(x,y) = (int)testMin(testMax(factor * blue + bias, 0), 255);
		}
	}
	return img;
}

int Filter::get(int i, int j){
	return matrix->get(i,j);
}

void Filter::set(int i, int j, int v){
	matrix->set(i,j,v);
}

Matrix* Filter::getMatrix(){
	return matrix;
}

double Filter::getFactor(){
	return factor;
}
void Filter::setMatrix(Matrix* m){
	matrix = m;
}

void Filter::setFactor(double f){
	factor = f;
}
