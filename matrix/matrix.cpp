//
//  matrix.cpp
//  matrix_class
//
//  Created by Yunus Syed on 9/12/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#include "matrix.hpp"
#include <iostream>
#include <vector>
#include <cmath>

Matrix::Matrix(int matrix_dimension) {
    dimension = matrix_dimension;
    std::vector<int> row;
    for (int i = 0; i < dimension; i++)
        row.push_back(0);
    for (int i = 0; i < dimension; i++)
        entry.push_back(row);
}

void Matrix::SetEntry(int row_number, int col_number, int val_entry) {
    if (row_number > dimension || row_number < 0 || col_number > dimension
        || col_number < 0) {
        std::cout << "Error, improper row or column number." << std::endl;
        return;
    }
   entry[row_number][col_number] = val_entry;
}

void Matrix::SetRow(int row_number, std::vector<int> new_row) {
    if (row_number > dimension || row_number < 0) {
       std::cout << "Error, improper row number." << std::endl;
        return;
    }
    if (new_row.size() != dimension) {
        std::cout << "Error, row is not of proper size" << std::endl;
        return;
    }
    for (int i = 0; i < dimension; i++)
        SetEntry(row_number, i, new_row[i]);
}

Matrix::Matrix(const Matrix &A): dimension(A.dimension), entry(A.entry) {}

void Matrix::SetColumn(int col_number, std::vector<int> new_col) {
    if (col_number > dimension || col_number < 0) {
           std::cout << "Error, improper column number." << std::endl;
            return;
        }
    if (new_col.size() != dimension) {
        std::cout << "Error, column is not of proper size" << std::endl;
        return;
    }
    for (int i = 0; i < dimension; i++)
        entry[i][col_number] = new_col[i];
}

void Matrix::Display() const {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            std::cout << entry[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<int> Matrix::GetRow(int row_number) {
    std::vector<int> row;
    if (row_number > dimension || row_number < 0) {
        std::cout << "Error, improper row number." << std::endl;
        return row;
    }
    for (int i = 0; i < dimension; i++)
        row.push_back(GetEntry(row_number, i));
    return row;
}

std::vector<int> Matrix::GetColumn(int col_number) {
    std::vector<int> col;
    if (col_number > dimension || col_number < 0) {
        std::cout << "Error, improper column number." << std::endl;
        return col;
    }
    for (int i = 0; i < dimension; i++)
        col.push_back(GetEntry(i, col_number));
    return col;
}

void Matrix::SwapEntry(int row, int col, int new_row, int new_col) {
    int temp = entry[row][col];
    entry[row][col] = entry[new_row][new_col];
    entry[new_row][new_col] = temp;
}

void Matrix::Transpose() {
    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < i; j++)
            SwapEntry(i, j, j, i);
}

Matrix Matrix::Cofactor(int row, int col) {
    Matrix C(dimension-1);
    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++) {
            if (i > row && j < col)
                C.SetEntry(i-1, j, entry[i][j]);
            else if (i > row && j > col)
                C.SetEntry(i-1, j-1, entry[i][j]);
            else if (i < row && j > col)
                C.SetEntry(i, j-1, entry[i][j]);
            else if (i < row && j < col)
                C.SetEntry(i, j, entry[i][j]);
        }
    return C;
}

int Matrix::Determinant() {
    int det = 0;
    if (dimension == 0)
        return 0;
    if (dimension == 1)
        return entry[0][0];
    
    for (int i = 0; i < dimension; i++) {
        det +=  pow(-1, i) * GetEntry(0, i) * Cofactor(0, i).Determinant();
    }
    return det;
}

int operator*(std::vector<int> const &A, std::vector<int> const &B) {
    if (A.size() != B.size()) {
        std::cout << "Error, vectors must have same size" << std::endl;
        return 0;
    }
    int prod = 0;
    for (int i = 0; i < A.size(); i++)
        prod += A[i] * B[i];
    return prod;
}


Matrix operator*(Matrix &A, Matrix &B) {
    if (A.GetDim() != B.GetDim()) {
        std::cout << "Error, matrices must have same dimensions" << std::endl;
        Matrix C(0);
        return C;
    }
    int n = A.GetDim();
    Matrix C(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C.SetEntry(i, j, A.GetRow(i) * B.GetColumn(j));
    
    return C;
}


Matrix Matrix::Power(int exponent) {
    Matrix C(this -> dimension);
    
    for (int i = 0; i < dimension; i++)
        C.SetEntry(i, i, 1); // identity matrix
    if (exponent == 0)
        return C;
    if (exponent > 0) {
        C = *this;
        for (int i = 1; i < exponent; i++)
            C = C * (*this);
    }
    return C;
}

bool operator==(Matrix &A, Matrix &B) {
    if (A.GetDim() != B. GetDim())
        return false;
    for (int i = 0; i < A.GetDim(); i++)
        for (int j = 0; j < A.GetDim(); j++)
            if (A.GetEntry(i, j) != B.GetEntry(i, j))
                return false;
    return true;
}

Matrix operator+(Matrix &A, Matrix &B) {
    if (A.dimension != B.dimension) {
        std::cout << "Error, matrices have different dimensions" << std::endl;
        Matrix C(0);
        return C;
    }
    int n = A.dimension;
    Matrix C(A);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C.entry[i][j] = A.entry[i][j] + B.entry[i][j];
        }
    
    return C;
}


Matrix operator-(Matrix &A, Matrix &B) {
    if (A.GetDim() != B.GetDim()) {
        std::cout << "Error, matrices have different dimensions" << std::endl;
        Matrix C(0);
        return C;
    }
    int n = A.GetDim();
    Matrix C(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C.SetEntry(i, j, A.GetEntry(i,j) - B.GetEntry(i,j));
    
    return C;
}

