#ifndef __MASK_H__
#define __MASK_H__

#include "image_png.h"
#include "color.h"
#include <vector>
#include <iostream>
#include "../../structure/headers/data.h"
#include <omp.h>


enum Shape {SQUARE,
		ROW,
		COLUMN };


class Mask
{
	public:
		Mask (Shape s, int order);
		Mask(const Mask&);
		Mask& operator=(const Mask&);
		virtual ~Mask (){};
		
		int moveTo(ImagePNG* img, int i, int j);
		int moveToNext(ImagePNG* img);
		void transform(ImagePNG* img, void (&f)(ImagePNG*, int, int));
		void fill(ImagePNG* img, Color* c);
		vector< vector<int> > getMask();

	private:
		int cornerX = 0;
		int cornerY = 0;
		Shape shape = Shape::SQUARE;
		int order = 0;
		vector< vector<int> > mask;
		
		int generate();
		int generateSQUARE();
		int generateROW();
		int generateCOLUMN();
};

#endif /* __MASK_H__ */
