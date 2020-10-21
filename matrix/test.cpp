//
//  test.cpp
//  matrix_class
//
//  created by Yunus Syed on 9/12/20.
//  copyright © 2020 Yunus Syed. all rights reserved.
//

#include <iostream>
#include <vector>
#include "matrix.hpp"
#include <thread>


void TestSetEntry();
void TestGetEntry(Matrix const &a, Matrix const &b, Matrix const &c);
void TestGetRow(Matrix const &a, Matrix const &b, Matrix const &c);
void TestGetColumn(Matrix const &a, Matrix const &b, Matrix const &c);
void TestSwapEntry(Matrix &a);
void TestTranspose(Matrix &a);
void TestCofactor(Matrix const &a, Matrix const &b);
void TestDeterminant(Matrix const &a, Matrix const &b, Matrix const &c);
void TestOperationPlus(Matrix const &a, Matrix const &b);
void TestOperationMinus(Matrix const &a, Matrix const &b);
void TestOperationTimes(Matrix const &a, Matrix const &b);
void TestPower(Matrix const &a, Matrix const &b);
void TestOperationIdentical(Matrix const &a, Matrix const &b);
void TestCreateRandom(int min, int max, int dim, double *p);

struct RandomParam {
    int min;
    int max;
    int dim;
};

int main(int argc, const char * argv[]) {
    
    Matrix a(2);
    std::vector<int> a_row1;
    a_row1.push_back(2);
    a_row1.push_back(3);
    a.SetRow(0, a_row1);
    
    std::vector<int> a_row2;
    a_row2.push_back(1);
    a_row2.push_back(3);
    a.SetRow(1, a_row2);
    
    Matrix b(2);
    std::vector<int> b_row1;
    b_row1.push_back(4);
    b_row1.push_back(-2);
    b.SetRow(0, b_row1);
    
    std::vector<int> b_row2;
    b_row2.push_back(1);
    b_row2.push_back(-3);
    b.SetRow(1, b_row2);
    
    Matrix c(2); // 2x2 zero matrix
    
    TestSetEntry();
    TestGetEntry(a, b, c);
    TestGetRow(a, b, c);
    TestGetColumn(a, b, c);
    TestSwapEntry(a);
    TestTranspose(a);
    TestCofactor(a, b);
    TestDeterminant(a, b, c);
    TestOperationPlus(a, b);
    TestOperationMinus(a, b);
    TestOperationTimes(a, b);
    TestPower(a, b);
    TestOperationIdentical(a, b);
    
    
    double *p = new double;
    double *q = new double;
    
    std::thread first(TestCreateRandom, 0, 5, 10, p);
    std::thread second(TestCreateRandom, 0, 6, 10, q);
    first.join();
    second.join();
    std::cout << (*p) << endl;
    std::cout << (*q) << endl;
    
    return 0;
}


void TestSetEntry() {
        Matrix d(2);
        d.SetEntry(1, 1, 9);
        if (d.GetEntry(1, 1) != 9)
            std::cout << "Error: SetEntry" << std::endl;
}

void TestGetEntry(Matrix const &a, Matrix const &b, Matrix const &c) {
    if (a.GetEntry(0,0) != 2 || b.GetEntry(1, 1) != -3 || c.GetEntry(0, 1) != 0)
        std::cout << "Error: GetEntry(1)" << std::endl;
    
    if (b.GetEntry(0,0) != 4 || c.GetEntry(1, 1) != 0 || a.GetEntry(0, 1) != 3)
        std::cout << "Error: GetEntry(2)" << std::endl;
    
    if (c.GetEntry(0,0) != 0 || a.GetEntry(1, 1) != 3 || b.GetEntry(0, 1) != -2)
        std::cout << "Error: GetEntry(3)" << std::endl;
}

void TestDeterminant(Matrix const &a, Matrix const &b, Matrix const &c) {
    if (a.Determinant() != 3 || b.Determinant() != -10 || c.Determinant() != 0)
        std::cout << "Error: Determinant" << std::endl;
}

void TestGetRow(Matrix const &a, Matrix const &b, Matrix const &c) {
    bool Error = false;
    int i = 0;
    int j = 0;
    for (i = 0; i < a.GetDim(); i++) {
        std::vector<int> a_row = a.GetRow(i);
        std::vector<int> b_row = b.GetRow(i);
        std::vector<int> c_row = c.GetRow(i);
        
        for (j = 0; j < b.GetDim(); j++) {
            if (a_row[j] != a.GetEntry(i, j))
                Error = true;
            if (b_row[j] != b.GetEntry(i, j))
                Error = true;
            if (c_row[j] != c.GetEntry(i, j))
                Error = true;
            if (Error == true)
                break;
        }
        if (Error == true)
            break;
    }
    if (Error == true)
        std::cout << "Error: GetRow" << std::endl;
}

void TestGetColumn(Matrix const &a, Matrix const &b, Matrix const &c) {
    bool Error = false;
    int i,j;
    for (i = 0; i < a.GetDim(); i++) {
        std::vector<int> a_col = a.GetColumn(i);
        std::vector<int> b_col = b.GetColumn(i);
        std::vector<int> c_col = c.GetColumn(i);
        
        for (j = 0; j < b.GetDim(); j++) {
            if (a_col[j] != a.GetEntry(j, i))
                Error = true;
            if (b_col[j] != b.GetEntry(j, i))
                Error = true;
            if (c_col[j] != c.GetEntry(j, i))
                Error = true;
            if (Error == true)
                break;
        }
        if (Error == true)
            break;
    }
    if (Error == true)
        std::cout << "Error: GetColumn" << std::endl;
}

void TestSwapEntry(Matrix &a) {
    a.SwapEntry(0, 0, 1, 1);
    if (a.GetEntry(1, 1) != 2 || a.GetEntry(0, 0) != 3) {
        std::cout << "Error: SwapEntry" << std::endl;
    }
    a.SwapEntry(0, 0, 1, 1);
}

void TestTranspose(Matrix &a) {
    Matrix d(a);
    d.Transpose();

    bool Error = false;
    int i,j;
    for (i = 0; i < a.GetDim(); i++) {
        for (j = 0; j < a.GetDim(); j++) {
            if (a.GetEntry(i, j) != d.GetEntry(j, i)) {
                Error = true;
                break;
            }
        }
        if (Error == true)
            break;
    }
    if (Error == true)
        std::cout << "Error: Transpose" << std::endl;
}

void TestCofactor(Matrix const &a, Matrix const &b) {
    Matrix d(a.Cofactor(1, 0));
    Matrix e(b.Cofactor(0, 0));
    if (d.GetEntry(0, 0) != 3 || e.GetEntry(0, 0) != -3)
        std::cout << "Error: Cofactor" << std::endl;
}

void TestOperationPlus(Matrix const &a, Matrix const &b) {
    Matrix d = a + b;
    if (d.GetEntry(1, 0) != 2 || d.GetEntry(0, 1) != 1)
        std::cout << "Error: +" << std::endl;
}

void TestOperationMinus(Matrix const &a, Matrix const &b) {
    Matrix d = a - b;
    if (d.GetEntry(0, 0) != -2 || d.GetEntry(1, 1) != 6)
        std::cout << "Error: -(1)" << std::endl;
}

void TestOperationTimes(Matrix const &a, Matrix const &b) {
    Matrix d = a * b;
    if (d.GetEntry(1, 0) != 7 || d.GetEntry(0, 1) != -13)
        std::cout << "Error: *" << std::endl;
}

void TestPower(Matrix const &a, Matrix const &b) {
    Matrix d = a.Power(3);
    if (d.GetEntry(1, 0) != 22 || d.GetEntry(0, 1) != 66)
        std::cout << "Error: Power(1)" << std::endl;
    
    Matrix e = b.Power(2);
    if (e.GetEntry(1, 0) != 1 || e.GetEntry(0, 1) != -2)
        std::cout << "Error: Power(2)" << std::endl;

    Matrix f = d - e;
    if (f.GetEntry(1, 0) != 21 || f.GetEntry(0, 1) != 68)
        std::cout << "Error: -(2)" << std::endl;
}

void TestOperationIdentical(Matrix const &a, Matrix const &b) {
    bool test1 = (a == b);
    if (test1 != false)
        std::cout << "Error: ==(1)" << std::endl;
    
    Matrix d(a);
    bool test2 = (a == d);
    if (test2 != true)
        std::cout << "Error: ==(2)" << std::endl;
}

void TestCreateRandom(int min, int max, int dim, double *p) {
    Matrix d(Matrix::CreateRandom(min, max, dim));
    *p = d.Determinant();
}
