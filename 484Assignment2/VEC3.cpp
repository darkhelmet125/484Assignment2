#include "VEC3.h"
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


VEC3 :: VEC3()
{
    components[0] = 1;
    components[1] = 1;
    components[2] = 1;
}

VEC3 :: VEC3(float a, float b, float c)
{
    components[0] = a;
    components[1] = b;
    components[2] = c;
}

VEC3 :: VEC3( const VEC3& v)
{
    components[0] = v.components[0];
    components[1] = v.components[1];
    components[2] = v.components[2];
}

VEC3 :: VEC3( const VEC3 * v)
{
    components[0] = v->components[0];
    components[1] = v->components[1];
    components[2] = v->components[2];
}

VEC3 :: VEC3( const float* a)
{
    components[0] = a[0];
    components[1] = a[1];
    components[2] = a[2];
}

VEC3 VEC3 :: operator+(const VEC3& v)const
{
    return(VEC3(components[0] + v.components[0],
                components[1] + v.components[1],
                components[2] + v.components[2]));
}

VEC3 VEC3 :: operator - (const VEC3& v){
    return(VEC3(components[0] - v.components[0],
                components[1] - v.components[1],
                components[2] - v.components[2]));
}

VEC3 VEC3 :: operator =( const VEC3 &v )
{
    for( int i=0; i <3;i++){
        components[i] = v.components[i];
    }
    return( *this);
}

VEC3 VEC3 :: operator = (const VEC3* v)
{
    for( int i=0; i <3;i++){
        components[i] = v->components[i];
    }
    return( *this);
}

VEC3 VEC3 :: operator = (const float* v)
{
    for( int i=0; i <3;i++){
        components[i] = v[i];
    }
    return( *this);
}

VEC3 VEC3 :: operator*(const float scalar)
{
    return(VEC3(scalar * components[0], scalar * components[1], scalar * components[2]));
}

VEC3 VEC3 :: operator/=(const float scalar)
{
    components[0] = components[0] / scalar;
    components[1] = components[1] / scalar;
    components[2] = components[2] / scalar;
    return(VEC3(components[0], components[1], components[2]));
}

VEC3 VEC3 :: operator*=(const float scalar)
{
    components[0] = scalar * components[0];
    components[1] = scalar * components[1];
    components[2] = scalar * components[2];
    return(VEC3(components[0], components[1], components[2]));
}

VEC3 VEC3 :: operator/(const float scalar)
{
    return(VEC3(components[0] / scalar, components[1] / scalar, components[2] / scalar));
}

bool VEC3 :: operator== (const VEC3& v)
{
    return ((fabs(components[0] - v.components[0]) <= EPSILON) && (fabs(components[1] - v.components[1]) <= EPSILON) && ((fabs(components[2] - v.components[2]) <= EPSILON)));
}

bool VEC3 :: operator != (const VEC3& v)
{
    return ((fabs(components[0] - v.components[0])> EPSILON) || (fabs(components[1] - v.components[1])> EPSILON) || ((fabs(components[2] - v.components[2])> EPSILON)));
}

float VEC3 :: operator[](const size_t index) const
{
    if (index == 0)
    {
        return (components[0]);
    }
    else if (index == 1)
    {
        return (components[1]);
    }
    else if (index == 2)
    {
        return (components[2]);
    }
    else
    {
        throw("Index too large. Out of bounds.");
    }
}

float& VEC3 :: operator[](const size_t index)
{
    if (index == 0)
    {
        return (components[0]);
    }
    else if (index == 1)
    {
        return (components[1]);
    }
    else if (index == 2)
    {
        return (components[2]);
    }
    else
    {
        throw("Index too large. Out of bounds.");
    }
}

VEC3 VEC3 :: normalize()
{
    float len = length( );
    //std::cout << len << std::endl;
    for (int i=0; i < 3; i++){
        components[i]= components[i]/len;
    }
    return(VEC3(components[0], components[1], components[2]));
}

float VEC3 :: length()
{
    float length_tmp = 0.0;
	length_tmp = sqrt( SQR(components[0]) +
                      SQR(components[1]) +
                      SQR(components[2]) );
	return length_tmp;
}

float VEC3 :: squarelength()
{
    return pow(length(), 2);
}

float VEC3 :: dot (const VEC3& v)
{
    return ((components[0] * v.components[0]) +(components[1] * v.components[1]) + (components[2] * v.components[2]));
}

VEC3 VEC3 :: operator -()
{
    components[0] = -1 * components[0];
    components[1] = -1 * components[1];
    components[2] = -1 * components[2];
    
    return(VEC3(components[0], components[1], components[2]));
}

float VEC3 :: x() const
{
    return components[0];
}

float VEC3 :: y() const
{
    return components[1];
}

float VEC3 :: z() const
{
    return components[2];
}

void VEC3 :: setX( float x)
{
    components[0]=x;
}

void VEC3 :: setY( float y)
{
    components[1]=y;
}

void VEC3 :: setZ( float z)
{
    components[2]=z;
}

VEC3 operator* (const float scalar, VEC3& v)
{
    return(VEC3(scalar * v.x(), scalar * v.y(), scalar * v.z()));
}

VEC3 cross(const VEC3& a, const VEC3& b)
{
    float x = (a.y()*b.z())-(b.y()*a.z());
    float y = (a.z()*b.x())-(b.z()*b.x());
    float z = (a.x()*b.y())-(b.x()*a.y());
    
    return (VEC3(x, y, z));
}

VEC3 :: ~VEC3(){}