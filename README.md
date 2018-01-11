# cmatrix
C++ matrix library.

# Usage
```c++
mat x = mat(2, 2); // Creates a 2 x 2 matrix filled withs 0s.
x = mat::identity(2) // Creates a 2 x 2 identity matrix.
```
## Addition
```c++
mat_a = mat_b + mat_c;
```

## Subtraction
```c++
mat_a = mat_b - mat_c;
```

## Multiplication
```c++
mat_a = mat_b * mat_c
```
## Transposition
```c++
mat_a = mat_b.transpose()
```
## Determinant
```c++
float_a = mat_a.det()
```
