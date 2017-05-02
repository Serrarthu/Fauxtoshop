#ifndef _COLOR_H_
#define _COLOR_H_

#include "image_png.h"


using namespace std;

const double luminance[3] = {0.299, 0.587, 0.114};

class Color
{
	public:
		Color();
		Color& operator=(Color &droit);
		Color (unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);
		Color (ImagePNG* img, int i, int j);
		virtual ~Color (){};
		
		void set(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);
		unsigned int* get();
		
		void fill(ImagePNG* img,int x, int y);
		int toGrey();
	private:
		unsigned int components[4];
};


#endif
