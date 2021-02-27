#pragma once
#include <iostream>
#include <string>
#define MATH_PI 3.1415926535897932384626433832795 /* PI */

using namespace std;

template <unsigned int rows, unsigned int columns>
class matrix {

private:

	float** createMatrix(int m, int n) {

		float** Matrix = nullptr;
		Matrix = 0;
		Matrix = new float* [m];

		for (int i = 0; i < m; i++)
		{
			Matrix[i] = new float[n];
		}

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				Matrix[i][j] = 0;
			}
		}

		return Matrix;
	}

public:

	int columnCount = 0;
	int rowCount = 0;
	float** values = createMatrix(rows, columns);

	//Create a matrix containing only zeros (0).
	matrix() {
		columnCount = columns;
		rowCount = rows;
	}

	matrix(float* arr1d) {
		columnCount = columns;
		rowCount = rows;
		Set<rows, columns>(arr1d);
	}

	//Create a matrix with specified data.
	matrix(float arr2d[rows][columns]) {
		columnCount = columns;
		rowCount = rows;
		Set<rows, columns>(arr2d);
	}

	//Set new data into the matrix or new data with different dimensions to create a whole new and different matrix.
	//Takes an 2d array as input.
	template <int r, int c>
	matrix Set(float arr2d[r][c]) {
		//cout << "r = " << r << " c = " << c << " rows = " << rows << " cols = " << columns << endl;
		if (r == rows && c == columns)
		{
			for (int col = 0; col < columnCount; col++)
			{
				for (int row = 0; row < rowCount; row++)
				{
					values[row][col] = arr2d[row][col];
				}
			}
			return *this;
		}
		else if (r != rows || c != columns)
		{
			values = 0;
			values = createMatrix(r, c);
			columnCount = c;
			rowCount = r;
			for (int col = 0; col < c; col++)
			{
				for (int row = 0; row < r; row++)
				{
					values[row][col] = arr2d[row][col];
				}
			}
			return *this;
		}
	}

	//Set new data into the matrix or new data with different dimensions to create a whole new and different matrix.
	//Takes a one dimensional array (like a vector).
	template <int r, int c>
	matrix Set(float * arr1d) {
		//cout << "r = " << r << " c = " << c << " rows = " << rows << " cols = " << columns << endl;
		if (r == rows && c == columns)
		{
			for (int col = 0; col < columnCount; col++)
			{
				for (int row = 0; row < rowCount; row++)
				{
					values[row][col] = arr1d[col];
				}
			}
			return *this;
		}
		else if (r != rows || c != columns)
		{
			values = 0;
			delete [] values;
			values = createMatrix(r, c);
			//delete[] Matrix;
			columnCount = c;
			rowCount = r;
			for (int col = 0; col < c; col++)
			{
				for (int row = 0; row < r; row++)
				{
					values[row][col] = arr1d[col];
				}
			}
			return *this;
		}
	}
	
	//Convert the data into a readable string.
	string toString() {
		if (this != NULL)
		{
			string str;
			for (int row = 0; row < rowCount; row++)
			{
				str += "{  ";
				for (int col = 0; col < columnCount; col++)
				{
					str += to_string(values[row][col]) + "  ";
				}
				str += "}\n";
			}
			return str;
		}
		else
		{
			return "";
		}
	}
	
	///Add two matrices together.
	matrix add(matrix addMatrix) {
		if (columnCount == addMatrix.columnCount && rowCount == addMatrix.rowCount)
		{
			for (int i = 0; i < rowCount; i++)
			{
				for (int j = 0; j < columnCount; j++)
				{
					values[i][j] += addMatrix.values[i][j];
				}
			}
		}
		return *this;
	}

	//Add a number to all the values in this matrix
	matrix add(float numb) {

		for (int i = 0; i < rowCount; i++)
		{
			for (int j = 0; j < columnCount; j++)
			{
				values[i][j] += numb;
			}
		}
		return *this;
	}

	//Subtract a matrix with another
	matrix subtract(matrix subratctMatrix) {
		if (columnCount == subratctMatrix.columnCount && rowCount == subratctMatrix.rowCount)
		{
			for (int i = 0; i < rowCount; i++)
			{
				for (int j = 0; j < columnCount; j++)
				{
					values[i][j] -= subratctMatrix.values[i][j];
				}
			}
		}
		return *this;
	}

	//Subtract a number from all of the values of this matrix
	matrix subtract(float numb) {

		for (int i = 0; i < rowCount; i++)
		{
			for (int j = 0; j < columnCount; j++)
			{
				values[i][j] -= numb;
			}
		}
		return *this;
	}


	matrix divide(matrix divideMatrix) {
		if (columnCount == divideMatrix.columnCount && rowCount == divideMatrix.rowCount)
		{
			for (int i = 0; i < rowCount; i++)
			{
				for (int j = 0; j < columnCount; j++)
				{
					values[i][j] /= divideMatrix.values[i][j];
				}
			}
		}
		return *this;
	}

	matrix divide(float scaler) {
		for (int i = 0; i < rowCount; i++)
		{
			for (int j = 0; j < columnCount; j++)
			{
				values[i][j] /= scaler;
			}
		}
		return *this;
	}

	//Scale a matrix with a scaler
	matrix scale(float scaler) {
		for (int i = 0; i < rowCount; i++)
		{
			for (int j = 0; j < columnCount; j++)
			{
				values[i][j] *= scaler;
			}
		}
		return *this;
	}

	//Multiply two matricies
	template <int n, int p>
	matrix<rows, p>* mult(matrix<n, p> multMatrix) {
		if (columnCount == n)
		{
			float** product = createMatrix(rows, p);
			/*float** tempValuesMatrix = createMatrix(rows, columns);

			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < columns; j++)
				{
					tempValuesMatrix[i][j] = values[i][j]; //Store the values in a temporary variable so that new values can be put in without destroying the real values
				}
			}

			delete[] values;
			values = createMatrix(rows, p); //Assign values to a new matrix so new values can be put in*/

			columnCount = p;
			rowCount = rows;
			//Go through each row of the first matrix

			for (int row = 0; row < rowCount; row++)
			{
				for (int column = 0; column < p; column++)
				{
					//Calculate the dot product
					for (int inner = 0; inner < columnCount; inner++)
					{
						//cout << " Inner: " << inner << "Column: " << column << endl;
						//cout << "values: " << values[row][inner] << " * " << " multvalues: " << multMatrix.values[inner][column] << endl;
						product[row][column] += (values[row][inner] * multMatrix.values[inner][column]);
					}
					//cout << product[row][column] << ", ";
				}
				//cout << "\n";
			}
			
			//float result[rows][p];
			matrix<rows, p>* res = new matrix<rows, p>();
			res->values = createMatrix(rows, p);
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < p; j++)
				{
					res->values[i][j] = product[i][j];
				}
			}

			delete[] product;

			return res;
		}
		else
		{
			matrix<rows, p>* res = new matrix<rows, p>();
			cerr << "Error: Can not multiply: column count isn't the same as the other's row count" << endl;
			return res;
		}
	}
};