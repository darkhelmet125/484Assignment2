#include "myGL.h"
#include <stack>

/* Do not edit these variables. */
bool myMatrixModeOn;
bool myTranslateOn;
bool myRotateOn;
bool myScaleOn;
bool myLookAtOn;
bool myFrustumOn;
bool myPerspectiveOn;
bool myOrthoOn;
std::stack<MAT3>* myProjectionStack;
std::stack<MAT3>* myModelingStack;
int _myMatrixMode;

/* To toggle something on or off, change from false to true. */
void myGLInit( )
{
    myMatrixModeOn = true;
    myTranslateOn = true;
    myRotateOn = true;
    myScaleOn = true;
    myLookAtOn = true;
    myFrustumOn = true;
    myPerspectiveOn = true;
    myOrthoOn = true;
    if( myMatrixModeOn )
    {
        myProjectionStack = new std::stack<MAT3>( );
        myModelingStack = new std::stack<MAT3>( );
        glGetIntegerv(GL_MATRIX_MODE, &_myMatrixMode);
    }
}

//********************************** Wait to code these ****************************

void myMatrixMode( GLenum mode ){
    if( myMatrixModeOn ){
        _myMatrixMode = mode;
    }else{
        glMatrixMode(mode);
    }
}

void myPushMatrix( ){
    if( myMatrixModeOn ){
        if(_myMatrixMode == GL_MODELVIEW){
            // your code here
        }else if(_myMatrixMode == GL_PROJECTION){
            // your code here
        }
    }else{
        glPushMatrix( );
    }
}

void myPopMatrix( ){
    if( myMatrixModeOn ){
        if(_myMatrixMode == GL_MODELVIEW){
            // your code here
        }else if(_myMatrixMode == GL_PROJECTION){
            // your code here
        }
    }else{
        glPopMatrix( );
    }
}

void myLoadIdentity( ){
    if( myMatrixModeOn ){
        if(_myMatrixMode == GL_MODELVIEW){
            // your code here
        }else if(_myMatrixMode == GL_PROJECTION){
            // your code here
        }
    }else{
        glLoadIdentity( );
    }
}

//********************************** End wait to code these ****************************

void copyTo4By4Matrix(float *m, MAT3 a)
{
    m[0] = a(0,0);
    m[1] = a(0,1);
    m[2] = a(0,2);
    m[4] = a(1,0);
    m[5] = a(1,1);
    m[6] = a(1,2);
    m[8] = a(2,0);
    m[9] = a(2,1);
    m[10] = a(2,2);
}

void multiply4by4By4by4(float result[16], float mat1[16], float mat2[16])
{
    result[0] = mat1[0]*mat2[0] + mat1[4]*mat1[1] + mat1[8]*mat2[2] + mat1[12]*mat1[3];
    result[4] = mat1[0]*mat2[4] + mat1[4]*mat1[5] + mat1[8]*mat2[6] + mat1[12]*mat1[7];
    result[8] = mat1[0]*mat2[8] + mat1[4]*mat1[9] + mat1[8]*mat2[10] + mat1[12]*mat1[11];
    result[12] = mat1[0]*mat2[12] + mat1[4]*mat1[13] + mat1[8]*mat2[15] + mat1[12]*mat1[16];
    
    result[1] = mat1[1]*mat2[0] + mat1[5]*mat1[1] + mat1[9]*mat2[2] + mat1[13]*mat1[3];
    result[5] = mat1[1]*mat2[4] + mat1[5]*mat1[5] + mat1[9]*mat2[6] + mat1[13]*mat1[7];
    result[9] = mat1[1]*mat2[8] + mat1[5]*mat1[9] + mat1[9]*mat2[10] + mat1[13]*mat1[11];
    result[13] = mat1[1]*mat2[12] + mat1[5]*mat1[13] + mat1[9]*mat2[15] + mat1[13]*mat1[16];
    
    result[2] = mat1[2]*mat2[0] + mat1[6]*mat1[1] + mat1[10]*mat2[2] + mat1[14]*mat1[3];
    result[6] = mat1[2]*mat2[4] + mat1[6]*mat1[5] + mat1[10]*mat2[6] + mat1[14]*mat1[7];
    result[10] = mat1[2]*mat2[8] + mat1[6]*mat1[9] + mat1[10]*mat2[10] + mat1[14]*mat1[11];
    result[14] = mat1[2]*mat2[12] + mat1[6]*mat1[13] + mat1[10]*mat2[15] + mat1[14]*mat1[16];
    
    result[3] = mat1[3]*mat2[0] + mat1[7]*mat1[1] + mat1[11]*mat2[2] + mat1[15]*mat1[3];
    result[7] = mat1[3]*mat2[4] + mat1[7]*mat1[5] + mat1[11]*mat2[6] + mat1[15]*mat1[7];
    result[11] = mat1[3]*mat2[8] + mat1[7]*mat1[9] + mat1[11]*mat2[10] + mat1[15]*mat1[11];
    result[15] = mat1[3]*mat2[12] + mat1[7]*mat1[13] + mat1[11]*mat2[15] + mat1[15]*mat1[16];
}

MAT3 copyTo3By3Matrix(float *m)
{
    return MAT3(m[0],m[1],m[2],
                m[4],m[5],m[6],
                m[8],m[9],m[10]);
}

void myTranslatef( float x, float y, float z )
{
    if( myTranslateOn )
    {
        float mat[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, mat);
        
        mat[12] = mat[0]*x + mat[4]*y + mat[8]*z + mat[12];
        mat[13] = mat[1]*x + mat[5]*y + mat[9]*z + mat[13];
        mat[14] = mat[2]*x + mat[6]*y + mat[10]*z + mat[14];
        mat[15] = 1.0;
        
        glLoadMatrixf(mat);
    }
    else
    {
        glTranslatef( x, y, z );
    }
}

void myRotatef( float angle, float x, float y, float z)
{
    if( myRotateOn )
    {
        float tempMat[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, tempMat);
        
        MAT3 mat = copyTo3By3Matrix(tempMat);
        MAT3 matRotate = rotate(angle, x, y, z);
        MAT3 xRotation = mat * matRotate;
        copyTo4By4Matrix(tempMat, xRotation);
        
        glLoadMatrixf(tempMat);
    }
    else
    {
        glRotatef(angle, x, y, z);
    }
}

void myScalef(float x, float y, float z )
{
    if(myScaleOn)
    {
        float m[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, m);
        
        MAT3 mat = copyTo3By3Matrix(m);
        MAT3 scalem = scale(x, y, z);
        MAT3 xScale = mat * scalem;
        copyTo4By4Matrix(m, xScale);
        
        glLoadMatrixf(m);
    }
    else
    {
        glScalef(x, y, z);
    }
}

void myLookAt(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX, double upY, double upZ)
{
    if( myLookAtOn )
    {
        VEC3 center = {centerX, centerY, centerZ};
        VEC3 eye = {eyeX, eyeY, eyeZ};
        VEC3 up = {upX, upY, upZ};
        
        VEC3 F = center - eye;
        VEC3 f = F.normalize();
        VEC3 UP = up.normalize();
        VEC3 s = cross(f, UP);
        VEC3 u = cross(s, f);
        
        MAT3 mat;
        mat(0,0) = s[0];
        mat(0,1) = u[0];
        mat(0,2) = -f[0];
        mat(1,0) = s[1];
        mat(1,1) = u[1];
        mat(1,2) = -f[1];
        mat(2,0) = s[2];
        mat(2,1) = u[2];
        mat(2,2) = -f[2];
        float mat4By4[16];
        copyTo4By4Matrix(mat4By4, mat);
        
        glMultMatrixf(mat4By4);
        myTranslatef(-eyeX, -eyeY, -eyeZ);
    }
    else
    {
        gluLookAt( eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
    }
}

void myFrustum(double left, double right, double bottom, double top, double zNear, double zFar)
{
    if( myFrustumOn )
    {
        float frustrummatrix[16];
        float rMINl = (2.0*zNear)/(right - left);
        float tMINb = (2.0*zNear)/(top - bottom);
        float A = (right + left)/(right - left);
        float B = (top + bottom)/(top - bottom);
        float C = -((zFar +zNear)/(zFar - zNear));
        float D = -((2.0*zFar * zNear)/(zFar - zNear));
        
        frustrummatrix[0] = rMINl;
        frustrummatrix[1] = 0.0;
        frustrummatrix[2] = 0.0;
        frustrummatrix[3] = 0.0;
        frustrummatrix[4] = 0.0;
        frustrummatrix[5] = tMINb;
        frustrummatrix[6] = 0.0;
        frustrummatrix[7] = 0.0;
        frustrummatrix[8] = A;
        frustrummatrix[9] = B;
        frustrummatrix[10] = C;
        frustrummatrix[11] = -1.0;
        frustrummatrix[12] = 0.0;
        frustrummatrix[13] = 0.0;
        frustrummatrix[14] = D;
        frustrummatrix[15] = 0.0;
        
        glMultMatrixf(frustrummatrix);
    }
    else
    {
        glFrustum(left, right, bottom, top, zNear, zFar);
    }
}

void myPerspective(double fovy, double aspect, double zNear, double zFar){
    if( myPerspectiveOn )
    {
        float f =1/(tan(fovy/2));
        float mat[16];
        float fDIV = f/aspect;
        float zADD = (zFar + zNear)/(zNear - zFar);
        float zMULT = (2.0 * zFar * zNear)/(zNear - zFar);
        
        mat[0] = fDIV;
        mat[1] = 0.0;
        mat[2] = 0.0;
        mat[3] = 0.0;
        mat[4] = 0.0;
        mat[5] = f;
        mat[6] = 0.0;
        mat[7] = 0.0;
        mat[8] = 0.0;
        mat[9] = 0.0;
        mat[10] = zADD;
        mat[11] = -1.0;
        mat[12] = 0.0;
        mat[13] = 0.0;
        mat[14] = zMULT;
        mat[15] = 0.0;
        
        glMultMatrixf(mat);
    }
    else
    {
        gluPerspective(fovy, aspect, zNear, zFar);
    }
}

void myOrtho(double left, double right, double bottom, double top, double zNear, double zFar )
{
    if( myOrthoOn )
    {
        float rMINl = 2.0/(right - left);
        float tMINb = 2.0/(top - bottom);
        float fMINn = -2.0/(zFar -zNear);
        float tx = -(right + left)/(right-left);
        float ty = -(top + bottom)/(top - bottom);
        float tz = -(zFar + zNear)/(zFar-zNear);
        
        float mat[16];
        mat[0] = rMINl;
        mat[1] = 0.0;
        mat[2] = 0.0;
        mat[3] = 0.0;
        mat[4] = 0.0;
        mat[5] = tMINb;
        mat[6] = 0.0;
        mat[7] = 0.0;
        mat[8] = 0.0;
        mat[9] = 0.0;
        mat[10] = fMINn;
        mat[11] = 0.0;
        mat[12] = tx;
        mat[13] = ty;
        mat[14] = tz;
        mat[15] = 1.0;
        
        float currentMat[16];
        float projectionMat[16];

        glGetFloatv(GL_PROJECTION_MATRIX, currentMat);
        multiply4by4By4by4(projectionMat, currentMat, mat);
        glLoadMatrixf(projectionMat);
    }
    else
    {
        glOrtho(left, right, bottom, top, zNear, zFar);
    }
}

void toggleMyMatrixMode( )
{
    printf("toggleMyMatrixMode not implemented\n");
}

void toggleMyTranslate( )
{
    printf("toggleMyTranslate not implemented\n");
}

void toggleMyRotate( )
{
    printf("toggleMyRotate not implemented\n");
}

void toggleMyScale( )
{
    printf("toggleMyScale not implemented\n");
}

void toggleMyLookAt( )
{
    printf("toggleMyLookAt not implemented\n");
}

void toggleMyFrustum( )
{
    printf("toggleMyFrustum not implemented\n");
}

void toggleMyPerspective( )
{
    printf("toggleMyPerspective not implemented\n");
}

void toggleMyOrtho( )
{
    printf("toggleMyOrtho not implemented\n");
}