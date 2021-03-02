#pragma once
#include <iostream>
#include <string>
#define MATH_PI 3.1415926535897932384626433832795 /* PI */

using namespace std;

template <typename T, const int rowCount, const int columnCount>
class Matrix {
private:
	template <typename _T>
	_T** getMatrix(const int _rows, const int _columns, _T _fill) {
		_T** newMatrix = new _T * [_rows];

		for (int i = 0; i < _rows; i++) // Create the columns.
		{
			newMatrix[i] = new _T [_columns];
		}

		for (int i = 0; i < _rows; i++)
		{
			for (int j = 0; j < _columns; j++)
			{
				newMatrix[i][j] = (_fill != NULL ? _fill : 0); // If the fill parameter isnt assigned any value the matrix will be filled with zeros.
			}
		}
		return newMatrix;
	}


	int columns;
	int rows;
	float** p_Values = nullptr;

	// If the size of the matrix is the same this function should be used
	void setValues(T** _values) {
		p_Values = getMatrix<T>(rows, columns, NULL);

		if (_values != NULL)
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < columns; j++)
				{
					p_Values[i][j] = _values[i][j];
				}
			}
		}
	}

	// If the size of the matrix is the same this function should be used
	void setValues(T _values[rowCount][columnCount]) {
		p_Values = getMatrix<T>(rows, columns, NULL);

		if (_values != NULL)
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < columns; j++)
				{
					p_Values[i][j] = _values[i][j];
				}
			}
		}
	}

	// If the size of the matrix is different this function should be used
	void replaceValues(T** values) {

	}

	void clean() {
		if (p_Values != nullptr)
		{
			try
			{
				for (int i = 0; i < rows; i++) // Delete the pointers inside the list of pointers
				{
					delete[] p_Values[i];
				}
				delete[] p_Values; // Delete the pointer that pointed to the list
			}
			catch (const std::exception& e)
			{
				cerr << "ERROR::CLEANING::FAILED:\n" << e.what() << endl;
			}
		}
	}

public:
	Matrix() {
		rows = rowCount; columns = columnCount;
		p_Values = getMatrix<T>(rows, columns, NULL);
	};

	Matrix(T** _values) {
		rows = rowCount; columns = columnCount;
		setValues(_values);
		//cout << "Constructed: " << rowCount << "x" << columnCount << endl;
	}
	//template <unsigned int _rows, unsigned int _columns>
	Matrix(T _values[rowCount][columnCount]) {
		rows = rowCount; columns = columnCount;
		setValues(_values);
		//cout << "Constructed: " << rowCount << "x" << columnCount << endl;
	}

	~Matrix() {
		clean();
		//cout << "Destructed" << rowCount << "x" << columnCount << endl;
	}
	
	// Get the number of columns
	int getColumnCount() {
		return columns;
	}

	// Get the number of rows
	int getRowCount() {
		return rows;
	}

	// Get the pointer to the matrix values
	T** getValues() {
		return p_Values;
	}

	// Returns a pointer to a new transposed version of a matrix
	Matrix<T, rowCount, columnCount>* Transposed() {
		T tempValues[rowCount][columnCount];
		if (p_Values != nullptr)
		{

			for (int i = 0; i < rowCount; i++)
			{
				for (int j = 0; j < columnCount; j++)
				{
					tempValues[i][j] = p_Values[j][i];
				}
			}
		}
		Matrix<T, rowCount, columnCount>* transposedMatrix = new Matrix<T, rowCount, columnCount>(tempValues);
		return transposedMatrix;
	}

	template <int _OtherRows, int _OtherColumns>
	Matrix<T, rowCount, _OtherColumns>* MatrixMult(Matrix<T, _OtherRows, _OtherColumns>* OtherMatrix) {
		T product[rowCount][_OtherColumns];

		for (int i = 0; i < rowCount; i++)
		{
			for (int j = 0; j < _OtherColumns; j++)
			{
				product[i][j] = 0;
			}
		}
		
		if (p_Values != nullptr && columnCount == _OtherRows)
		{
			for (int row = 0; row < rowCount; row++)
			{
				for (int column = 0; column < _OtherColumns; column++)
				{
					//Calculate the dot product
					for (int inner = 0; inner < columnCount; inner++)
					{
						product[row][column] += (p_Values[row][inner] * OtherMatrix->getValues()[inner][column]);
					}
				}
			}
		}

		Matrix<T, rowCount, _OtherColumns>* resultMatrix = new Matrix<T, rowCount, _OtherColumns>(product);
		
		return resultMatrix;
	}

	template <int _OtherRows, int _OtherColumns>
	Matrix<T, rowCount, _OtherColumns>* MatrixMult(Matrix<T, _OtherRows, _OtherColumns> &OtherMatrix) {
		T product[rowCount][_OtherColumns];
		if (this != nullptr)
		{

			for (int i = 0; i < rowCount; i++)
			{
				for (int j = 0; j < _OtherColumns; j++)
				{
					product[i][j] = 0;
				}
			}

			if (p_Values != nullptr && columnCount == _OtherRows)
			{
				for (int row = 0; row < rowCount; row++)
				{
					for (int column = 0; column < _OtherColumns; column++)
					{
						//Calculate the dot product
						for (int inner = 0; inner < columnCount; inner++)
						{
							product[row][column] += (p_Values[row][inner] * OtherMatrix.getValues()[inner][column]);
						}
					}
				}
			}
		}

		Matrix<T, rowCount, _OtherColumns>* resultMatrix = new Matrix<T, rowCount, _OtherColumns>(product);

		return resultMatrix;
	}

	// Returns a readable version of a matrix
	string toString() {
		string str;
		if (p_Values != nullptr)
		{
			for (int row = 0; row < rows; row++)
			{
				str += "{  ";
				for (int col = 0; col < columns; col++)
				{
					try
					{
						str += to_string(p_Values[row][col]) + "  ";
					}
					catch (const std::exception&)
					{
						return NULL;
					}
				}
				str += "}\n";
			}
		}
		return str;
	}
};

template <unsigned int rows, unsigned int columns>
class matrix {

private:

	template <unsigned int m, unsigned int n>
	float** createMatrix() {

		float** Matrix = nullptr;
		Matrix = new float* [m]; //Create the rows

		for (int i = 0; i < m; i++) //Create the columns
		{
			Matrix[i] = new float[n];
		}

		for (int i = 0; i < m; i++) //Fill the matrix with 0:os
		{
			for (int j = 0; j < n; j++)
			{
				Matrix[i][j] = 0;
			}
		}

		//cout << "Address1: " << Matrix << " Rows: " << rows << " Columns: " << columns<< endl;
		return Matrix;
	}


public:

	int columnCount = 0;
	int rowCount = 0;
	float** values = 0;

	void cleanValues() {
		if (values != 0)
		{
			for (int i = 0; i < rows; i++)
			{
				delete[] values[i];
			}
			delete[] values;
		}
	}

	//Create a matrix containing only zeros (0).

	matrix() {
		columnCount = columns;
		rowCount = rows;
		if (values == 0)
		{
			values = createMatrix<rows, columns>();
		}
	}

	matrix(float* arr1d) {
		columnCount = columns;
		rowCount = rows;
		if (values == 0)
		{
			values = createMatrix<rows, columns>();
		}
		Set<rows, columns>(arr1d);
	}

	matrix(float** arr2d) {
		columnCount = columns;
		rowCount = rows;
		if (values == 0)
		{
			values = createMatrix<rows, columns>();
		}

		Set<rows, columns>(arr2d);
	}

	//Create a matrix with specified data.
	matrix(float arr2d[rows][columns]) {
		columnCount = columns;
		rowCount = rows;
		if (values == 0)
		{
			values = createMatrix<rows, columns>();
		}
		Set<rows, columns>(arr2d);
	}

	//Set new data into the matrix or new data with different dimensions to create a whole new and different matrix.
	//Takes an 2d array as input.
	template <int r, int c>
	matrix Set(float arr2d[r][c]) {
		//cout << "r = " << r << " c = " << c << " rows = " << rows << " cols = " << columns << endl;
		if (r == rows && c == columns && values != 0) //If the matrix has the same size as the one before
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
		else if (r != rows || c != columns || values == 0) //If the matrix has another size then the one before
		{
			if (values != 0) { // Because new values are going to be set the previous ones have to get deleted so that garbage wont be piled up
				cleanValues();
			}
			values = 0;
			values = createMatrix<r,c>();

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
	//Takes an 2d array as input.
	template <int r, int c>
	matrix Set(float** arr2d) {
		//cout << "r = " << r << " c = " << c << " rows = " << rows << " cols = " << columns << endl;
		if (r == rows && c == columns && values != 0) //If the matrix has the same size as the one before
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
		else if (r != rows || c != columns || values == 0) //If the matrix has another size then the one before
		{
			if (values != 0) {
				cleanValues();
			}
			values = 0;
			values = createMatrix<r, c>();

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
		if (r == rows && c == columns && values != 0)
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
		else if (r != rows || c != columns || values == 0)
		{
			if (values != 0)
			{
				cleanValues();
			}
			values = 0;
			values = createMatrix(r, c);
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
			float** product = createMatrix<rows,p>();
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
			if (values != 0)
			{
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
			}
			
			//float result[rows][p];
			matrix<rows, p>* res = new matrix<rows, p>(product);
			

			for (int i = 0; i < rows; i++)
			{
				delete[] product[i];
			}
			delete[] product;

			return res;
		}
		else
		{
			cerr << "Error: Can not multiply: column count isn't the same as the other's row count" << endl;
			return this;
		}
	}
};