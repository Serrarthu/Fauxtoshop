#include "headers/fft.h"
#include <cmath>

#define PI 3.1415926535897932384626433832795


int CFFT::X=0;

ImagePNG* CFFT::Fourier(const ImagePNG* img)
{
	int c=img->getWidth();
	int l=img->getHeight();

	if (!img || c < 1 || l<1 || c & (c - 1) || l & (l - 1))	return NULL;
	return Perform(img);
}

ImagePNG* CFFT::Cepstre(const ImagePNG* img)
{
	int c=img->getWidth();
	int l=img->getHeight();

	if (!img || c < 1 || l<1 || c & (c - 1) || l & (l - 1)) return NULL;
	return Perform(Scale(Perform(img)));
}

ImagePNG* CFFT::Perform(const ImagePNG* img)
{
	int l=img->getHeight();
	int c=img->getWidth();
	int N=c*l;
	int i,j;

	ImagePNG* even = new ImagePNG();
	if (N == 1) {
		even = new ImagePNG(*img);
		return even;
	}
	even->newImage(l/2,c/2);
	for (i = 0; i < l/2; i++)
	{
		for (j = 0; j < c/2; j++)
		{
			even->red(i,j)=img->red(2*i, 2*j);
			even->green(i,j)=img->green(2*i,2*j);
			even->blue(i,j)=img->blue(2*i,2*j);
		}
	
	}
	ImagePNG* q = Perform(even);

	ImagePNG* odd = even;
	for (i = 0; i < l/2; i++)
	{
		for (j = 0; j < c/2; j++)
		{
			odd->red(i,j)=img->red(2*i+1,2*j+1);
			odd->green(i,j)=img->green(2*i+1,2*j+1);
			odd->blue(i,j)=img->blue(2*i+1,2*j+1);
		}
	
	}
	ImagePNG* r = Perform(odd);

	ImagePNG* y = new ImagePNG();
	y->newImage(l,c);
	double kth;
	for (i = 0; i < l/2; i++)
	{
		for(j =0; j<c/2; j++)
		{
			kth = -2 * i*j* PI / N;
			complex wk(cos(kth), sin(kth));
			
			complex cprod_red=wk*complex(r->red(i,j));
			complex cprod_green=wk*complex(r->green(i,j));
			complex cprod_blue=wk*complex(r->blue(i,j));
			
			y->red(i,j)=int(q->red(i,j)+cprod_red.re());
			y->green(i,j)=int(q->green(i,j)+cprod_green.re());
			y->blue(i,j)=int(q->blue(i,j)+cprod_blue.re());

			y->red(i+l/2,j+c/2)=int(q->red(i,j)-cprod_red.re());
			y->green(i+l/2,j+c/2)=int(q->green(i,j)-cprod_green.re());
			y->blue(i+l/2,j+c/2)=int(q->blue(i,j)-cprod_blue.re());
		}
	}
	return y;
}


ImagePNG* CFFT::Scale(const ImagePNG* img)
{
	img->save("img/testicool.png");
	int l=img->getHeight();
	int c=img->getWidth();

	ImagePNG* y = new ImagePNG();
	y->newImage(c,l);

	for (int i = 0; i < l; i++)
	{
		for (int j=0; j<c;j++)
		{
			y->red(i,j)=int(log(img->red(i,j)));
			y->green(i,j)=int(log(img->green(i,j)));
			y->blue(i,j)=int(log(img->blue(i,j)));
		}
	}
	return y;

}


