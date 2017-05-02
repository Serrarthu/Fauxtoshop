#include "headers/color.h"


Color::Color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha) {
	components[0] = red;
	components[1] = green;
	components[2] = blue;
	components[3] = alpha;
}

Color::Color (ImagePNG* img, int i, int j){
	components[0] = img->red(i,j);
	components[1] = img->green(i,j);
	components[2] = img->blue(i,j);
	components[3] = img->alpha(i,j);
}

Color& Color::operator=(Color &droit) {
	components[0] = droit.get()[0];
	components[1] = droit.get()[1];
	components[2] = droit.get()[2];
	components[3] = droit.get()[3];
	return *this;
}

void Color::set(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha) {
	components[0] = red;
	components[1] = green;
	components[2] = blue;
	components[3] = alpha;
}

unsigned int* Color::get(){
	return components;
}

void Color::fill(ImagePNG* img, int x, int y){
	img->red(x,y)=components[0];
	img->green(x,y)=components[1];
	img->blue(x,y)=components[2];
	img->alpha(x,y)=components[3];
}

int Color::toGrey(){return components[0]*luminance[0] + components[1]*luminance[1] + components[2]*luminance[2];}
