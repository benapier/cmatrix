//
// Created by ben.napier on 01/12/2017.
//

#ifndef CMATRIX_MATRIX_H
#define CMATRIX_MATRIX_H

#include <utility>
#include <vector>
#include <iostream>

class mat {
private:
    std::vector<std::vector<long double>> mat_data;
    int rows, cols;

    void AllocateSpace();
    long double DeterminantCall(mat& p_mat);
public:
    // Constructors
    mat(); // default const
    mat(int rows, int cols); // from rows and cols
    mat(const mat &p_mat); // from matrix

    // Operators
    long double& operator()(int x, int y);
    mat& operator=(const mat &rhs);
    mat& operator+=(const mat &rhs);
    mat& operator-=(const mat &rhs);
    mat& operator*=(long double rhs);
    mat& operator*=(const mat &rhs);
    mat& operator/=(long double rhs);

    // Operations
    mat Transpose();
    mat RemoveRow(int row);
    mat RemoveCol(int col);
    long double det();
    mat Inverse();
    

    // Static functions
    static mat Identity(int size);

    // Misc functions
    void print();


};


#endif //CMATRIX_MATRIX_H
