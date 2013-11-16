#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

#include "Shape.h"

using namespace std;
static Shape shape;
static bool red = false;
static bool fullscreen = false;
static int shape_key = 8;
static double spin_angle = 0.001;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

float house_vertices2[] = {  
            -4,-4,4, 4,-4,4, 4,4,4, -4,4,4,     // front face
            -4,-4,-4, -4,-4,4, -4,4,4, -4,4,-4, // left face
            4,-4,-4,-4,-4,-4, -4,4,-4, 4,4,-4,  // back face
            4,-4,4, 4,-4,-4, 4,4,-4, 4,4,4,     // right face
            4,4,4, 4,4,-4, -4,4,-4, -4,4,4,     // top face
            -4,-4,4, -4,-4,-4, 4,-4,-4, 4,-4,4, // bottom face

            -20,-4,20, 20,-4,20, 20,-4,-20, -20,-4,-20, // grass
            -4,4,4, 4,4,4, 0,8,4,                       // front attic wall
            4,4,4, 4,4,-4, 0,8,-4, 0,8,4,               // left slope
            -4,4,4, 0,8,4, 0,8,-4, -4,4,-4,             // right slope
            4,4,-4, -4,4,-4, 0,8,-4};                   // rear attic wall

// These are the RGB colors corresponding to the vertices, in the same order
float house_colors2[] = { 
            1,0,0, 1,0,0, 1,0,0, 1,0,0,  // front is red
            0,1,0, 0,1,0, 0,1,0, 0,1,0,  // left is green
            1,0,0, 1,0,0, 1,0,0, 1,0,0,  // back is red
            0,1,0, 0,1,0, 0,1,0, 0,1,0,  // right is green
            0,0,1, 0,0,1, 0,0,1, 0,0,1,  // top is blue
            0,0,1, 0,0,1, 0,0,1, 0,0,1,  // bottom is blue
  
            0,0.5,0, 0,0.5,0, 0,0.5,0, 0,0.5,0, // grass is dark green
            0,0,1, 0,0,1, 0,0,1,                // front attic wall is blue
            1,0,0, 1,0,0, 1,0,0, 1,0,0,         // left slope is green
            0,1,0, 0,1,0, 0,1,0, 0,1,0,         // right slope is red
            0,0,1, 0,0,1, 0,0,1,};              // rear attic wall is red

int house_indices2[] = {
            0,2,3,    0,1,2,      // front face
            4,6,7,    4,5,6,      // left face
            8,10,11,  8,9,10,     // back face
            12,14,15, 12,13,14,   // right face
            16,18,19, 16,17,18,   // top face
            20,22,23, 20,21,22,   // bottom face
                   
            24,26,27, 24,25,26,   // grass
            28,29,30,             // front attic wall
            31,33,34, 31,32,33,   // left slope
            35,37,38, 35,36,37,   // right slope
            39,40,41};            // rear attic wall

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback(void)
{
	shape.spin(spin_angle);
  displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Window::reshapeCallback(int w, int h)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -20);
}

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Window::displayCallback(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(shape.getCameraMatrix().getGLMatrix());

	switch (shape_key) {

		case 1: // cube
			drawCube();
			break;
		case 2: // sphere
			//shape.getCameraMatrix().c.scale(shape.scaling_x, shape.scaling_y, shape.scaling_z);
			drawShape(shape.sphere_nVerts, (shape.sphere_vertices), shape.sphere_nIndices, (shape.sphere_indices));
			//shape.getCameraMatrix().c.scale(shape.scaling_x, shape.scaling_y, shape.scaling_z);
			break;
		case 3: // teddy
			drawShape(shape.teddy_nVerts, (shape.teddy_vertices), shape.teddy_nIndices, (shape.teddy_indices));
			//shape.getCameraMatrix().c.scale(shape.scaling_x, shape.scaling_y, shape.scaling_z);
			break;
		case 4: // teapot
			drawShape(shape.teapot_nVerts, (shape.teapot_vertices), shape.teapot_nIndices, (shape.teapot_indices));
			break;
		case 5: // cow
			drawShape(shape.cow_nVerts, (shape.cow_vertices), shape.cow_nIndices, (shape.cow_indices));
			break;
		case 6: // bunny
			drawShape(shape.bunny_nVerts, (shape.bunny_vertices), shape.bunny_nIndices, (shape.bunny_indices));
			break;
		case 8: // house scene1
			shape.drawHouse();
		case 9: // house scene2
			shape.drawHouse();
			break;
	}

  glFlush();  
  glutSwapBuffers();
}
void Window::drawCube() {
		glBegin(GL_QUADS);
			glColor3f(0, 1, 0);

			// Draw front face:
			glNormal3f(0.0, 0.0, 1.0);   
			glVertex3f(-1.0,  1.0,  1.0);
			glVertex3f( 1.0,  1.0,  1.0);
			glVertex3f( 1.0, -1.0,  1.0);
			glVertex3f(-1.0, -1.0,  1.0);
    
			// Draw left side:
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(-1.0,  1.0,  1.0);
			glVertex3f(-1.0,  1.0, -1.0);
			glVertex3f(-1.0, -1.0, -1.0);
			glVertex3f(-1.0, -1.0,  1.0);
    
			// Draw right side:
			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f( 1.0,  1.0,  1.0);
			glVertex3f( 1.0,  1.0, -1.0);
			glVertex3f( 1.0, -1.0, -1.0);
			glVertex3f( 1.0, -1.0,  1.0);
  
			// Draw back face:
			glNormal3f(0.0, 0.0, -1.0);
			glVertex3f(-1.0,  1.0, -1.0);
			glVertex3f( 1.0,  1.0, -1.0);
			glVertex3f( 1.0, -1.0, -1.0);
			glVertex3f(-1.0, -1.0, -1.0);
  
			// Draw top side:
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(-1.0,  1.0,  1.0);
			glVertex3f( 1.0,  1.0,  1.0);
			glVertex3f( 1.0,  1.0, -1.0);
			glVertex3f(-1.0,  1.0, -1.0);
  
			// Draw bottom side:
			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(-1.0, -1.0, -1.0);
			glVertex3f( 1.0, -1.0, -1.0);
			glVertex3f( 1.0, -1.0,  1.0);
			glVertex3f(-1.0, -1.0,  1.0);
		glEnd();
}

void Shape::calculateStuff(int nVerts, float *vertices) {
	float max_arr[3] = {-1000, -1000, -1000};
	float min_arr[3] = {1000, 1000, 1000};

	for (int i = 0; i < nVerts/3; i++) {
		for (int v = 0; v < 3; v++) {
			if (vertices[9*i+3*v] < min_arr[0]) {
				min_arr[0] = vertices[9*i+3*v];
			}
			if (vertices[9*i+3*v] > max_arr[0]) {
				max_arr[0] = vertices[9*i+3*v];
			}
			if (vertices[(9*i)+(3*v)+1] < min_arr[1]) {
				min_arr[1] = vertices[(9*i)+(3*v)+1];
			}
			if (vertices[(9*i)+(3*v)+1] > max_arr[1]) {
				max_arr[1] = vertices[(9*i)+(3*v)+1];
			}
			if (vertices[(9*i)+(3*v)+2] < min_arr[2]) {
				min_arr[2] = vertices[(9*i)+(3*v)+2];
			}
			if (vertices[(9*i)+(3*v)+2] > max_arr[2]) {
				max_arr[2] = vertices[(9*i)+(3*v)+2];
			}

		}
	}

	shape.x = 0.5*(max_arr[0] + min_arr[0]);
	shape.y = 0.5*(max_arr[1] + min_arr[1]);
	shape.z = 0.5*(max_arr[2] + min_arr[2]);

	shape.translation.identity();
	shape.translation.m[0][3] = -shape.x;
	shape.translation.m[1][3] = -shape.y;
	shape.translation.m[2][3] = -shape.z;



	cout << "minimum values: " << min_arr[0] << ", " << min_arr[1] << ", " << min_arr[2] << "\n";
  cout << "maximum values: " << max_arr[0] << ", " << max_arr[1] << ", " << max_arr[2] << "\n\n";

	cout << "center: (" << shape.x << ", " << shape.y << ", " << shape.z << ")\n\n";
	
	float x_diff = max_arr[0]-min_arr[0];
	float y_diff = max_arr[1]-min_arr[1];
	float z_diff = max_arr[2]-min_arr[2];

	float max1 = max(x_diff, y_diff);
	max1 = max(max1, z_diff);

	scaling_x = 28/max1;
	scaling_y = 28/max1;
	scaling_z = 28/max1;

	shape.scale.identity();
	shape.scale.m[0][0] = scaling_x;
	shape.scale.m[1][1] = scaling_y;
	shape.scale.m[2][2] = scaling_z;

	cout << "scaling factor : " << scaling_x << ", " << scaling_y <<  ", " << scaling_z <<"\n\n";

}

void Window::drawShape(int nVerts, float *vertices, 
																int nIndices, int *indices) {
	glBegin(GL_TRIANGLES);
	for (int i=0; i<nVerts/3; i++) {
		if (red == true) {
			// red
			glColor3f(1,0,0);
			red = false;
		}
		else {
			// blue
			glColor3f(1,1,1);
			red = true;
		}
		glNormal3f(indices[i*3], indices[i*3+1], indices[i*3+2]);
		for (int v=0; v<3; v++) {
			glVertex3f(vertices[9*i+3*v], vertices[(9*i)+(3*v)+1], vertices[(9*i)+(3*v)+2]);
		}
	}
	glEnd();
}

Shape::Shape() {
	ObjReader::readObj("sphere.obj", sphere_nVerts, &sphere_vertices, &sphere_normals, &sphere_texcoords, sphere_nIndices, &sphere_indices);
	ObjReader::readObj("teddy.obj", teddy_nVerts, &teddy_vertices, &teddy_normals, &teddy_texcoords, teddy_nIndices, &teddy_indices);
	ObjReader::readObj("teapot.obj", teapot_nVerts, &teapot_vertices, &teapot_normals, &teapot_texcoords, teapot_nIndices, &teapot_indices);
	ObjReader::readObj("cow.obj", cow_nVerts, &cow_vertices, &cow_normals, &cow_texcoords, cow_nIndices, &cow_indices);
	ObjReader::readObj("bunny.obj", bunny_nVerts, &bunny_vertices, &bunny_normals, &bunny_texcoords, bunny_nIndices, &bunny_indices);

	house_nVerts = 42;
	house_vertices = house_vertices2;
	house_colors = house_colors2;
	house_indices = house_indices2;
}

Camera& Shape::getCameraMatrix()
{
  return camera;
}

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position

  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("OpenGL Cube for CSE167");    	      // open window and set window title
  glDisable(GL_LIGHTING);
  
  
  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
  glDisable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION); 
  
  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  
  
  //Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  //glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);

	// to avoid cube turning white on scaling down
  glEnable(GL_NORMALIZE);

	// Process keyboard input
  glutKeyboardFunc(Window::processNormalKeys);
  glutSpecialFunc(Window::processSpecialKeys);
	
	// initialize camera matrix
	shape.getCameraMatrix().identity();
	shape.getCameraMatrix().set(Vector3(0, 10, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	shape.getCameraMatrix().c.transpose();
	shape.getCameraMatrix().inverse();

	cout << "Initialized Camera Matrix:\n";
	shape.getCameraMatrix().c.print();

  glutMainLoop();
  return 0;
}

double Shape::getAngle() {
	return angle;
}

void Shape::setAngle(double a) {
	angle = a;
}

void Shape::drawHouse() {
	int tris = 0;
	glBegin(GL_QUADS);
	for (int i=0; i<7; i++) {
		glColor3f(shape.house_colors[12*i], shape.house_colors[12*i+1], shape.house_colors[12*i+2]);
		glNormal3f(shape.house_indices[i*6], shape.house_indices[i*6+1], shape.house_indices[i*6+2]);
		for (int v=0; v<4; v++) {
			glVertex3f(shape.house_vertices[12*i+3*v], shape.house_vertices[(12*i)+(3*v)+1], shape.house_vertices[(12*i)+(3*v)+2]);
		}
		glNormal3f(shape.house_indices[i*6+3], shape.house_indices[i*6+4], shape.house_indices[i*6+5]);
	}
	glEnd();

	glBegin(GL_TRIANGLES);
	for (int i=7; i<8; i++) {
		glColor3f(shape.house_colors[12*i], shape.house_colors[12*i+1], shape.house_colors[12*i+2]);
		glNormal3f(shape.house_indices[i*6], shape.house_indices[i*6+1], shape.house_indices[i*6+2]);
		for (int v=0; v<3; v++) {
			glVertex3f(shape.house_vertices[12*i+3*v], shape.house_vertices[(12*i)+(3*v)+1], shape.house_vertices[(12*i)+(3*v)+2]);
		}
		tris++;
	}
	glEnd();

	glBegin(GL_QUADS);
	for (int i=8; i<10; i++) {
		glColor3f(shape.house_colors[12*i-3*tris], shape.house_colors[12*i+1-3*tris], shape.house_colors[12*i+2-3*tris]);
		glNormal3f(shape.house_indices[i*6-3*tris], shape.house_indices[i*6+1-3*tris], shape.house_indices[i*6+2-3*tris]);
		for (int v=0; v<4; v++) {
			glVertex3f(shape.house_vertices[12*i+3*v-3*tris], shape.house_vertices[(12*i)+(3*v)+1-3*tris], shape.house_vertices[(12*i)+(3*v)+2-3*tris]);
		}
		glNormal3f(shape.house_indices[i*6+3-3*tris], shape.house_indices[i*6+4-3*tris], shape.house_indices[i*6+5-3*tris]);
	}
	glEnd();
	
	glBegin(GL_TRIANGLES);
	for (int i=10; i<11; i++) {
		glColor3f(shape.house_colors[12*i-3*tris], shape.house_colors[12*i+1-3*tris], shape.house_colors[12*i+2-3*tris]);
		glNormal3f(shape.house_indices[i*6]-3*tris, shape.house_indices[i*6+1]-3*tris, shape.house_indices[i*6+2]-3*tris);
		for (int v=0; v<3; v++) {
			glVertex3f(shape.house_vertices[12*i+3*v-3*tris], shape.house_vertices[(12*i)+(3*v)+1-3*tris], shape.house_vertices[(12*i)+(3*v)+2-3*tris]);
		}
		tris++;
	}
	glEnd();
}

void Shape::spin(double deg)
{
  if (shape.angle > 360.0 || shape.angle < -360.0) shape.angle = 0.0;
	shape.getCameraMatrix().c.rotateY(deg);
}


void Window::processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) 
	{
		case 'c':
			// reverse the direction of the spin
			spin_angle = -spin_angle;
			cout << "reverse spin\n";
			break;
		case 'x':
			// move cube left by a small amount
			shape.getCameraMatrix().c.transpose();
			shape.getCameraMatrix().c.translate(-1, 0, 0);
			shape.getCameraMatrix().c.transpose();
			cout << "move left\n";
			break;
		case 'X':
			// move cube right by a small amount
			shape.getCameraMatrix().c.transpose();
			shape.getCameraMatrix().c.translate(1, 0, 0);
			shape.getCameraMatrix().c.transpose();
			cout << "move right\n";
			break;
		case 'y':
			// move cube down by a small amount
			shape.getCameraMatrix().c.transpose();
			shape.getCameraMatrix().c.translate(0, -1, 0);
			shape.getCameraMatrix().c.transpose();
			cout << "move down\n";
			break;
		case 'Y':
			// move cube up by a small amount
			shape.getCameraMatrix().c.transpose();
			shape.getCameraMatrix().c.translate(0, 1, 0);
			shape.getCameraMatrix().c.transpose();
			cout << "move up\n";
			break;
		case 'z':
			// move cube into of the screen by a small amount
			shape.getCameraMatrix().c.transpose();
			shape.getCameraMatrix().c.translate(0, 0, -1);
			shape.getCameraMatrix().c.transpose();
			cout << "move in\n";
			break;
		case 'Z':
			// move cube out of the screen by a small amount
			shape.getCameraMatrix().c.transpose();
			shape.getCameraMatrix().c.translate(0, 0, 1);
			shape.getCameraMatrix().c.transpose();
			cout << "move out\n";
			break;
		case 'r':
			// reset position and size to its initial position
			shape.getCameraMatrix().identity();
			shape.getCameraMatrix().c.transpose();
			shape.getCameraMatrix().inverse();
			shape.setAngle(0);
			break;
		case 'a':
			// rotate cube about the OpenGL window's z axis by a small number of degrees counterclockwise
			// The z axis crosses the screen in its center.
			if (shape.angle > 360.0 || shape.angle < -360.0) shape.angle = 0.0;
			shape.getCameraMatrix().c.rotateCubeZ(-100*spin_angle);
			cout << "rotate CW window z-axis\n";
			break;
		case 'A':
			// rotate cube about the OpenGL window's z axis by a small number of degrees clockwise
			// The z axis crosses the screen in its center.
			if (shape.angle > 360.0 || shape.angle < -360.0) shape.angle = 0.0;
			shape.getCameraMatrix().c.rotateCubeZ(100*spin_angle);
			cout << "rotate CCW window z-axis\n";
			break;
		case 's':
			// scale cube down (about its center, not the center of the screen)
			shape.getCameraMatrix().c.scale(0.95, 0.95, 0.95);
			cout << "scale down\n";
			break;
		case 'S':
			// scale cube up (about its center, not the center of the screen)
			//shape.getCameraMatrix().c.scale(64, 64, 1);
			shape.getCameraMatrix().c.scale(1.05, 1.05, 1.05);
			cout << "scale up\n";
			break;
		case 'f': //toggle screenmode
			if(!fullscreen) {
        glutFullScreen();
        fullscreen = true;
			} 
			else {
        glutReshapeWindow(Window::width, Window::height);
        glutPositionWindow(100, 100);
        fullscreen = false;
			}
    break;
	}
}

void Window::processSpecialKeys(int key, int x, int y)
{

	shape.getCameraMatrix().identity();
	shape.getCameraMatrix().c.transpose();
	shape.getCameraMatrix().inverse();

	switch (key) 
	{	
		case GLUT_KEY_F1:
			// sphere
			shape_key = 1;
			shape.calculateStuff(shape.sphere_nVerts, shape.sphere_vertices);

			shape.getCameraMatrix().c = *shape.getCameraMatrix().c.multiply(shape.translation);
			cout << "translation matrix:\n";
			shape.translation.print();
			
			shape.scale.identity();
			shape.scale.m[0][0] = 10;
			shape.scale.m[1][1] = 10;
			shape.scale.m[2][2] = 10;
		  shape.getCameraMatrix().c = *shape.getCameraMatrix().c.multiply(shape.scale);
			cout << "scale matrix:\n";
			shape.scale.print();
			break;
		case GLUT_KEY_F2:
			// sphere
			shape_key = 2;
			shape.calculateStuff(shape.sphere_nVerts, shape.sphere_vertices);

			shape.getCameraMatrix().c = *shape.getCameraMatrix().c.multiply(shape.translation);
			cout << "translation matrix:\n";
			shape.translation.print();
			
		  shape.getCameraMatrix().c = *shape.getCameraMatrix().c.multiply(shape.scale);
			cout << "scale matrix:\n";
			shape.scale.print();
			break;
		case GLUT_KEY_F3:
			// teddy
			shape_key = 3;
			shape.calculateStuff(shape.teddy_nVerts, shape.teddy_vertices);
			
			shape.getCameraMatrix().c = *shape.getCameraMatrix().c.multiply(shape.translation);
			cout << "translation matrix:\n";
			shape.translation.print();
		  
			shape.getCameraMatrix().c = *shape.getCameraMatrix().c.multiply(shape.scale);
			cout << "scale matrix:\n";
			shape.scale.print();
			break;
		case GLUT_KEY_F4:
			// teapot
			shape_key = 4;
			shape.calculateStuff(shape.teapot_nVerts, shape.teapot_vertices);
			
			shape.getCameraMatrix().c = *shape.getCameraMatrix().c.multiply(shape.translation);
			cout << "translation matrix:\n";
			shape.translation.print();

		  shape.getCameraMatrix().c = *shape.getCameraMatrix().c.multiply(shape.scale);
			cout << "scale matrix:\n";
			shape.scale.print();
			break;
		case GLUT_KEY_F5:
			// cow
			shape_key = 5;
			shape.calculateStuff(shape.cow_nVerts, shape.cow_vertices);
			shape.getCameraMatrix().c = *shape.getCameraMatrix().c.multiply(shape.scale);
			shape.getCameraMatrix().c = *shape.getCameraMatrix().c.multiply(shape.translation);

			cout << "translation matrix:\n";
			shape.translation.print();

			cout << "scale matrix:\n";
			shape.scale.print();
			break;
		case GLUT_KEY_F6:
			// bunny
			shape_key = 6;
			shape.calculateStuff(shape.bunny_nVerts, shape.bunny_vertices);
			
			shape.getCameraMatrix().c = *shape.getCameraMatrix().c.multiply(shape.translation);
			cout << "translation matrix:\n";
			shape.translation.print();
			
		  shape.getCameraMatrix().c = *shape.getCameraMatrix().c.multiply(shape.scale);
			cout << "scale matrix:\n";
			shape.scale.print();
			break;
		case GLUT_KEY_F8:
			// house view1
			shape_key = 8;
			shape.getCameraMatrix().identity();
			shape.getCameraMatrix().set(Vector3(0, 10, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
			shape.getCameraMatrix().c.transpose();
			shape.getCameraMatrix().inverse();
			break;
		case GLUT_KEY_F9:
			// show house view2
			shape_key = 9;
			shape.getCameraMatrix().identity();
			shape.getCameraMatrix().set(Vector3(-15, 5, 10), Vector3(-5, 0, 0), Vector3(0, 1, 0.5));
			shape.getCameraMatrix().c.transpose();
			shape.getCameraMatrix().inverse();
			break;
	}
}