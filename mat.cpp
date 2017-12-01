//
// Created by ben.napier on 01/12/2017.
//

#include <cmath>
#include <iomanip>
#include "mat.h"

/*
 * Public member functions
 */

mat::mat() : rows(1), cols(1) {
    AllocateSpace();
    mat_data[0][0] = 0;
}

mat::mat(int rows, int cols) : rows(rows), cols(cols) {
    AllocateSpace();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat_data[i][j] = 0;
        }
    }
}

mat::mat(const mat& p_mat) : rows(p_mat.rows), cols(p_mat.cols) {
    AllocateSpace();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat_data[i][j] = p_mat.mat_data[i][j];
        }
    }
}

long double& mat::operator()(int x, int y) {
    return mat_data[x][y];
}


mat& mat::operator=(const mat& rhs) {
    if (this ==& rhs) {
        return *this;
    }

    rows = rhs.rows;
    cols = rhs.cols;
    AllocateSpace();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat_data[i][j] = rhs.mat_data[i][j];
        }
    }

    return *this;
}

mat& mat::operator+=(const mat& rhs) {
    if (rows != rhs.rows || cols != rhs.cols) {
        std::cerr << "cmatrix error: mismatch in size for matrix addition, returning original matrix." << std::endl;
        return *this;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat_data[i][j] += rhs.mat_data[i][j];
        }
    }

    return *this;
}

mat& mat::operator-=(const mat& rhs) {
    if (rows != rhs.rows || cols != rhs.cols) {
        std::cerr << "cmatrix error: mismatch in size for matrix subtraction, "
                "returning original matrix." << std::endl;
        return *this;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat_data[i][j] -= rhs.mat_data[i][j];
        }
    }

    return *this;
}

mat& mat::operator*=(long double rhs) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat_data[i][j] *= rhs;
        }
    }

    return *this;
}

mat& mat::operator*=(const mat& rhs) {
    if (cols != rhs.rows) {
        std::cerr << "cmatrix error: mismatch in size for matrix multiplication, "
                "returning original matrix." << std::endl;
    }

    mat return_value(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                return_value.mat_data[i][j] += mat_data[i][k] * rhs.mat_data[k][j];
            }
        }
    }

    return (*this = return_value);
}

mat &mat::operator/=(long double rhs) {
    if (rhs == 0) {
        std::cerr << "cmatrix error: division by 0 in matrix scalar division,"
                "returning original matrix.";
        return *this;
    }

    *this *= pow(rhs, -1);
    return *this;
}

mat mat::transpose() {
    mat return_value(cols, rows);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            return_value.mat_data[j][i] = mat_data[i][j];
        }
    }

    return return_value;
}

mat mat::RemoveRow(int row) {
    if (row >= rows || row < 0) {
        std::cerr << "cmatrix error: row out of range for row removal, "
                "returning original matrix.";
        return *this;
    }

    mat return_value(*this);
    return_value.mat_data.erase(return_value.mat_data.begin() + row);
    return_value.rows--;
    return return_value;
}

mat mat::RemoveCol(int col) {
    if (col >= cols || col < 0) {
        std::cerr << "cmatrix error: column out of range for column removal, "
                "returning original matrix";
        return *this;
    }

    mat return_value(*this);
    for (int i = 0; i < rows; ++i) {
        return_value.mat_data[i].erase(return_value.mat_data[i].begin() + col);
    }
    return_value.cols--;
    return return_value;
}

long double mat::det() {
    if (rows != cols) {
        std::cerr << "cmatrix error: non-square matrix for determinant,"
                "returning 0." << std::endl;
        return 0;
    }
    return DeterminantCall(*this);
}

mat mat::inverse() {
    if (rows != cols) {
        std::cerr << "cmatrix error: non-square matrix for inverse,"
                "returning original matrix." << std::endl;
        return *this;
    }

    mat return_value(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            return_value.mat_data[i][j] = pow(-1, i + j) * RemoveRow(i).RemoveCol(j).det() / det();
        }
    }
    return_value = return_value.transpose();
    return return_value;
}

/*
 * Static functions
 */

mat mat::identity(int size) {
    mat return_value(size, size);
    for (int i = 0; i < size; ++i) {
        return_value(i, i) = 1;
    }
    return return_value;
}

/*
 * Misc functions
 */

void mat::print() {
    for (int i = 0; i < rows; ++i) {
        std::cout << "(";
        for (int j = 0; j < cols; ++j) {
            std::cout << mat_data[i][j];
            if (j < cols - 1) {
                std::cout << ", ";
            }
        }
        std::cout << ")" << std::endl;
    }
}

/*
 * Private member functions
 */

void mat::AllocateSpace() {
    auto temp_col = std::vector<long double>(static_cast<unsigned int>(cols));
    mat_data = std::vector<std::vector<long double>>(static_cast<unsigned int>(rows), temp_col);
}

long double mat::DeterminantCall(mat& p_mat) {
    if (p_mat.rows == 1) {
        return p_mat.mat_data[0][0];
    }
    long double total = 0;
    mat temp;
    for (int i = 0; i < p_mat.cols; ++i) {
        temp = p_mat.RemoveRow(0).RemoveCol(i);
        total += pow(-1, i) * p_mat.mat_data[0][i] * DeterminantCall(temp);
    }
    return total;
}

