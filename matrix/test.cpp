//
//  test.cpp
//  matrix_class
//
//  Created by Yunus Syed on 9/12/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#include <iostream>
#include <vector>
#include "matrix.hpp"

using namespace std;


int main(int argc, const char * argv[]) {
    
    Matrix A(2), B(2), C(2);
    std::vector<int> arow1, arow2;
    arow1.push_back(2);
    arow1.push_back(3);
    A.SetRow(0, arow1);
    
    arow2.push_back(1);
    arow2.push_back(3);
    A.SetRow(1, arow2);
    
    std::vector<int> brow1, brow2;
    brow1.push_back(4);
    brow1.push_back(-2);
    B.SetRow(0, brow1);
    
    brow2.push_back(1);
    brow2.push_back(-3);
    B.SetRow(1, brow2);
    
    {
        Matrix D(2);
        D.SetEntry(1, 1, 9);
        if (D.GetEntry(1, 1) != 9)
            std::cout << "Error: SetEntry" << std::endl;
    }
    
    {
        if (A.GetEntry(0,0) != 2 || B.GetEntry(1, 1) != -3 || C.GetEntry(0, 1) != 0)
            std::cout << "Error: GetEntry(1)" << std::endl;
        
        if (B.GetEntry(0,0) != 4 || C.GetEntry(1, 1) != 0 || A.GetEntry(0, 1) != 3)
            std::cout << "Error: GetEntry(2)" << std::endl;
        
        if (C.GetEntry(0,0) != 0 || A.GetEntry(1, 1) != 3 || B.GetEntry(0, 1) != -2)
            std::cout << "Error: GetEntry(3)" << std::endl;
    }
    
    {
    if (A.Determinant() != 3 || B.Determinant() != -10 || C.Determinant() != 0)
        std::cout << "Error: Determinant" << std::endl;
    }
    
    {
    bool error = false;
    int i = 0;
    int j = 0;
    for (i = 0; i < A.GetDim(); i++) {
        std::vector<int> a = A.GetRow(i);
        std::vector<int> b = B.GetRow(i);
        std::vector<int> c = C.GetRow(i);
        
        for (j = 0; j < B.GetDim(); j++) {
            if (a[j] != A.GetEntry(i, j))
                error = true;
            if (b[j] != B.GetEntry(i, j))
                error = true;
            if (c[j] != C.GetEntry(i, j))
                error = true;
            if (error == true)
                break;
        }
        if (error == true)
            break;
    }
    if (error == true)
        std::cout << "Error. GetRow" << std::endl;
    }
    
    {
    bool error = false;
    int i,j;
    for (i = 0; i < A.GetDim(); i++) {
        std::vector<int> a = A.GetColumn(i);
        std::vector<int> b = B.GetColumn(i);
        std::vector<int> c = C.GetColumn(i);
        
        for (j = 0; j < B.GetDim(); j++) {
            if (a[j] != A.GetEntry(j, i))
                error = true;
            if (b[j] != B.GetEntry(j, i))
                error = true;
            if (c[j] != C.GetEntry(j, i))
                error = true;
            if (error == true)
                break;
        }
        if (error == true)
            break;
    }
    if (error == true)
        std::cout << "Error: GetColumn" << std::endl;
    }
    
    {
        A.SwapEntry(0, 0, 1, 1);
        if (A.GetEntry(1, 1) != 2 || A.GetEntry(0, 0) != 3) {
            std::cout << "Error: SwapEntry" << std::endl;
        }
        A.SwapEntry(0, 0, 1, 1);
    }
    
    {
        
        Matrix D(A);
        D.Transpose();

        bool error = false;
        int i,j;
        for (i = 0; i < A.GetDim(); i++) {
            for (j = 0; j < A.GetDim(); j++) {
                if (A.GetEntry(i, j) != D.GetEntry(j, i)) {
                    error = true;
                    break;
                }
            }
            if (error == true)
                break;
        }
        if (error == true)
            std::cout << "Error: Transpose" << std::endl;
    }
    
    {
        Matrix D(A.Cofactor(1, 0));
        Matrix E(B.Cofactor(0, 0));
        if (D.GetEntry(0, 0) != 3 || E.GetEntry(0, 0) != -3)
            std::cout << "Error: Cofactor" << std::endl;
    }
    
    {
        Matrix D = A + B;
        if (D.GetEntry(1, 0) != 2 || D.GetEntry(0, 1) != 1)
            std::cout << "Error: +" << std::endl;
    }
    
    {
        Matrix D = A - B;
        if (D.GetEntry(0, 0) != -2 || D.GetEntry(1, 1) != 6)
            std::cout << "Error: -(1)" << std::endl;
    }
    
    {
        Matrix D = A * B;
        if (D.GetEntry(1, 0) != 7 || D.GetEntry(0, 1) != -13)
            std::cout << "Error: *" << std::endl;
    }
    
    {
        Matrix D = A.Power(3);
        if (D.GetEntry(1, 0) != 22 || D.GetEntry(0, 1) != 66)
            std::cout << "Error: Power(1)" << std::endl;
        
        Matrix E = B.Power(2);
        if (E.GetEntry(1, 0) != 1 || E.GetEntry(0, 1) != -2)
            std::cout << "Error: Power(2)" << std::endl;

        Matrix F = D - E;
        if (F.GetEntry(1, 0) != 21 || F.GetEntry(0, 1) != 68)
            std::cout << "Error: -(2)" << std::endl;
    }
    
    {
        bool test1 = (A == B);
        if (test1 != false)
            std::cout << "Error: ==(1)" << std::endl;
        
        Matrix D(A);
        bool test2 = (A == D);
        if (test2 != true)
            std::cout << "Error: ==(2)" << std::endl;
    }
    
    return 0;
}
