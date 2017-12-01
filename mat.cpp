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

double& mat::operator()(int x, int y) {
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

mat& mat::operator*=(double rhs) {
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

    mat return_val(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                return_val.mat_data[i][j] += mat_data[i][k] * rhs.mat_data[k][j];
            }
        }
    }

    return (*this = return_val);
}

mat& mat::transpose() {
    mat return_val(cols, rows);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            return_val.mat_data[j][i] = mat_data[i][j];
        }
    }

    return return_val;
}

mat &mat::RemoveRow(int row) {
    if (row >= rows) {
        std::cerr << "cmatrix error: row out of range for row removal, "
                "returning original matrix.";
        return *this;
    }

    mat_data.erase(mat_data.begin() + row);
    rows--;
    return *this;
}

mat &mat::RemoveCol(int col) {
    if (col >= cols) {
        std::cerr << "cmatrix error: column out of range for column removal, "
                "returning original matrix";
        return *this;
    }

    for (int i = 0; i < cols; ++i) {
        mat_data[i].erase(mat_data[i].begin() + col);
    }
    cols--;
    return *this;
}

double mat::det() {
    if (rows != cols) {
        std::cerr << "cmatrix error: non-square matrix for determinant,"
                "returning 0." << std::endl;
        return 0;
    }

}

/*
 * Static functions
 */

mat mat::identity(int size) {
    mat return_val(size, size);
    for (int i = 0; i < size; ++i) {
        return_val(i, i) = 1;
    }
    return return_val;
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
    auto temp_col = std::vector<double>(static_cast<unsigned int>(cols));
    mat_data = std::vector<std::vector<double>>(static_cast<unsigned int>(rows), temp_col);
}

double mat::DeterminantCall(const mat& p_mat) {
    if (p_mat.rows == 1) {
        return p_mat.mat_data[0][0];
    }
    for (int i = 0; i < p_mat.rows; ++i) {

    }
}

