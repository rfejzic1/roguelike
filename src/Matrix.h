#pragma once
#include <algorithm>

template <typename T>
class Matrix {
    int rows;
    int cols;
    T** matrix;

    T** allocate(int numOfRows, int numOfCols, T defaultValue);
    void deallocate();
public:
    Matrix(int rows, int cols, T defaultValue = T());
    Matrix(const Matrix<T>& other);
    Matrix(Matrix<T>&& other);
    Matrix<T>& operator =(const Matrix<T>& other);
    Matrix<T>& operator =(Matrix<T>&& other);
    T get(int row, int col);
    void set(int row, int col, const T& value);
    ~Matrix();
};

template<typename T>
Matrix<T>::Matrix(int rows, int cols, T defaultValue)
    : rows(rows), cols(cols), matrix(nullptr)
{
    matrix = allocate(rows, cols, defaultValue);
}

template<typename T>
Matrix<T>::~Matrix() {
    deallocate();
}

template<typename T>
T Matrix<T>::get(int row, int col) {
    return matrix[row][col];
}

template<typename T>
void Matrix<T>::set(int row, int col, const T &value) {
    matrix[row][col] = value;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &other) {
    matrix = allocate(other.rows, other.cols, T());
    rows = other.rows;
    cols = other.cols;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> &&other) {
    rows = other.rows;
    cols = other.cols;
    matrix = other.matrix;
    other.rows = 0;
    other.cols = 0;
    other.matrix = nullptr;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other) {
    if(&other == this) {
        return *this;
    }

    deallocate();
    matrix = allocate(other.rows, other.cols, T());
    rows = other.rows;
    cols = other.cols;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            matrix[i][j] = other.matrix[i][j];
        }
    }

    return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&other) {
    if(&other == this) {
        return *this;
    }

    rows = other.rows;
    cols = other.cols;
    matrix = other.matrix;
    other.rows = 0;
    other.cols = 0;
    other.matrix = nullptr;

    return *this;
}

template<typename T>
T **Matrix<T>::allocate(int numOfRows, int numOfCols, T defaultValue) {
    T** mat = nullptr;
    try{
        mat = new T*[numOfRows] {nullptr};
        for(int i = 0; i < numOfRows; i++) {
            mat[i] = new T[numOfCols];
            std::fill(mat[i], mat[i] + numOfCols, defaultValue);
        }
    } catch(std::bad_alloc& err) {
        for(int i = 0; i < numOfRows; i++) {
            delete[] mat[i];
        }
        delete[] mat;
    }
    return mat;
}

template<typename T>
void Matrix<T>::deallocate() {
    for(int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}
