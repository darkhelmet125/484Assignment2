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
std::stack<Mat3>* myProjectionStack;
std::stack<Mat3>* myModelingStack;
int _myMatrixMode;

/* To toggle something on or off, change from false to true. */
void myGLInit( ){
  myMatrixModeOn = false;
  myTranslateOn = false;
  myRotateOn = false;
  myScaleOn = false;
  myLookAtOn = false;
  myFrustumOn = false;
  myPerspectiveOn = false;
  myOrthoOn = false;
  if( myMatrixModeOn ){
    myProjectionStack = new std::stack<Mat3>( );
    myModelingStack = new std::stack<Mat3>( );
    glGetIntegerv(GL_MATRIX_MODE, &_myMatrixMode);
  }
}

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

void myTranslatef( float x, float y, float z ){
  if( myTranslateOn ){
    // your code here
  }else{
    glTranslatef( x, y, z );
  }
}
		 
void myRotatef( float angle, float x, float y, float z){
  if( myRotateOn ){
    // your code here
  }else{
    glRotatef(angle, x, y, z);
  }
}
		 
void myScalef(float x, float y, float z ){
  if(myScaleOn){
    double m[16];
    Mat3 aUniformScale = uniformScale(double(x));
    // copy aUniformScale into m
    copyToFourByFourMatrix(m, aUniformScale);
    glMultMatrixd(m);
  }else{
    glScalef(x, y, z);
  }
}
		  
void myLookAt(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX, double upY, double upZ){
  if( myLookAtOn ){
    // your code here
  }else{
    gluLookAt( eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
  }
}

void myFrustum(double left, double right, double bottom, double top, double zNear, double zFar){
  if( myFrustumOn ){
    // your code here
  }else{
    glFrustum(left, right, bottom, top, zNear, zFar);
  }
}

void myPerspective(double fovy, double aspect, double zNear, double zFar){
  if( myPerspectiveOn ){
    // your code here
  }else{
    gluPerspective(fovy, aspect, zNear, zFar);
  }
}

void myOrtho(double left, double right, double bottom, double top, double zNear, double zFar ){
  if( myOrthoOn ){
    // your code here
  }else{
    glOrtho(left, right, bottom, top, zNear, zFar);
  }
}


void toggleMyMatrixMode( ){
  printf("toggleMyMatrixMode not implemented\n");
}

void toggleMyTranslate( ){
  printf("toggleMyTranslate not implemented\n");
}

void toggleMyRotate( ){
  printf("toggleMyRotate not implemented\n");
}

void toggleMyScale( ){
  printf("toggleMyScale not implemented\n");
}

void toggleMyLookAt( ){
  printf("toggleMyLookAt not implemented\n");
}

void toggleMyFrustum( ){
  printf("toggleMyFrustum not implemented\n");
}

void toggleMyPerspective( ){
  printf("toggleMyPerspective not implemented\n");
}

void toggleMyOrtho( ){
  printf("toggleMyOrtho not implemented\n");
}

vec3 simpleshader(vec3& l, vec3& n, vec3& v)
{
	vec3 r;
	float costheta = r.dot(v);
	vec3 w(1.0,1.0,1.0);
	vec3 p(1.0,2.0,20.0);
	float red = w[0]*powf((costheta+1.0)/2.0,p[0]);
	float green = w[1]*powf((costheta+1.0)/2.0,p[1]);
	float blue = w[2]*powf((costheta+1.0)/2.0,p[2]);
	return(vec3(red,green,blue))
}