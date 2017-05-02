#include "headers/imageProcess.h"

ImagePNG* ImageProcess::cepstre(const ImagePNG* img){
	ImagePNG* newImg = new ImagePNG(*CFFT::Cepstre(img));
	return newImg;
}

long double ImageProcess::compareImages(const ImagePNG* img1, const ImagePNG* img2){
	long double cpt = -1;
	if (img1->getWidth() == img2->getWidth() && img1->getHeight() == img2->getHeight()){
		cpt = 0;
		for (unsigned int i=0;i<img1->getHeight();i++)
			for (unsigned int j=0;j<img1->getWidth();j++){
				cpt += abs(img1->red(i,j)-img2->red(i,j))+abs(img1->green(i,j)-img2->green(i,j))+abs(img1->blue(i,j)-img2->blue(i,j));
			}
	}
	return cpt;
}

ImagePNG* ImageProcess::autoEnlarge(const ImagePNG* img){
	unsigned int newWidth = 1;
	unsigned int newHeight = 1;
	while (img->getWidth()>newWidth) newWidth *=2;
	while (img->getHeight()>newHeight) newHeight *=2;
	
	ImagePNG* img2 = new ImagePNG();
	img2->newImage(newHeight,newWidth);
	for (unsigned int i=0;i<img->getHeight();i++)
		for (unsigned int j=0;j<img->getWidth();j++){
				img2->red(i,j) = img->red(i,j);
				img2->green(i,j) = img->green(i,j);
				img2->blue(i,j) = img->blue(i,j);
		}
	return img2;
}

ImagePNG* ImageProcess::autoShrink(const ImagePNG* img){
	unsigned int newWidth = 1;
	unsigned int newHeight = 1;
	while (img->getWidth()>newWidth) newWidth *=2;
	while (img->getHeight()>newHeight) newHeight *=2;
	newWidth /=2;
	newHeight /=2;
	ImagePNG* img2 = new ImagePNG();
	img2->newImage(newHeight,newWidth);
	for (unsigned int i=0;i<img2->getHeight();i++)
		for (unsigned int j=0;j<img2->getWidth();j++){
				img2->red(i,j) = img->red(i,j);
				img2->green(i,j) = img->green(i,j);
				img2->blue(i,j) = img->blue(i,j);
		}
	return img2;
}

void ImageProcess::findAutoEnlarge(const ImagePNG* img, int* dimI, int* dimJ){
	int newWidth = 1;
	int newHeight = 1;
	while ((int)img->getWidth()>newWidth) newWidth *=2;
	while ((int)img->getHeight()>newHeight) newHeight *=2;
	*dimI = newHeight;
	*dimJ = newWidth;
}

void ImageProcess::findAutoShrink(const ImagePNG* img, int* dimI, int* dimJ){
	int newWidth = 1;
	int newHeight = 1;
	while ((int)img->getWidth()>newWidth) newWidth *=2;
	while ((int)img->getHeight()>newHeight) newHeight *=2;
	newWidth /=2;
	newHeight /=2;
	*dimI = newHeight;
	*dimJ = newWidth;
}
ImagePNG* ImageProcess::autoResize(const ImagePNG* img, int dim){
	return autoResize(img,dim,dim);
}

ImagePNG* ImageProcess::autoResize(const ImagePNG* img, int dimI, int dimJ){
	ImagePNG* img2 = new ImagePNG();
	img2->newImage(dimI,dimJ);
	if (img2->getHeight()<img->getHeight())
	for (unsigned int i=0;i<img2->getHeight();i++)
		if (img2->getWidth()<img->getWidth())
		for (unsigned int j=0;j<img2->getWidth();j++){
				img2->red(i,j) = img->red(i,j);
				img2->green(i,j) = img->green(i,j);
				img2->blue(i,j) = img->blue(i,j);
		}
		else
		for (unsigned int j=0;j<img->getWidth();j++){
				img2->red(i,j) = img->red(i,j);
				img2->green(i,j) = img->green(i,j);
				img2->blue(i,j) = img->blue(i,j);
		}
	else
	for (unsigned int i=0;i<img->getHeight();i++)
		if (img2->getWidth()<img->getWidth())
		for (unsigned int j=0;j<img2->getWidth();j++){
				img2->red(i,j) = img->red(i,j);
				img2->green(i,j) = img->green(i,j);
				img2->blue(i,j) = img->blue(i,j);
		}
		else
		for (unsigned int j=0;j<img->getWidth();j++){
				img2->red(i,j) = img->red(i,j);
				img2->green(i,j) = img->green(i,j);
				img2->blue(i,j) = img->blue(i,j);
		}
	return img2;
}
