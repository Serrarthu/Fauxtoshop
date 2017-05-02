#ifndef _FFT_H_
#define _FFT_H_

#include "../../base/headers/complex.h"
#include "../../base/headers/image_png.h"
#include <cstdlib>

using namespace std;

class CFFT
{
public:
	static ImagePNG* Fourier(const ImagePNG* img);
	static ImagePNG* Cepstre(const ImagePNG* img);
	static int X;

protected:
	static ImagePNG* Perform(const ImagePNG* img);
	static ImagePNG* Scale(const ImagePNG* img);
};

#endif
