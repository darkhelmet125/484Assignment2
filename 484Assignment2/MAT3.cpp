#include "MAT3.h"
MAT3 :: MAT3(){
    components[0]=1;
    components[1]=0;
    components[2]=0;
    components[3]=0;
    components[4]=1;
    components[5]=0;
    components[6]=0;
    components[7]=0;
    components[8]=1;
}

MAT3 :: MAT3( float a, float b, float c, float d, float e, float f, float g, float h, float i){
    components[0] = a;
    components[1] = b;
    components[2] = c;
    components[3] = d;
    components[4] = e;
    components[5] = f;
    components[6] = g;
    components[7] = h;
    components[8] = i;
}
MAT3 :: MAT3(float * array){
    for (int i = 0; i < 9; i++) {
        components[i] = array[i];
    }
}

MAT3 :: MAT3 (const VEC3& a, const VEC3& b, const VEC3& c){
    components[0]= a.x();
    components[1]= a.y();
    components[2]= a.z();
    components[3]= a.x();
    components[4]= a.y();
    components[5]= a.z();
    components[6]= a.x();
    components[7]= a.y();
    components[8]= a.z();
}

MAT3 MAT3 :: operator =(const MAT3& m){
    for( int i=0; i <9;i++){
        components[i] = m.components[i];
    }
    return( *this);
}
MAT3 MAT3 :: operator +(const MAT3& m){
    return(MAT3(components[0] + m.components[0],
                components[1] + m.components[1],
                components[2] + m.components[2],
                components[3] + m.components[3],
                components[4] + m.components[4],
                components[5] + m.components[5],
                components[6] + m.components[6],
                components[7] + m.components[7],
                components[8] + m.components[8]));
}
MAT3 MAT3 :: operator -(const MAT3& m){
    return(MAT3(components[0] - m.components[0],
                components[1] - m.components[1],
                components[2] - m.components[2],
                components[3] - m.components[3],
                components[4] - m.components[4],
                components[5] - m.components[5],
                components[6] - m.components[6],
                components[7] - m.components[7],
                components[8] - m.components[8]));
}
MAT3 MAT3 :: operator -(){
    return (MAT3 (-1*components[0],
                  -1*components[1],
                  -1*components[2],
                  -1*components[3],
                  -1*components[4],
                  -1*components[5],
                  -1*components[6],
                  -1*components[7],
                  -1*components[8]));
}
MAT3 MAT3 :: operator*(const float &m)
{
    return (MAT3 (m*components[0],
                  m*components[1],
                  m*components[2],
                  m*components[3],
                  m*components[4],
                  m*components[5],
                  m*components[6],
                  m*components[7],
                  m*components[8]));
}
MAT3 MAT3 :: operator*(const MAT3& m)
{
    float j , b, c , d, e , f , g, h, i;
    j = ((components[0]*m.components[0])+(components[3]*m.components[1])+(components[6]*m.components[2]));
    d = ((components[0]*m.components[3])+(components[3]*m.components[4])+(components[6]*m.components[5]));
    g = ((components[0]*m.components[6])+(components[3]*m.components[7])+(components[6]*m.components[8]));
    b = ((components[1]*m.components[0])+(components[4]*m.components[1])+(components[7]*m.components[2]));
    e = ((components[1]*m.components[3])+(components[4]*m.components[4])+(components[7]*m.components[5]));
    h = ((components[1]*m.components[6])+(components[4]*m.components[7])+(components[7]*m.components[8]));
    c = ((components[2]*m.components[0])+(components[5]*m.components[1])+(components[8]*m.components[2]));
    f = ((components[2]*m.components[3])+(components[5]*m.components[4])+(components[8]*m.components[5]));
    i = ((components[2]*m.components[6])+(components[5]*m.components[7])+(components[8]*m.components[8]));
    
    return (MAT3(j, b, c, d, e, f, g, h, i));
    
}
float& MAT3 :: operator()(const size_t &col, const size_t &row)
{
    size_t value = 0;
    if (col == 0)
    {
        value = 0 + row;
    }
    else  if (col == 1)
    {
        value = 3 + row;
    }
    else if (col == 2)
    {
        value = 6 + row;
    }
    
    return (components[value]);
    
    
}
MAT3 MAT3 :: operator/(const float& m)
{
    return (MAT3(components[0]/ m,
                 components[1]/ m,
                 components[2]/ m,
                 components[3]/ m,
                 components[4]/ m,
                 components[5]/ m,
                 components[6]/ m,
                 components[7]/ m,
                 components[8]/ m ));
}
bool MAT3 :: operator ==(const MAT3& m){
    return ((fabs(components[0] - m.components[0]) <= EPSILON) &&
            (fabs(components[1] - m.components[1]) <= EPSILON) &&
            (fabs(components[2] - m.components[2]) <= EPSILON) &&
            (fabs(components[3] - m.components[3]) <= EPSILON) &&
            (fabs(components[4] - m.components[4]) <= EPSILON) &&
            (fabs(components[5] - m.components[5]) <= EPSILON) &&
            (fabs(components[6] - m.components[6]) <= EPSILON) &&
            (fabs(components[7] - m.components[7]) <= EPSILON) &&
            (fabs(components[8] - m.components[8]) <= EPSILON));
}
bool MAT3 :: operator !=(const MAT3& m){
    return ((fabs(components[0] - m.components[0]) > EPSILON) ||
            (fabs(components[1] - m.components[1]) > EPSILON) ||
            (fabs(components[2] - m.components[2]) > EPSILON) ||
            (fabs(components[3] - m.components[3]) > EPSILON) ||
            (fabs(components[4] - m.components[4]) > EPSILON) ||
            (fabs(components[5] - m.components[5]) > EPSILON) ||
            (fabs(components[6] - m.components[6]) > EPSILON) ||
            (fabs(components[7] - m.components[7]) > EPSILON) ||
            (fabs(components[8] - m.components[8]) > EPSILON));
}
MAT3 MAT3 :: adjoint()
{
	//slow?
	return(MAT3(cross(row(1), row(2)), cross(row(2), row(0)), cross(row(0), row(1))));
}
MAT3 MAT3 :: transpose()
{
    return (MAT3 (components[0],
                  components[3],
                  components[6],
                  components[1],
                  components[4],
                  components[7],
                  components[2],
                  components[5],
                  components[8]));
}
float MAT3 ::determinant()
{
    float a = components[0] * components[4] * components[8];
    float b = components[3] * components[7] * components[2];
    float c = components[6] * components[1] * components[5];
    float d = components[2] * components[4] * components[6];
    float e = components[5] * components[7] * components[0];
    float f = components[8] * components[1] * components[3];
    float determinant = a + b + c - d - e - f;
    return (determinant);
}


MAT3 MAT3::inverse(float *determinant)
{
    MAT3 inverted = adjoint();
    float zero = 0.0;
    float check = fabs(*determinant - zero);
    if ( !(check > EPSILON))
    {
        inverted = inverted / *determinant;
    }
    return inverted;
}
VEC3 MAT3 :: column(const size_t& col)
{
    float x = 0;
    float y = 0;
    float z = 0;
    if (col == 1)
    {
        x = components[0];
        y = components[1];
        z = components[2];
    }
    else if (col == 2)
    {
        x = components[3];
        y = components[4];
        z = components[5];
    }
    else if (col == 3)
    {
        x = components[6];
        y = components[7];
        z = components[8];
    }
    return (VEC3(x, y, z));
}
VEC3 MAT3 :: row(const size_t& row)
{
    float x = 0;
    float y = 0;
    float z = 0;
    if (row == 1)
    {
        x = components[0];
        y = components[3];
        z = components[6];
    }
    else if (row == 2)
    {
        x = components[1];
        y = components[4];
        z = components[7];
    }
    else if (row == 3)
    {
        x = components[2];
        y = components[5];
        z = components[8];
    }
    return (VEC3(x, y, z));
}
MAT3 rotate(const float degrees, const float x, const float y, const float z) {
	MAT3 rotMat;
	float radians = DEG2RAD(degrees);
    
	rotMat(0,0) = SQR(x)*(1-cos(radians))+cos(radians);
	rotMat(0,1) = y*x*(1-cos(radians))+z*sin(radians);
	rotMat(0,2) = x*z*(1-cos(radians))-y*sin(radians);
	
	rotMat(1,0) = x*y*(1-cos(radians))-z*sin(radians);
	rotMat(1,1) = SQR(y)*(1-cos(radians))+cos(radians);
	rotMat(1,2) = y*z*(1-cos(radians))+x*sin(radians);
    
	rotMat(2,0) = x*z*(1-cos(radians))+y*sin(radians);
	rotMat(2,1) = y*z*(1-cos(radians))-x*sin(radians);
	rotMat(2,2) = SQR(z)*(1-cos(radians))+cos(radians);
	
	return rotMat;
}

MAT3 scale(float a, float b, float c) {
	MAT3 ret;
	ret(0,0) = a;
	ret(1,1) = b;
	ret(2,2) = c;
	return ret;
}