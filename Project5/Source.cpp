#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;

class Matrix 
{
private:
    int** matrix;
    int rows;
    int cols;

    void allocateMemory() 
    {
        matrix = new int* [rows];
        for (int i = 0; i < rows; i++) 
        {
            matrix[i] = new int[cols];
        }
    }

    void freeMemory() 
    {
        for (int i = 0; i < rows; i++) 
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols) 
    {
        allocateMemory();
    }

    ~Matrix() 
    {
        freeMemory();
    }

    void fillFromKeyboard() 
    {
        cout << "Enter elements for " << rows << "x" << cols << " matrix:\n";
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++) 
            {
                cin >> matrix[i][j];
            }
        }
    }

    void fillRandom() 
    {
        srand(time(nullptr));
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                matrix[i][j] = rand() % 100;
            }
        }
    }

    void display() const 
    {
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                cout << matrix[i][j] << ' ';
            }
            cout << '\n';
        }
    }

    Matrix operator+(const Matrix& other) const 
    {
        if (rows != other.rows || cols != other.cols) 
        {
            throw invalid_argument("Matrices must have the same dimensions for addition");
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const
    {
        if (rows != other.rows || cols != other.cols) 
        {
            throw invalid_argument("Matrices must have the same dimensions for subtraction");
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++) 
            {
                result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const 
    {
        if (cols != other.rows) 
        {
            throw invalid_argument("Matrices must have compatible dimensions for multiplication");
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < other.cols; j++) 
            {
                result.matrix[i][j] = 0;
                for (int k = 0; k < cols; k++)
                {
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator/(const int& scalar) const 
    {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                result.matrix[i][j] = matrix[i][j] / scalar;
            }
        }
        return result;
    }

    int maxElement() const 
    {
        int maxVal = matrix[0][0];
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                if (matrix[i][j] > maxVal) 
                {
                    maxVal = matrix[i][j];
                }
            }
        }
        return maxVal;
    }

    int minElement() const 
    {
        int minVal = matrix[0][0];
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                if (matrix[i][j] < minVal) 
                {
                    minVal = matrix[i][j];
                }
            }
        }
        return minVal;
    }
};

class A 
{
private:
    int value;

public:
    A(int v = 0) : value(v) {}

    A operator+(const A& other) const
    {
        return A(value + other.value);
    }

    A operator-(const A& other) const 
    {
        return A(value - other.value);
    }

    A operator*(const A& other) const
    {
        return A(value * other.value);
    }

    A operator/(const A& other) const 
    {
        return A(value / other.value);
    }

    friend ostream& operator<<(ostream& os, const A& obj)
    {
        os << obj.value;
        return os;
    }

    friend istream& operator>>(istream& is, A& obj) 
    {
        is >> obj.value;
        return is;
    }
};
