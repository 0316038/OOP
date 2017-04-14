#include "0316038_vector3.h"
#include <iostream>
#include <math.h>
using namespace std;

/* constructors */
// constructor with initializing float values
vector3 :: vector3(float inX, float inY, float inZ)
{
    x=inX;
    y=inY;
    z=inZ;
}

// constructor with initializing vector3
vector3 :: vector3(const vector3 &v)
{
    x=v.x;
    y=v.y;
    z=v.z;
}

/* Operators */
// access element
float& vector3::operator [] (unsigned int index)
{
    if(index==0) return x;
    else if(index==1) return y;
    else return z;
}

const float& vector3::operator [] (unsigned int index) const
{
    if(index==0) return x;
    else if(index==1) return y;
    else return z;

}

vector3& vector3::operator = (const vector3 &v)
{
    x=v.x;
    y=v.y;
    z=v.z;
    return *this;
}

vector3& vector3::operator += (const vector3 &v)
{
    x+=v.x;
    y+=v.y;
    z+=v.z;
    return *this;
}

vector3& vector3::operator -= (const vector3 &v)
{
    x-=v.x;
    y-=v.y;
    z-=v.z;
    return *this;
}

vector3& vector3::operator *= (float f)
{
    x*=f;
    y*=f;
    z*=f;
    return *this;
}

vector3& vector3::operator /= (float f)
{
    x/=f;
    y/=f;
    z/=f;
    return *this;
}

bool operator == (const vector3 &a,const vector3 &b)
{
    if(a.x==b.x && a.y==b.y && a.z==b.z) return 1;
    else return 0;
}

bool operator != (const vector3 &a,const vector3 &b)
{
    if(a.x==b.x && a.y==b.y && a.z==b.z) return 0;
    else return 1;
}

vector3 operator -(const vector3 &a)
{
    vector3 result;
    result.x=-a.x;
    result.y=-a.y;
    result.z=-a.z;
    return result;
}

vector3 operator +(const vector3 &a,const vector3 &b)
{
    vector3 result;
    result.x=a.x+b.x;
    result.y=a.y+b.y;
    result.z=a.z+b.z;
    return result;
}

vector3 operator -(const vector3 &a,const vector3 &b)
{
    vector3 result;
    result.x=a.x-b.x;
    result.y=a.y-b.y;
    result.z=a.z-b.z;
    return result;
}

vector3 operator *(const vector3 &v,float f)
{
    vector3 result;
    result.x=v.x*f;
    result.y=v.y*f;
    result.z=v.z*f;
    return result;
}

vector3 operator *(float f,const vector3 &v)
{
    vector3 result;
    result.x=f*v.x;
    result.y=f*v.y;
    result.z=f*v.z;
    return result;
}

vector3 operator /(const vector3 &v,float f)
{
    vector3 result;
    result.x=v.x/f;
    result.y=v.y/f;
    result.z=v.z/f;
    return result;
}

/* Methods */

void vector3::set(float xIn, float yIn, float zIn)
{
    x=xIn;
    y=yIn;
    z=zIn;
}

float vector3::length() const
{
    return sqrt(x*x+y*y+z*z);
}

void vector3::printVector3() const
{
    cout << "(" << x << ", " << y << ", " << z << ")";
}
