#ifndef MATRIX_H
#define MATRIX_H

class Matrix //Defining the Matrix Class
{
public: 
	//Declare member functions.
	Matrix (int sizeR, int sizeC, double*);
	Matrix (int sizeR, int sizeC);
	Matrix (int SizeR, int sizeC, double val);
	Matrix (const Matrix& A);
	Matrix();
	~Matrix(); //Matrix Destructor

	Matrix operator *(const Matrix& A);
	Matrix& operator =(const Matrix& rhs);
	Matrix operator +(const Matrix& A);
	Matrix operator -(const Matrix& A);
	double operator () (int i, int j);

	double sum();
	double get(int i, int j) const;
	double display(int i, int j) const;
	void set(int i, int j, double val);

	Matrix Matrix ::setBlock(int startR, int startC, Matrix& A);
	Matrix Matrix ::getBlock(int startR, int endR, int startC,int endC); 
	
	int Matrix ::getR() const;
	int Matrix ::getC() const;
	
protected: 
	int R; //Number of Rows
	int C; //Number of columns 
	double* data; //pointer to array.
};

#endif