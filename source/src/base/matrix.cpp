#include "headers/matrix.h"

Matrix::Matrix() {
	Matrix(0,0);
}

Matrix::Matrix(int r, int c){
	rows=r;
	columns=c;
	matrix = new double * [r];
	for (int i=0; i<r; ++i) {
		matrix [i] = new double [c];
		for (int j=0; j<c; ++j) 
			matrix[i][j] = 0;
	}
}

Matrix::Matrix(int r, int c, int* m) {
	rows=r;
	columns=c;
	matrix = new double * [r];
	for(int i=0; i<r; i++) {
		matrix [i] = new double [c];
		for (int j =0; j<c; j++)
			matrix[i][j]=m[c*i+j];
	}
}

Matrix::~Matrix(){
	if (matrix) { 
		for(int i=0; i<rows ; i++) {delete matrix[i];}
		delete [] matrix;
	} 
}

Matrix::Matrix(const Matrix &m)
{
	if ( &m != this ) {
		rows=m.rows;
		columns=m.columns;
		matrix = new double * [rows];
		for (int i=0; i<rows; ++i) {matrix [i] = new double [columns];}
		for(int i = 0; i < rows; i++)
			for(int j = 0; j < columns; j++)
				matrix[i][j] = m.matrix[i][j];
	}
}

const Matrix &Matrix::operator =(const Matrix &m){
	if ( &m != this ) {
		rows=m.rows;
		columns=m.columns;
		matrix = new double * [rows];
		for (int i=0; i<rows; ++i) {matrix [i] = new double [columns];}
		for(int i = 0; i < rows; i++)
			for(int j = 0; j < columns; j++)
				matrix[i][j] = m.matrix[i][j];
	}
	return *this;
}


void Matrix::display(){
	cout<<"-----------------------------";
	cout << endl;
	for(int i=0; i<rows ; i++) {
		for(int j=0; j<columns ; j++) {cout<< (*this)(i,j) <<"  ";}
		cout << endl;
	}
	cout<<"-----------------------------";
	cout << endl;
}

double & Matrix::operator()(unsigned short int i, unsigned short int j)
{
	if (i>=rows && j>=columns) cout << "offset"<<endl;
	return matrix[i][j];
}

double Matrix::operator()(unsigned short int i, unsigned short int j) const
{
	if (i>=rows && j>=columns) cout << "offset"<<endl;
	return matrix[i][j];
}

double Matrix::get(int i, int j){
	return matrix[i][j];
}

void Matrix::set(int i, int j, double v){
	matrix[i][j] = v;
}
