# cmatrix
C++ matrix library.

# Usage
We can use the following syntax to define matrices.
```c++
mat mat_a = mat(2, 2); // Creates a 2 x 2 matrix filled with 0s
mat_a = mat::identity(2) // Creates a 2 x 2 identity matrix
```
We can also access individual values.
```c++
mat_a(0, 0) = 5; // Sets the first value to 5
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
