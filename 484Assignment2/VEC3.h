#ifndef __VEC3_H__
#define __VEC3_H__

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

enum values {
    x = 0,
    y = 1,
    z = 2
};

const float EPSILON = .0000001;
#define VEC3_SIZE 3

#ifndef M_PI
#define M_PI        3.14159265358979323846264338327950288
#endif

#ifndef DEG2RAD
#define DEG2RAD( theta ) ((theta) * (M_PI/180.0))
#endif

#ifndef RAD2DEG
#define RAD2DEG( theta ) ((theta) * (180.0/M_PI))
#endif

#ifndef ABS
#define ABS( x ) ((x) < (0) ? (-x) : (x))
#endif

#ifndef SQR
#define SQR( x ) ((x) * (x))
#endif

#ifndef MAX
#define MAX( a, b ) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN( a, b ) ((a) < (b) ? (a) : (b))
#endif

#ifndef MSGFX_FP
#define MSGFX_FP

#define FP_EPSILON 1e-6
#define ALMOST_ZERO FP_EPSILON

#define FP_EQUAL(a, b, delta) ( ((a) == (b)) || \
((a)-(delta) < (b) && \
(a)+(delta) > (b)) )

#define FP_LT(a, b, delta)  (fabs((a) - (b)) < (delta))

#define FP_GT(a, b, delta)  (fabs((a) - (b)) > (delta))

#define IOS_FP_PRECISION 5
#endif


class VEC3 {
private:
    float components[3];
public:
    
    values space;
    VEC3();
    VEC3(float a, float b, float c);
    VEC3( const VEC3& v);
	explicit VEC3( const VEC3 * v);
    explicit VEC3( const float* a);
    ~VEC3();
    
    VEC3 operator+(const VEC3& v)const;
    VEC3 operator-(const VEC3& v);
	VEC3 operator-();
    VEC3 operator=( const VEC3 &v );
    VEC3 operator=(const VEC3* v);
	VEC3 operator=(const float* v);
    VEC3 operator*(const float scalar);
    VEC3 operator/=(const float scalar);
    VEC3 operator*=(const float scalar);
    VEC3 operator/(const float scalar);
    bool operator==(const VEC3& v);
    bool operator!=(const VEC3& v);
    float operator[](const size_t index) const;
	float& operator[](const size_t index);
    
    VEC3 normalize();
    float length();
	float squarelength();
    float dot (const VEC3& v);
    float x() const;
    float y() const;
    float z() const;
    void setX( float x);
    void setY( float y);
    void setZ( float z);
    
    std::ostream& write(std::ostream& out ) const{
        out << "[";
        for( int i = 0; i < 3; i++ ){
            out << components[i];
            if( i < 2 ){
                out << std::endl;
            }
        }
        out << "]" << std::endl;
        return(out);
    }
};
/*
 *          End of VEC3 class
 */

VEC3 operator* (const float scalar, VEC3& v);
VEC3 cross(const VEC3& a, const VEC3& b);
#endif