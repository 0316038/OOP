#ifndef _MATRIX33_H_
#define _MATRIX33_H_
#include "0316038_vector3.h"

class matrix33 
{  
public:
    vector3 vec[3];
public:
    /*constructor*/
    // default constructor -- don't do anything with it
    matrix33() {};
    
    // constructor with initializing vector values
    matrix33(vector3 vec1, vector3 vec2, vector3 vec3);
    
    // constructor with initializing matrix33
    matrix33(const matrix33 &m);
    
public:
    /* Operators */
    // access element
    vector3& operator [](unsigned int index);
    const vector3& operator [] (unsigned int index) const;
    
    matrix33& operator = (const matrix33 &m);
    matrix33& operator *=(float f);
    friend matrix33 operator *(const matrix33 &m, float f);
    friend matrix33 operator +(const matrix33 &a, const matrix33 &b);
    friend matrix33 operator *(const matrix33 &a, const matrix33 &b);
    friend bool     operator == (const matrix33 &a, const matrix33 &b);
    friend bool     operator != (const matrix33 &a, const matrix33 &b);
    
public:
    /* Methods */
    void printMatrix() const;
    matrix33& invert();
    matrix33& identity();
    void setmatrix(vector3 vec1, vector3 vec2, vector3 vec3);
    int determinant();
};

#endif
