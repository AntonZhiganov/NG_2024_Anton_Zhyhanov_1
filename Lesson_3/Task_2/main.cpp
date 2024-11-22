#include <iostream>
using namespace std;

struct Matrix {
    int** data;
    int rows, cols;
};

Matrix createMatrix(int rows, int cols) {
    Matrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.data = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix.data[i] = new int[cols]{0};
    }
    return matrix;
}

void inputMatrix(Matrix& matrix, const string& name) {
    cout << "Enter the matrix elements " << name << " (" << matrix.rows << "x" << matrix.cols << "):\n";
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            cin >> matrix.data[i][j];
        }
    }
}

void printMatrix(const Matrix& matrix, const string& name) {
    cout << "Matrix " << name << ":\n";
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            cout << matrix.data[i][j] << " ";
        }
        cout << endl;
    }
}

Matrix addMatrices(const Matrix& A, const Matrix& B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        throw invalid_argument("The dimensions of the matrices do not match!");
    }
    Matrix result = createMatrix(A.rows, A.cols);
    for (int i = 0; i < A.rows; ++i) {
        for (int j = 0; j < A.cols; ++j) {
            result.data[i][j] = A.data[i][j] + B.data[i][j];
        }
    }
    return result;
}

Matrix subtractMatrices(const Matrix& A, const Matrix& B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        throw invalid_argument("The dimensions of the matrices do not match!");
    }
    Matrix result = createMatrix(A.rows, A.cols);
    for (int i = 0; i < A.rows; ++i) {
        for (int j = 0; j < A.cols; ++j) {
            result.data[i][j] = A.data[i][j] - B.data[i][j];
        }
    }
    return result;
}

void deleteMatrix(Matrix& matrix) {
    for (int i = 0; i < matrix.rows; ++i) {
        delete[] matrix.data[i];
    }
    delete[] matrix.data;
}

int main() {
    int rows, cols;

    cout << "Enter the number of rows and columns of the matrices: ";
    cin >> rows >> cols;

    Matrix A = createMatrix(rows, cols);
    Matrix B = createMatrix(rows, cols);

    inputMatrix(A, "A");
    inputMatrix(B, "B");

    try {
        Matrix sum = addMatrices(A, B);
        printMatrix(sum, "Summ (A + B)");
        deleteMatrix(sum);

        Matrix difference = subtractMatrices(A, B);
        printMatrix(difference, "difference (A - B)");
        deleteMatrix(difference);
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    deleteMatrix(A);
    deleteMatrix(B);

    return 0;
}
