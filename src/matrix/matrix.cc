// Pre-processor directives to prevent redundant library loading
#ifndef CW13_MATRIX_CPP_
#define CW13_MATRIX_CPP_

// include the header declarations
#include "matrix.h"
#include <iostream>
#include <fstream>
//*************
//
// CONSTRUCTORS
//
//*************

// Default constructor
template<typename T> 
Matrix<T>::Matrix(unsigned int _rows, unsigned int _cols, const T& _initial) {
    // use vector method to resize outer vector of rows to length _rows
    // this is like preallocating a numpy array of zeros of the proper length
    mat.resize(_rows);
    for (unsigned int i=0; i<mat.size(); i++) {
        // for each row, resize to length _cols of columns
        // and initialize elements to value _initial
        mat[i].resize(_cols, _initial);
    }
    // set private fields rows and cols properly
    // These lines are why there is a convention of passing underscore-prefixed
    // variable names to the constructor function, which each correspond to one
    // of the attributes of the class needing to be set
    rows = _rows;
    cols = _cols;
}

// "Rule of 3" memory management:
// 1) Copy-constructor
//    This performs a "shallow copy" of the data in rhs, meaning that
//    the instances are different, but the memory contained in this->mat
//    is the same as the memory contained in rhs.mat at the end
template<typename T> Matrix<T>::Matrix(const Matrix<T>& rhs) {
    // Simply set private fields according to fields
    // of existing Matrix<T> object
    //
    // Note the convention of calling the object on the right-hand-side
    // of the operation "rhs" - this happens frequently in C++
    mat = rhs.mat;
    rows = rhs.get_rows();
    cols = rhs.get_cols();
}

// 2) Destructor
// No memory is dynamically allocated in the class,
// so just use default compiler cleanup of memory 
template<typename T> Matrix<T>::~Matrix() {}

// 3) Assignment operator
//    This performs a "deep copy" of the data in rhs, meaning that
//    the instances are different, and all memory is copied to new
//    and distinct memory locations
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
    // If assigning to itself, just return itself
    // Note dereferencing of "this", since "this" is a pointer to the instance
    if (&rhs == this)
        return *this;
  
    // Acquire new rows and cols
    unsigned int new_rows = rhs.get_rows();
    unsigned int new_cols = rhs.get_cols();
  
    // resize to new number of rows
    // Note that in the constructor the field mat of the current instance
    // is just available in the local scope. In Python, this would be self.mat
    mat.resize(new_rows);
    // resize each row to new number of cols
    for (unsigned int i=0; i<mat.size(); i++) {
        mat[i].resize(new_cols);
    }
  
    // assign each element 
    for (unsigned int i=0; i<new_rows; i++) {
        for (unsigned int j=0; j<new_cols; j++) {
            mat[i][j] = rhs(i, j);
        }
    }
  
    // store new number of rows and columns
    // Note, in python this would be self.rows and self.cols
    rows = new_rows;
    cols = new_cols;
  
    // return newly modified object
    return *this;
}



//*************
//
// ACCESSORS
//
//*************


// Access individual elements (non-const: read + write)
// Note that it returns a reference to the type stored in the matrix,
// so it doesn't create a new copy of the accessed value
template<typename T>
T& Matrix<T>::operator() (const unsigned int &row, const unsigned int &col) {
    return this->mat[row][col];
}

// Access individual elements (const: read only)
// Note this is almost identical to above, but is needed for when the constancy
// of a read-only access must be guaranteed by the type signature of what uses
// this method
template<typename T>
const T& Matrix<T>::operator() (const unsigned int &row, const unsigned int &col) 
const {
    return this->mat[row][col];
}

// Get number of rows
template<typename T>
unsigned int Matrix<T>::get_rows() const {
    return this->rows;
}

// Get number of cols
template<typename T>
unsigned int Matrix<T>::get_cols() const {
    return this->cols;
}

template<typename T>
void Matrix<T>::print(){
  for (unsigned int i=0; i<this->get_rows(); i++) {
      for (unsigned int j=0; j<this->get_cols(); j++) {
          std::cout <<this->mat[i][j] << "\t";
      }
      std::cout << std::endl;
  }
}

template<typename T>
void Matrix<T>::save(std::string filename){
    std::ofstream myfile;
    myfile.open (filename);
     for (unsigned int j=0; j<rows; j++) {
        for (unsigned int i=0; i<cols; i++) {
           myfile <<this->mat[i][j]<<",";
        }
         myfile <<"\n";
    }
    myfile.close();
}

//*********************
//
// OPERATOR OVERLOADING
//
//*********************


// Addition of two matrices
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) {
    // Create new matrix to store result, initialize to zero
    Matrix<T> result(rows, cols, (T)0.0);
  
    // Add each matrix element-by-element
    for (unsigned int i=0; i<rows; i++) {
        for (unsigned int j=0; j<cols; j++) {
            result(i,j) = this->mat[i][j] + rhs(i,j);
        }
    }
  
    return result;
}
// multiplication
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) {
    // Create new matrix to store result, initialize to zero
    Matrix<T> result(rows, rhs.get_cols(), (T)0.0);
    
    // Add each matrix element-by-element
    for (unsigned int i=0; i<rows; i++) {
        for (unsigned int j=0; j<rhs.get_cols(); j++) {
          int sum = 0;
          for( unsigned int k=0; k< cols; k++){
            sum = sum + this->mat[i][k] * rhs(k,j);
          }
            result(i,j) = sum;
        }
    }

    return result;
}


// Addition of scalar to matrix
template<typename T>
Matrix<T> Matrix<T>::operator+(long double val){
     Matrix<T> result(rows, cols, (T)0.0);
        // Add each matrix element-by-element
    for (unsigned int i=0; i<rows; i++) {
        for (unsigned int j=0; j<cols; j++) {
            result(i,j) = this->mat[i][j] + val;
        }
    }

    return result;
}


#endif // CW13_MATRIX_CPP_
