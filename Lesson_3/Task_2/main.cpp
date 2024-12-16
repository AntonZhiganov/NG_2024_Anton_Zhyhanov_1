#include <iostream>
#include <stdexcept>
using namespace std;

struct Matrix {
    int** elements;
    int numberOfRows, numberOfColumns;

    Matrix(int rows, int columns) : numberOfRows(rows), numberOfColumns(columns) {
        elements = new int*[numberOfRows];
        for (int rowIndex = 0; rowIndex < numberOfRows; ++rowIndex) {
            elements[rowIndex] = new int[numberOfColumns]{0};
        }
    }

    Matrix(const Matrix& otherMatrix) : numberOfRows(otherMatrix.numberOfRows), numberOfColumns(otherMatrix.numberOfColumns) {
        elements = new int*[numberOfRows];
        for (int rowIndex = 0; rowIndex < numberOfRows; ++rowIndex) {
            elements[rowIndex] = new int[numberOfColumns];
            for (int columnIndex = 0; columnIndex < numberOfColumns; ++columnIndex) {
                elements[rowIndex][columnIndex] = otherMatrix.elements[rowIndex][columnIndex];
            }
        }
    }

    ~Matrix() {
        for (int rowIndex = 0; rowIndex < numberOfRows; ++rowIndex) {
            delete[] elements[rowIndex];
        }
        delete[] elements;
    }

    Matrix operator+(const Matrix& otherMatrix) const {
        if (numberOfRows != otherMatrix.numberOfRows || numberOfColumns != otherMatrix.numberOfColumns) {
            throw invalid_argument("The matrix sizes do not match!");
        }
        Matrix resultMatrix(numberOfRows, numberOfColumns);
        for (int rowIndex = 0; rowIndex < numberOfRows; ++rowIndex) {
            for (int columnIndex = 0; columnIndex < numberOfColumns; ++columnIndex) {
                resultMatrix.elements[rowIndex][columnIndex] = elements[rowIndex][columnIndex] + otherMatrix.elements[rowIndex][columnIndex];
            }
        }
        return resultMatrix;
    }

    Matrix operator-(const Matrix& otherMatrix) const {
        if (numberOfRows != otherMatrix.numberOfRows || numberOfColumns != otherMatrix.numberOfColumns) {
            throw invalid_argument("The matrix sizes do not match!");
        }
        Matrix resultMatrix(numberOfRows, numberOfColumns);
        for (int rowIndex = 0; rowIndex < numberOfRows; ++rowIndex) {
            for (int columnIndex = 0; columnIndex < numberOfColumns; ++columnIndex) {
                resultMatrix.elements[rowIndex][columnIndex] = elements[rowIndex][columnIndex] - otherMatrix.elements[rowIndex][columnIndex];
            }
        }
        return resultMatrix;
    }

    void inputMatrix(const string& matrixName) {
        cout << "Enter matrix elements" << matrixName << " (" << numberOfRows << "x" << numberOfColumns << "):\n";
        for (int rowIndex = 0; rowIndex < numberOfRows; ++rowIndex) {
            for (int columnIndex = 0; columnIndex < numberOfColumns; ++columnIndex) {
                cin >> elements[rowIndex][columnIndex];
            }
        }
    }

    void printMatrix(const string& matrixName) const {
        cout << "Matrix " << matrixName << ":\n";
        for (int rowIndex = 0; rowIndex < numberOfRows; ++rowIndex) {
            for (int columnIndex = 0; columnIndex < numberOfColumns; ++columnIndex) {
                cout << elements[rowIndex][columnIndex] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int numberOfRows, numberOfColumns;

    cout << "Enter the number of rows and columns of matrices: ";
    cin >> numberOfRows >> numberOfColumns;

    Matrix matrixA(numberOfRows, numberOfColumns);
    Matrix matrixB(numberOfRows, numberOfColumns);

    matrixA.inputMatrix("A");
    matrixB.inputMatrix("B");

    cout << "Choose an operation: 1 - Sum, 2 - Difference: ";
    int choice;
    cin >> choice;

    try {
        if (choice == 1) {
            Matrix sumMatrix = matrixA + matrixB;
            sumMatrix.printMatrix("Sum (A + B)");
        } else if (choice == 2) {
            Matrix differenceMatrix = matrixA - matrixB;
            differenceMatrix.printMatrix("Difference (A - B)");
        } else {
            cout << "Wrong choice of operation!" << endl;
        }
    } catch (const exception& error) {
        cout << "Error: " << error.what() << endl;
    }

    return 0;
}

