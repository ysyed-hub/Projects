//
//  matrix.hpp
//  matrix_class
//
//  Created by Yunus Syed on 9/12/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class Matrix {
    int dimension;
    std::vector<std::vector<int> > entry;
public:
    Matrix(int matrix_dimension);
    void SetEntry(int row_number, int col_number, int entry);
    void SetRow(int row_number, std::vector<int> new_row);
    void SetColumn(int col_number, std::vector<int> new_col);
    void Display() const;
    int GetDim() const {return dimension;}
    int GetEntry(int row_number, int col_number) const {return entry[row_number][col_number];}
    std::vector<int> GetRow(int row_number) const;
    std::vector<int> GetColumn(int col_number) const;
    void SwapEntry(int row1, int col1, int row2, int col2);
    void Transpose();
    Matrix Cofactor(int row, int col) const;
    double Determinant() const;
    Matrix Power(int exponent) const;
    static Matrix CreateRandom(int min, int max, int dimension);
    
    
    
    /*Matrix operator+(const Matrix &A) {
        if (A.GetDim() != this -> GetDim()) {
            std::cout << "Error, matrices have different dimensions" << std::endl;
            return *this;
        }
        int n = A.GetDim();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                int new_entry = this -> GetEntry(i, j) + A.GetEntry(i,j);
                this -> SetEntry(i, j, new_entry);
            }
        return *this;
    } */
    
    friend Matrix operator+(Matrix const &a, Matrix const &b);
    friend Matrix operator-(Matrix const &a, Matrix const &b);
    friend Matrix operator*(Matrix const &a, Matrix const &b);
    friend bool operator==(Matrix const &a, Matrix const &b);
    
};



#endif /* matrix_hpp */
