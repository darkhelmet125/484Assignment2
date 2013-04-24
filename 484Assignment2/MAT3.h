#ifndef __MAT3_H__
#define __MAT3_H__

#include "VEC3.h"
#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>

class MAT3{
private:
    float components[9];
public:
    MAT3();
    MAT3(float a, float b, float c,
         float d, float e, float f,
         float g, float h, float i);
    MAT3( float* array);
    MAT3(const VEC3& a, const VEC3& b, const VEC3& c);
    bool operator ==(const MAT3& m);
	bool operator !=(const MAT3& m);
	MAT3 operator =(const MAT3& m);
	MAT3 operator +(const MAT3& m);
	MAT3 operator -(const MAT3& m);
	MAT3 operator -();
	MAT3 operator *(const MAT3& m);
	MAT3 operator *(const float& s);
	MAT3 operator /(const float& s);
	float& operator()(const size_t& col, const size_t& row);
	VEC3 column(const size_t& columnIndex);
	VEC3 row(const size_t& rowIndex);
	MAT3 transpose();
	float determinant();
	MAT3 inverse( float* determnant);
    MAT3 adjoint();
};
MAT3 rotate(const float degrees, const float x, const float y, const float z);
MAT3 scale(float a, float b, float c);

#endif