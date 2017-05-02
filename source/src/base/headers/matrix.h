#ifndef MATRIX_H_
#define MATRIX_H_
#include <iostream>
using namespace std;

class Matrix{

public:
	Matrix();
	Matrix(int r , int c);
	Matrix(const Matrix &m);
	Matrix(int r, int c, int* m);
	~Matrix();
	void display();
	const Matrix &operator =(const Matrix &m);
	double operator()(unsigned short int i, unsigned short int j) const;
	double &operator()(unsigned short int i, unsigned short int j);
	double get(int i, int j);
	void set(int i, int j, double v);
	int getRows(){return rows;};
	int getColumns(){return columns;};
	void init(int r, int c, int* m);
private:
	int rows = 0;
	int columns = 0;
	double** matrix = NULL;
};
#endif /* MATRICE_H_ */
