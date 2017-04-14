#include "0316038_matrix33.h"
#include <iostream>

using namespace std;

/*constructor*/
// constructor with initializing vector values
matrix33::matrix33(vector3 vec1, vector3 vec2, vector3 vec3)
{
    vec[0]=vec1;
    vec[1]=vec2;
    vec[2]=vec3;
}

// constructor with initializing matrix33
matrix33::matrix33(const matrix33 &m)
{
    vec[0]=m.vec[0];
    vec[1]=m.vec[1];
    vec[2]=m.vec[2];
}

/* Operators */
// access element
vector3& matrix33::operator[](unsigned int index)
{
    return this->vec[index];
}

const vector3& matrix33::operator[](unsigned int index) const
{
    return this->vec[index];
}

matrix33& matrix33::operator=(const matrix33 &m)
{
    vec[0]=m.vec[0];
    vec[1]=m.vec[1];
    vec[2]=m.vec[2];
    return *this;
}

matrix33& matrix33::operator*=(float f)
{
    vec[0]*=f;
    vec[1]*=f;
    vec[2]*=f;
    return *this;
}

matrix33 operator *(const matrix33 &m, float f)
{
    matrix33 result;
    result.vec[0]=m.vec[0]*f;
    result.vec[1]=m.vec[1]*f;
    result.vec[2]=m.vec[2]*f;
    return result;
}

matrix33 operator +(const matrix33 &a, const matrix33 &b)
{
    matrix33 result;
    result.vec[0]=a.vec[0]+b.vec[0];
    result.vec[1]=a.vec[1]+b.vec[1];
    result.vec[2]=a.vec[2]+b.vec[2];
    return result;
}

matrix33 operator *(const matrix33 &a, const matrix33 &b)
{
    matrix33 result;
    vector3 v1
    (a.vec[0].x*b.vec[0].x+a.vec[1].x*b.vec[0].y+a.vec[2].x*b.vec[0].z,
     a.vec[0].y*b.vec[0].x+a.vec[1].y*b.vec[0].y+a.vec[2].y*b.vec[0].z,
     a.vec[0].z*b.vec[0].x+a.vec[1].z*b.vec[0].y+a.vec[2].z*b.vec[0].z);
    
    vector3 v2
    (a.vec[0].x*b.vec[1].x+a.vec[1].x*b.vec[1].y+a.vec[2].x*b.vec[1].z,
     a.vec[0].y*b.vec[1].x+a.vec[1].y*b.vec[1].y+a.vec[2].y*b.vec[1].z,
     a.vec[0].z*b.vec[1].x+a.vec[1].z*b.vec[1].y+a.vec[2].z*b.vec[1].z);
    
    vector3 v3
    (a.vec[0].x*b.vec[2].x+a.vec[1].x*b.vec[2].y+a.vec[2].x*b.vec[2].z,
     a.vec[0].y*b.vec[2].x+a.vec[1].y*b.vec[2].y+a.vec[2].y*b.vec[2].z,
     a.vec[0].z*b.vec[2].x+a.vec[1].z*b.vec[2].y+a.vec[2].z*b.vec[2].z);
    
    result.setmatrix(v1,v2,v3);
    return result;
}

bool operator ==(const matrix33 &a, const matrix33 &b)
{
    if(a.vec[0]==b.vec[0] && a.vec[1]==b.vec[1] && a.vec[2]==b.vec[2])
        return 1;
    else
        return 0;
}

bool operator !=(const matrix33 &a, const matrix33 &b)
{
    if(a.vec[0]==b.vec[0] && a.vec[1]==b.vec[1] && a.vec[2]==b.vec[2])
        return 0;
    else
        return 1;
}

/* Methods */
void matrix33::printMatrix() const
{
    cout << vec[0].x << " " << vec[1].x << " " << vec[2].x << endl;
    cout << vec[0].y << " " << vec[1].y << " " << vec[2].y << endl;
    cout << vec[0].z << " " << vec[1].z << " " << vec[2].z;
}

matrix33& matrix33::invert()
{
    static matrix33 result;
    int det=this->determinant();
    
    vector3 v1(vec[1].y*vec[2].z-vec[2].y*vec[1].z,
               vec[2].y*vec[0].z-vec[0].y*vec[2].z,
               vec[0].y*vec[1].z-vec[1].y*vec[0].z);
    vector3 v2(vec[2].x*vec[1].z-vec[1].x*vec[2].z,
               vec[0].x*vec[2].z-vec[2].x*vec[0].z,
               vec[1].x*vec[0].z-vec[0].x*vec[1].z);
    vector3 v3(vec[1].x*vec[2].y-vec[2].x*vec[1].y,
               vec[2].x*vec[0].y-vec[0].x*vec[2].y,
               vec[0].x*vec[1].y-vec[1].x*vec[0].y);
    result.setmatrix(v1/det,v2/det,v3/det);
    return result;
}

matrix33& matrix33::identity()
{
    vector3 v1(1,0,0);
    vector3 v2(0,1,0);
    vector3 v3(0,0,1);
    this->setmatrix(v1,v2,v3);
    return *this;
}

void matrix33::setmatrix(vector3 vec1, vector3 vec2, vector3 vec3)
{
    vec[0]=vec1;
    vec[1]=vec2;
    vec[2]=vec3;
}

int matrix33::determinant()
{
    int det;
    det=vec[0].x*(vec[1].y*vec[2].z-vec[2].y*vec[1].z)
        -vec[1].x*(vec[0].y*vec[2].z-vec[2].y*vec[0].z)
        +vec[2].x*(vec[0].y*vec[1].z-vec[1].y*vec[0].z);
    return det;
}
