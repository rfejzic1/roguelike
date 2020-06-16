#pragma once
#include <algorithm>

template <typename T>
class Matrix {
    int rows;
    int cols;
    T** matrix;
public:
    Matrix(int rows, int cols, T defaultValue = T());
    Matrix(const Matrix& other) = delete;
    Matrix(Matrix&& other) = delete;
    Matrix& operator =(const Matrix& other) = delete;
    Matrix& operator =(Matrix&& other) = delete;
    T get(int row, int col);
    void set(int row, int col, const T& value);
    ~Matrix();
};

template<typename T>
Matrix<T>::Matrix(int rows, int cols, T defaultValue)
    : rows(rows), cols(cols), matrix(nullptr)
{
    try{
        matrix = new int*[rows] {nullptr};
        for(int i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
            std::fill(matrix[i], matrix[i] + cols, defaultValue);
        }
    } catch(std::bad_alloc& err) {
        for(int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

template<typename T>
Matrix<T>::~Matrix() {
    for(int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

template<typename T>
T Matrix<T>::get(int row, int col) {
    return matrix[row][col];
}

template<typename T>
void Matrix<T>::set(int row, int col, const T &value) {
    matrix[row][col] = value;
}
