//
// Created by ben.napier on 01/12/2017.
//

#ifndef CMATRIX_MATRIX_H
#define CMATRIX_MATRIX_H

#include <utility>
#include <vector>
#include <iostream>

class Mat {
private:
    std::vector<std::vector<long double>> mat_data;
    int rows, cols;

    void AllocateSpace();
    long double DeterminantCall(Mat& p_mat);
public:
    // Constructors
    Mat(); // default const
    Mat(int rows, int cols); // from rows and cols
    Mat(const Mat &p_mat); // from matrix

    // Operators
    long double& operator()(int x, int y);
    Mat& operator=(const Mat &rhs);
    Mat& operator+=(const Mat &rhs);
    Mat& operator-=(const Mat &rhs);
    Mat& operator*=(long double rhs);
    Mat& operator*=(const Mat &rhs);
    Mat& operator/=(long double rhs);

    // Operations
    Mat Transpose();
    Mat RemoveRow(int row);
    Mat RemoveCol(int col);
    long double det();
    Mat Inverse();
    Mat HorizontalConcatenate(const Mat &rhs);

    // Static functions
    static Mat Identity(int size);

    // Misc functions
    void print();


};


#endif //CMATRIX_MATRIX_H
