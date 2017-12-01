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
    std::vector<std::vector<double>> mat_data;
    int rows, cols;

    void AllocateSpace();
public:
    // Constructors
    mat(); // default const
    mat(int rows, int cols); // from rows and cols
    mat(const mat &p_mat);

    // Operators
    double& operator()(int x, int y);
    mat& operator=(const mat &rhs);
    mat& operator+=(const mat &rhs);
    mat& operator-=(const mat &rhs);
    mat& operator*=(double rhs);
    mat& operator*=(const mat &rhs);

    mat& transpose();

    // Static functions
    static mat identity(int size);


    // Misc functions
    void print();


};


#endif //CMATRIX_MATRIX_H
