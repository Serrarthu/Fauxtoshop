#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <cstdlib>
#include <iostream>
#include "../../base/headers/color.h"
#include "../../base/headers/image_png.h"
#include "filterFitness.h"
#include "fft.h"

#include <omp.h>


using namespace std;

class ImageProcess
{
    public:
	static ImagePNG* refImage;
	static ImagePNG* autoEnlarge(const ImagePNG* img);
	static ImagePNG* autoShrink(const ImagePNG* img);
	static ImagePNG* autoResize(const ImagePNG* img, int dimI, int dimJ);
	static ImagePNG* autoResize(const ImagePNG* img, int dim);
	static void findAutoEnlarge(const ImagePNG* img, int* dimI, int* dimJ);
	static void findAutoShrink(const ImagePNG* img, int* dimI, int* dimJ);
	static long double compareImages(const ImagePNG* img1, const ImagePNG* img2);
	static ImagePNG* cepstre(const ImagePNG* img);
};

#endif
