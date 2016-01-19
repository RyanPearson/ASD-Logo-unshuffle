#include "Matrix.h"
#include <iostream>

using namespace std;

Matrix ::Matrix (int sizeR, int sizeC, double* input_data)
{

	//This Constructor passes by pointer.

	R = sizeR;
	C = sizeC;

	data = new double [R * C];

	for (int i = 0; i < R; i++){
		for(int j = 0; j< C; j++){
			data[i * C + j] = input_data[ i * C + j];
		}
	}
}

Matrix ::Matrix (int sizeR, int sizeC)
{

	//This constructor creates the Matrix object and leaves the data = 0.

	R = sizeR;
	C = sizeC;
	
	data = new double [R * C];

	for(int i = 0; i < R; i++)
	{
		for(int j = 0; j < C; j++)
		{
			data[i * C + j] = 0;
		}
	}
}

Matrix::Matrix (int sizeR, int sizeC, double val) 
{
	//This constructor passes by value.

	R = sizeR;
	C = sizeC;

	data = new double[R * C];

	for (int i = 0; i < R; i++)
	{
		for(int j = 0; j < C; j++)
		{
			data[i * C + j] = val;
		}
	}
}

Matrix ::Matrix(const Matrix &A)
{
	R = A.R;
	C = A.C;
	data = new double[R * C];

	for (int i = 0; i < R; i++){
		for (int j = 0; j < C; j++){
			data[i * C + j] = A.get(i, j);
		}
	}

}

Matrix::~Matrix(){ 
	//cout<<"~Matrix() Destructor is invoked ..."<<endl;
	delete [] data;
}


Matrix Matrix::operator *(const Matrix& A)
{
	double val = 0;
	Matrix B(R, C, val);
	for(int i = 0; i < R; i++)
	{
		for(int j = 0; j < C; j++)
		{
			val = data[ i * C + j] * A.get(i, j);
			B.set(i, j, val);
		}
	}
	return B;
}

Matrix& Matrix::operator =(const Matrix& rhs)
{
	if (this ==&rhs)
	{
		return *this; 
	}
	else
	{
		delete [] data; //Deletes old stored data
		//Then creates the new data and copies it to data

		R = rhs.getR();
		C = rhs.getC();

		data = new double[R*C];

		for (int i = 0; i < R; i++)
		{
			for(int j = 0; j < C; j++)
			{
				set(i, j, rhs.get(i,j));
			}
		}
	return *this;
	}
}

Matrix Matrix::operator +(const Matrix& A) 
{ 
	double val = 0;

	Matrix B(R, C, val);

	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++)
		{
			val = data[i * C + j] + A.get(i, j);
			B.set(i, j, val);
		}
	}
	return B;
}

Matrix Matrix::operator -(const Matrix& A)
{ 
//	cout<<"Matrix::operator- is invoked...." <<endl;
	double val = 0;
	Matrix B(R, C, val);
	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++){
			val = data[i * C + j] - A.get(i, j);
			B.set(i, j, val);
		}
	}
	return B;
}

double Matrix::operator () (int i, int j)
{
 return data[(i * C) + j];
}


double Matrix ::sum()
{
	double Sum = 0;

	for(int i = 0; i <= R * C; i++)
	{
		Sum = Sum + data[i];
	}
	
	return Sum;
}

double Matrix ::get(int i, int j) const
{
	return data[i * C + j];
}

void Matrix ::set(int i, int j, double val)  
{
	 data[i * C + j] = val;
}

Matrix Matrix ::setBlock(int startR, int startC, Matrix& A)
{
	int endR = startR + A.getR();
	int endC = startC + A.getC();
   

	for (int i = startR; i < endR; i++)
	{
		for(int j = startC; j < endC; j++)
		{
			double temp = A.get(i - startR, j - startC);
			this -> set(i, j, temp);

		}
 
	}
	return A;
}

Matrix Matrix ::getBlock(int startR, int endR, int startC,int endC) 
{ 
	int row;
	int column;
	double temp = 0.0;

	row = endR - startR; 
	column = endC - startC;
	Matrix F(row, column, 1.2);	

	for (int i = startR; i < endR; i++)
	{
		for(int j = startC; j < endC; j++)
		{
			temp = get(i, j);
			F.set(i - startR, j - startC, temp);
		}
	
	}

	return F;
}


int Matrix::getR() const
{
	return R;
}

int Matrix::getC() const
{
	return C;
}