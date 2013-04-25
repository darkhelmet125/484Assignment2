
#ifdef __APPLE__
/* Apple's weird location of their OpenGL & GLUT implementation */
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif

#include <cstdlib>
#include <cstdio>
#include <string>
#include <cassert>

#include "SGFaceList.h"
#include "getopt.h"
#include "MAT3.h"
#include "VEC3.h"
#include "myGL.h"
/* Thanks to Apple's Sample Code... */
#include "SurfaceGeometry.h"

SGFaceList *gModel[kSurfaces];
unsigned int gCurrentModel;
VEC3 gLightPosition;

enum{R = 0, G, B};

struct cameraStruct //struct for camera
{
    VEC3 location;
    VEC3 gaze;
    VEC3 up;
};

cameraStruct gCamera;   //camera object

float gTranslation[3], gRotationAngle[3], gScaleFactor[3];

bool gMouseButtonDown, orthoProjection, cameraBool, flatShading;

int gMousePosition[2], windowSize[2];
double eyex = 0.0, eyey=0.0, eyez= -15.0;


void printVector(float v[3])
{
    printf( "(%g, %g, %g)\n", v[0], v[1], v[2] );
}

void usage( std::string msg ){
    std::cerr << msg << std::endl;
    std::cerr << "usage: psurfviewer [-v -h]" << std::endl;
    std::cerr << "                 or" << std::endl;
    std::cerr << "       psurfviewer [--verbose --help]" << std::endl;
}

/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
void init( void )
{
    
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glDisable( GL_LIGHTING );
    glEnable( GL_DEPTH_TEST );
    glFrontFace( GL_CCW );
 	
    for( int i = 0; i < kSurfaces; i++ ){
        gModel[i] = BuildGeometry( i, 4, 64, 24 );
    }
    gCurrentModel = 0;
    for( int i = 0; i < 3; i++ ){
        gRotationAngle[i] = 0.0f;
        gTranslation[i] = 0.0f;
        gScaleFactor[i] = 1.0f;
    }
    gMouseButtonDown = false;
    orthoProjection = false;
    gLightPosition.setX(1.25);
    gLightPosition.setY(1.25);
    gLightPosition.setZ(0.5);
    gCamera.location[0] = eyex;
    gCamera.location[1] = eyey;
    gCamera.location[2] = eyez;
    gCamera.gaze[0] = 0.0;
    gCamera.gaze[1] = 0.0;
    gCamera.gaze[2] = 0.0;
    gCamera.up[0] = 0.0;
    gCamera.up[1] = 1.0;
    gCamera.up[2] = 0.0;
    flatShading = false;
}

VEC3 simpleShader(VEC3& l, VEC3& n, VEC3& v)
{
    l = l.normalize();
    VEC3 r = (2*n) * (n.dot(l)) - l;
    float costheta = r.dot(v);
    costheta = DEG2RAD(costheta);
    VEC3 w(1.0, 1.0, 1.0);
    VEC3 p(1.0, 2.0, 20.0);
    //initialize red, green, blue colors
    float red = w[X] * powf((((costheta)+1.0)/2.0), p[X]);
    float green = w[Y]* powf((((costheta)+1.0)/2.0), p[Y]);
    float blue = w[Z]* powf((((costheta)+1.0)/2.0), p[Z]);
    VEC3 color(red,green,blue);
    //asserts used to make sure that colors are less than 1
    assert(red <= 1.0);
    assert(blue <= 1.0);
    assert(green <= 1.0);
    return(color);
}

void drawSurface( SGFaceList *f )
{
    int i = 0;
    int j = 0;
    int index;
    VEC3 color;
    VEC3 N, L, V;
    if( f->surface == kCube ){
        glEnable( GL_POLYGON_OFFSET_FILL );
        glBegin( GL_TRIANGLES );
        for( i = 0; i < f->fc; i++ )
        {
            for( j = 0; j < 3; j++ )
            {
                V = gCamera.location -VEC3( f->vertices[ f->faces[i][j] ] );
                L = gLightPosition -VEC3( f->vertices[ f->faces[i][j] ] );
                N = VEC3( f->v_normals[ f->faces[i][j] ] );
                color = simpleShader(L, N, V);
                glColor3f( color[0], color[1], color[2]);
                glVertex3fv( f->vertices[ f->faces[i][j] ] );
            }
        }
        glEnd( );
        glColor3f( 0.0, 0.0, 0.0 );
        for( i = 0; i < (f->fc); i++ ){
            glBegin( GL_LINE_LOOP );
            for( j = 0; j < 3; j++ ){
                glVertex3fv( f->vertices[ f->faces[i][j] ] );
            }
            glEnd( );
        }
        glDisable( GL_POLYGON_OFFSET_LINE );
    }else{
        
        for( i = 0; i < (f->maxI); i++ ){
            int fnormal_index=0;
            glBegin( GL_TRIANGLE_STRIP );
            for( j = 0; j <= (f->maxJ); j++ ){
                if(index - fnormal_index == 2){
                    //fnormal_index++;
                }
                index = (i % (f->maxI)) * (f->maxJ) + (j % (f->maxJ));
                
                V = gCamera.location - VEC3( f->vertices[index] );
                L = gLightPosition - VEC3( f->vertices[index] );
                
                if( flatShading == true ){
                    N = VEC3( f->f_normals[fnormal_index] );
                }else{
                    N = VEC3( f->v_normals[index] );
                }
                color = simpleShader(L, N, V);
                glColor3f( color[0], color[1], color[2]);
                
                glVertex3fv( f->vertices[index] );
                
                index = ((i + 1) % f->maxI) * f->maxJ + (j % f->maxJ);
                
                V = gCamera.location - VEC3( f->vertices[index] );
                L = gLightPosition - VEC3( f->vertices[index] );
                if( flatShading == true ){
                    N = VEC3( f->f_normals[fnormal_index] );
                }else{
                    N = VEC3( f->v_normals[index] );
                }
                color = simpleShader(L, N, V);
                glColor3f( color[0], color[1], color[2]);
                
                glVertex3fv( f->vertices[index] );
            }
            glEnd( );
        }
    }
}



void display( void ){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    myLoadIdentity( );
    myLookAt( gCamera.location[0], gCamera.location[1], gCamera.location[2], gCamera.gaze[0], gCamera.gaze[1], gCamera.gaze[2], gCamera.up[0], gCamera.up[1], gCamera.up[Z] );
    myRotatef( gRotationAngle[X], 1.0, 0.0, 0.0 );
    myRotatef( gRotationAngle[Y], 0.0, 1.0, 0.0 );
    myRotatef( gRotationAngle[Z], 0.0, 0.0, 1.0 );
    myScalef( gScaleFactor[X], gScaleFactor[Y], gScaleFactor[Z] );
    myTranslatef(gTranslation[X], gTranslation[Y], gTranslation[Z] );
    //glutSolidTorus (0.5, 1.0, 32, 60);
    drawSurface( gModel[gCurrentModel] );
    glFlush ();
    glutSwapBuffers();
}

void reshape( int w, int h ){
    windowSize[X] = w;
    windowSize[Y] = h;
    glViewport( 0, 0, (GLsizei) w, (GLsizei) h );
    myMatrixMode( GL_PROJECTION );
    myLoadIdentity( );
    if (orthoProjection) {
        GLfloat ar = (GLfloat)w/(GLfloat)h;
        myOrtho(-4.0*ar, 4.0*ar, -4.0, 4.0, -1.0, 20.0);
    }
    else {
        myPerspective( 40.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0 );
    }
    myMatrixMode( GL_MODELVIEW );
    myLoadIdentity( );
}

void mouseMotion(int x, int y){
    int current[2];
    current[X]=x;
    current[Y]=y;
    if(gMouseButtonDown == false && cameraBool == false)
    {
        if(gMousePosition[X] > current[X])
        {
            gTranslation[X] += .075;
            gMousePosition[X] = current[X];
        }
        if(gMousePosition[X] < current[X])
        {
            gTranslation[X] -= .075;       
            gMousePosition[X] = current[X];
        }
        if(gMousePosition[Y] > current[Y])
        {
            gTranslation[Y] += .075;       
            gMousePosition[Y] = current[Y];
        }
        if(gMousePosition[Y] < current[Y])
        {
            gTranslation[Y] -= .075; 
            gMousePosition[Y] = current[Y];
        }
        
    }
    if(gMouseButtonDown == true && cameraBool == false)
    {
        if(gMousePosition[Y] > current[Y]){
            gTranslation[Z] += .075;       
            gMousePosition[Y] = current[Y];
        }
        if(gMousePosition[Y] < current[Y]){
            gTranslation[Z] -= .075;       
            gMousePosition[Y] = current[Y];
        }
        if(gMousePosition[X] > current[X]){
            gTranslation[X] += .075;  
            gMousePosition[X] = current[X];
        }
        if(gMousePosition[X] < current[X]){
            gTranslation[X] -= .075;      
            gMousePosition[X] = current[X];
        }
        
    }
    if(cameraBool == true && gMouseButtonDown == false)
    {
        if(gMousePosition[Y] > current[Y])
        {
            gCamera.location[Z] += .15;
            gMousePosition[Y] = current[Y];
        }
        if(gMousePosition[Y] < current[Y])
        {
            gCamera.location[Z] -= .15; 
            gMousePosition[Y] = current[Y];
        }
    }
    glutPostRedisplay( );
    
}

void mousePassiveMotion(int x, int y){}

void mouse( int button, int state, int x, int y )
{
    gMousePosition[X]=x;
    gMousePosition[Y]=y;
    if( glutGetModifiers( ) == GLUT_ACTIVE_SHIFT ){
        switch (button) {
            case GLUT_LEFT_BUTTON:
                gMouseButtonDown = !gMouseButtonDown;
                break;
            case GLUT_MIDDLE_BUTTON:
                // Fall through
            case GLUT_RIGHT_BUTTON:
                break;
            default:
                // You have more than three buttons on your mouse?
                break;
        }
	}else if( glutGetModifiers( ) == GLUT_ACTIVE_CTRL ){
        switch (button) {
            case GLUT_LEFT_BUTTON:
                cameraBool = !cameraBool;
                //printf("The mouse button state is %d\n");
                break;
            case GLUT_MIDDLE_BUTTON:
                // Fall through
            case GLUT_RIGHT_BUTTON:
                break;
            default:
                // You have more than three buttons on your mouse?
                break;
        }
    }else{
        switch (button) {
            case GLUT_LEFT_BUTTON:
                break;
            case GLUT_MIDDLE_BUTTON:
                // Fall through
            case GLUT_RIGHT_BUTTON:
                break;
            default:
                // You have more than three buttons on your mouse?
                break;
        }
    }
    glutPostRedisplay( );
}

void special( int key, int px, int py ){
	if( glutGetModifiers( ) == GLUT_ACTIVE_SHIFT ){
		switch( key ){
            case GLUT_KEY_UP:
                gRotationAngle[Z]+=1; 
                break;
            case GLUT_KEY_DOWN:
                gRotationAngle[Z]-=1; 
                break;
        }
	}else{
        switch( key ){
            case GLUT_KEY_UP:
                gRotationAngle[X]+=1; 
                break;
            case GLUT_KEY_DOWN:
                gRotationAngle[X]-=1;
                break;
            case GLUT_KEY_LEFT:
                gRotationAngle[Y]-=1;
                break;
            case GLUT_KEY_RIGHT:
                gRotationAngle[Y]+=1; 
                break;
        }
	}
    glutPostRedisplay( );
}

void keyboard( unsigned char key, int x, int y ){
    switch( key ){
        case 27:
            // The esc key
            exit( 0 );
            break;
        case '+':
            gScaleFactor[X] += 0.25;
            gScaleFactor[Y] += 0.25;
            break;
        case '-':
            gScaleFactor[X] -= 0.25;
            gScaleFactor[Y] -= 0.25;
            break;
        case ' ':
            gCurrentModel = (gCurrentModel + 1) % kSurfaces;
            break;
        case 'p':
            orthoProjection = !orthoProjection;
            reshape(windowSize[X], windowSize[Y]);
            break;
        case 'd':
            flatShading = !flatShading;
            break;
        default:
            std::cerr << "Unknown key press \'" << key << "\'" << std::endl;
            break;
    }
    glutPostRedisplay( );
}

int main(int argc, char** argv){
    int ch;
    struct option longopts[] = {
        { "verbose", required_argument, NULL, 'v' },
        { "help", required_argument, NULL, 'h' },
        { NULL, 0, NULL, 0 }
    };
    
    // Let GLUT process the command line first
    glutInit(&argc, argv);
    
    // Let's figure out what the command line options are
    while( (ch = getopt_long(argc, argv, "vh", longopts, NULL)) != -1 ){
        switch( ch ){
            case 'v':
                // Turn on debugging
                break;
            case 'h':
                usage( std::string( "Hope this helps..." ) );
                break;
            default:
                /* do nothing */
                fprintf( stderr, "Ignoring unknown option: %c\n", ch );
                break;
        }
    }
    
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize( 800, 800 );
    glutInitWindowPosition( 100, 100 );
    glutCreateWindow( argv[0] );
    
    // Initialize our OpenGL environment
    init( );
    
    /*
     * Set up our call back functions to handle events
     */
    // Handle window size changes
    glutReshapeFunc( reshape );
    // Handle keyboard events
    glutKeyboardFunc( keyboard );
    glutSpecialFunc( special );
    // display gets called every time we want to refresh the screen
    glutDisplayFunc( display );
    // handle user input via the mouse
    glutMouseFunc( mouse );
    glutMotionFunc( mouseMotion );
    glutPassiveMotionFunc(mousePassiveMotion);
    
    
    // The program doesn't return from the next call.
    glutMainLoop( );
    
    return( 0 );
}