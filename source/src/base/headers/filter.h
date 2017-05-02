#ifndef __FILTER_H__
#define __FILTER_H__

#include <string>
#include <fstream>
#include <sstream>
#include "image_png.h"
#include "matrix.h"
#include "../../structure/headers/data.h"
#include <omp.h>

#define testMin(a, b)  (((a) < (b)) ? (a) : (b))
#define testMax(a, b)  (((a) > (b)) ? (a) : (b))


class Filter
{
	public:
		Filter();
		Filter (double f, double b);
		Filter (Matrix* m, double f, double b);
		virtual ~Filter (){delete matrix;};
		Filter(const Filter &f);
		const Filter &operator =(const Filter &f);
		int get(int i, int j);
		void set(int i, int j, int v);
		Matrix* getMatrix();
		double getFactor();
		void setMatrix(Matrix* m);
		void setFactor(double f);
		ImagePNG* apply(ImagePNG* img);
		virtual void display(){cout<< "factor= "<<factor<<", bias= "<<bias<<endl; matrix->display();};
	protected:
		Matrix* matrix;
		double factor;
		double bias;
	private:
};

#endif /* __FILTER_H__ */

