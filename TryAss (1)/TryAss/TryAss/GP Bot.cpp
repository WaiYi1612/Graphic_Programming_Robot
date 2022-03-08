
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "WLL Jaegers Robot"
#define PI 3.1415926535898
#define DEG2RAD 3.14159/180.0

/*---
-----Author : Cecelia Lim Jie Shi, Wong Wai Yi, Dennis Lau Yik Ann
-----Class	: RSF Y2
-----Date	: 09/04/2021
-----Version: 5
-----
-----*/

// UI Module
int robot_choice = 1;
int weapon_choice = 1;
int background_choice = 1;
float x = 0.0;			// Robot Coordinate
float y = 0.0;
float z = 0.0;
float c_x = 0;
float c_y = 0;
float c_z = 0;
float c2_x = 0;
float c2_y = 0;
float c2_z = 0;
float c3_x = 0;
float c3_y = 0;
float c3_z = 0;
float bgspeed = 0;
float bgspeed1 = 0;
float bgspeed2 = 0;
float bgspeed3 = 0;
int bgcount = 0;
int bgcount1 = 0;
int bgcount2 = 0;
int bgcount3 = 0;
boolean turnArround = false;
boolean turnArround1 = false;
boolean turnArround2 = false;
boolean turnArround3 = false;
float perspective = 1.0;


//texture
//Step 1: Variable declaration
BITMAP BMP;             //bitmap structure
HBITMAP hBMP = NULL;    //bitmap handle
bool isTexture = true;  //is texture enabled?

//color
bool red = true;

//change background
bool sky = false;

// Projection Module
bool isOrtho = true;
float tz = 0.0;
float tSpeed = 1.0;
float tx = 0.0;
float ty = 0.0;
float tSpeedP = 0.1;
float tSpeedL = 0.3;
float ry = 0.0;
float rSpeedP = 3.0;


// Lighthing Module
bool Pinkcolor = false;
bool isOn = false;
float txL = 0.0, tyL = 0.0, ryLAngle = 0.0, tzL = 0.0;
float xL = 3.0, yL = 0.0, zL = 5.0; //yL = -5.5,
float amb3[] = { 1.0, 0.0, 0.0 }; //light yellow	#FFFFE0	(255,255,224) ambient light
//float posA3[] = { 6.0 , -5.5, -8.0 }; //left position of the light at origin(0,1,0) |  (0,1,0) light pos above the sphere (0,1,0)
float posA3[] = { xL , yL, zL };
float diff3[] = { 1.0,1.0, 0.0 }; //right light yellow	#FFFFE0	(255,255,224) diffuse light   =======
//float posD3[] = { 6.0, -5.5, -8.0 };
float posD3[] = { xL, yL, zL };
float ambM[] = { 0.87,1.0,1.0 }; //light cyan	#E0FFFF	(224,255,255)  red color ambient material
float diffM[] = { 1.0, 0.41, 0.70 }; //hot pink color diffuse material




// Body & Head Module
int circleMin;
int circleMax;
int eyeno = 1;
int movecount = 0;
float bspeed = 0;
float Rx = 0;
float Ry = 0;
float cx = 0;
float cy = 0;
float cx2 = 0;
float cy2 = 0;
float headx = 0;
float heady = 0;
float heads = 0;
float movey = 0;
float movez = 0;
float bowz = 0;
GLenum type = GL_POLYGON;
GLenum gltype = GL_LINE_LOOP;
GLenum triangle = GL_TRIANGLES;
GLenum quad = GL_QUADS;
bool changeColor = true;
bool walkforward = false;
bool walkbackward = false;
bool runforward = false;
bool fly = false;

// Leg & Wing Module
int c = 0;
bool isFly = false;
float lSpeed = 1.0;
float lx = 0;
float ly = 0;
float lm = 0;
float ln = 0;
float lAngle = 0;
float lcAngle = 0;
float lx2 = 0;
float ly2 = 0;
float lm2 = 0;
float ln2 = 0;
float lAngle2 = 0;
float lcAngle2 = 0;
float lwx = 0;
float lwy = 0;
float lwm = 0;
float lwn = 0;
float lwAngle = 0;
float wSpeed = 1.0;
float lwx2 = 0;
float lwy2 = 0;
float lwm2 = 0;
float lwn2 = 0;
float lwAngle2 = 0;

// Hand & Weapon Module
int bcount = 0;
int attackCount = 0;
boolean attack = false;				// attack move varies on weapon_choice
float attackSpeed1 = 1.0;
float attackSpeed2 = 0.7;
float attackSpeed3 = 0.4;
float effect_x = 0;
float effect_y = 0;
float effect_z = 0;
float x_resize = 3.0;				// Scales and speed
float y_resize = 5.0;
float z_resize = 3.0;
float hspeed = 4.0;
float Shoulder_width = 0.6;			// One-side Shoulder Size
float Shoulder_height = 0.16;
float Shoulder_depth = 0.14;
float Arm_width = 0.2;				// One-side Arm size
float Arm_height = 0.4;
float Arm_depth = 0.14;
float LArm_x = 0;					// Robot Left Arm Coordinate
float LArm_y = 0;
float LArm_z = 0;
float RArm_x = 0;					// Robot Right Arm Coordinate
float RArm_y = 0;
float RArm_z = 0;
float Lpalm_angle = 0.0;			// Palm Transformation
float Rpalm_angle = 0.0;
float palm_x_rotate = 0.0;
float palm_y_rotate = 1.0;
float palm_z_rotate = 0.0;
float Lhangle = 0.0;				// Arm Transformation
float Lx_spin = 1.0;
float Ly_spin = 0.0;
float Lz_spin = 0.0;
float Rhangle = 0.0;				// Arm Transformation
float Rx_spin = 1.0;
float Ry_spin = 0.0;
float Rz_spin = 0.0;
float Lshangle = 0.0;				// Small Arm Transformation
float Rshangle = 0.0;				// Small Arm Transformation

// Pet Module
int petAtkCount = 0;
bool petAttack = false;
bool pethead = true;
bool iceAttack = false;
float bom_z = 0;
float xc = 0, yc = 0; // origin(x,y) center of circle   right hand side is positive x = 0.5
float x2c = 0, y2c = 0; //(x2,y2) calculate for (rcosA, rsinA)
float radiusc = 0.1;
float anglec = 0; //use for loop to draw circle
float noOfSegmentc = 30; //no of triangles/segments inside the circle  10 or 30
float xc1 = 0, yc1 = 0; // origin(x,y) center of circle   right hand side is positive x = 0.5
float x2c1 = 0, y2c1 = 0; //(x2,y2) calculate for (rcosA, rsinA)
float radiusc1 = 0.08;
float anglec1 = 0; //use for loop to draw circle
float noOfSegmentc1 = 30; //no of triangles/segments inside the circle  10 or 30
float xD = 0, yD = 0, zD = 0, speed = 0.1;
float Twz = 0.0, TwSpeed = 0.1;
float phx = 0.0, phy = 0.0, phm = 0, phn = 0, phAngle = 0, phSpeed = 2.5;
float phx2 = 0, phy2 = 0, phm2 = 0, phn2 = 0, phAngle2 = 0;
float px = 0, py = 0, pm = 0, pn = 0, pAngle = 0;
float tpx = 0.0, tpy = 0.0, tpz = 0.0, tpSpeed = 0.1;
float plx = 0, ply = 0, plm = 0, pln = 0, plAngle = 0, plSpeed = 0.5;
float plx2 = 0, ply2 = 0, plm2 = 0, pln2 = 0, plAngle2 = 0;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == VK_UP) {				// 'up' key		- Move robot farther to view
			if (isOrtho) {
				if (tz > -7.0)
					tz -= tSpeed;
			}
			else {
				if (tz > 4.0)
					tz -= tSpeed;
			}
		}
		else if (wParam == VK_DOWN) {			// 'down' key	- Move robot nearer from view
			if (isOrtho) {
				if (tz < 7.0)
					tz += tSpeed;
			}
			else {
				if (tz < 14.0)
					tz += tSpeed;
			}
		}
		else if (wParam == VK_LEFT)				// 'left' key	- Rotate view to the left
			//perspective
			ry -= rSpeedP;
		else if (wParam == VK_RIGHT)			// 'right' key	- Rotate view to the right
			//perspective
			ry += rSpeedP;
		else if (wParam == 0x4f)				// 'o' key		- Ortho projection
			//orthgraphic 
			isOrtho = true, tz = 0.0;
		else if (wParam == 0x50)				// 'p' key		- Perspective projection
			//perspective
			isOrtho = false, tz = 4.0;
		else if (wParam == 0x41)				// 'A' key		- move view left
			//orthgraphic 
			tx += tSpeedP;
		else if (wParam == 0x44)				// 'D' key		- move view right
			//perspective
			tx -= tSpeedP;
		else if (wParam == 0x57)				// 'W' key		- move view up
		//orthgraphic 
			ty -= tSpeedP;
		else if (wParam == 0x53)				// 'S' key		- move view down
			//perspective
			ty += tSpeedP;
		else if (wParam == VK_F1)				// 'F1' Key		- change color
		{
			changeColor = !changeColor, red = !red;
		}
		else if (wParam == VK_F2)				// 'F2' key		- Change background
			sky = !sky;
		else if (wParam == VK_F3)				// 'F3' key		- Texture On/Off
			isTexture = !isTexture, pethead = !pethead;
		else if (wParam == VK_F4)				// 'F4' key		- Lighthing  On/Off Pink 
			isOn = !isOn, Pinkcolor = !Pinkcolor;
		else if (wParam == VK_F5) {				// 'F5' key		- Move the light up
			if (isOn && Pinkcolor) {
				tyL += tSpeedL;
			}
		}
		else if (wParam == VK_F6) {				// 'F6' key		- Move the light down
			if (isOn && Pinkcolor) {
				tyL -= tSpeedL;
			}
		}
		else if (wParam == VK_F7) {				// 'F7' key		- Move the light left
			if (isOn && Pinkcolor) {
				txL -= tSpeedL;
			}
		}
		else if (wParam == VK_F8) {				// 'F8' key		- Move the light right
			if (isOn && Pinkcolor) {
				txL += tSpeedL;
			}
		}
		else if (wParam == 0xBF) {				// '/' key	- Move the light near
			if (isOn && Pinkcolor) {
				tzL += tSpeedL;
			}
		}
		else if (wParam == 0xDC) {				// '\' key	- Move the light far
			if (isOn && Pinkcolor) {
				tzL -= tSpeedL;
			}
		}
		else if (wParam == 0x46) {				// 'F' Key	- Change face espression
			if (eyeno == 3) {
				eyeno = 1;
			}
			else {
				eyeno += 1;
			}
		}
		else if (wParam == VK_DELETE)			// 'DELETE' Key	- Change to flg leg
			isFly = true, lwAngle -= wSpeed, lwAngle2 += wSpeed;
		else if (wParam == 0x51)				// 'Q' Key		- Change weapon
			if (weapon_choice == 3) {
				weapon_choice = 1;
			}
			else {
				weapon_choice += 1;
			}
		else if (wParam == 0x45)				// 'E' Key		- Attack move
		{
			attack = true;
		}
		//-------------------parts flexibility-----------------------------------
		else if (wParam == 0x31)				// '1' Key		- turn the head up
			headx = 1.0, heady = 0.0, heads += 1.0;	
		else if (wParam == 0x32)				// '2' Key		- turn the head down
			headx = 1.0, heady = 0.0, heads -= 1.0;
		else if (wParam == 0x33)				// '3' Key		- turn the head left
			headx = 0.0, heady = 1.0, heads += 1.0;	
		else if (wParam == 0x34)				// '4' Key		- turn the head right
			headx = 0.0, heady = 1.0, heads -= 1.0;	
		else if (wParam == 0x35)				// '5' Key		- whole leg movement 1
			lAngle += lSpeed, lAngle2 -= lSpeed;
		else if (wParam == 0x36)				// '6' Key		- whole leg movement 2
			lAngle -= lSpeed, lAngle2 += lSpeed;
		else if (wParam == 0x37)				// '7' Key		- small leg movement 1
			lcAngle += lSpeed, lcAngle2 += lSpeed;
		else if (wParam == 0x38)				// '8' Key		- small leg movement 2
			lcAngle -= lSpeed, lcAngle2 -= lSpeed;
		else if (wParam == 0x39)				// '9' Key		- whole hand movement 1
			Lhangle += hspeed, Rhangle -= hspeed, Lx_spin = 1.0, Ly_spin = 0.0, Lz_spin = 0.0;
		else if (wParam == 0x30)				// '0' Key		- whole hand movement 2
			Lhangle -= hspeed, Rhangle += hspeed, Lx_spin = 1.0, Ly_spin = 0.0, Lz_spin = 0.0;
		else if (wParam == 0xBD)				// '-' Key		- palm movement 1
			Lpalm_angle += hspeed, Rpalm_angle -= hspeed, palm_x_rotate = 0.0, palm_y_rotate = 1.0, palm_z_rotate = 0.0;
		else if (wParam == 0xBB)				// '=' Key		- body movement 1
			bowz += lSpeed;
		else if (wParam == 0xDB)				// '[' key		- pet movement 1
			phAngle += phSpeed, phAngle2 -= phSpeed, plAngle -= plSpeed, plAngle2 += plSpeed, pAngle -= phSpeed;
		else if (wParam == 0xDD)				// ']' key		- pet movement 2
			phAngle -= phSpeed, phAngle2 += phSpeed, plAngle += plSpeed, plAngle2 -= plSpeed, pAngle += phSpeed;//do sth on leg
		//-------------------animation--------------------------------------------
		else if (wParam == 0x5A)				// 'Z' Key		- Walk forward animation
			walkforward = true;
		else if (wParam == 0x58)				// 'X' Key		- Walk backward animation
			walkbackward = true;
		else if (wParam == 0x43)				// 'C' Key		- Run forward animation
			runforward = true;
		else if (wParam == 0x56)				// 'V' Key		- Fly upward animation
			fly = true;
		else if (wParam == 0x42)				// 'B' key		- Boom sakalia
			petAttack = true;
		else if (wParam == 0x4E)				// 'N' key		- Switch attack type (ice/fire)
			iceAttack = !iceAttack;
		else if (wParam == VK_SPACE)			// 'SPACE' key	- Reset everything
			heads = 0,
			ry = 0, movez = 0, movey = 0, bowz = 0,
			lAngle = 0, lAngle2 = 0, lcAngle = 0, lcAngle2 = 0,
			Lhangle = 0, Rhangle = 0, Lx_spin = 0.0, Ly_spin = 0.0, Lz_spin = 0.0,
			walkforward = false, walkbackward = false, runforward = false, fly = false,
			isFly = false, phAngle = 0, phAngle2 = 0, plAngle = 0, plAngle2 = 0, pAngle = 0,
			txL = 0.0, tyL = 0.0, ryLAngle = 0.0, tzL = 0.0, Twz = 0.0;
		else {
		}		
		break;
	}
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
//------------------------------------BACKGROUND---------------------------------------------
//-------------------------------------------------------------------------------------------
void drawCloud(float rad, int sl, int st)
{
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, rad, sl, st);
	gluDeleteQuadric(sphere);
}
void cloudsPart1() {
	glPushMatrix();
	glTranslatef(-15, 0, -2);

	// cloud 1
	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glTranslatef(6, 4, 0.4);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(5, 4.8, 0.4);
	drawCloud(1.1, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.95, 0.95, 0.95);
	glTranslatef(5.5, 4.5, 0.8);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glTranslatef(4, 4, 0.4);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(5, 4, 1.2);
	drawCloud(0.6, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(5, 3.8, 0);
	drawCloud(0.6, 10, 30);
	glPopMatrix();

	// cloud 2
	glPushMatrix();
	glScalef(0.8, 0.8, 0.8);
	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glTranslatef(4, 5.1, -1.4);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(3, 5.3, -1.4);
	drawCloud(1.1, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.95, 0.95, 0.95);
	glTranslatef(3.5, 5, -1.8);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glTranslatef(2, 4.5, -1.4);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(3, 4.5, -2.2);
	drawCloud(0.6, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(3, 4.5, -1);
	drawCloud(0.6, 10, 30);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}
void cloudsPart2() {
	glPushMatrix();
	glTranslatef(-20, 0, -2);

	// cloud 3
	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glTranslatef(-6, 4, -0.4);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-5, 4.8, -0.4);
	drawCloud(1.1, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.95, 0.95, 0.95);
	glTranslatef(-5.5, 4.5, 0);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glTranslatef(-4, 4, -0.4);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-5, 4, 0.4);
	drawCloud(0.6, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-5, 3.8, -0.8);
	drawCloud(0.6, 10, 30);
	glPopMatrix();

	glPopMatrix();
}
void cloudsPart3() {
	glPushMatrix();
	glTranslatef(-17, -4, -2);

	// cloud 1
	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glTranslatef(6, 4, 0.4);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(5, 4.8, 0.4);
	drawCloud(1.1, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.95, 0.95, 0.95);
	glTranslatef(5.5, 4.5, 0.8);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glTranslatef(4, 4, 0.4);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(5, 4, 1.2);
	drawCloud(0.6, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(5, 3.8, 0);
	drawCloud(0.6, 10, 30);
	glPopMatrix();

	// cloud 2
	glPushMatrix();
	glScalef(0.8, 0.8, 0.8);
	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glTranslatef(4, 5.1, -1.4);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(3, 5.3, -1.4);
	drawCloud(1.1, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.95, 0.95, 0.95);
	glTranslatef(3.5, 5, -1.8);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glTranslatef(2, 4.5, -1.4);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(3, 4.5, -2.2);
	drawCloud(0.6, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(3, 4.5, -1);
	drawCloud(0.6, 10, 30);
	glPopMatrix();
	glPopMatrix();

	// cloud 3
	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glTranslatef(-6, 4, -0.4);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-5, 4.8, -0.4);
	drawCloud(1.1, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.95, 0.95, 0.95);
	glTranslatef(-5.5, 4.5, 0);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glTranslatef(-4, 4, -0.4);
	drawCloud(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-5, 4, 0.4);
	drawCloud(0.6, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-5, 3.8, -0.8);
	drawCloud(0.6, 10, 30);
	glPopMatrix();

	glPopMatrix();
}
void drawBaloon(float rad, int sl, int st)
{
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, rad, sl, st);
	gluDeleteQuadric(sphere);
}
void drawLineBaloon(float rad, int sl, int st)
{
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_LINE);
	gluSphere(sphere, rad * 1.1, sl, st);
	gluDeleteQuadric(sphere);
}
void drawPyramidLine(float szp) {
	glBegin(GL_POLYGON);

	if (isTexture) {
		glColor3f(1.0, 1.0, 1.0);  //white
	}
	else {
		glColor3f(0.86, 0.07, 0.23);  //crimson	#DC143C	(220,20,60)
	}

	// Face 1 // bottom face
	//glColor3f(1.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-szp, 0.0f, -szp); //a
	glTexCoord2f(1.0, 1.0);
	glVertex3f(szp, 0.0f, -szp); //b
	glTexCoord2f(1.0, 0.0);
	glVertex3f(szp, 0.0f, szp); //c
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-szp, 0.0f, szp); //d
	glEnd();


	//glBegin(GL_LINE_LOOP);
	// Face a // tri
	glBegin(GL_LINE_LOOP);
	//glColor3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0, szp * 2, 0); //top point//glVertex3f(szp, 1.0f, szp);  //top point
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-szp, 0.0f, -szp); //a
	glTexCoord2f(0.0, 0.0);
	glVertex3f(szp, 0.0f, -szp); //b
	glEnd();

	//glBegin(GL_LINE_LOOP);
	// Face b // tri
	glBegin(GL_LINE_LOOP);
	//glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0, szp * 2, 0); //top point
	glTexCoord2f(1.0, 0.0);
	glVertex3f(szp, 0.0f, -szp); //b
	glTexCoord2f(0.0, 0.0);
	glVertex3f(szp, 0.0f, szp); //c
	glEnd();

	//glBegin(GL_LINE_LOOP);
	// Face c // tri
	glBegin(GL_LINE_LOOP);
	//glColor3f(1.0, 0.0, 1.0);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0, szp * 2, 0); //top point
	glTexCoord2f(1.0, 0.0);
	glVertex3f(szp, 0.0f, szp); //c
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-szp, 0.0f, szp); //d
	glEnd();

	//glBegin(GL_LINE_LOOP);
	// Face d // tri
	glBegin(GL_LINE_LOOP);
	//glColor3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0, szp * 2, 0); //top point
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-szp, 0.0f, szp); //d
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-szp, 0.0f, -szp); //a
	glEnd();
}
void drawShip(GLenum type, float cube1, float cube2) {
	glLineWidth(2);
	glBegin(type);//top
	glVertex3f(0, 0, 0);//cube 1 - 1.0 cube 2 -0.5
	glVertex3f(cube1, 0, 0);
	glVertex3f(cube1, 0, cube2);
	glVertex3f(0, 0, cube2);
	glEnd();
	glBegin(type);
	glVertex3f(0, 0, 0);
	glVertex3f(cube1, 0, 0);
	glVertex3f(cube1, cube2, 0);
	glVertex3f(0, cube2, 0);
	glEnd();
	glBegin(type);
	glVertex3f(0, 0, 0);
	glVertex3f(0, cube2, 0);
	glVertex3f(0, cube2, cube2);
	glVertex3f(0, 0, cube2);
	glEnd();
	glBegin(type);
	glVertex3f(0, cube2, 0);
	glVertex3f(cube1, cube2, 0);
	glVertex3f(cube1, cube2, cube2);
	glVertex3f(0, cube2, cube2);
	glEnd();
	glBegin(type);
	glVertex3f(cube1, 0, cube2);
	glVertex3f(cube1, cube2, cube2);
	glVertex3f(cube1, cube2, 0);
	glVertex3f(cube1, 0, 0);
	glEnd();
	glBegin(type);
	glVertex3f(cube1, 0, cube2);
	glVertex3f(cube1, cube2, cube2);
	glVertex3f(0, cube2, cube2);
	glVertex3f(0, 0, cube2);
	glEnd();
}
void drawShipLine(GLenum type, float cube1, float cube2) {
	glLineWidth(2);
	glBegin(type);//top
	glVertex3f(0, 0, 0);//cube 1 - 1.0 cube 2 -0.5
	glVertex3f(cube1, 0, 0);
	glVertex3f(cube1, 0, cube2);
	glVertex3f(0, 0, cube2);
	glEnd();
	glBegin(type);
	glVertex3f(0, 0, 0);
	glVertex3f(cube1, 0, 0);
	glVertex3f(cube1, cube2, 0);
	glVertex3f(0, cube2, 0);
	glEnd();
	glBegin(type);
	glVertex3f(0, 0, 0);
	glVertex3f(0, cube2, 0);
	glVertex3f(0, cube2, cube2);
	glVertex3f(0, 0, cube2);
	glEnd();
	glBegin(type);
	glVertex3f(0, cube2, 0);
	glVertex3f(cube1, cube2, 0);
	glVertex3f(cube1, cube2, cube2);
	glVertex3f(0, cube2, cube2);
	glEnd();
	glBegin(type);
	glVertex3f(cube1, 0, cube2);
	glVertex3f(cube1, cube2, cube2);
	glVertex3f(cube1, cube2, 0);
	glVertex3f(cube1, 0, 0);
	glEnd();
	glBegin(type);
	glVertex3f(cube1, 0, cube2);
	glVertex3f(cube1, cube2, cube2);
	glVertex3f(0, cube2, cube2);
	glVertex3f(0, 0, cube2);
	glEnd();
}
void airBaloon() {
	glPushMatrix();
	glTranslatef(-10, 2, -2);

	glPushMatrix();
	glColor3f(1, 0, 0);
	drawBaloon(0.8, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0.4);
	drawLineBaloon(0.8, 4, 10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	drawPyramidLine(0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, -1.85, -0.3);
	glColor3f(0.5, 0.25, 0.25);
	drawShip(quad, 0.5, 0.6);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, -1.85, -0.3);
	glColor3f(1, 0, 0);
	drawShipLine(GL_LINE_LOOP, 0.525, 0.625);
	glPopMatrix();

	glPopMatrix();
}
void drawSky() {
	// Draw a textured quad
	glBegin(GL_QUADS);		// 1 quad
	glTexCoord2f(-0.1f, -0.1f); glVertex3f(-1, -1, -1);
	glTexCoord2f(-0.1f, 0.1f); glVertex3f(-1, 1, 1);
	glTexCoord2f(0.1f, 0.1f); glVertex3f(1, 1, 1);
	glTexCoord2f(0.1f, -0.1f); glVertex3f(1, -1, -1);
	glEnd();

	glBegin(GL_QUADS);		// 2 quad
	glTexCoord2f(-0.1f, -0.1f); glVertex3f(-1, -1, 1);
	glTexCoord2f(-0.1f, 0.1f); glVertex3f(-1, 1, -1);
	glTexCoord2f(0.1f, 0.1f); glVertex3f(1, 1, -1);
	glTexCoord2f(0.1f, -0.1f); glVertex3f(1, -1, 1);
	glEnd();

	glBegin(GL_QUADS);		// 3 quad
	glTexCoord2f(-0.1f, -0.1f); glVertex3f(-1, -1, -1);
	glTexCoord2f(-0.1f, 0.1f); glVertex3f(-1, 1, -1);
	glTexCoord2f(0.1f, 0.1f); glVertex3f(1, 1, 1);
	glTexCoord2f(0.1f, -0.1f); glVertex3f(1, -1, 1);
	glEnd();

	glBegin(GL_QUADS);		// 4 quad
	glTexCoord2f(-0.1f, -0.1f); glVertex3f(-1, -1, 1);
	glTexCoord2f(-0.1f, 0.1f); glVertex3f(-1, 1, 1);
	glTexCoord2f(0.1f, 0.1f); glVertex3f(1, 1, -1);
	glTexCoord2f(0.1f, -0.1f); glVertex3f(1, -1, -1);
	glEnd();
}
void displayBackground()						// Background
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear screen color
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.53f, 0.80f, 0.90f, 0.0f);	// Background colour
}

//-------------------------------------------------------------------------------------------
//------------------------------------PROJECTION---------------------------------------------
//-------------------------------------------------------------------------------------------
void Projection() {  //#CC change 

	glMatrixMode(GL_PROJECTION); // refer projection matrix
	glLoadIdentity(); //reset projection matrix

	glTranslatef(tx, ty, 0.0);    //translate along the x-axis and y-axis move tx and ty
	glRotatef(ry, 0.0, 1.0, 0.0); //rotate at y-axis spedd x y z

	if (isOrtho) {
		glOrtho(-8.0, 8.0, -8.0, 8.0, -8.0, 8.0);    //default is -1.0/1.0
	}
	else {
		gluPerspective(60.0, 1.0, -1.0, 1.0);
		glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 17.0);
		//glFrustum(-6.0, 6.0, -4.0, 4.0, 1.0, 17);
	}
}

//-------------------------------------------------------------------------------------------
//------------------------------------LIGHTHING----------------------------------------------
//-------------------------------------------------------------------------------------------
void lighting() {
	if (isOn) {
		glEnable(GL_LIGHTING);   //Enable lighthing for whole sphere
		//Light0 - Red color ambient light

	}
	else {
		glDisable(GL_LIGHTING); //Disable the light
	}

	glPushMatrix();
	glTranslatef(txL, tyL, 0.0);    //translate along the x-axis and y-axis move tx and ty
	glRotatef(ryLAngle, 0.0, 1.0, 0.0); //rotate at y-axis spedd x y z
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb3); //red color amb light
	glLightfv(GL_LIGHT0, GL_POSITION, posA3); //pos (0,1,0)
	glEnable(GL_LIGHT0);         //Turn on Light0       //default position of light : at the center (origin) 

	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff3); //red color diff light
	glLightfv(GL_LIGHT1, GL_POSITION, posD3); //pos (0,1,0)
	glEnable(GL_LIGHT1);  //Turn on Light1

	glPopMatrix();
}

GLuint loadTexture(LPCSTR filename) {

	//From step 1
	GLuint texture = 0; //texture name

	//Step 3: Initialize texture info 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	//Step 4: Assign texture to polygon. 
	if (isTexture)
		glEnable(GL_TEXTURE_2D);
	else
		glDisable(GL_TEXTURE_2D);


	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


	//From step 5
	DeleteObject(hBMP);
	return texture;
}

//-------------------------------------------------------------------------------------------
//------------------------------------HEAD---------------------------------------------------
//-------------------------------------------------------------------------------------------
void color(char location, int color) {
	if (changeColor) {
		switch (location) {
		case 'h':
			switch (color) {
			case 1:
				glColor3f(0.545, 0.604, 0.921);
				break;
			case 2:
				glColor3f(0.404, 0.667, 0.929);
				break;
			case 3:
				glColor3f(0.192, 0.192, 1.0);
				break;
			default:
				break;
			}
			break;
		case 'm':
			switch (color)
			{
			case 1:
				glColor3f(0, 0, 1.0);
				break;
			default:
				break;
			}
			break;
		case 'e':
			switch (color)
			{
			case 1:
				glColor3f(0.772, 0.772, 0.772);
				break;
			case 2:
				glColor3f(0.502, 0.502, 1.0);
				break;
			default:
				break;
			}
			break;
		case 'b':
			switch (color)
			{
			case 1:
				glColor3f(0.733, 0.733, 0.733);
				break;
			case 2:
				glColor3f(0.223, 0.612, 1.0);
				break;
			case 3:
				glColor3f(0.717, 0.858, 1.0);
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}
	else {
		switch (location) {
		case 'h':
			switch (color) {
			case 1:
				glColor3f(0.921, 0.545, 0.686);
				break;
			case 2:
				glColor3f(0.929, 0.404, 0.560);
				break;
			case 3:
				glColor3f(0.992, 0.007, 0.423);
				break;
			default:
				break;
			}
			break;
		case 'm':
			switch (color)
			{
			case 1:
				glColor3f(1.0, 0, 0);
				break;
			default:
				break;
			}
			break;
		case 'e':
			switch (color)
			{
			case 1:
				glColor3f(0.772, 0.772, 0.772);
				break;
			case 2:
				glColor3f(0.992, 0.510, 0.749);
				break;
			default:
				break;
			}
			break;
		case 'b':
			switch (color)
			{
			case 1:
				glColor3f(0.733, 0.733, 0.733);
				break;
			case 2:
				glColor3f(0.988, 0.239, 0.258);
				break;
			case 3:
				glColor3f(1.0, 0.729, 0.717);
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}
void drawCube(GLenum type, float cube1, float cube2) {
	glLineWidth(2);
	glBegin(type);//top
	glVertex3f(0, 0, 0);//cube 1 - 1.0 cube 2 -0.5
	glVertex3f(cube1, 0, 0);
	glVertex3f(cube1, 0, cube2);
	glVertex3f(0, 0, cube2);
	glEnd();
	glBegin(type);
	glVertex3f(0, 0, 0);
	glVertex3f(cube1, 0, 0);
	glVertex3f(cube1, cube2, 0);
	glVertex3f(0, cube2, 0);
	glEnd();
	glBegin(type);
	glVertex3f(0, 0, 0);
	glVertex3f(0, cube2, 0);
	glVertex3f(0, cube2, cube2);
	glVertex3f(0, 0, cube2);
	glEnd();
	glBegin(type);
	glVertex3f(0, cube2, 0);
	glVertex3f(cube1, cube2, 0);
	glVertex3f(cube1, cube2, cube2);
	glVertex3f(0, cube2, cube2);
	glEnd();
	glBegin(type);
	glVertex3f(cube1, 0, cube2);
	glVertex3f(cube1, cube2, cube2);
	glVertex3f(cube1, cube2, 0);
	glVertex3f(cube1, 0, 0);
	glEnd();
	glBegin(type);
	glVertex3f(cube1, 0, cube2);
	glVertex3f(cube1, cube2, cube2);
	glVertex3f(0, cube2, cube2);
	glVertex3f(0, 0, cube2);
	glEnd();
}
void eyes1() {
	GLuint textures;
	textures = loadTexture("newblackfur.bmp");
	glColor3f(0, 0, 0);
	glBegin(type);//right eye
	glTexCoord2f(0, 1);
	glVertex3f(0.07, 0.19, -0.2);
	glVertex3f(0.1, 0.11, -0.19);
	glTexCoord2f(0, 0);
	glVertex3f(0.125, 0.1, -0.18);
	glVertex3f(0.135, 0.1, -0.16);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, 0.11, -0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.18, 0.19, -0.12);
	glEnd();
	glBegin(type);//left eye
	glTexCoord2f(0, 1);
	glVertex3f(-0.07, 0.19, -0.2);
	glVertex3f(-0.1, 0.11, -0.19);
	glTexCoord2f(0, 0);
	glVertex3f(-0.125, 0.1, -0.18);
	glVertex3f(-0.135, 0.1, -0.16);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, 0.11, -0.15);
	glTexCoord2f(1, 1);
	glVertex3f(-0.18, 0.19, -0.12);
	glEnd();
	glDeleteTextures(1, &textures);
}
void eyes2() {
	GLuint textures[2];
	textures[0] = loadTexture("newblackfur.bmp");
	glColor3f(0, 0, 0);
	glBegin(type);//right eye
	glTexCoord2f(0, 1);
	glVertex3f(0.07, 0.19, -0.2);
	glVertex3f(0.1, 0.11, -0.19);
	glTexCoord2f(0, 0);
	glVertex3f(0.125, 0.1, -0.18);
	glVertex3f(0.135, 0.1, -0.16);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, 0.11, -0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.18, 0.19, -0.12);
	glEnd();
	glDeleteTextures(1, &textures[0]);

	textures[1] = loadTexture("newfur.bmp");
	glColor3f(1.0, 1.0, 1.0);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.1, 0.18, -0.19);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 0.15, -0.19);
	glTexCoord2f(1, 0);
	glVertex3f(0.12, 0.15, -0.185);
	glTexCoord2f(1, 1);
	glVertex3f(0.12, 0.18, -0.185);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.14, 0.13, -0.17);
	glTexCoord2f(0, 0);
	glVertex3f(0.14, 0.15, -0.17);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 0.15, -0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.13, -0.16);
	glEnd();
	glDeleteTextures(1, &textures[1]);


	textures[0] = loadTexture("newblackfur.bmp");
	glColor3f(0, 0, 0);
	glBegin(type);//left eye
	glTexCoord2f(0, 1);
	glVertex3f(-0.07, 0.19, -0.2);
	glVertex3f(-0.1, 0.11, -0.19);
	glTexCoord2f(0, 0);
	glVertex3f(-0.125, 0.1, -0.18);
	glVertex3f(-0.135, 0.1, -0.16);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, 0.11, -0.15);
	glTexCoord2f(1, 1);
	glVertex3f(-0.18, 0.19, -0.12);
	glEnd();
	glDeleteTextures(1, &textures[0]);

	textures[1] = loadTexture("newfur.bmp");
	glColor3f(1.0, 1.0, 1.0);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, 0.18, -0.19);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.15, -0.19);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, 0.15, -0.185);
	glTexCoord2f(1, 1);
	glVertex3f(-0.12, 0.18, -0.185);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.14, 0.13, -0.17);
	glTexCoord2f(0, 0);
	glVertex3f(-0.14, 0.15, -0.17);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.15, -0.16);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, 0.13, -0.16);
	glEnd();
	glDeleteTextures(1, &textures[1]);
}
void eyes3() {
	GLuint textures;
	textures = loadTexture("newblackfur.bmp");
	glColor3f(0, 0, 0);
	glBegin(type);//right eye
	glTexCoord2f(0, 1);
	glVertex3f(0.07, 0.19, -0.2);
	glVertex3f(0.1, 0.11, -0.19);
	glTexCoord2f(0, 0);
	glVertex3f(0.125, 0.1, -0.18);
	glVertex3f(0.135, 0.1, -0.16);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, 0.11, -0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.18, 0.19, -0.12);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.07, 0.15, -0.2);
	glTexCoord2f(0, 0);
	glVertex3f(-0.17, 0.19, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(-0.18, 0.17, -0.11);
	glTexCoord2f(1, 1);
	glVertex3f(-0.07, 0.13, -0.2);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.07, 0.13, -0.21);
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, 0.11, -0.15);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, 0.12, -0.15);
	glTexCoord2f(1, 1);
	glVertex3f(-0.07, 0.14, -0.21);
	glEnd();
}
void headshapefront() {
	//--------------------------------
	//helmet right
	//--------------------------------
	GLuint textures[2];
	if (!red) {
		textures[1] = loadTexture("pink2.bmp");
	}
	else {
		textures[0] = loadTexture("blue2.bmp");
	}
	color('h',1);
	glBegin(quad);//1
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.36, -0.279);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0.19, -0.279);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, 0.19, -0.278);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, 0.36, -0.278);
	glEnd();

	glBegin(triangle);//2
	glTexCoord2f(0, 1);
	glVertex3f(0.05, 0.36, -0.278);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, 0.29, -0.278);
	glTexCoord2f(1, 0);
	glVertex3f(0.26, 0.29, -0.14);
	glEnd();

	glBegin(quad);//3
	glTexCoord2f(0, 1);
	glVertex3f(0.05, 0.29, -0.278);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, 0.19, -0.278);
	glTexCoord2f(1, 0);
	glVertex3f(0.26, 0.2, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.26, 0.29, -0.14);
	glEnd();

	glBegin(triangle);//4
	glTexCoord2f(0, 1);
	glVertex3f(0.26, 0.29, -0.14);
	glTexCoord2f(0, 0);
	glVertex3f(0.26, 0.2, -0.14);
	glTexCoord2f(1, 0);
	glVertex3f(0.36, 0.2, -0.06);
	glEnd();

	glBegin(quad);//5
	glTexCoord2f(0, 1);
	glVertex3f(0.26, 0.2, -0.14);
	glTexCoord2f(0, 0);
	glVertex3f(0.21, -0.04, -0.14);
	glTexCoord2f(1, 0);
	glVertex3f(0.32, -0.05, -0.06);
	glTexCoord2f(1, 1);
	glVertex3f(0.36, 0.2, -0.06);
	glEnd();

	glBegin(triangle);//6
	glTexCoord2f(0, 1);
	glVertex3f(0.21, -0.04, -0.14);
	glTexCoord2f(0, 0);
	glVertex3f(0.19, -0.15, -0.14);
	glTexCoord2f(1, 0);
	glVertex3f(0.32, -0.05, -0.06);
	glEnd();

	glBegin(quad);//7
	glTexCoord2f(0, 1);
	glVertex3f(0.09, -0.04, -0.22);
	glTexCoord2f(0, 0);
	glVertex3f(0.09, -0.2, -0.22);
	glTexCoord2f(1, 0);
	glVertex3f(0.19, -0.15, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.21, -0.04, -0.14);
	glEnd();

	glBegin(quad);//8
	glTexCoord2f(0, 1);
	glVertex3f(0.04, -0.1, -0.24);
	glTexCoord2f(0, 0);
	glVertex3f(0.04, -0.2, -0.24);
	glTexCoord2f(1, 0);
	glVertex3f(0.09, -0.2, -0.22);
	glTexCoord2f(1, 1);
	glVertex3f(0.09, -0.1, -0.22);
	glEnd();

	glBegin(quad);//9
	glTexCoord2f(0, 1);
	glVertex3f(0, -0.015, -0.28);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.2, -0.28);
	glTexCoord2f(1, 0);
	glVertex3f(0.04, -0.2, -0.24);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, -0.015, -0.24);
	glEnd();

	//-----------------------------------------------------
	//helmet with head right
	//-----------------------------------------------------
	color('h', 2);
	glBegin(type);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.19, -0.279);
	glVertex3f(0, 0.19, -0.25);
	glTexCoord2f(0, 0);
	glVertex3f(0.25, 0.2, -0.06);
	glVertex3f(0.26, 0.2, -0.14);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, 0.19, -0.278);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, 0.2, -0.06);
	glTexCoord2f(0, 0);
	glVertex3f(0.21, -0.04, -0.09);
	glTexCoord2f(1, 0);
	glVertex3f(0.21, -0.04, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.26, 0.2, -0.14);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0, -0.015, -0.26);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.015, -0.28);
	glTexCoord2f(1, 0);
	glVertex3f(0.04, -0.015, -0.24);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, -0.015, -0.21);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, -0.015, -0.24);
	glTexCoord2f(0, 0);
	glVertex3f(0.04, -0.1, -0.24);
	glTexCoord2f(1, 0);
	glVertex3f(0.04, -0.1, -0.21);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, -0.015, -0.21);
	glEnd();

	glBegin(type);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, -0.1, -0.21);
	glVertex3f(0.04, -0.1, -0.24);
	glTexCoord2f(0, 0);
	glVertex3f(0.09, -0.1, -0.22);
	glVertex3f(0.09, -0.1, -0.19);
	glTexCoord2f(1, 0);
	glVertex3f(0.06, -0.1, -0.17);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.09, -0.04, -0.19);
	glTexCoord2f(0, 0);
	glVertex3f(0.09, -0.1, -0.19);
	glTexCoord2f(1, 0);
	glVertex3f(0.09, -0.1, -0.22);
	glTexCoord2f(1, 1);
	glVertex3f(0.09, -0.04, -0.22);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.09, -0.04, -0.19);
	glTexCoord2f(0, 0);
	glVertex3f(0.09, -0.04, -0.22);
	glTexCoord2f(1, 0);
	glVertex3f(0.21, -0.04, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.21, -0.04, -0.09);
	glEnd();

	//--------------------------------
	//helmet left
	//--------------------------------
	color('h', 1);
	glBegin(quad);//1
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.36, -0.279);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0.19, -0.279);
	glTexCoord2f(1, 0);
	glVertex3f(-0.05, 0.19, -0.278);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, 0.36, -0.278);
	glEnd();

	glBegin(triangle);//2
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, 0.36, -0.278);
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, 0.29, -0.278);
	glTexCoord2f(1, 0);
	glVertex3f(-0.26, 0.29, -0.14);
	glEnd();

	glBegin(quad);//3
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, 0.29, -0.278);
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, 0.19, -0.278);
	glTexCoord2f(1, 0);
	glVertex3f(-0.26, 0.2, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.26, 0.29, -0.14);
	glEnd();

	glBegin(triangle);//4
	glTexCoord2f(0, 1);
	glVertex3f(-0.26, 0.29, -0.14);
	glTexCoord2f(0, 0);
	glVertex3f(-0.26, 0.2, -0.14);
	glTexCoord2f(1, 0);
	glVertex3f(-0.36, 0.2, -0.06);
	glEnd();

	glBegin(quad);//5
	glTexCoord2f(0, 1);
	glVertex3f(-0.26, 0.2, -0.14);
	glTexCoord2f(0, 0);
	glVertex3f(-0.21, -0.04, -0.14);
	glTexCoord2f(1, 0);
	glVertex3f(-0.32, -0.05, -0.06);
	glTexCoord2f(1, 1);
	glVertex3f(-0.36, 0.2, -0.06);
	glEnd();

	glBegin(triangle);//6
	glTexCoord2f(0, 1);
	glVertex3f(-0.21, -0.04, -0.14);
	glTexCoord2f(0, 0);
	glVertex3f(-0.19, -0.15, -0.14);
	glTexCoord2f(1, 0);
	glVertex3f(-0.32, -0.05, -0.06);
	glEnd();

	glBegin(quad);//7
	glTexCoord2f(0, 1);
	glVertex3f(-0.09, -0.04, -0.22);
	glTexCoord2f(0, 0);
	glVertex3f(-0.09, -0.2, -0.22);
	glTexCoord2f(1, 0);
	glVertex3f(-0.19, -0.15, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.21, -0.04, -0.14);
	glEnd();

	glBegin(quad);//8
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, -0.1, -0.24);
	glTexCoord2f(0, 0);
	glVertex3f(-0.04, -0.2, -0.24);
	glTexCoord2f(1, 0);
	glVertex3f(-0.09, -0.2, -0.22);
	glTexCoord2f(1, 1);
	glVertex3f(-0.09, -0.1, -0.22);
	glEnd();

	glBegin(quad);//9
	glTexCoord2f(0, 1);
	glVertex3f(0, -0.015, -0.28);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.2, -0.28);
	glTexCoord2f(1, 0);
	glVertex3f(-0.04, -0.2, -0.24);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, -0.015, -0.24);
	glEnd();

	//-----------------------------------------------------
	//helmet with head left
	//-----------------------------------------------------
	color('h', 2);
	glBegin(type);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.19, -0.279);
	glVertex3f(0, 0.19, -0.25);
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0.2, -0.06);
	glVertex3f(-0.26, 0.2, -0.14);
	glTexCoord2f(1, 0);
	glVertex3f(-0.05, 0.19, -0.278);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.25, 0.2, -0.06);
	glTexCoord2f(0, 0);
	glVertex3f(-0.21, -0.04, -0.09);
	glTexCoord2f(1, 0);
	glVertex3f(-0.21, -0.04, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.26, 0.2, -0.14);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0, -0.015, -0.26);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.015, -0.28);
	glTexCoord2f(1, 0);
	glVertex3f(-0.04, -0.015, -0.24);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, -0.015, -0.21);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, -0.015, -0.24);
	glTexCoord2f(0, 0);
	glVertex3f(-0.04, -0.1, -0.24);
	glTexCoord2f(1, 0);
	glVertex3f(-0.04, -0.1, -0.21);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, -0.015, -0.21);
	glEnd();

	glBegin(type);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, -0.1, -0.21);
	glVertex3f(-0.04, -0.1, -0.24);
	glTexCoord2f(0, 0);
	glVertex3f(-0.09, -0.1, -0.22);
	glVertex3f(-0.09, -0.1, -0.19);
	glTexCoord2f(1, 0);
	glVertex3f(-0.06, -0.1, -0.17);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.09, -0.04, -0.19);
	glTexCoord2f(0, 0);
	glVertex3f(-0.09, -0.1, -0.19);
	glTexCoord2f(1, 0);
	glVertex3f(-0.09, -0.1, -0.22);
	glTexCoord2f(1, 1);
	glVertex3f(-0.09, -0.04, -0.22);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.09, -0.04, -0.19);
	glTexCoord2f(0, 0);
	glVertex3f(-0.09, -0.04, -0.22);
	glTexCoord2f(1, 0);
	glVertex3f(-0.21, -0.04, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.21, -0.04, -0.09);
	glEnd();

	glDeleteTextures(1, &textures[0]);
	glDeleteTextures(1, &textures[1]);

	//-------------------------------------------------
	glColor3f(1.0, 1.0, 1.0);
	glBegin(type);//right white
	glVertex3f(0, 0.19, -0.25);
	glVertex3f(0, -0.02, -0.259);
	glVertex3f(0.06, 0.02, -0.169);
	glVertex3f(0.06, 0, -0.169);
	glVertex3f(0.22, 0, -0.089);
	glVertex3f(0.25, 0.2, -0.06);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(type);
	glVertex3f(0, 0.19, -0.25);
	glVertex3f(0, -0.02, -0.259);
	glVertex3f(-0.06, 0.02, -0.169);
	glVertex3f(-0.06, 0, -0.169);
	glVertex3f(-0.22, 0, -0.089);
	glVertex3f(-0.25, 0.2, -0.06);
	glEnd();


	//----------------------------------
	//right mouth
	//----------------------------------
	color('m', 1);
	glBegin(quad);
	glVertex3f(0, 0.02, -0.26);
	glVertex3f(0, -0.015, -0.26);
	glVertex3f(0.04, -0.015, -0.21);
	glVertex3f(0.04, 0.02, -0.21);
	glEnd();

	glBegin(quad);
	glVertex3f(0.04, 0.02, -0.21);
	glVertex3f(0.04, -0.1, -0.21);
	glVertex3f(0.06, -0.1, -0.17);
	glVertex3f(0.06, 0.02, -0.17);
	glEnd();

	glBegin(quad);
	glVertex3f(0.06, 0, -0.17);
	glVertex3f(0.06, -0.1, -0.17);
	glVertex3f(0.09, -0.1, -0.19);
	glVertex3f(0.09, 0, -0.19);
	glEnd();

	glBegin(quad);
	glVertex3f(0.09, 0, -0.19);
	glVertex3f(0.09, -0.04, -0.19);
	glVertex3f(0.21, -0.04, -0.09);
	glVertex3f(0.22, 0, -0.09);
	glEnd();

	//----------------------------------
	//left mouth
	//----------------------------------
	glBegin(quad);
	glVertex3f(0, 0.02, -0.26);
	glVertex3f(0, -0.015, -0.26);
	glVertex3f(-0.04, -0.015, -0.21);
	glVertex3f(-0.04, 0.02, -0.21);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.04, 0.02, -0.21);
	glVertex3f(-0.04, -0.1, -0.21);
	glVertex3f(-0.06, -0.1, -0.17);
	glVertex3f(-0.06, 0.02, -0.17);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.06, 0, -0.17);
	glVertex3f(-0.06, -0.1, -0.17);
	glVertex3f(-0.09, -0.1, -0.19);
	glVertex3f(-0.09, 0, -0.19);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.09, 0, -0.19);
	glVertex3f(-0.09, -0.04, -0.19);
	glVertex3f(-0.21, -0.04, -0.09);
	glVertex3f(-0.22, 0, -0.09);
	glEnd();

	//white with mouth
	glBegin(triangle);
	glVertex3f(0.06, 0.02, -0.19);
	glVertex3f(0.09, 0, -0.19);
	glVertex3f(0.22, 0, -0.09);
	glEnd();
	glBegin(triangle);
	glVertex3f(-0.06, 0.02, -0.2);
	glVertex3f(-0.09, 0, -0.19);
	glVertex3f(-0.22, 0, -0.09);
	glEnd();
}
void headtop() {
	color('h', 3);
	glBegin(quad);//1
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.36, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0.36, -0.279);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, 0.36, -0.278);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, 0.36, 0.1);
	glEnd();

	color('h', 1);
	glBegin(quad);//2
	glTexCoord2f(0,1);
	glVertex3f(0.05, 0.36, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, 0.36, -0.278);
	glTexCoord2f(1, 0);
	glVertex3f(0.26, 0.29, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.26, 0.29, 0.05);
	glEnd();

	glBegin(quad);//4
	glTexCoord2f(0, 1);
	glVertex3f(0.26, 0.29, 0.05);
	glTexCoord2f(0, 0);
	glVertex3f(0.26, 0.29, -0.14);
	glTexCoord2f(1, 0);
	glVertex3f(0.36, 0.2, -0.06);
	glTexCoord2f(1, 1);
	glVertex3f(0.36, 0.2, -0.06);
	glEnd();

	glBegin(quad);//6
	glTexCoord2f(0, 1);
	glVertex3f(0.19, -0.15, -0.14);
	glTexCoord2f(0, 0);
	glVertex3f(0.26, -0.15, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(0.36, -0.04, -0.06);
	glTexCoord2f(1, 1);
	glVertex3f(0.32, -0.05, -0.06);
	glEnd();

	color('h', 3);
	glBegin(quad);//1
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.36, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0.36, -0.279);
	glTexCoord2f(1, 0);
	glVertex3f(-0.05, 0.36, -0.278);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, 0.36, 0.1);
	glEnd();

	color('h', 1);
	glBegin(quad);//2
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, 0.36, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, 0.36, -0.278);
	glTexCoord2f(1, 0);
	glVertex3f(-0.26, 0.29, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.26, 0.29, 0.05);
	glEnd();

	glBegin(quad);//4
	glTexCoord2f(0, 1);
	glVertex3f(-0.26, 0.29, 0.05);
	glTexCoord2f(0, 0);
	glVertex3f(-0.26, 0.29, -0.14);
	glTexCoord2f(1, 0);
	glVertex3f(-0.36, 0.2, -0.06);
	glTexCoord2f(1, 1);
	glVertex3f(-0.36, 0.2, -0.06);
	glEnd();

	glBegin(quad);//6
	glTexCoord2f(0, 1);
	glVertex3f(-0.19, -0.15, -0.14);
	glTexCoord2f(0, 0);
	glVertex3f(-0.26, -0.15, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(-0.36, -0.04, -0.06);
	glTexCoord2f(1, 1);
	glVertex3f(-0.32, -0.05, -0.06);
	glEnd();
}
void headshapeback() {
	//--------------------------------
	//helmet right
	//--------------------------------
	color('h', 1);
	glBegin(quad);//1
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.36, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.2, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.2, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, 0.36, 0.1);
	glEnd();

	glBegin(triangle);//2
	glTexCoord2f(0, 1);
	glVertex3f(0.05, 0.36, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, 0.29, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.26, 0.29, 0.05);
	glEnd();

	glBegin(quad);//3
	glTexCoord2f(0, 1);
	glVertex3f(0.05, 0.29, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.15, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.26, -0.15, 0.05);
	glTexCoord2f(1, 1);
	glVertex3f(0.26, 0.29, 0.05);
	glEnd();

	glBegin(triangle);//4
	glTexCoord2f(0, 1);
	glVertex3f(0.26, 0.29, 0.05);
	glTexCoord2f(0, 0);
	glVertex3f(0.26, 0.2, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(0.36, 0.2, -0.06);
	glEnd();

	glBegin(quad);//5
	glTexCoord2f(0, 1);
	glVertex3f(0.26, 0.2, 0.05);
	glTexCoord2f(0, 0);
	glVertex3f(0.26, -0.04, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(0.36, -0.04, -0.06);
	glTexCoord2f(1, 1);
	glVertex3f(0.36, 0.2, -0.06);
	glEnd();

	glBegin(triangle);//6
	glTexCoord2f(0, 1);
	glVertex3f(0.26, -0.04, 0.05);
	glTexCoord2f(0, 0);
	glVertex3f(0.26, -0.15, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(0.36, -0.04, -0.06);
	glEnd();

	glBegin(triangle);//7
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.15, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.2, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.26, -0.15, 0.05);
	glEnd();

	//--------------------------------
	//helmet left
	//--------------------------------
	color('h', 1);
	glBegin(quad);//1
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.36, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.2, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.05, -0.2, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, 0.36, 0.1);
	glEnd();

	glBegin(triangle);//2
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, 0.36, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, 0.29, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.26, 0.29, 0.05);
	glEnd();

	glBegin(quad);//3
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, 0.29, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, -0.15, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.26, -0.15, 0.05);
	glTexCoord2f(1, 1);
	glVertex3f(-0.26, 0.29, 0.05);
	glEnd();

	glBegin(triangle);//4
	glTexCoord2f(0, 1);
	glVertex3f(-0.26, 0.29, 0.05);
	glTexCoord2f(0, 0);
	glVertex3f(-0.26, 0.2, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(-0.36, 0.2, -0.06);
	glEnd();

	glBegin(quad);//5
	glTexCoord2f(0, 1);
	glVertex3f(-0.26, 0.2, 0.05);
	glTexCoord2f(0, 0);
	glVertex3f(-0.26, -0.04, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(-0.36, -0.04, -0.06);
	glTexCoord2f(1, 1);
	glVertex3f(-0.36, 0.2, -0.06);
	glEnd();

	glBegin(triangle);//6
	glTexCoord2f(0, 1);
	glVertex3f(-0.26, -0.04, 0.05);
	glTexCoord2f(0, 0);
	glVertex3f(-0.26, -0.15, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(-0.36, -0.04, -0.06);
	glEnd();

	glBegin(triangle);//7
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, -0.15, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, -0.2, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.26, -0.15, 0.05);
	glEnd();
}
void rightear() {
	color('e', 1);
	glBegin(quad);
	glVertex3f(0.38, 0.2, -0.06);
	glVertex3f(0.38, 0, -0.06);
	glVertex3f(0.38, 0, 0.03);
	glVertex3f(0.38, 0.2, 0.03);
	glEnd();

	glBegin(quad);
	glVertex3f(0.36, 0.2, -0.06);
	glVertex3f(0.32, -0.05, -0.06);
	glVertex3f(0.38, 0, -0.06);
	glVertex3f(0.38, 0.2, -0.06);
	glEnd();

	glBegin(quad);
	glVertex3f(0.28, 0.2, 0.03);
	glVertex3f(0.28, -0.05, 0.03);
	glVertex3f(0.38, 0, 0.03);
	glVertex3f(0.38, 0.2, 0.03);
	glEnd();

	glPushMatrix();
	glScalef(1.0, 0.8, 1.0);
	glTranslatef(0.38, 0.05, -0.06);
	color('e', 2);
	drawCube(type, 0.06, 0.09);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.6, 4.0, 1.0);
	glTranslatef(0.73, 0.008, -0.06);
	color('e', 2);
	drawCube(type, 0.06, 0.09);
	glPopMatrix();
}
void leftear() {
	color('e', 1);
	glBegin(quad);
	glVertex3f(-0.38, 0.2, -0.06);
	glVertex3f(-0.38, 0, -0.06);
	glVertex3f(-0.38, 0, 0.03);
	glVertex3f(-0.38, 0.2, 0.03);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.36, 0.2, -0.06);
	glVertex3f(-0.32, -0.05, -0.06);
	glVertex3f(-0.38, 0, -0.06);
	glVertex3f(-0.38, 0.2, -0.06);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.28, 0.2, 0.03);
	glVertex3f(-0.28, -0.05, 0.03);
	glVertex3f(-0.38, 0, 0.03);
	glVertex3f(-0.38, 0.2, 0.03);
	glEnd();


	glPushMatrix();
	glScalef(1.0, 0.8, 1.0);
	glTranslatef(-0.44, 0.05, -0.06);
	color('e', 2);
	drawCube(type, 0.06, 0.09);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.6, 4.0, 1.0);
	glTranslatef(-0.77, 0.008, -0.06);
	color('e', 2);
	drawCube(type, 0.06, 0.09);
	glPopMatrix();
}
void head() {
	GLuint textures[3];
	glPushMatrix();
	glScalef(0.6, 0.8, 1.0);
	headshapefront();
	rightear();
	leftear();
	if (!red) {
		textures[1] = loadTexture("pink4.bmp");
	}
	else {
		textures[0] = loadTexture("blue1.bmp");
	}
	headshapeback();
	headtop();
	glDeleteTextures(1, &textures[0]);
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();
}

//-------------------------------------------------------------------------------------------
//------------------------------------BODY---------------------------------------------------
//-------------------------------------------------------------------------------------------
void shapefront() {
	GLuint textures[3];
	if (!red) {
		textures[1] = loadTexture("pink2.bmp");
	}
	else {
		textures[0] = loadTexture("blue4.bmp");
	}
	color('h', 1);//1
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.15, 0.25);;
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, 0, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.15, 0.25);
	glEnd();

	//2
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(-0.21, 0.08, 0.25);
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, 0, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.15, 0.25);
	glEnd();
	

	//3
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -0.03, 0.25);
	glTexCoord2f(0, 0);
	glVertex3f(-0.11, -0.08, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.05, 0, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.21, 0.08, 0.25);
	glEnd();

	//4
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.15, 0.25);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, 0, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.15, 0.25);
	glEnd();

	//5
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.15, 0.25);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, 0, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.21, 0.08, 0.25);
	glEnd();

	//6
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.21, 0.08, 0.25);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, 0, 0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.11, -0.08, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, -0.03, 0.25);
	glEnd();
	glDeleteTextures(1, &textures[0]);
	glDeleteTextures(1, &textures[1]);
}
void shapeback() {
	GLuint textures[3];
	if (!red) {
		textures[1] = loadTexture("pink2.bmp");
	}
	else {
		textures[0] = loadTexture("blue4.bmp");
	}
	color('h', 1);//1
	glBegin(type);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.15, -0.45);
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, 0, -0.45);
	color('b', 1);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, -0.45);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.15, -0.45);
	glEnd();

	color('h', 1);//2
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(-0.21, 0.08, -0.45);
	glTexCoord2f(0, 0);
	color('b', 1);
	glVertex3f(-0.05, 0, -0.45);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.15, -0.45);
	glEnd();

	color('h', 1);//3
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -0.03, -0.45);
	glTexCoord2f(0, 0);
	glVertex3f(-0.11, -0.08, -0.45);
	glTexCoord2f(1, 0);
	glVertex3f(-0.05, 0, -0.45);
	glTexCoord2f(1, 1);
	glVertex3f(-0.21, 0.08, -0.45);
	glEnd();

	color('h', 1);//4
	glBegin(type);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.15, -0.45);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, -0.45);
	color('b', 1);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, 0, -0.45);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.15, -0.45);
	glEnd();

	color('h', 1);//5
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.15, -0.45);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, 0, -0.45);
	color('b', 1);
	glTexCoord2f(1, 0);
	glVertex3f(0.21, 0.08, -0.45);
	glEnd();

	color('h', 1);//6
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.21, 0.08, -0.45);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, 0, -0.45);
	glTexCoord2f(1, 0);
	glVertex3f(0.11, -0.08, -0.45);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, -0.03, -0.45);
	glEnd();
	glDeleteTextures(1, &textures[0]);
	glDeleteTextures(1, &textures[1]);
}//12
void shapeleft() {
	GLuint textures[3];
	if (!red) {
		textures[1] = loadTexture("pink2.bmp");
	}
	else {
		textures[0] = loadTexture("blue4.bmp");
	}
	color('b', 2);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.15, -0.45);
	glTexCoord2f(0, 0);
	glVertex3f(-0.21, 0.08, -0.45);
	glTexCoord2f(1, 0);
	glVertex3f(-0.21, 0.08, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, 0.15, 0.25);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.21, 0.08, -0.45);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, -0.03, -0.45);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -0.03, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.21, 0.08, 0.25);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, -0.03, -0.45);
	glTexCoord2f(0, 0);
	glVertex3f(-0.11, -0.08, -0.45);
	glTexCoord2f(1, 0);
	glVertex3f(-0.11, -0.08, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -0.03, 0.25);
	glEnd();
	glDeleteTextures(1, &textures[0]);
	glDeleteTextures(1, &textures[1]);
}
void shaperight() {
	GLuint textures[3];
	if (!red) {
		textures[1] = loadTexture("pink2.bmp");
	}
	else {
		textures[0] = loadTexture("blue4.bmp");
	}
	color('b', 2);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.15, -0.45);
	glTexCoord2f(0, 0);
	glVertex3f(0.21, 0.08, -0.45);
	glTexCoord2f(1,0);
	glVertex3f(0.21, 0.08, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.15, 0.25);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.21, 0.08, -0.45);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, -0.03, -0.45);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, -0.03, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.21, 0.08, 0.25);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, -0.03, -0.45);
	glTexCoord2f(0, 0);
	glVertex3f(0.11, -0.08, -0.45);
	glTexCoord2f(1, 0);
	glVertex3f(0.11, -0.08, 0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, -0.03, 0.25);
	glEnd();
	glDeleteTextures(1, &textures[0]);
	glDeleteTextures(1, &textures[1]);
}//18
void shapeleft2(float cx, float cy, float cz) {
	glColor3f(cx, cy, cz);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.4, 0.28, -0.35);
	glTexCoord2f(0, 0);
	glVertex3f(-0.35, 0.05, -0.35);
	glTexCoord2f(1,0);
	glVertex3f(-0.35, 0.05, 0.24);
	glTexCoord2f(1, 1);
	glVertex3f(-0.4, 0.28, 0.24);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.35, 0.05, -0.30);
	glTexCoord2f(0, 0);
	glVertex3f(-0.35, 0.05, -0.35);
	glTexCoord2f(1, 0);
	glVertex3f(-0.17, 0, -0.35);
	glTexCoord2f(1, 1);
	glVertex3f(-0.17, 0, -0.30);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.17, 0, -0.30);
	glTexCoord2f(0, 0);
	glVertex3f(-0.17, 0, -0.35);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, -0.06, -0.35);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, -0.06, -0.30);
	glEnd();

}
void shaperight2(float cx, float cy, float cz) {
	glColor3f(cx, cy, cz);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.4, 0.28, 0.24);
	glTexCoord2f(0, 0);
	glVertex3f(0.35, 0.05, 0.24);
	glTexCoord2f(1, 0);
	glVertex3f(0.35, 0.05, -0.35);
	glTexCoord2f(1, 1);
	glVertex3f(0.4, 0.28, -0.35);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.35, 0.05, -0.30);
	glTexCoord2f(0, 0);
	glVertex3f(0.35, 0.05, -0.35);
	glTexCoord2f(1, 0);
	glVertex3f(0.17, 0, -0.35);
	glTexCoord2f(1, 1);
	glVertex3f(0.17, 0, -0.30);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.17, 0, -0.30);
	glTexCoord2f(0, 0);
	glVertex3f(0.17, 0, -0.35);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, -0.06, -0.35);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, -0.06, -0.30);
	glEnd();

}
void shapefront2(float cx, float cy, float cz) {
	glColor3f(cx, cy, cz);//left1
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(-0.4, 0.28, 0.24);
	glTexCoord2f(0, 0);
	glVertex3f(-0.35, 0.05, 0.24);
	glTexCoord2f(1, 0);
	glVertex3f(-0.35, 0.28, 0.24);
	glEnd();

	glColor3f(cx, cy, cz);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.35, 0.28, 0.24);
	glTexCoord2f(0, 0);
	glVertex3f(-0.35, 0.05, 0.24);
	glTexCoord2f(1, 0);
	glVertex3f(-0.17, 0.05, 0.24);
	glTexCoord2f(1, 1);
	glVertex3f(-0.17, 0.28, 0.24);
	glEnd();

	glColor3f(cx, cy, cz);
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(-0.35, 0.05, 0.24);
	glTexCoord2f(0, 0);
	glVertex3f(-0.17, 0, 0.24);
	glTexCoord2f(1, 0);
	glVertex3f(-0.17, 0.05, 0.24);
	glEnd();

	glColor3f(cx, cy, cz);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.17, 0.28, 0.24);
	glTexCoord2f(0, 0);
	glVertex3f(-0.17, 0, 0.24);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, 0.24);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.28, 0.24);
	glEnd();

	glColor3f(cx, cy, cz);
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(-0.17, 0, 0.24);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0, 0.24);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, -0.06, 0.24);
	glEnd();

	glColor3f(cx, cy, cz);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0, 0.24);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.06, 0.24);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.06, 0.24);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0, 0.24);
	glEnd();

	//right1
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.28, 0.24);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0.24);
	glTexCoord2f(1, 0);
	glVertex3f(0.17, 0, 0.24);
	glTexCoord2f(1, 1);
	glVertex3f(0.17, 0.28, 0.24);
	glEnd();


	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0.24);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.06, 0.24);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, -0.06, 0.24);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0, 0.24);
	glEnd();


	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -0.06, 0.24);
	glTexCoord2f(0, 0);
	glVertex3f(0.15, 0, 0.24);
	glTexCoord2f(1, 0);
	glVertex3f(0.17, 0, 0.24);
	glEnd();


	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.17, 0.28, 0.24);
	glTexCoord2f(0, 0);
	glVertex3f(0.17, 0.05, 0.24);
	glTexCoord2f(1, 0);
	glVertex3f(0.35, 0.05, 0.24);
	glTexCoord2f(1, 1);
	glVertex3f(0.35, 0.28, 0.24);
	glEnd();


	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(0.35, 0.28, 0.24);
	glTexCoord2f(0, 0);
	glVertex3f(0.35, 0.05, 0.24);
	glTexCoord2f(1, 0);
	glVertex3f(0.4, 0.28, 0.24);
	glEnd();


	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(0.17, 0.05, 0.24);
	glTexCoord2f(0, 0);
	glVertex3f(0.17, 0, 0.24);
	glTexCoord2f(1, 0);
	glVertex3f(0.35, 0.05, 0.24);
	glEnd();


}
void shapeback2(float cx, float cy, float cz) {
	glColor3f(cx, cy, cz);//left1
	glBegin(triangle);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.4, 0.28, -0.35);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.35, 0.05, -0.35);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-0.35, 0.28, -0.35);
	glEnd();

	glColor3f(cx, cy, cz);
	glBegin(type);
	glTexCoord2f(0, 1);
	glVertex3f(-0.35, 0.28, -0.35);
	glTexCoord2f(0, 0);
	glVertex3f(-0.35, 0.05, -0.35);
	glTexCoord2f(1, 0);
	glColor3f(0.937, 0.937, 0.937);
	glVertex3f(-0.17, 0.05, -0.35);
	glTexCoord2f(1, 1);
	glVertex3f(-0.17, 0.28, -0.35);
	glEnd();

	glColor3f(cx, cy, cz);
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(-0.35, 0.05, -0.35);
	glTexCoord2f(0, 0);
	glVertex3f(-0.17, 0, -0.35);
	glTexCoord2f(1, 0);
	glVertex3f(-0.17, 0.05, -0.35);
	glEnd();

	glColor3f(cx, cy, cz);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.17, 0.28, -0.35);
	glTexCoord2f(0, 0);
	glVertex3f(-0.17, 0, -0.35);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, -0.35);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.28, -0.35);
	glEnd();

	glColor3f(cx, cy, cz);
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(-0.17, 0, -0.35);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0, -0.35);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, -0.06, -0.35);
	glEnd();

	glColor3f(cx, cy, cz);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0, -0.35);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.06, -0.35);
	glTexCoord2f(1, 0);
	glVertex3f(0, -0.06, -0.35);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0, -0.35);
	glEnd();

	glColor3f(cx, cy, cz);//right1
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.28, -0.35);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, -0.35);
	glTexCoord2f(1, 0);
	glVertex3f(0.17, 0, -0.35);
	glTexCoord2f(1, 1);
	glVertex3f(0.17, 0.28, -0.35);
	glEnd();

	glColor3f(cx, cy, cz);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, -0.35);
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.06, -0.35);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, -0.06, -0.35);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0, -0.35);
	glEnd();

	glColor3f(cx, cy, cz);
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -0.06, -0.35);
	glTexCoord2f(0, 0);
	glVertex3f(0.15, 0, -0.35);
	glTexCoord2f(1, 0);
	glVertex3f(0.17, 0, -0.35);
	glEnd();


	glBegin(type);
	glTexCoord2f(0, 1);
	glColor3f(0.937, 0.937, 0.937);
	glTexCoord2f(0, 0);
	glVertex3f(0.17, 0.28, -0.35);
	glTexCoord2f(1, 0);
	glVertex3f(0.17, 0.05, -0.35);
	glColor3f(cx, cy, cz);
	glVertex3f(0.35, 0.05, -0.35);
	glTexCoord2f(1, 1);
	glVertex3f(0.35, 0.28, -0.35);
	glEnd();

	glColor3f(cx, cy, cz);
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(0.35, 0.28, -0.35);
	glTexCoord2f(0, 0);
	glVertex3f(0.35, 0.05, -0.35);
	glTexCoord2f(1, 0);
	glVertex3f(0.4, 0.28, -0.35);
	glEnd();

	glColor3f(cx, cy, cz);
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(0.17, 0.05, -0.35);
	glTexCoord2f(0, 0);
	glVertex3f(0.17, 0, -0.35);
	glTexCoord2f(1, 0);
	glVertex3f(0.35, 0.05, -0.35);
	glEnd();
}
void connectLegfront() {//back?
	color('b', 3);
	glBegin(type);
	glTexCoord2f(0, 1);
	glVertex3f(0.35, 0, 0.2);
	glVertex3f(0.3, -0.15, 0.2);
	glTexCoord2f(0, 0);
	glVertex3f(0.24, -0.15, 0.2);
	glVertex3f(0.2, -0.2, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -0.2, 0.2);
	glVertex3f(-0.24, -0.15, 0.2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.3, -0.15, 0.2);
	glVertex3f(-0.35, 0, 0.2);
	glEnd();
}
void connectLegLeft() {
	color('b', 3);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.35, 0.1, 0.2);
	glTexCoord2f(0, 0);
	glVertex3f(0.3, -0.15, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, -0.15, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(0.35, 0.1, -0.2);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.3, -0.15, 0.2);
	glTexCoord2f(0, 0);
	glVertex3f(0.24, -0.15, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(0.24, -0.15, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.3, -0.15, -0.25);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.24, -0.15, 0.2);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, -0.2, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, -0.2, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.24, -0.15, -0.25);
	glEnd();

}
void connectLegRight() {
	color('b', 3);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.35, 0.2, 0.2);
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, -0.15, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.3, -0.15, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.35, 0.2, -0.25);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.3, -0.15, 0.2);
	glTexCoord2f(0, 0);
	glVertex3f(-0.24, -0.15, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.24, -0.15, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.3, -0.15, -0.25);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.24, -0.15, 0.2);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, -0.2, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -0.2, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.24, -0.15, -0.25);
	glEnd();

}
void connectLegback() {
	color('b', 3);
	glBegin(type);
	glTexCoord2f(0, 1);
	glVertex3f(0.35, 0.1, -0.25);
	glVertex3f(0.3, -0.15, -0.25);
	glTexCoord2f(0, 0);
	glVertex3f(0.24, -0.15, -0.25);
	glVertex3f(0.2, -0.2, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -0.2, -0.25);
	glVertex3f(-0.24, -0.15, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.3, -0.15, -0.25);
	glVertex3f(-0.35, 0.1, -0.25);
	glEnd();
}
void shoulderfront() {
	color('b', 3);


	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.3, 0.25, 0.2);
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, 0.2);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.25, 0.2);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.25, 0.2);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.3, 0, 0.2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.3, 0.25, 0.2);
	glEnd();

	
}
void shoulderback() {
	color('b', 3);
	/*glBegin(quad);
	glVertex3f(0.3, 0.25, -0.2);
	glVertex3f(0.4, 0.25, -0.2);
	glVertex3f(0.4, 0, -0.2);
	glVertex3f(0.3, 0, -0.2);
	glEnd();*/

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.3, 0.25, -0.2);
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.25, -0.2);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.25, -0.2);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.3, 0, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.3, 0.25, -0.2);
	glEnd();

	/*glBegin(quad);
	glVertex3f(-0.3, 0.25, -0.2);
	glVertex3f(-0.3, 0, -0.2);
	glVertex3f(-0.4, 0, -0.2);
	glVertex3f(-0.4, 0.25, -0.2);
	glEnd();*/

	//neck


}
void neck() {
	//front
	color('b', 3);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.3, 0.25, 0.2);
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, 0.25, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, 0.25, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(0.3, 0.25, 0.2);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.25, -0.2);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.25, -0.15);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 0.25, -0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.25, -0.2);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.3, -0.15);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.25, -0.15);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 0.25, -0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.3, -0.15);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, 0.3, -0.1);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.3, -0.15);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.3, -0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0.3, -0.1);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, 0.35, -0.1);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.3, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.3, -0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0.35, -0.1);
	glEnd();

	//back
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.25, 0.2);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.25, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 0.25, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.25, 0.2);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.3, 0.15);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.25, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 0.25, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.3, 0.15);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, 0.3, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.3, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.3, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0.3, 0.1);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, 0.35, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.3, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.3, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0.35, 0.1);
	glEnd();

	//left
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.3, 0.15);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.25, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.25, -0.15);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, 0.3, -0.15);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, 0.35, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.3, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, 0.3, -0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.1, 0.35, -0.1);
	glEnd();

	//right
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.3, 0.15);
	glTexCoord2f(0, 0);
	glVertex3f(0.15, 0.25, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 0.25, -0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.3, -0.15);
	glEnd();

	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.1, 0.35, 0.1);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 0.3, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.3, -0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0.35, -0.1);
	glEnd();
}
void bodyshoulderLeft() {
	color('b', 3);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.3, 0.25, -0.2);
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, 0, 0.2);
	glTexCoord2f(1, 1);
	glVertex3f(0.3, 0.25, 0.2);
	glEnd();
}
void bodyshoulderRight() {
	color('b', 3);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.3, 0.25, -0.2);
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, 0, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.3, 0, 0.2);
	glTexCoord2f(1, 1);
	glVertex3f(-0.3, 0.25, 0.2);
	glEnd();
}
void acces() {
	glColor3f(0, 0, 0);
	glBegin(gltype);
	glVertex3f(0.2, 0.07, -0.451);
	glVertex3f(0.2, -0.03, -0.451);
	glVertex3f(0.31, 0.11, -0.451);
	glEnd();
	glColor3f(0.733, 0.733, 0.733);
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.07, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, -0.03, -0.451);
	glTexCoord2f(1, 0);
	glVertex3f(0.31, 0.11, -0.451);
	glEnd();
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.07, -0.39);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, -0.03, -0.39);
	glTexCoord2f(1, 0);
	glVertex3f(0.31, 0.11, -0.39);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.31, 0.11, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(0.31, 0.11, -0.39);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, -0.03, -0.39);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, -0.03, -0.451);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.07, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.07, -0.39);
	glTexCoord2f(1, 0);
	glVertex3f(0.31, 0.11, -0.39);
	glTexCoord2f(1, 1);
	glVertex3f(0.31, 0.11, -0.451);
	glEnd();


	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.08, -0.39);
	glTexCoord2f(0, 0);
	glVertex3f(0.6, -0.3, -0.39);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0.08, -0.39);
	glEnd();
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.08, -0.34);
	glTexCoord2f(0, 0);
	glVertex3f(0.6, -0.3, -0.34);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0.08, -0.34);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 0.08, -0.39);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0.08, -0.34);
	glTexCoord2f(1, 0);
	glVertex3f(0.6, -0.3, -0.34);
	glTexCoord2f(1, 1);
	glVertex3f(0.6, -0.3, -0.39);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 0.08, -0.39);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0.08, -0.34);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.08, -0.34);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.08, -0.39);
	glEnd();



	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, 0.25, -0.441);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.08, -0.441);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, 0.08, -0.441);
	glEnd();
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, 0.25, -0.39);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.08, -0.39);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, 0.08, -0.39);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.3, 0.08, -0.441);
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0.08, -0.39);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, 0.25, -0.39);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, 0.25, -0.441);
	glEnd();



	glColor3f(0, 0, 0);
	glBegin(gltype);
	glVertex3f(-0.2, 0.07, -0.451);
	glVertex3f(-0.2, -0.03, -0.451);
	glVertex3f(-0.31, 0.11, -0.451);
	glEnd();

	glColor3f(0.733, 0.733, 0.733);
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, 0.07, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, -0.03, -0.451);
	glTexCoord2f(1, 0);
	glVertex3f(-0.31, 0.11, -0.451);
	glEnd();
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, 0.07, -0.39);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, -0.03, -0.39);
	glTexCoord2f(1, 0);
	glVertex3f(-0.31, 0.11, -0.39);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.31, 0.11, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(-0.31, 0.11, -0.39);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, -0.03, -0.39);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, -0.03, -0.451);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, 0.07, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.07, -0.39);
	glTexCoord2f(1, 0);
	glVertex3f(-0.31, 0.11, -0.39);
	glTexCoord2f(1, 1);
	glVertex3f(-0.31, 0.11, -0.451);
	glEnd();

	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, 0.08, -0.39);
	glTexCoord2f(0, 0);
	glVertex3f(-0.6, -0.3, -0.39);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 0.08, -0.39);
	glEnd();
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, 0.08, -0.34);
	glTexCoord2f(0, 0);
	glVertex3f(-0.6, -0.3, -0.34);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5, 0.08, -0.34);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 0.08, -0.39);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0.08, -0.34);
	glTexCoord2f(1, 0);
	glVertex3f(-0.6, -0.3, -0.34);
	glTexCoord2f(1, 1);
	glVertex3f(-0.6, -0.3, -0.39);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, 0.08, -0.39);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0.08, -0.34);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 0.08, -0.34);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, 0.08, -0.39);
	glEnd();


	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, 0.25, -0.441);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.08, -0.441);
	glTexCoord2f(1, 0);
	glVertex3f(-0.3, 0.08, -0.441);
	glEnd();
	glBegin(triangle);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, 0.25, -0.39);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.08, -0.39);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, 0.08, -0.39);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.3, 0.08, -0.441);
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0.08, -0.39);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, 0.25, -0.39);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, 0.25, -0.441);
	glEnd();


	//bottom
	glBegin(type);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, 0, -0.451);
	glVertex3f(-0.11, -0.08, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, -0.12, -0.451);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.12, -0.451);
	glTexCoord2f(1, 1);
	glVertex3f(0.11, -0.08, -0.451);
	glVertex3f(0.05, 0, -0.451);
	glEnd();
	glBegin(type);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, 0, -0.3);
	glVertex3f(-0.11, -0.08, -0.3);
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, -0.12, -0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.12, -0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.11, -0.08, -0.3);
	glVertex3f(0.05, 0, -0.3);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, 0, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, 0, -0.3);
	glTexCoord2f(1, 0);
	glVertex3f(-0.11, -0.08, -0.3);
	glTexCoord2f(1, 1);
	glVertex3f(-0.11, -0.08, -0.451);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.11, -0.08, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(-0.11, -0.08, -0.3);
	glTexCoord2f(1, 0);
	glVertex3f(-0.05, -0.12, -0.3);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, -0.12, -0.451);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, 0, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, 0, -0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.11, -0.08, -0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.11, -0.08, -0.451);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.11, -0.08, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(0.11, -0.08, -0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.12, -0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -0.12, -0.451);
	glEnd();


	glBegin(type);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, -0.12, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.12, -0.451);
	glTexCoord2f(1, 0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.05, -0.18, -0.451);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, -0.18, -0.451);
	glEnd();
	glBegin(type);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, -0.12, -0.3);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.12, -0.3);
	glTexCoord2f(1, 0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.05, -0.18, -0.3);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, -0.18, -0.3);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glColor3f(0.733, 0.733, 0.733);
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, -0.12, -0.451);
	glTexCoord2f(1, 0);
	glVertex3f(-0.05, -0.12, -0.3);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-0.05, -0.18, -0.3);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, -0.18, -0.451);
	glEnd();
	glColor3f(0.733, 0.733, 0.733);
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.12, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.12, -0.3);
	glTexCoord2f(1, 0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.05, -0.18, -0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -0.18, -0.451);
	glEnd();


	glColor3f(0.733, 0.733, 0.733);
	glBegin(type);
	glTexCoord2f(0, 1);
	glVertex3f(-0.09, -0.21, -0.451);
	glVertex3f(-0.05, -0.18, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.18, -0.451);
	glVertex3f(0.09, -0.21, -0.451);
	glTexCoord2f(1, 0);
	glVertex3f(0.09, -0.27, -0.451);
	glTexCoord2f(1, 1);
	glVertex3f(-0.09, -0.27, -0.451);
	glEnd();
	glBegin(type);
	glTexCoord2f(0, 1);
	glVertex3f(-0.09, -0.21, -0.25);
	glVertex3f(-0.05, -0.18, -0.25);
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.18, -0.25);
	glVertex3f(0.09, -0.21, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.09, -0.27, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.09, -0.27, -0.25);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.09, -0.21, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(-0.09, -0.21, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.05, -0.18, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, -0.18, -0.451);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(-0.09, -0.21, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(-0.09, -0.21, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(-0.09, -0.27, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(-0.09, -0.27, -0.451);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.09, -0.21, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(0.09, -0.21, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, -0.18, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -0.18, -0.451);
	glEnd();
	glBegin(quad);
	glTexCoord2f(0, 1);
	glVertex3f(0.09, -0.21, -0.451);
	glTexCoord2f(0, 0);
	glVertex3f(0.09, -0.21, -0.25);
	glTexCoord2f(1, 0);
	glVertex3f(0.09, -0.27, -0.25);
	glTexCoord2f(1, 1);
	glVertex3f(0.09, -0.27, -0.451);
	glEnd();

}
void circle() {

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	circleMin = 0, circleMax = 361;

	for (GLfloat i = circleMin; i < circleMax; i++)
	{
		cx2 = cx + cos(i * PI / 180.f) * 0.35; // keep the axes radius same
		cy2 = cy + sin(i * PI / 180.f) * 0.35;
		glVertex3f(cx2, cy2, -0.359);
	}
	glEnd();
}
void body() {
	GLuint textures[7];
	glPushMatrix();
	glScalef(0.98, 1.4, 0.5);
	glPushMatrix();
	glScalef(0.3, 0.3, 1.0);
	glTranslatef(0, -1.1, 0);
	circle();
	glPopMatrix();
	glPushMatrix();
	textures[4] = loadTexture("grey.bmp");
	acces();
	glDeleteTextures(1, &textures[4]);
	if (!red) {
		textures[5] = loadTexture("lPink.bmp");
	}
	else {
		textures[6] = loadTexture("lBlue.bmp");
	}
	neck();
	shoulderback();
	shoulderfront();
	bodyshoulderLeft();
	bodyshoulderRight();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.28, 0);
	connectLegfront();
	connectLegback();
	connectLegLeft();
	connectLegRight();
	glPopMatrix();
	glDeleteTextures(1, &textures[5]);
	glDeleteTextures(1, &textures[6]);
	glPushMatrix();
	glScalef(1.3, 1.3, 0.9);
	glTranslatef(0, -0.25, 0);
	
	if (!red) {
		textures[1] = loadTexture("pink2.bmp");
	}
	else {
		textures[0] = loadTexture("blue4.bmp");
	}
	
	if (changeColor) {
		shapefront2(0.125, 0.615, 0.823);
		shapeback2(0.125, 0.615, 0.823);
		shapeleft2(0.125, 0.615, 0.823);
		shaperight2(0.125, 0.615, 0.823);
	}
	else {
		shapefront2(0.823, 0.125, 0.267);
		shapeback2(0.823, 0.125, 0.267);
		shapeleft2(0.823, 0.125, 0.267);
		shaperight2(0.823, 0.125, 0.267);
	}
	glPopMatrix();
	glDeleteTextures(1, &textures[0]);
	glDeleteTextures(1, &textures[1]);
	if (!red) {
		textures[2] = loadTexture("pink4.bmp");
	}
	else {
		textures[3] = loadTexture("blue5.bmp");
	}
	

	glPushMatrix();
	glTranslatef(0, -0.2, 0);
	if (changeColor) {
		shapefront2(0.278, 0.372, 0.878);
		shapeback2(0.278, 0.372, 0.878);
		shapeleft2(0.278, 0.372, 0.878);
		shaperight2(0.278, 0.372, 0.878);
	}
	else {
		shapefront2(0.894, 0.263, 0.439);
		shapeback2(0.894, 0.263, 0.439);
		shapeleft2(0.894, 0.263, 0.439);
		shaperight2(0.894, 0.263, 0.439);
	}
	glDeleteTextures(1, &textures[2]);
	glDeleteTextures(1, &textures[3]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -0.03);
	shapefront();
	shapeback();
	shapeleft();
	shaperight();
	glPopMatrix();
	glPopMatrix();
}


//-------------------------------------------------------------------------------------------
//------------------------------------LEG & WING---------------------------------------------
//-------------------------------------------------------------------------------------------
void sphereC(float rad, int sl, int st) {

	//glPointSize(5.0);   //draw the point size
	GLUquadricObj* sphere = NULL;  //create quadric obj pointer
	sphere = gluNewQuadric(); //create quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL); //set the draw style GLU_LINE,GLU_FILL,GLU_POINT GLU_SILHOUETTE

	//add texture
	//gluQuadricTexture(GLUquadric* quad, GLboolean texture);
	gluQuadricTexture(sphere, true);




	gluSphere(sphere, rad, sl, st); //draw sphere 0.5,30,30 (rad,slice,stacks)
	gluDeleteQuadric(sphere);  //free up the memory to avoid crash
}
void sphereCP(float rad, int sl, int st) {

	//glPointSize(5.0);   //draw the point size
	GLUquadricObj* sphere = NULL;  //create quadric obj pointer
	sphere = gluNewQuadric(); //create quadric obj
	glPointSize(5);
	gluQuadricDrawStyle(sphere, GLU_POINT); //set the draw style GLU_LINE,GLU_FILL,GLU_POINT GLU_SILHOUETTE
	//add texture
	//gluQuadricTexture(GLUquadric* quad, GLboolean texture);

	gluQuadricTexture(sphere, true);

	gluSphere(sphere, rad, sl, st); //draw sphere 0.5,30,30 (rad,slice,stacks)
	gluDeleteQuadric(sphere);  //free up the memory to avoid crash
}
void cylinderC(float br, float tr, float h, float csl, float cst) {
	//glPointSize(5.0);   //draw the point size
	GLUquadricObj* cylinder = NULL;  //create quadric obj pointer
	cylinder = gluNewQuadric(); //create quadric obj
	gluQuadricDrawStyle(cylinder, GLU_FILL); //set the draw style GLU_LINE,GLU_FILL,GLU_POINT GLU_SILHOUETTE
	//add texture
	//gluQuadricTexture(GLUquadric* quad, GLboolean texture);

	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, br, tr, h, csl, cst); //(GLUquadric obj *, baseRadius,topRadius, height, slices, stacks) gluCylinder(cylinder,0.4,0.0,0.5,10,10);
	gluDeleteQuadric(cylinder);  //free up the memory to avoid crash
}
void cylinderCLine(float br, float tr, float h, float csl, float cst) {
	//glPointSize(5.0);   //draw the point size
	GLUquadricObj* cylinder = NULL;  //create quadric obj pointer
	cylinder = gluNewQuadric(); //create quadric obj
	gluQuadricDrawStyle(cylinder, GLU_LINE); //set the draw style GLU_LINE,GLU_FILL,GLU_POINT GLU_SILHOUETTE
	//add texture
	//gluQuadricTexture(GLUquadric* quad, GLboolean texture);

	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, br, tr, h, csl, cst); //(GLUquadric obj *, baseRadius,topRadius, height, slices, stacks) gluCylinder(cylinder,0.4,0.0,0.5,10,10);
	gluDeleteQuadric(cylinder);  //free up the memory to avoid crash
}
void cubeC(float sz) {
	glBegin(GL_QUADS);


	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, sz);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, 0.0f, sz);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 … /Left
	//glColor3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, 0.0f);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sz, sz);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, sz);

	// Face 3 / Front face
	//glColor3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, sz);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, sz);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, sz, sz);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, 0.0f, sz);

	// Face 4 / Right face
	//glColor3f(0.0, 1.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, 0.0f, sz);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, sz, sz);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, sz, 0.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);

	// Face 5 / Back face
	//glColor3f(1.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, 0.0f, 0.0f);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sz, 0.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, sz, 0.0f);

	// Face 6 / Top face
	//glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, sz, 0.0f);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, sz, sz);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sz, sz);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, sz, 0.0f);


	glEnd();
}
void rectangleC() {
	glBegin(GL_QUADS);
	// Face 1  abdc

	//face 2  bdhf
	//glColor3f(1.0, 0.0, 1.0); //magenta  purple
	glVertex3f(0.12, 0.0, 0.0); //b
	glVertex3f(0.12, 0.0, -0.14); //d
	glVertex3f(0.12, 0.15, -0.14); //h
	glVertex3f(0.12, 0.15, 0.0); //f

	//face 3  fhge
	//glColor3f(0.0, 1.0, 1.0); //cyan  green
	glVertex3f(0.12, 0.15, 0.0); //f
	glVertex3f(0.12, 0.15, -0.14); //h
	glVertex3f(0, 0.15, -0.14); //g
	glVertex3f(0.0, 0.15, 0.0); //e


	//face 4 efba top
	//glColor3f(1.0, 1.0, 1.0); //white
	glVertex3f(0.0, 0.15, 0.0); //e
	glVertex3f(0.12, 0.15, 0.0); //f
	glVertex3f(0.12, 0.0, 0.0); //b
	glVertex3f(0.0, 0.0, 0.0); //a

	//face 5 aegc
	//glColor3f(1.0, 1.0, 0.0); //yellow
	glVertex3f(0.0, 0.0, 0.0); //a
	glVertex3f(0.0, 0.15, 0.0); //e
	glVertex3f(0, 0.15, -0.14); //g
	glVertex3f(0.0, 0.0, -0.14); //c

	//face 6 cdhg
	//glColor3f(0.0, 0.0, 1.0);  //blue
	glVertex3f(0.0, 0.0, -0.14); //c
	glVertex3f(0.12, 0.0, -0.14); //d
	glVertex3f(0.12, 0.15, -0.14); //h
	glVertex3f(0, 0.15, -0.14); //g

	//glColor3f(1.0, 0.0, 0.0); //red
	glVertex3f(0.0, 0.0, 0.0); //a
	glVertex3f(0.12, 0.0, 0.0); //b
	glVertex3f(0.12, 0.0, -0.14); //d
	glVertex3f(0.0, 0.0, -0.14); //c
	glEnd();

}

void legA() {

	//cylinder
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);   // 2. Rotate 
	glTranslatef(0.085, 0.0, 0.0);
	glColor3f(0.9, 0.9, 0.98); //lavender	#E6E6FA	(230,230,250)
	cylinderC(0.02, 0.02, 0.06, 50, 50);
	glPopMatrix();

	//Cube
	glPushMatrix();
	glTranslatef(0.06, -0.06, -0.03);
	glColor3f(0.9, 0.9, 0.98); //lavender	#E6E6FA	(230,230,250)
	cubeC(0.06);
	glPopMatrix();

	//cylinder
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);   // 2. Rotate 
	glTranslatef(0.125, 0.0, 0.0);
	glColor3f(0.9, 0.9, 0.98); //lavender	#E6E6FA	(230,230,250)
	cylinderC(0.02, 0.02, 0.06, 50, 50);
	glPopMatrix();

	// 2 cylinder 1 cube
}
void legB() {
	//move leg to vertical
	glPushMatrix();
	glTranslatef(0.1, 0.1, 0.0); //fix size
	glPushMatrix();
	glRotatef(270, 1.0, 0.0, 0.0); //fix size at vertical 

	//B3

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.20);
	glColor3f(0.9, 0.9, 0.98); //lavender	#E6E6FA	(230,230,250)
	cylinderC(0.04, 0.02, 0.02, 50, 50);
	glPopMatrix();

	//B2 ball
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.20);
	glColor3f(0.98, 0.98, 0.82);//light golden rod yellow	#FAFAD2	(250,250,210)
	sphereC(0.02, 50, 50);
	glPopMatrix();

	//B2
	if (!red) {
		glColor3f(1.0, 0.71, 0.75); //light pink	#FFB6C1	(255,182,193)
	}
	else {
		glColor3f(0.52, 0.80, 0.92); // #cc sky blue	#87CEEB	(135,206,235)
	}
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.20);
	cylinderC(0.02, 0.04, 0.02, 50, 50);
	glPopMatrix();

	//B
	if (!red) {
		glColor3f(1.0, 0.75, 0.79); //#ccpink	#FFC0CB	(255,192,203)
	}
	else {
		glColor3f(0.52, 0.80, 0.98); // #cc light sky blue	#87CEFA(135, 206, 250)
	}
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.18);
	cylinderC(0.04, 0.07, 0.16, 50, 50);
	glPopMatrix();

	//B1
	if (!red) {
		glColor3f(1.0, 0.71, 0.75); //light pink	#FFB6C1	(255,182,193)
	}
	else {
		glColor3f(0.52, 0.80, 0.92); // #cc sky blue	#87CEEB	(135,206,235)
	}
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.02);
	cylinderC(0.07, 0.03, 0.02, 50, 50);
	glPopMatrix();


	//move leg to vertical
	glPopMatrix();
	glPopMatrix();

	//total 4 cylinder 2 sphere
}
void legC() {
	//move leg to vertical
	glPushMatrix();
	glTranslatef(0.1, 0.1, 0.0); //fix size
	glPushMatrix();
	glRotatef(270, 1.0, 0.0, 0.0); //fix size at vertical 

	//C ball
	glColor3f(0.28, 0.23, 0.54);//dark slate blue	#483D8B	(72,61,139)
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.02);
	sphereC(0.025, 50, 50);
	glPopMatrix();


	//C
	glColor3f(0.94, 1.0, 1.0); // #cc azure	#F0FFFF	(240,255,255)
	cylinderC(0.03, 0.03, 0.02, 50, 50);
	//#cc D1
	if (!red) {
		glColor3f(0.69, 0.13, 0.13); //firebrick	#B22222	(178,34,34)
	}
	else {
		glColor3f(0.69, 0.76, 0.87); //light steel blue	#B0C4DE	(176,196,222)
	}
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.02);
	cylinderC(0.03, 0.05, 0.02, 50, 50);
	glPopMatrix();
	//#cc D
	if (!red) {
		glColor3f(0.86, 0.07, 0.23); //crimson	#DC143C	(220,20,60)
	}
	else {
		glColor3f(0.69, 0.87, 0.90); //powder blue	#B0E0E6	(176,224,230)
	}
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.04);
	cylinderC(0.05, 0.05, 0.08, 50, 50);
	glPopMatrix();

	//#cc D2
	if (!red) {
		glColor3f(0.69, 0.13, 0.13); //firebrick	#B22222	(178,34,34)
	}
	else {
		glColor3f(0.69, 0.76, 0.87); //light steel blue	#B0C4DE	(176,196,222)
	}
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.12);
	cylinderC(0.05, 0.03, 0.02, 50, 50);
	glPopMatrix();
	//E
	glColor3f(0.66, 0.66, 0.66); // dark grey	#A9A9A9	(169,169,169)
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.14);
	cylinderC(0.03, 0.022, 0.02, 50, 50);
	glPopMatrix();

	//E1
	// change this to the leg B
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.16);
	if (!isFly) {
		//C2
		if (red) {
			glColor3f(0.09, 0.09, 0.43); // midnight blue	#191970	(25,25,112)
		}
		else {
			glColor3f(0.69, 0.13, 0.13); //firebrick	#B22222	(178,34,34)
		}
		cylinderC(0.03, 0.03, 0.02, 50, 50);
	}
	else {
		glColor3f(0.98, 0.98, 0.82);//light golden rod yellow	#FAFAD2	(250,250,210)
		sphereC(0.022, 50, 50);
	}
	glPopMatrix();

	//move leg to vertical
	glPopMatrix();
	glPopMatrix();

	//6 cylinder 1 sphere
}
void combineRightleg() {
	if (lcAngle >= 10)
		lcAngle -= lSpeed;
	if (lcAngle <= -10)
		lcAngle += lSpeed;

	//big leg
	glPushMatrix();
	glTranslatef(0.08, -0.08, 0.0);                 // 3. Translate back to original 
	glRotatef(180, 1.0, 0.0, 0.0);   // 2. Rotate the object around angle 
	glTranslatef(-(0.08), -(-0.08), 0.0);            // 1. Move to origin 
	legB();
	//legC();
	glPopMatrix();

	//small leg (Still in process modification
	glPushMatrix();
	glTranslatef(lx, ly, 0.0);                 // 3. Translate back to original 
	glRotatef(lcAngle, 1.0, 0.0, 0.0);   // 2. Rotate the object around angle 
	glTranslatef(-lm, -ln, 0.0);            // 1. Move to origin 
	glPushMatrix();
	glTranslatef(0.08, -0.08, 0.0);                 // 3. Translate back to original 
	glRotatef(180, 1.0, 0.0, 0.0);   // 2. Rotate the object around angle 
	glTranslatef(-(0.08), -(-0.08), 0.0);            // 1. Move to origin 
	legC();
	glPopMatrix();
	glPopMatrix();



}
void combineLeftleg() {
	if (lcAngle2 >= 10)
		lcAngle2 -= lSpeed;
	if (lcAngle2 <= -10)
		lcAngle2 += lSpeed;

	//big leg
	glPushMatrix();
	glTranslatef(0.08, -0.08, 0.0);                 // 3. Translate back to original 
	glRotatef(180, 1.0, 0.0, 0.0);   // 2. Rotate the object around angle 
	glTranslatef(-(0.08), -(-0.08), 0.0);            // 1. Move to origin 
	legB();
	//legC();
	glPopMatrix();

	//small leg (Still in process modification
	glPushMatrix();
	glTranslatef(lx, ly, 0.0);                 // 3. Translate back to original 
	glRotatef(lcAngle2, 1.0, 0.0, 0.0);   // 2. Rotate the object around angle 
	glTranslatef(-lm, -ln, 0.0);            // 1. Move to origin 
	glPushMatrix();
	glTranslatef(0.08, -0.08, 0.0);                 // 3. Translate back to original 
	glRotatef(180, 1.0, 0.0, 0.0);   // 2. Rotate the object around angle 
	glTranslatef(-(0.08), -(-0.08), 0.0);            // 1. Move to origin 
	legC();
	glPopMatrix();
	glPopMatrix();



}
void leftleg() {
	if (lAngle2 >= 35)
		lAngle2 -= lSpeed;
	if (lAngle2 <= -35)
		lAngle2 += lSpeed;
	//top leg
	legA();
	//leg that will move
	glPushMatrix();
	glTranslatef(lx2, ly2, 0.0);                 // 3. Translate back to original 
	glRotatef(lAngle2, 1.0, 0.0, 0.0);   // 2. Rotate the object around angle 
	glTranslatef(-lm2, -ln2, 0.0);            // 1. Move to origin 
	combineLeftleg();
	glPopMatrix();

}
void rightleg() {

	if (lAngle >= 35)
		lAngle -= lSpeed;
	if (lAngle <= -35)
		lAngle += lSpeed;
	//top leg
	legA();
	//leg that will move
	glPushMatrix();
	glTranslatef(lx, ly, 0.0);                 // 3. Translate back to original 
	glRotatef(lAngle, 1.0, 0.0, 0.0);   // 2. Rotate the object around angle 
	glTranslatef(-lm, -ln, 0.0);            // 1. Move to origin 
	combineRightleg();
	glPopMatrix();

}
void wholeLeg() {
	//left leg
	glPushMatrix();
	glTranslatef(-0.195, -0.06, 0.5);
	leftleg();
	glPopMatrix();

	//body leg
	//brige A 
	glPushMatrix();
	glTranslatef(-0.052, -0.09, 0.53);
	glPushMatrix();
	glScalef(0.8, 0.3, 0.5); //length ? height / width
	glColor3f(0.66, 0.66, 0.66); // dark grey	#A9A9A9	(169,169,169)
	rectangleC();
	glPopMatrix();
	glPopMatrix();



	//bridge B
	glPushMatrix();
	glTranslatef(-0.052, -0.12, 0.53);
	glPushMatrix();
	glScalef(0.8, 0.3, 0.5); //length ? height / width
	glColor3f(0.66, 0.66, 0.66); // dark grey	#A9A9A9	(169,169,169)
	rectangleC();
	glPopMatrix();
	glPopMatrix();



	//right leg
	glPushMatrix();
	glTranslatef(-0.02, -0.06, 0.5);
	rightleg();
	glPopMatrix();

	//1 rectangle
}
void wingLine() {
	//wing 2
	glPushMatrix();
	glTranslatef(0.135, 0.17, 0.45);  // Tz 0.55 true
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.9, 0.9, 0.98); //lavender	#E6E6FA	(230,230,250)
	cylinderC(0.015, 0.015, 0.1, 50, 50);
	glPopMatrix();

	//ball a
	glPushMatrix();
	glTranslatef(0.135, 0.17, 0.45);   //Tz 0.55 
	glColor3f(0.9, 0.9, 0.98); //lavender	#E6E6FA	(230,230,250)
	//glColor3f(0.0, 0.0, 0.5); //navy	#000080	(0,0,128)
	sphereC(0.015, 50, 50);
	glPopMatrix();

	//ball b
	glPushMatrix();
	glTranslatef(0.235, 0.17, 0.45);  //Tz 0.55
	glColor3f(0.9, 0.9, 0.98); //lavender	#E6E6FA	(230,230,250)
	//glColor3f(0.0, 0.0, 0.5); //navy	#000080	(0,0,128)
	sphereC(0.015, 50, 50);
	glPopMatrix();
}
void wingC() {
	//wing 1
	glPushMatrix();
	glTranslatef(0.01, -0.02, 0.0);
	glScalef(0.8, 1.0, 1.0);
	wingLine();
	glPopMatrix();

	//wing 2
	wingLine();

	//wing 3
	glPushMatrix();
	glTranslatef(-0.03, 0.02, 0.0);
	glScalef(1.3, 1.0, 1.0);
	wingLine();
	glPopMatrix();

	//wing 4
	glPushMatrix();
	glTranslatef(-0.04, 0.04, 0.0);
	glScalef(1.5, 1.0, 1.0);
	wingLine();
	glPopMatrix();

	//wing 5
	glPushMatrix();
	glTranslatef(-0.04, 0.06, 0.0);
	glScalef(1.7, 1.0, 1.0);
	wingLine();
	glPopMatrix();

}
void wingAB() {
	//wingA
	glPushMatrix();
	glTranslatef(0.1, 0.1, 0.5);
	glScalef(0.1, 0.6, 0.1);
	glColor3f(0.98, 0.98, 0.82);//light golden rod yellow	#FAFAD2	(250,250,210)
	rectangleC();
	glPopMatrix();

	//wing B
	glPushMatrix();
	glTranslatef(0.1, 0.15, 0.5);
	glScalef(0.3, 0.4, 0.1);
	glColor3f(0.98, 0.98, 0.82);//light golden rod yellow	#FAFAD2	(250,250,210)
	rectangleC();
	glPopMatrix();
}
void wingC1() {
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.06);
	wingC();
	glPopMatrix();
}
void leftWing() {
	if (!isFly) {
		//wing AB
		wingAB();
		
		//wing C
		wingC1();
		
	}
	else {
		if (lwAngle >= 45)
			lwAngle -= wSpeed;
		if (lwAngle <= -45)
			lwAngle += wSpeed;

		//move wing to down
		glPushMatrix();
		glTranslatef(lwx, lwy, 0.0);
		glRotatef(lwAngle, 0.0, 0.0, 1.0);
		glTranslatef(-lwm, -lwn, 0.0);
		//wing AB
		wingAB();
		wingC1();
		glPopMatrix();
	}
}
void rightWing() {
	if (!isFly) {
		glPushMatrix();
		glTranslatef(-0.003, 0.0, 0.99);
		glRotatef(180, 0.0, 1.0, 0.0); //rotate 
		wingAB();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 0.0, 1.02);   //Tz 1.0 will be change afterward
		glRotatef(180, 0.0, 1.0, 0.0); //rotate 
		wingC1();
		glPopMatrix();

	}
	else {
		if (lwAngle2 >= 45)
			lwAngle2 -= wSpeed;
		if (lwAngle2 <= -45)
			lwAngle2 += wSpeed;
		//move wing to down
		glPushMatrix();
		glTranslatef(lwx2, lwy2, 0.0);
		glRotatef(lwAngle2, 0.0, 0.0, 1.0);
		glTranslatef(-lwm2, -lwn2, 0.0);


		glPushMatrix();
		glTranslatef(-0.003, 0.0, 0.99);
		glRotatef(180, 0.0, 1.0, 0.0); //rotate 
		wingAB();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 0.0, 1.02);   //Tz 1.0 will be change afterward
		glRotatef(180, 0.0, 1.0, 0.0); //rotate 
		wingC1();
		glPopMatrix();


		glPopMatrix();
	}
}
void wholeWing() {

	glPushMatrix();
	glTranslatef(-0.05, 0.1, 0.0);   //Tz 1.0 will be change afterward
	leftWing();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.04, 0.1, 0.0);   //Tz 1.0 will be change afterward
	rightWing();
	glPopMatrix();
}



//-------------------------------------------------------------------------------------------
//------------------------------------HAND-----------------------------------------------
//-------------------------------------------------------------------------------------------
void drawSphere(float rad, int sl, int st, float angle)
{
	float angle_rotate = angle;
	float x_rotate = 0;
	float y_rotate = 1;
	float z_rotate = 0;
	glPushMatrix();
	glRotatef(angle_rotate, x_rotate, y_rotate, z_rotate);		// Rotate the object


	glColor3f(1.00, 1.00, 0.72);
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricTexture(sphere, true);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, rad, sl, st);
	gluDeleteQuadric(sphere);
	glPopMatrix();
}
void drawPowerSphere(float rad, int sl, int st, float angle, float x, float y, float z)
{
	float x_translate = x;
	float y_translate = y;
	float z_translate = z;
	float angle_rotate = angle;
	float x_rotate = 0;
	float y_rotate = 1;
	float z_rotate = 0;
	glPushMatrix();
	glTranslatef(x_translate, y_translate, z_translate);		// Move the object
	glRotatef(angle_rotate, x_rotate, y_rotate, z_rotate);		// Rotate the object

	glColor3f(1.0, 0.5, 0.25);
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, rad, sl, st);
	gluDeleteQuadric(sphere);
	glPopMatrix();
}
void drawLineSphere(float rad, int sl, int st, float angle)
{
	float angle_rotate = angle;
	float x_rotate = 0;
	float y_rotate = 1;
	float z_rotate = 0;
	glPushMatrix();
	glRotatef(angle_rotate, x_rotate, y_rotate, z_rotate);		// Rotate the object

	glColor3f(0.88, 0.88, 1.00);
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_LINE);
	gluSphere(sphere, rad, sl, st);
	gluDeleteQuadric(sphere);
	glPopMatrix();
}
void drawCylinder(float base_rad, float top_rad, float h, int sl, int st, float angle, float x, float y, float z)
{
	float x_translate = x;
	float y_translate = y;
	float z_translate = z;
	float angle_rotate = angle;
	float x_rotate = 1;
	float y_rotate = 0;
	float z_rotate = 0;
	glPushMatrix();
	glTranslatef(x_translate, y_translate, z_translate);		// Move the object
	glRotatef(angle_rotate, x_rotate, y_rotate, z_rotate);		// Rotate the object

	glColor3f(0.55, 0.65, 0.65);
	GLUquadricObj* Cylinder = NULL;
	Cylinder = gluNewQuadric();
	gluQuadricDrawStyle(Cylinder, GLU_FILL);
	gluCylinder(Cylinder, base_rad, top_rad, h, sl, st);
	gluDeleteQuadric(Cylinder);
	glPopMatrix();
}
void drawOuterCase(float base_rad, float top_rad, float h, int sl, int st, float angle, float x, float y, float z)
{
	float x_translate = x;
	float y_translate = y;
	float z_translate = z;
	float angle_rotate = angle;
	float x_rotate = 1;
	float y_rotate = 0;
	float z_rotate = 0;
	glPushMatrix();
	glTranslatef(x_translate, y_translate, z_translate);		// Move the object
	glRotatef(angle_rotate, x_rotate, y_rotate, z_rotate);		// Rotate the object

	glColor3f(0.69, 0.76, 0.87);
	GLUquadricObj* Cylinder = NULL;
	Cylinder = gluNewQuadric();
	gluQuadricDrawStyle(Cylinder, GLU_FILL);
	gluCylinder(Cylinder, base_rad, top_rad, h, sl, st);
	gluDeleteQuadric(Cylinder);
	glPopMatrix();
}
void shoulderLeft()
{
	float obj_x = 0;
	float obj_y = 0.3 * 1.1;
	float obj_z = 0.3;
	float width = Shoulder_width;
	float height = Shoulder_height;
	float depth = Shoulder_depth;

	//--------------------------------
	//	OpenGL drawing
	//--------------------------------	
	glPushMatrix();												// Move to final result or transformation
	drawSphere(0.12, 4, 10, 90);
	drawLineSphere(0.125, 4, 5, 90);
	glPopMatrix();

	if (isOn) {
		c_x = 1.00, c_y = 1.00, c_z = 1.00;
		c2_x = 1.00, c2_y = 1.00, c2_z = 1.00;
		c3_x = 0.40, c3_y = 0.40, c3_z = 1.00;
	}
	if (isTexture && changeColor == true) {
		c_x = 1.00, c_y = 1.00, c_z = 1.00;
		c2_x = 1.00, c2_y = 1.00, c2_z = 1.00;
		c3_x = 0.40, c3_y = 0.40, c3_z = 1.00;
	}
	if (isTexture && changeColor == false) {
		c_x = 1.00, c_y = 1.00, c_z = 1.00;
		c2_x = 1.00, c2_y = 1.00, c2_z = 1.00;
		c3_x = 1.00, c3_y = 0.00, c3_z = 0.20;
	}
	else if (!isTexture && changeColor == true) {
		c_x = 0.40, c_y = 0.40, c_z = 1.00;
		c2_x = 0.20, c2_y = 1.00, c2_z = 1.00;
		c3_x = 0.40, c3_y = 0.40, c3_z = 1.00;
	}
	else if (!isTexture && changeColor == false) {
		c_x = 1.00, c_y = 0.00, c_z = 0.20;
		c2_x = 1.00, c2_y = 1.00, c2_z = 0.72;
		c3_x = 1.00, c3_y = 0.00, c3_z = 0.20;
	}

	glPushMatrix();
	glTranslatef(0.32, -0.31, -0.3);
	glBegin(GL_QUADS);											// Left 
		// Front
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.4, obj_y + height * 0.5, obj_z + depth * -0.4);
	glVertex3f(obj_x + width * -0.1, obj_y + height * 0.6, obj_z + depth * -0.4);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * -0.1, obj_y + height * -0.5, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.5, obj_y + height * -0.5, obj_z + depth * -0.5);
	// Back
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.4, obj_y + height * 0.5, obj_z + depth * 0.4);
	glVertex3f(obj_x + width * -0.1, obj_y + height * 0.6, obj_z + depth * 0.4);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * -0.1, obj_y + height * -0.5, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * -0.5, obj_y + height * -0.5, obj_z + depth * 0.5);
	// Left
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.4, obj_y + height * 0.5, obj_z + depth * 0.4);
	glVertex3f(obj_x + width * -0.4, obj_y + height * 0.5, obj_z + depth * -0.4);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * -0.5, obj_y + height * -0.5, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.5, obj_y + height * -0.5, obj_z + depth * 0.5);
	// Right
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.1, obj_y + height * 0.6, obj_z + depth * 0.4);
	glVertex3f(obj_x + width * -0.1, obj_y + height * 0.6, obj_z + depth * -0.4);
	glVertex3f(obj_x + width * -0.1, obj_y + height * -0.5, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.1, obj_y + height * -0.5, obj_z + depth * 0.5);
	// Top
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.4, obj_y + height * 0.5, obj_z + depth * 0.4);
	glVertex3f(obj_x + width * -0.1, obj_y + height * 0.6, obj_z + depth * 0.4);
	glVertex3f(obj_x + width * -0.1, obj_y + height * 0.6, obj_z + depth * -0.4);
	glVertex3f(obj_x + width * -0.4, obj_y + height * 0.5, obj_z + depth * -0.4);
	// Bottom
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * -0.5, obj_y + height * -0.5, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * -0.1, obj_y + height * -0.5, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * -0.1, obj_y + height * -0.5, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.5, obj_y + height * -0.5, obj_z + depth * -0.5);
	glEnd();

	glBegin(GL_QUADS);											// Left 
	// Front
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * -0.4, obj_y + height * 0.47, obj_z + depth * -0.37);
	glVertex3f(obj_x + width * -0.07, obj_y + height * 0.6, obj_z + depth * -0.37);
	glVertex3f(obj_x + width * -0.07, obj_y + height * -0.5, obj_z + depth * -0.47);
	glVertex3f(obj_x + width * -0.5, obj_y + height * -0.47, obj_z + depth * -0.47);
	// Back
	glVertex3f(obj_x + width * -0.4, obj_y + height * 0.47, obj_z + depth * 0.37);
	glVertex3f(obj_x + width * -0.07, obj_y + height * 0.6, obj_z + depth * 0.37);
	glVertex3f(obj_x + width * -0.07, obj_y + height * -0.5, obj_z + depth * 0.47);
	glVertex3f(obj_x + width * -0.5, obj_y + height * -0.47, obj_z + depth * 0.47);
	// Left
	glVertex3f(obj_x + width * -0.4, obj_y + height * 0.47, obj_z + depth * 0.37);
	glVertex3f(obj_x + width * -0.4, obj_y + height * 0.47, obj_z + depth * -0.37);
	glVertex3f(obj_x + width * -0.5, obj_y + height * -0.47, obj_z + depth * -0.47);
	glVertex3f(obj_x + width * -0.5, obj_y + height * -0.47, obj_z + depth * 0.47);
	// Right
	glVertex3f(obj_x + width * -0.07, obj_y + height * 0.6, obj_z + depth * 0.37);
	glVertex3f(obj_x + width * -0.07, obj_y + height * 0.6, obj_z + depth * -0.37);
	glVertex3f(obj_x + width * -0.07, obj_y + height * -0.5, obj_z + depth * -0.47);
	glVertex3f(obj_x + width * -0.07, obj_y + height * -0.5, obj_z + depth * 0.47);
	// Top
	glVertex3f(obj_x + width * -0.4, obj_y + height * 0.47, obj_z + depth * 0.37);
	glVertex3f(obj_x + width * -0.07, obj_y + height * 0.6, obj_z + depth * 0.37);
	glVertex3f(obj_x + width * -0.07, obj_y + height * 0.6, obj_z + depth * -0.37);
	glVertex3f(obj_x + width * -0.4, obj_y + height * 0.47, obj_z + depth * -0.37);
	// Bottom
	glVertex3f(obj_x + width * -0.5, obj_y + height * -0.47, obj_z + depth * 0.47);
	glVertex3f(obj_x + width * -0.07, obj_y + height * -0.47, obj_z + depth * 0.47);
	glVertex3f(obj_x + width * -0.07, obj_y + height * -0.47, obj_z + depth * -0.47);
	glVertex3f(obj_x + width * -0.5, obj_y + height * -0.47, obj_z + depth * -0.47);
	glEnd();
	glPopMatrix();
}
void left_Arm()
{
	float obj_x = LArm_x;
	float obj_y = LArm_y;
	float obj_z = LArm_z;
	float width = Arm_width;
	float height = Arm_height;
	float depth = Arm_depth;

	if (isOn) {
		c_x = 1.00, c_y = 1.00, c_z = 1.00;
		c2_x = 1.00, c2_y = 1.00, c2_z = 1.00;
		c3_x = 0.40, c3_y = 0.40, c3_z = 1.00;
	}
	if (isTexture && changeColor == true) {
		c_x = 1.00, c_y = 1.00, c_z = 1.00;
		c2_x = 1.00, c2_y = 1.00, c2_z = 1.00;
		c3_x = 0.40, c3_y = 0.40, c3_z = 1.00;
	}
	if (isTexture && changeColor == false) {
		c_x = 1.00, c_y = 1.00, c_z = 1.00;
		c2_x = 1.00, c2_y = 1.00, c2_z = 1.00;
		c3_x = 1.00, c3_y = 0.00, c3_z = 0.20;
	}
	else if (!isTexture && changeColor == true) {
		c_x = 0.40, c_y = 0.40, c_z = 1.00;
		c2_x = 0.20, c2_y = 1.00, c2_z = 1.00;
		c3_x = 0.40, c3_y = 0.40, c3_z = 1.00;
	}
	else if (!isTexture && changeColor == false) {
		c_x = 1.00, c_y = 0.00, c_z = 0.20;
		c2_x = 1.00, c2_y = 1.00, c2_z = 0.72;
		c3_x = 1.00, c3_y = 0.00, c3_z = 0.20;
	}

	//--------------------------------
	//	OpenGL drawing
	//--------------------------------	
	glPushMatrix();												// Move to final result or transformation
	glBegin(GL_QUADS);											// Hand Part 1
	// Front
	glColor3f(c_x, c_y, c_z);
	glVertex3f(width * -0.35, height * 0, obj_z + depth * -0.35);
	glVertex3f(width * 0.35, obj_y + height * 0, obj_z + depth * -0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(width * 0.35, height * -0.7, obj_z + depth * -0.5);
	glVertex3f(width * -0.5, height * -0.7, obj_z + depth * -0.5);
	// Back
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * 0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * 0.35, height * -0.7, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * -0.5, height * -0.7, obj_z + depth * 0.5);
	// Left
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * -0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * -0.5, height * -0.7, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.5, height * -0.7, obj_z + depth * 0.5);
	// Right
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * -0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * 0.35, height * -0.7, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * 0.35, height * -0.7, obj_z + depth * 0.5);
	// Top
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * -0.4);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * -0.4);
	// Bottom
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * -0.5, height * -0.7, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.35, height * -0.7, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.35, height * -0.7, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.5, height * -0.7, obj_z + depth * -0.5);
	glEnd();

	glBegin(GL_QUADS);
	// Front
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * -0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * -0.35);
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * 0.35, height * -0.8, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.5, height * -0.8, obj_z + depth * -0.5);
	// Back
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * 0.35);
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * 0.35, height * -0.8, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * -0.5, height * -0.8, obj_z + depth * 0.5);
	// Left
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * -0.35);
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * -0.5, height * -0.8, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.5, height * -0.8, obj_z + depth * 0.5);
	// Right
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * -0.35);
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * 0.35, height * -0.8, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * 0.35, height * -0.8, obj_z + depth * 0.5);
	// Top
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * -0.4);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * -0.4);
	// Bottom
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * -0.5, height * -0.8, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.35, height * -0.8, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.35, height * -0.8, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.5, height * -0.8, obj_z + depth * -0.5);
	glEnd();

	glBegin(GL_QUADS);											// Hand Part 2
	// Front
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.35, height * -0.3, obj_z + depth * -0.35);
	glVertex3f(obj_x + width * 0.35, height * -0.3, obj_z + depth * -0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * 0.30, height * -1.1, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.30, height * -1.1, obj_z + depth * -0.5);
	// Back
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.35, height * -0.3, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * -0.3, obj_z + depth * 0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * 0.30, height * -1.1, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * -0.30, height * -1.1, obj_z + depth * 0.5);
	// Left
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.35, height * -0.3, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * -0.35, height * -0.3, obj_z + depth * -0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * -0.30, height * -1.1, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.30, height * -1.1, obj_z + depth * 0.5);
	// Right
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * 0.35, height * -0.3, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * -0.3, obj_z + depth * -0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * 0.30, height * -1.1, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * 0.30, height * -1.1, obj_z + depth * 0.5);
	// Top
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.35, height * -0.3, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * -0.3, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.30, height * -0.3, obj_z + depth * -0.4);
	glVertex3f(obj_x + width * -0.30, height * -0.3, obj_z + depth * -0.4);
	// Bottom
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * -0.30, height * -1.1, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.30, height * -1.1, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.30, height * -1.1, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.30, height * -1.1, obj_z + depth * -0.5);
	glEnd();

	glPushMatrix();
	glRotatef(Lpalm_angle, palm_x_rotate, palm_y_rotate, palm_z_rotate);
	if (weapon_choice == 2) {
		drawOuterCase(0.06, 0.04, 0.1, 4, 10, 90, obj_x, height * -1.1, obj_z);
		glBegin(GL_POLYGON);										// Palm part 1 left
		// Front
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.05, height * -1.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.05, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.05, height * -2.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.05, height * -2.1, obj_z + depth * -0.1);
		// Back
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.05, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.05, height * -1.1, obj_z + depth * 0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.05, height * -2.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.05, height * -2.1, obj_z + depth * 0.1);
		// Left
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.05, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.05, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * -0.05, height * -2.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.05, height * -2.1, obj_z + depth * 0.1);
		// Right
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * 0.05, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.05, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.05, height * -2.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.05, height * -2.1, obj_z + depth * 0.1);
		// Top
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.05, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.05, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.05, height * -1.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.05, height * -1.1, obj_z + depth * -0.1);
		// Bottom
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * -0.05, height * -2.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.05, height * -2.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.05, height * -2.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.05, height * -2.1, obj_z + depth * -0.1);
		glEnd();
	}
	else if (weapon_choice == 3) {
		glPushMatrix();
		glColor3f(1.0, 0, 0.25);
		drawOuterCase(0.08, 0.10, 0.1, 4, 10, 90, LArm_x, height * -1.1, obj_z);
		glPopMatrix();
		drawCylinder(0.08, 0.10, 0.15, 4, 10, 90, LArm_x, height * -1.1, obj_z);
		drawOuterCase(0.08, 0.06, 0.2, 4, 10, 90, LArm_x, height * -1.1, obj_z);
		drawPowerSphere(0.08, 4, 10, 0, LArm_x, height * -1.1, obj_z);
	}
	else {
		glBegin(GL_POLYGON);										// Palm part 1 left
		// Front
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.4, height * -1.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * -0.1, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.4, height * -1.4, obj_z + depth * -0.1);
		// Back
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.4, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.1, obj_z + depth * 0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * -0.1, height * -1.4, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.4, height * -1.4, obj_z + depth * 0.1);
		// Left
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.4, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.4, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * -0.4, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.4, height * -1.4, obj_z + depth * 0.1);
		// Right
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.1, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * -0.1, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.4, obj_z + depth * 0.1);
		// Top
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.4, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.4, height * -1.1, obj_z + depth * -0.1);
		// Bottom
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * -0.4, height * -1.4, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.4, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.4, height * -1.4, obj_z + depth * -0.1);
		glEnd();

		glBegin(GL_POLYGON);										// Palm part 2 Right
		// Front
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * 0.4, height * -1.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.1, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.4, height * -1.4, obj_z + depth * -0.1);
		// Back
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * 0.4, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.1, obj_z + depth * 0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.1, height * -1.4, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.4, height * -1.4, obj_z + depth * 0.1);
		// Left
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * 0.4, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.4, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.4, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.4, height * -1.4, obj_z + depth * 0.1);
		// Right
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * 0.1, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.1, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.4, obj_z + depth * 0.1);
		// Top
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * 0.4, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.4, height * -1.1, obj_z + depth * -0.1);
		// Bottom
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.4, height * -1.4, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.4, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.4, height * -1.4, obj_z + depth * -0.1);
		glEnd();

		drawPowerSphere(0.04, 4, 10, 0, LArm_x, height * -1.1, obj_z);
	}
	glPopMatrix();
	glPopMatrix();
}
void shoulderRight()
{
	float obj_x = 0;
	float obj_y = 0.3 * 1.1;
	float obj_z = 0.3;
	float width = Shoulder_width;
	float height = Shoulder_height;
	float depth = Shoulder_depth;

	glPushMatrix();												// Move to final result or transformation
	drawSphere(0.12, 4, 10, 90);
	drawLineSphere(0.125, 4, 5, 90);
	glPopMatrix();

	if (isOn) {
		c_x = 1.00, c_y = 1.00, c_z = 1.00;
		c2_x = 1.00, c2_y = 1.00, c2_z = 1.00;
		c3_x = 0.40, c3_y = 0.40, c3_z = 1.00;
	}
	if (isTexture && changeColor == true) {
		c_x = 1.00, c_y = 1.00, c_z = 1.00;
		c2_x = 1.00, c2_y = 1.00, c2_z = 1.00;
		c3_x = 0.40, c3_y = 0.40, c3_z = 1.00;
	}
	if (isTexture && changeColor == false) {
		c_x = 1.00, c_y = 1.00, c_z = 1.00;
		c2_x = 1.00, c2_y = 1.00, c2_z = 1.00;
		c3_x = 1.00, c3_y = 0.00, c3_z = 0.20;
	}
	else if (!isTexture && changeColor == true) {
		c_x = 0.40, c_y = 0.40, c_z = 1.00;
		c2_x = 0.20, c2_y = 1.00, c2_z = 1.00;
		c3_x = 0.40, c3_y = 0.40, c3_z = 1.00;
	}
	else if (!isTexture && changeColor == false) {
		c_x = 1.00, c_y = 0.00, c_z = 0.20;
		c2_x = 1.00, c2_y = 1.00, c2_z = 0.72;
		c3_x = 1.00, c3_y = 0.00, c3_z = 0.20;
	}

	glPushMatrix();
	glTranslatef(-0.32, -0.31, -0.3);
	glBegin(GL_QUADS);											// Right 
	// Front
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * 0.4, obj_y + height * 0.5, obj_z + depth * -0.4);
	glVertex3f(obj_x + width * 0.1, obj_y + height * 0.6, obj_z + depth * -0.4);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * 0.1, obj_y + height * -0.5, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * 0.5, obj_y + height * -0.5, obj_z + depth * -0.5);
	// Back
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * 0.4, obj_y + height * 0.5, obj_z + depth * 0.4);
	glVertex3f(obj_x + width * 0.1, obj_y + height * 0.6, obj_z + depth * 0.4);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * 0.1, obj_y + height * -0.5, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.5, obj_y + height * -0.5, obj_z + depth * 0.5);
	// Left
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * 0.4, obj_y + height * 0.5, obj_z + depth * 0.4);
	glVertex3f(obj_x + width * 0.4, obj_y + height * 0.5, obj_z + depth * -0.4);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * 0.5, obj_y + height * -0.5, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * 0.5, obj_y + height * -0.5, obj_z + depth * 0.5);
	// Right
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * 0.1, obj_y + height * 0.6, obj_z + depth * 0.4);
	glVertex3f(obj_x + width * 0.1, obj_y + height * 0.6, obj_z + depth * -0.4);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * 0.1, obj_y + height * -0.5, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * 0.1, obj_y + height * -0.5, obj_z + depth * 0.5);
	// Top
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * 0.4, obj_y + height * 0.5, obj_z + depth * 0.4);
	glVertex3f(obj_x + width * 0.1, obj_y + height * 0.6, obj_z + depth * 0.4);
	glVertex3f(obj_x + width * 0.1, obj_y + height * 0.6, obj_z + depth * -0.4);
	glVertex3f(obj_x + width * 0.4, obj_y + height * 0.5, obj_z + depth * -0.4);
	// Bottom
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * 0.5, obj_y + height * -0.5, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.1, obj_y + height * -0.5, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.1, obj_y + height * -0.5, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * 0.5, obj_y + height * -0.5, obj_z + depth * -0.5);
	glEnd();


	glBegin(GL_QUADS);											// Right 
	// Front
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * 0.4, obj_y + height * 0.47, obj_z + depth * -0.37);
	glVertex3f(obj_x + width * 0.07, obj_y + height * 0.6, obj_z + depth * -0.37);
	glVertex3f(obj_x + width * 0.07, obj_y + height * -0.47, obj_z + depth * -0.47);
	glVertex3f(obj_x + width * 0.5, obj_y + height * -0.47, obj_z + depth * -0.47);
	// Back
	glVertex3f(obj_x + width * 0.4, obj_y + height * 0.47, obj_z + depth * 0.37);
	glVertex3f(obj_x + width * 0.07, obj_y + height * 0.6, obj_z + depth * 0.37);
	glVertex3f(obj_x + width * 0.07, obj_y + height * -0.47, obj_z + depth * 0.47);
	glVertex3f(obj_x + width * 0.5, obj_y + height * -0.47, obj_z + depth * 0.47);
	// Left
	glVertex3f(obj_x + width * 0.4, obj_y + height * 0.47, obj_z + depth * 0.37);
	glVertex3f(obj_x + width * 0.4, obj_y + height * 0.47, obj_z + depth * -0.37);
	glVertex3f(obj_x + width * 0.5, obj_y + height * -0.47, obj_z + depth * -0.47);
	glVertex3f(obj_x + width * 0.5, obj_y + height * -0.47, obj_z + depth * 0.47);
	// Right
	glVertex3f(obj_x + width * 0.07, obj_y + height * 0.6, obj_z + depth * 0.37);
	glVertex3f(obj_x + width * 0.07, obj_y + height * 0.6, obj_z + depth * -0.37);
	glVertex3f(obj_x + width * 0.07, obj_y + height * -0.5, obj_z + depth * -0.47);
	glVertex3f(obj_x + width * 0.07, obj_y + height * -0.5, obj_z + depth * 0.47);
	// Top
	glVertex3f(obj_x + width * 0.4, obj_y + height * 0.47, obj_z + depth * 0.37);
	glVertex3f(obj_x + width * 0.07, obj_y + height * 0.6, obj_z + depth * 0.37);
	glVertex3f(obj_x + width * 0.07, obj_y + height * 0.6, obj_z + depth * -0.37);
	glVertex3f(obj_x + width * 0.4, obj_y + height * 0.47, obj_z + depth * -0.37);
	// Bottom
	glVertex3f(obj_x + width * 0.5, obj_y + height * -0.47, obj_z + depth * 0.47);
	glVertex3f(obj_x + width * 0.07, obj_y + height * -0.47, obj_z + depth * 0.47);
	glVertex3f(obj_x + width * 0.07, obj_y + height * -0.47, obj_z + depth * -0.47);
	glVertex3f(obj_x + width * 0.5, obj_y + height * -0.47, obj_z + depth * -0.47);
	glEnd();
	glPopMatrix();
}
void right_Arm()
{
	float obj_x = RArm_x;
	float obj_y = RArm_y;
	float obj_z = RArm_z;
	float width = Arm_width;
	float height = Arm_height;
	float depth = Arm_depth;

	//--------------------------------
	//	OpenGL drawing
	//--------------------------------	
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------										// Move to final result or transformation
	if (isOn) {
		c_x = 1.00, c_y = 1.00, c_z = 1.00;
		c2_x = 1.00, c2_y = 1.00, c2_z = 1.00;
		c3_x = 0.40, c3_y = 0.40, c3_z = 1.00;
	}
	if (isTexture && changeColor == true) {
		c_x = 1.00, c_y = 1.00, c_z = 1.00;
		c2_x = 1.00, c2_y = 1.00, c2_z = 1.00;
		c3_x = 0.40, c3_y = 0.40, c3_z = 1.00;
	}
	if (isTexture && changeColor == false) {
		c_x = 1.00, c_y = 1.00, c_z = 1.00;
		c2_x = 1.00, c2_y = 1.00, c2_z = 1.00;
		c3_x = 1.00, c3_y = 0.00, c3_z = 0.20;
	}
	else if (!isTexture && changeColor == true) {
		c_x = 0.40, c_y = 0.40, c_z = 1.00;
		c2_x = 0.20, c2_y = 1.00, c2_z = 1.00;
		c3_x = 0.40, c3_y = 0.40, c3_z = 1.00;
	}
	else if (!isTexture && changeColor == false) {
		c_x = 1.00, c_y = 0.00, c_z = 0.20;
		c2_x = 1.00, c2_y = 1.00, c2_z = 0.72;
		c3_x = 1.00, c3_y = 0.00, c3_z = 0.20;
	}

	glPushMatrix();
	glBegin(GL_QUADS);											// Hand Part 1
	// Front
	glColor3f(c_x, c_y, c_z);
	glVertex3f(width * -0.35, height * 0, obj_z + depth * -0.35);
	glVertex3f(width * 0.35, obj_y + height * 0, obj_z + depth * -0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(width * 0.5, height * -0.7, obj_z + depth * -0.5);
	glVertex3f(width * -0.35, height * -0.7, obj_z + depth * -0.5);
	// Back
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * 0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * 0.5, height * -0.7, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * -0.35, height * -0.7, obj_z + depth * 0.5);
	// Left
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * -0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * -0.35, height * -0.7, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.35, height * -0.7, obj_z + depth * 0.5);
	// Right
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * -0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * 0.5, height * -0.7, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * 0.5, height * -0.7, obj_z + depth * 0.5);
	// Top
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * -0.4);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * -0.4);
	// Bottom
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * -0.35, height * -0.7, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.5, height * -0.7, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.5, height * -0.7, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.35, height * -0.7, obj_z + depth * -0.5);
	glEnd();

	glBegin(GL_QUADS);
	// Front
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * -0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * -0.35);
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * -0.35, height * -0.8, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * 0.5, height * -0.8, obj_z + depth * -0.5);
	// Back
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * 0.35);
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * -0.35, height * -0.8, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.5, height * -0.8, obj_z + depth * 0.5);
	// Left
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * -0.35);
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * -0.35, height * -0.8, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.35, height * -0.8, obj_z + depth * 0.5);
	// Right
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * -0.35);
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * 0.5, height * -0.8, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * 0.5, height * -0.8, obj_z + depth * 0.5);
	// Top
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * 0, obj_z + depth * -0.4);
	glVertex3f(obj_x + width * -0.35, height * 0, obj_z + depth * -0.4);
	// Bottom
	glColor3f(c3_x, c3_y, c3_z);
	glVertex3f(obj_x + width * -0.35, height * -0.8, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.5, height * -0.8, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.5, height * -0.8, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.35, height * -0.8, obj_z + depth * -0.5);
	glEnd();

	glBegin(GL_QUADS);											// Hand Part 2
	// Front
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.35, height * -0.3, obj_z + depth * -0.35);
	glVertex3f(obj_x + width * 0.35, height * -0.3, obj_z + depth * -0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * 0.30, height * -1.1, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.30, height * -1.1, obj_z + depth * -0.5);
	// Back
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.35, height * -0.3, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * -0.3, obj_z + depth * 0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * 0.30, height * -1.1, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * -0.30, height * -1.1, obj_z + depth * 0.5);
	// Left
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.35, height * -0.3, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * -0.35, height * -0.3, obj_z + depth * -0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * -0.30, height * -1.1, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.30, height * -1.1, obj_z + depth * 0.5);
	// Right
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * 0.35, height * -0.3, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * -0.3, obj_z + depth * -0.35);
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * 0.30, height * -1.1, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * 0.30, height * -1.1, obj_z + depth * 0.5);
	// Top
	glColor3f(c_x, c_y, c_z);
	glVertex3f(obj_x + width * -0.35, height * -0.3, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.35, height * -0.3, obj_z + depth * 0.35);
	glVertex3f(obj_x + width * 0.30, height * -0.3, obj_z + depth * -0.4);
	glVertex3f(obj_x + width * -0.30, height * -0.3, obj_z + depth * -0.4);
	// Bottom
	glColor3f(c2_x, c2_y, c2_z);
	glVertex3f(obj_x + width * -0.30, height * -1.1, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.30, height * -1.1, obj_z + depth * 0.5);
	glVertex3f(obj_x + width * 0.30, height * -1.1, obj_z + depth * -0.5);
	glVertex3f(obj_x + width * -0.30, height * -1.1, obj_z + depth * -0.5);
	glEnd();

	glPushMatrix();
	glRotatef(Rpalm_angle, palm_x_rotate, palm_y_rotate, palm_z_rotate);
	if (weapon_choice == 2) {
		drawOuterCase(0.06, 0.04, 0.1, 4, 10, 90, obj_x, height * -1.1, obj_z);
		glBegin(GL_POLYGON);										// Palm part 1 left
		// Front
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.05, height * -1.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.05, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.05, height * -2.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.05, height * -2.1, obj_z + depth * -0.1);
		// Back
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.05, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.05, height * -1.1, obj_z + depth * 0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.05, height * -2.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.05, height * -2.1, obj_z + depth * 0.1);
		// Left
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.05, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.05, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * -0.05, height * -2.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.05, height * -2.1, obj_z + depth * 0.1);
		// Right
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * 0.05, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.05, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.05, height * -2.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.05, height * -2.1, obj_z + depth * 0.1);
		// Top
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.05, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.05, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.05, height * -1.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.05, height * -1.1, obj_z + depth * -0.1);
		// Bottom
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * -0.05, height * -2.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.05, height * -2.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.05, height * -2.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.05, height * -2.1, obj_z + depth * -0.1);
		glEnd();
	}
	else if (weapon_choice == 3) {
		drawOuterCase(0.08, 0.08, 0.1, 4, 10, 90, LArm_x, height * -1.1, obj_z);
		drawCylinder(0.06, 0.08, 0.15, 4, 10, 90, LArm_x, height * -1.1, obj_z);
		drawOuterCase(0.06, 0.04, 0.2, 4, 10, 90, LArm_x, height * -1.1, obj_z);
		drawPowerSphere(0.06, 4, 10, 0, LArm_x, height * -1.1, obj_z);
	}
	else {
		glBegin(GL_POLYGON);										// Palm part 1 left
		// Front
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.4, height * -1.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * -0.1, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.4, height * -1.4, obj_z + depth * -0.1);
		// Back
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.4, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.1, obj_z + depth * 0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * -0.1, height * -1.4, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.4, height * -1.4, obj_z + depth * 0.1);
		// Left
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.4, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.4, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * -0.4, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.4, height * -1.4, obj_z + depth * 0.1);
		// Right
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.1, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * -0.1, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.4, obj_z + depth * 0.1);
		// Top
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * -0.4, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.4, height * -1.1, obj_z + depth * -0.1);
		// Bottom
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * -0.4, height * -1.4, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.4, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * -0.1, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * -0.4, height * -1.4, obj_z + depth * -0.1);
		glEnd();

		glBegin(GL_POLYGON);										// Palm part 2 Right
		// Front
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * 0.4, height * -1.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.1, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.4, height * -1.4, obj_z + depth * -0.1);
		// Back
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * 0.4, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.1, obj_z + depth * 0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.1, height * -1.4, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.4, height * -1.4, obj_z + depth * 0.1);
		// Left
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * 0.4, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.4, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.4, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.4, height * -1.4, obj_z + depth * 0.1);
		// Right
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * 0.1, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.1, obj_z + depth * -0.1);
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.1, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.4, obj_z + depth * 0.1);
		// Top
		glColor3f(0.55, 0.65, 0.65);
		glVertex3f(obj_x + width * 0.4, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.1, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.1, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.4, height * -1.1, obj_z + depth * -0.1);
		// Bottom
		glColor3f(0.95, 0.95, 0.95);
		glVertex3f(obj_x + width * 0.4, height * -1.4, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.4, obj_z + depth * 0.1);
		glVertex3f(obj_x + width * 0.1, height * -1.4, obj_z + depth * -0.1);
		glVertex3f(obj_x + width * 0.4, height * -1.4, obj_z + depth * -0.1);
		glEnd();

		drawPowerSphere(0.04, 4, 10, 0, LArm_x, height * -1.1, obj_z);
	}
	glPopMatrix();
	glPopMatrix();
}
void handWeapon()
{
	float x_size = x_resize;
	float y_size = y_resize;
	float z_size = z_resize;
	float Lx_move = -1.5;
	float Ly_move = 1.6;
	float Lz_move = 0;
	float Rx_move = 1.5;
	float Ry_move = 1.6;
	float Rz_move = 0;

	if (Lhangle >= 100) {
		Lhangle -= hspeed;
	}
	if (Lhangle <= -160) {
		Lhangle += hspeed;
	}

	if (Rhangle >= 100) {
		Rhangle -= hspeed;
	}
	if (Rhangle <= -160) {
		Rhangle += hspeed;
	}

	if (Lshangle >= 10) {
		Lshangle -= hspeed;
	}
	if (Lshangle <= -10) {
		Lshangle += hspeed;
	}

	if (Rshangle >= 10) {
		Rshangle -= hspeed;
	}
	if (Rshangle <= -10) {
		Rshangle += hspeed;
	}

	glPushMatrix();
	glTranslatef(Lx_move, Ly_move, Lz_move);
	glScalef(x_size, y_size, z_size);
	shoulderLeft();
	glPushMatrix();
	glRotatef(Lhangle, Lx_spin, Ly_spin, Lz_spin);
	left_Arm();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(Rx_move, Ry_move, Rz_move);
	glScalef(x_size, y_size, z_size);
	shoulderRight();
	glPushMatrix();
	glRotatef(Rhangle, Rx_spin, Ry_spin, Rz_spin);
	right_Arm();
	glPopMatrix();
	glPopMatrix();
}
void drawLaser(float base_rad, float top_rad, float h, int sl, int st) {
	glPushMatrix();
	GLUquadricObj* Cylinder = NULL;
	Cylinder = gluNewQuadric();
	gluQuadricDrawStyle(Cylinder, GLU_FILL);
	gluCylinder(Cylinder, base_rad, top_rad, h, sl, st);
	gluDeleteQuadric(Cylinder);
	glPopMatrix();
}
void drawBladeSwing() {
	glPushMatrix();
	drawLaser(0.1, 0.1, 5, 5, 5);
	glPopMatrix();

	glPushMatrix();
	drawLaser(0.1, 0.1, 5, 5, 5);
	glPopMatrix();
}
void drawCannonBall(float rad, int sl, int st) {
	glPushMatrix();
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, rad, sl, st);
	gluDeleteQuadric(sphere);
	glPopMatrix();
}
void drawEffect(float rad, int sl, int st)
{
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.00);
	glPointSize(2);
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_POINT);
	gluSphere(sphere, rad, sl, st);
	gluDeleteQuadric(sphere);
	glPopMatrix();
}
void attackMove1() {			// Laser attack
	float Lx_move = -1.5;
	float Ly_move = 1.6;
	float Lz_move = 0;
	float Rx_move = 1.5;
	float Ry_move = 1.6;
	float Rz_move = 0;
	glPushMatrix();
	glColor3f(1, 0, 0);
	effect_z += attackSpeed1;
	glTranslatef(0, 0, effect_z);

	glPushMatrix();				// Left laser
	glTranslatef(Lx_move, Ly_move, Lz_move);
	drawLaser(0.1, 0.1, 5, 5, 5);
	glPopMatrix();

	glPushMatrix();				// Right laser
	glTranslatef(Rx_move, Ry_move, Rz_move);
	drawLaser(0.1, 0.1, 5, 5, 5);
	glPopMatrix();

	glPopMatrix();
}
void attackMove2() {			// Blade Swing
	float Lx_move = -1.5;
	float Ly_move = 1.6;
	float Lz_move = 0;
	float Rx_move = 1.5;
	float Ry_move = 1.6;
	float Rz_move = 0;
	glPushMatrix();				// wave 1
	glColor3f(1, 1, 0);
	effect_z += attackSpeed2;
	glTranslatef(0, 0, effect_z);

	glPushMatrix();				// Left blade wind
	glTranslatef(Lx_move, Ly_move * 1.5, Lz_move);
	glRotatef(90, 1, 1, 0);
	drawBladeSwing();
	glPopMatrix();

	glPushMatrix();				// Right blade wind
	glTranslatef(Rx_move, Ry_move * 1.5, Rz_move);
	glRotatef(-90, 1, 1, 0);
	drawBladeSwing();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();				// wave 2
	glColor3f(1, 1, 0);
	effect_z += attackSpeed2;
	glTranslatef(0, 0, effect_z * 0.5);

	glPushMatrix();				// Left blade wind
	glTranslatef(Lx_move, Ly_move * 1.5, Lz_move);
	glRotatef(90, 1, 1, 0);
	drawBladeSwing();
	glPopMatrix();

	glPushMatrix();				// Right blade wind
	glTranslatef(Rx_move, Ry_move * 1.5, Rz_move);
	glRotatef(-90, 1, 1, 0);
	drawBladeSwing();
	glPopMatrix();
	glPopMatrix();
}
void attackMove3() {			// Cannon ball
	float Lx_move = -1.5;
	float Ly_move = 1.6;
	float Lz_move = 3;
	float Rx_move = 1.5;
	float Ry_move = 1.6;
	float Rz_move = 3;
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	effect_z += attackSpeed3;
	glTranslatef(0, 0, effect_z);

	glPushMatrix();				// Left cannon
	glTranslatef(Lx_move, Ly_move, Lz_move);
	drawCannonBall(0.6, 30, 30);
	drawEffect(0.61, 30, 30);
	glPushMatrix();				// effect 1
	glColor3f(1, 1, 1);
	glTranslatef(0.3, 0.2, -2);
	drawLaser(0.05, 0.05, 2, 5, 5);
	glPopMatrix();
	glPushMatrix();				// effect 2
	glColor3f(1, 1, 1);
	glTranslatef(-0.3, -0.2, -2);
	drawLaser(0.05, 0.05, 2, 5, 5);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();				// Right cannon
	glTranslatef(Rx_move, Ry_move, Rz_move);
	drawCannonBall(0.2, 30, 30);
	drawEffect(0.21, 30, 30);
	glPushMatrix();				// effect 1
	glColor3f(1, 1, 1);
	glTranslatef(-0.1, -0.1, -2);
	drawLaser(0.05, 0.05, 2, 5, 5);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(Rx_move, Ry_move, Rz_move + 1);
	drawCannonBall(0.2, 30, 30);
	drawEffect(0.21, 30, 30);
	glPushMatrix();				// effect 2
	glColor3f(1, 1, 1);
	glTranslatef(0.1, 0.1, -2);
	drawLaser(0.05, 0.05, 2, 5, 5);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(Rx_move, Ry_move, Rz_move + 2);
	drawCannonBall(0.2, 30, 30);
	drawEffect(0.21, 30, 30);
	glPushMatrix();				// effect 3
	glColor3f(1, 1, 1);
	glTranslatef(-0.1, -0.1, -2);
	drawLaser(0.05, 0.05, 2, 5, 5);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}
void attackMove() {
	switch (weapon_choice) {
	case 1:				// normal laser
		attackMove1();
		break;
	case 2:				// blade swing
		attackMove2();
		break;
	case 3:				// cannon ball
		attackMove3();
		break;
	default:
		break;
	}
}


//----------------------------PET HEAD--------------------------------
void pandaheadfront() {
	if (isTexture) {
		glColor3f(0.96, 0.96, 0.96);  //white smoke	#F5F5F5	(245,245,245)
	}
	else {
		glColor3f(1.0, 0.98, 0.98);   //snow	#FFFAFA	(255,250,250)
	}

	//right front face
	//glColor3f(1.0, 1.0, 1.0);
	glBegin(triangle);//1
	glVertex3f(0, 0.28, -0.5);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0.1, 0.26, -0.47);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.1, 0.26, -0.47);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0.17, 0.22, -0.45);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.17, 0.22, -0.45);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0.23, 0.18, -0.43);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.23, 0.18, -0.43);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0.27, 0.14, -0.41);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.27, 0.14, -0.41);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0.31, 0.06, -0.39);
	glEnd();

	glBegin(triangle);//3,2
	glVertex3f(0.31, 0.06, -0.39);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0.32, 0, -0.39);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.32, 0, -0.39);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0.31, -0.06, -0.39);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.31, -0.06, -0.39);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0.28, -0.14, -0.41);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.28, -0.14, -0.41);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0.25, -0.17, -0.43);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.25, -0.17, -0.43);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0.17, -0.24, -0.45);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.17, -0.24, -0.45);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0, -0.25, -0.5);
	glEnd();

	//left front face
	glColor3f(1.0, 1.0, 1.0);
	glBegin(triangle);//1
	glVertex3f(0, 0.28, -0.5);
	glVertex3f(0, 0, -0.5);
	glVertex3f(-0.1, 0.26, -0.47);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.1, 0.26, -0.47);
	glVertex3f(0, 0, -0.5);
	glVertex3f(-0.17, 0.22, -0.45);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.17, 0.22, -0.45);
	glVertex3f(0, 0, -0.5);
	glVertex3f(-0.23, 0.18, -0.43);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.23, 0.18, -0.43);
	glVertex3f(0, 0, -0.5);
	glVertex3f(-0.27, 0.14, -0.41);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.27, 0.14, -0.41);
	glVertex3f(0, 0, -0.5);
	glVertex3f(-0.31, 0.06, -0.39);
	glEnd();

	glBegin(triangle);//3,2
	glVertex3f(-0.31, 0.06, -0.39);
	glVertex3f(0, 0, -0.5);
	glVertex3f(-0.32, 0, -0.39);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.32, 0, -0.39);
	glVertex3f(0, 0, -0.5);
	glVertex3f(-0.31, -0.06, -0.39);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.31, -0.06, -0.39);
	glVertex3f(0, 0, -0.5);
	glVertex3f(-0.28, -0.14, -0.41);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.28, -0.14, -0.41);
	glVertex3f(0, 0, -0.5);
	glVertex3f(-0.25, -0.17, -0.43);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.25, -0.17, -0.43);
	glVertex3f(0, 0, -0.5);
	glVertex3f(-0.17, -0.24, -0.45);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.17, -0.24, -0.45);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0, -0.25, -0.5);
	glEnd();
}
void pandaheadback() {
	//right back face
	if (isTexture) {
		glColor3f(0.96, 0.96, 0.96);  //white smoke	#F5F5F5	(245,245,245)
	}
	else {
		glColor3f(1.0, 0.98, 0.98);   //snow	#FFFAFA	(255,250,250)
	}
	//glColor3f(1.0, 1.0, 1.0);
	glBegin(triangle);//1
	glVertex3f(0, 0.28, -0.25);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0.1, 0.26, -0.27);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.1, 0.26, -0.27);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0.17, 0.22, -0.29);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.17, 0.22, -0.29);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0.23, 0.18, -0.31);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.23, 0.18, -0.31);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0.27, 0.14, -0.33);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.27, 0.14, -0.33);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0.31, 0.06, -0.35);
	glEnd();

	glBegin(triangle);//3,2
	glVertex3f(0.31, 0.06, -0.35);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0.32, 0, -0.35);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.32, 0, -0.35);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0.31, -0.06, -0.35);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.31, -0.06, -0.35);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0.28, -0.14, -0.33);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.28, -0.14, -0.33);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0.25, -0.17, -0.31);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.25, -0.17, -0.31);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0.17, -0.24, -0.29);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.17, -0.24, -0.29);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0, -0.25, -0.25);
	glEnd();

	//left front face
	glColor3f(1.0, 1.0, 1.0);
	glBegin(triangle);//1
	glVertex3f(0, 0.28, -0.25);
	glVertex3f(0, 0, -0.25);
	glVertex3f(-0.1, 0.26, -0.27);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.1, 0.26, -0.27);
	glVertex3f(0, 0, -0.25);
	glVertex3f(-0.17, 0.22, -0.29);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.17, 0.22, -0.29);
	glVertex3f(0, 0, -0.25);
	glVertex3f(-0.23, 0.18, -0.31);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.23, 0.18, -0.31);
	glVertex3f(0, 0, -0.25);
	glVertex3f(-0.27, 0.14, -0.33);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.27, 0.14, -0.33);
	glVertex3f(0, 0, -0.25);
	glVertex3f(-0.31, 0.06, -0.35);
	glEnd();

	glBegin(triangle);//3,2
	glVertex3f(-0.31, 0.06, -0.35);
	glVertex3f(0, 0, -0.25);
	glVertex3f(-0.32, 0, -0.35);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.32, 0, -0.35);
	glVertex3f(0, 0, -0.25);
	glVertex3f(-0.31, -0.06, -0.35);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.31, -0.06, -0.35);
	glVertex3f(0, 0, -0.25);
	glVertex3f(-0.28, -0.14, -0.33);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.28, -0.14, -0.33);
	glVertex3f(0, 0, -0.25);
	glVertex3f(-0.25, -0.17, -0.31);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.25, -0.17, -0.31);
	glVertex3f(0, 0, -0.25);
	glVertex3f(-0.17, -0.24, -0.29);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.17, -0.24, -0.29);
	glVertex3f(0, 0, -0.25);
	glVertex3f(0, -0.25, -0.25);
	glEnd();
}
void pandaheadtop() {
	//right
	glColor3f(0.831, 0.831, 0.831);
	glBegin(quad);
	glVertex3f(0, 0.28, -0.25);
	glVertex3f(0, 0.28, -0.5);
	glVertex3f(0.1, 0.26, -0.47);
	glVertex3f(0.1, 0.26, -0.27);
	glEnd();

	glBegin(quad);
	glVertex3f(0.1, 0.26, -0.27);
	glVertex3f(0.1, 0.26, -0.47);
	glVertex3f(0.17, 0.22, -0.45);
	glVertex3f(0.17, 0.22, -0.29);
	glEnd();

	glBegin(quad);
	glVertex3f(0.17, 0.22, -0.29);
	glVertex3f(0.17, 0.22, -0.45);
	glVertex3f(0.23, 0.18, -0.43);
	glVertex3f(0.23, 0.18, -0.31);
	glEnd();

	glBegin(quad);
	glVertex3f(0.23, 0.18, -0.31);
	glVertex3f(0.23, 0.18, -0.43);
	glVertex3f(0.27, 0.14, -0.41);
	glVertex3f(0.27, 0.14, -0.33);
	glEnd();

	glBegin(quad);
	glVertex3f(0.27, 0.14, -0.33);
	glVertex3f(0.27, 0.14, -0.41);
	glVertex3f(0.31, 0.06, -0.39);
	glVertex3f(0.31, 0.06, -0.35);
	glEnd();

	glBegin(quad);
	glVertex3f(0.31, 0.06, -0.35);
	glVertex3f(0.31, 0.06, -0.39);
	glVertex3f(0.32, 0, -0.39);
	glVertex3f(0.32, 0, -0.35);
	glEnd();

	glBegin(quad);
	glVertex3f(0.32, 0, -0.35);
	glVertex3f(0.32, 0, -0.39);
	glVertex3f(0.31, -0.06, -0.39);
	glVertex3f(0.31, -0.06, -0.35);
	glEnd();

	glBegin(quad);
	glVertex3f(0.31, -0.06, -0.35);
	glVertex3f(0.31, -0.06, -0.39);
	glVertex3f(0.28, -0.14, -0.41);
	glVertex3f(0.28, -0.14, -0.33);
	glEnd();

	glBegin(quad);
	glVertex3f(0.28, -0.14, -0.33);
	glVertex3f(0.28, -0.14, -0.41);
	glVertex3f(0.25, -0.17, -0.43);
	glVertex3f(0.25, -0.17, -0.31);
	glEnd();

	glBegin(quad);
	glVertex3f(0.25, -0.17, -0.31);
	glVertex3f(0.25, -0.17, -0.43);
	glVertex3f(0.17, -0.24, -0.45);
	glVertex3f(0.17, -0.24, -0.29);
	glEnd();

	glBegin(quad);
	glVertex3f(0.17, -0.24, -0.29);
	glVertex3f(0.17, -0.24, -0.45);
	glVertex3f(0, -0.25, -0.5);
	glVertex3f(0, -0.25, -0.25);
	glEnd();

	//left
	glColor3f(0.831, 0.831, 0.831);
	glBegin(quad);
	glVertex3f(0, 0.28, -0.25);
	glVertex3f(0, 0.28, -0.5);
	glVertex3f(-0.1, 0.26, -0.47);
	glVertex3f(-0.1, 0.26, -0.27);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.1, 0.26, -0.27);
	glVertex3f(-0.1, 0.26, -0.47);
	glVertex3f(-0.17, 0.22, -0.45);
	glVertex3f(-0.17, 0.22, -0.29);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.17, 0.22, -0.29);
	glVertex3f(-0.17, 0.22, -0.45);
	glVertex3f(-0.23, 0.18, -0.43);
	glVertex3f(-0.23, 0.18, -0.31);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.23, 0.18, -0.31);
	glVertex3f(-0.23, 0.18, -0.43);
	glVertex3f(-0.27, 0.14, -0.41);
	glVertex3f(-0.27, 0.14, -0.33);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.27, 0.14, -0.33);
	glVertex3f(-0.27, 0.14, -0.41);
	glVertex3f(-0.31, 0.06, -0.39);
	glVertex3f(-0.31, 0.06, -0.35);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.31, 0.06, -0.35);
	glVertex3f(-0.31, 0.06, -0.39);
	glVertex3f(-0.32, 0, -0.39);
	glVertex3f(-0.32, 0, -0.35);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.32, 0, -0.35);
	glVertex3f(-0.32, 0, -0.39);
	glVertex3f(-0.31, -0.06, -0.39);
	glVertex3f(-0.31, -0.06, -0.35);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.31, -0.06, -0.35);
	glVertex3f(-0.31, -0.06, -0.39);
	glVertex3f(-0.28, -0.14, -0.41);
	glVertex3f(-0.28, -0.14, -0.33);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.28, -0.14, -0.33);
	glVertex3f(-0.28, -0.14, -0.41);
	glVertex3f(-0.25, -0.17, -0.43);
	glVertex3f(-0.25, -0.17, -0.31);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.25, -0.17, -0.31);
	glVertex3f(-0.25, -0.17, -0.43);
	glVertex3f(-0.17, -0.24, -0.45);
	glVertex3f(-0.17, -0.24, -0.29);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.17, -0.24, -0.29);
	glVertex3f(-0.17, -0.24, -0.45);
	glVertex3f(0, -0.25, -0.5);
	glVertex3f(0, -0.25, -0.25);
	glEnd();
}
void pandaear() {
	//right
	//front
	glColor3f(0.67, 0.67, 0.67);
	glBegin(triangle);
	glVertex3f(0.17, 0.22, -0.4);
	glVertex3f(0.23, 0.18, -0.4);
	glVertex3f(0.21, 0.25, -0.4);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.21, 0.25, -0.4);
	glVertex3f(0.23, 0.18, -0.4);
	glVertex3f(0.24, 0.24, -0.39);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.24, 0.24, -0.39);
	glVertex3f(0.23, 0.18, -0.4);
	glVertex3f(0.26, 0.21, -0.38);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.26, 0.21, -0.38);
	glVertex3f(0.23, 0.18, -0.4);
	glVertex3f(0.27, 0.14, -0.37);
	glEnd();

	//back
	glColor3f(0.67, 0.67, 0.67);
	glBegin(triangle);
	glVertex3f(0.17, 0.22, -0.32);
	glVertex3f(0.23, 0.18, -0.32);
	glVertex3f(0.21, 0.25, -0.32);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.21, 0.25, -0.32);
	glVertex3f(0.23, 0.18, -0.32);
	glVertex3f(0.24, 0.24, -0.33);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.24, 0.24, -0.33);
	glVertex3f(0.23, 0.18, -0.32);
	glVertex3f(0.26, 0.21, -0.33);
	glEnd();

	glBegin(triangle);
	glVertex3f(0.26, 0.21, -0.33);
	glVertex3f(0.23, 0.18, -0.32);
	glVertex3f(0.27, 0.14, -0.34);
	glEnd();


	//top
	glBegin(quad);
	glVertex3f(0.17, 0.22, -0.4);
	glVertex3f(0.17, 0.22, -0.32);
	glVertex3f(0.21, 0.25, -0.32);
	glVertex3f(0.21, 0.25, -0.4);
	glEnd();

	glBegin(quad);
	glVertex3f(0.21, 0.25, -0.4);
	glVertex3f(0.21, 0.25, -0.32);
	glVertex3f(0.24, 0.24, -0.33);
	glVertex3f(0.24, 0.24, -0.39);
	glEnd();

	glBegin(quad);
	glVertex3f(0.24, 0.24, -0.39);
	glVertex3f(0.24, 0.24, -0.33);
	glVertex3f(0.26, 0.21, -0.33);
	glVertex3f(0.26, 0.21, -0.38);
	glEnd();

	glBegin(quad);
	glVertex3f(0.26, 0.21, -0.38);
	glVertex3f(0.26, 0.21, -0.33);
	glVertex3f(0.27, 0.14, -0.34);
	glVertex3f(0.27, 0.14, -0.37);
	glEnd();

	//left
	//front
	glColor3f(0.67, 0.67, 0.67);
	glBegin(triangle);
	glVertex3f(-0.17, 0.22, -0.4);
	glVertex3f(-0.23, 0.18, -0.4);
	glVertex3f(-0.21, 0.25, -0.4);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.21, 0.25, -0.4);
	glVertex3f(-0.23, 0.18, -0.4);
	glVertex3f(-0.24, 0.24, -0.39);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.24, 0.24, -0.39);
	glVertex3f(-0.23, 0.18, -0.4);
	glVertex3f(-0.26, 0.21, -0.38);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.26, 0.21, -0.38);
	glVertex3f(-0.23, 0.18, -0.4);
	glVertex3f(-0.27, 0.14, -0.37);
	glEnd();

	//back
	glColor3f(0.67, 0.67, 0.67);
	glBegin(triangle);
	glVertex3f(-0.17, 0.22, -0.32);
	glVertex3f(-0.23, 0.18, -0.32);
	glVertex3f(-0.21, 0.25, -0.32);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.21, 0.25, -0.32);
	glVertex3f(-0.23, 0.18, -0.32);
	glVertex3f(-0.24, 0.24, -0.33);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.24, 0.24, -0.33);
	glVertex3f(-0.23, 0.18, -0.32);
	glVertex3f(-0.26, 0.21, -0.33);
	glEnd();

	glBegin(triangle);
	glVertex3f(-0.26, 0.21, -0.33);
	glVertex3f(-0.23, 0.18, -0.32);
	glVertex3f(-0.27, 0.14, -0.34);
	glEnd();


	//top
	glBegin(quad);
	glVertex3f(-0.17, 0.22, -0.4);
	glVertex3f(-0.17, 0.22, -0.32);
	glVertex3f(-0.21, 0.25, -0.32);
	glVertex3f(-0.21, 0.25, -0.4);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.21, 0.25, -0.4);
	glVertex3f(-0.21, 0.25, -0.32);
	glVertex3f(-0.24, 0.24, -0.33);
	glVertex3f(-0.24, 0.24, -0.39);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.24, 0.24, -0.39);
	glVertex3f(-0.24, 0.24, -0.33);
	glVertex3f(-0.26, 0.21, -0.33);
	glVertex3f(-0.26, 0.21, -0.38);
	glEnd();

	glBegin(quad);
	glVertex3f(-0.26, 0.21, -0.38);
	glVertex3f(-0.26, 0.21, -0.33);
	glVertex3f(-0.27, 0.14, -0.34);
	glVertex3f(-0.27, 0.14, -0.37);
	glEnd();
}
void pandaeye() {
	//right
	glColor3f(0, 0, 0);
	glBegin(type);
	glVertex3f(0.19, 0.132, -0.44);
	glVertex3f(0.17, 0.132, -0.44);
	glVertex3f(0.07, 0.05, -0.475);
	glVertex3f(0.07, 0.04, -0.475);
	glVertex3f(0.19, -0.11, -0.44);
	glVertex3f(0.26, 0, -0.42);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(type);
	glVertex3f(0.166, 0.05, -0.45);
	glVertex3f(0.168, 0, -0.45);
	glVertex3f(0.178, -0.02, -0.445);
	glVertex3f(0.182, -0.02, -0.445);
	glVertex3f(0.192, 0, -0.445);
	glVertex3f(0.194, 0.05, -0.445);
	glVertex3f(0.192, 0.06, -0.445);
	glVertex3f(0.182, 0.08, -0.445);
	glVertex3f(0.178, 0.08, -0.445);
	glVertex3f(0.176, 0.06, -0.445);
	glEnd();

	//left
	glColor3f(0, 0, 0);
	glBegin(type);
	glVertex3f(-0.19, 0.132, -0.44);
	glVertex3f(-0.17, 0.132, -0.44);
	glVertex3f(-0.07, 0.05, -0.475);
	glVertex3f(-0.07, 0.04, -0.475);
	glVertex3f(-0.19, -0.11, -0.44);
	glVertex3f(-0.26, 0, -0.42);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(type);
	glVertex3f(-0.166, 0.05, -0.45);
	glVertex3f(-0.168, 0, -0.45);
	glVertex3f(-0.178, -0.02, -0.445);
	glVertex3f(-0.182, -0.02, -0.445);
	glVertex3f(-0.192, 0, -0.445);
	glVertex3f(-0.194, 0.05, -0.445);
	glVertex3f(-0.192, 0.06, -0.445);
	glVertex3f(-0.182, 0.08, -0.445);
	glVertex3f(-0.178, 0.08, -0.445);
	glVertex3f(-0.176, 0.06, -0.445);
	glEnd();
}
void pandanose() {
	glColor3f(0, 0, 0);
	glBegin(type);
	glVertex3f(0, -0.035, -0.5);
	glVertex3f(-0.01, -0.04, -0.5);
	glVertex3f(-0.03, -0.045, -0.5);
	glVertex3f(-0.03, -0.055, -0.5);
	glVertex3f(-0.01, -0.06, -0.5);
	glVertex3f(0, -0.065, -0.5);
	glVertex3f(0.01, -0.06, -0.5);
	glVertex3f(0.03, -0.055, -0.5);
	glVertex3f(0.03, -0.045, -0.5);
	glVertex3f(0.01, -0.04, -0.5);
	glEnd();
}
void pandahead() {
	pandaeye();
	pandanose();
	pandaheadfront();
	pandaheadback();
	pandaheadtop();
	pandaear();

}

//---------------------------------pet body-----------------------------
void drawSphere(float rad, int sl, int st) {

	//glPointSize(5.0);   //draw the point size
	GLUquadricObj* sphere = NULL;  //create quadric obj pointer
	sphere = gluNewQuadric(); //create quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL); //set the draw style GLU_LINE,GLU_FILL,GLU_POINT GLU_SILHOUETTE

	if (isTexture) {
		glColor3f(1.0, 1.0, 1.0);  //white
	}
	else {
		glColor3f(1.0, 0.98, 0.98);   //snow	#FFFAFA	(255,250,250)
	}
	//add texture
	//gluQuadricTexture(GLUquadric* quad, GLboolean texture);
	gluQuadricTexture(sphere, true);



	gluSphere(sphere, rad, sl, st); //draw sphere 0.5,30,30 (rad,slice,stacks)
	gluDeleteQuadric(sphere);  //free up the memory to avoid crash
}
void drawSphere1(float rad, int sl, int st) {

	//glPointSize(5.0);   //draw the point size
	GLUquadricObj* sphere = NULL;  //create quadric obj pointer
	sphere = gluNewQuadric(); //create quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL); //set the draw style GLU_LINE,GLU_FILL,GLU_POINT GLU_SILHOUETTE

	if (isTexture) {
		glColor3f(1.0, 1.0, 1.0);  //white
	}
	else {
		glColor3f(0.0, 0.0, 0.0);  //black
	}
	//add texture
	//gluQuadricTexture(GLUquadric* quad, GLboolean texture);
	gluQuadricTexture(sphere, true);



	gluSphere(sphere, rad, sl, st); //draw sphere 0.5,30,30 (rad,slice,stacks)
	gluDeleteQuadric(sphere);  //free up the memory to avoid crash
}
void drawSphere2(float rad, int sl, int st) {

	//glPointSize(5.0);   //draw the point size
	GLUquadricObj* sphere = NULL;  //create quadric obj pointer
	sphere = gluNewQuadric(); //create quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL); //set the draw style GLU_LINE,GLU_FILL,GLU_POINT GLU_SILHOUETTE

	if (isTexture) {
		glColor3f(1.0, 1.0, 1.0);  //white
	}
	else {
		glColor3f(0.86, 0.07, 0.23);  //crimson	#DC143C	(220,20,60)
	}
	//add texture
	//gluQuadricTexture(GLUquadric* quad, GLboolean texture);
	gluQuadricTexture(sphere, true);



	gluSphere(sphere, rad, sl, st); //draw sphere 0.5,30,30 (rad,slice,stacks)
	gluDeleteQuadric(sphere);  //free up the memory to avoid crash
}
void drawSphere3(float rad, int sl, int st) {

	//glPointSize(5.0);   //draw the point size
	GLUquadricObj* sphere = NULL;  //create quadric obj pointer
	sphere = gluNewQuadric(); //create quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL); //set the draw style GLU_LINE,GLU_FILL,GLU_POINT GLU_SILHOUETTE

	if (isTexture) {
		glColor3f(1.0, 1.0, 1.0);  //white
	}
	else if (iceAttack) {
		glColor3f(0.0, 1.0, 1.0);  //aqua	#00FFFF	(0,255,255)
	}
	else {
		glColor3f(1.0, 0.64, 0.0);  //orange	#FFA500	(255,165,0)
	}
	//add texture
	//gluQuadricTexture(GLUquadric* quad, GLboolean texture);
	gluQuadricTexture(sphere, true);



	gluSphere(sphere, rad, sl, st); //draw sphere 0.5,30,30 (rad,slice,stacks)
	gluDeleteQuadric(sphere);  //free up the memory to avoid crash
}
void drawSphere4(float rad, int sl, int st) {

	//glPointSize(5.0);   //draw the point size
	GLUquadricObj* sphere = NULL;  //create quadric obj pointer
	sphere = gluNewQuadric(); //create quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL); //set the draw style GLU_LINE,GLU_FILL,GLU_POINT GLU_SILHOUETTE
	/*
	if (isTexture) {
		glColor3f(1.0, 1.0, 1.0);  //white
	}
	else {
		glColor3f(1.0, 0.64, 0.0);  //orange	#FFA500	(255,165,0)
	} */
	//add texture
	//gluQuadricTexture(GLUquadric* quad, GLboolean texture);
	gluQuadricTexture(sphere, true);



	gluSphere(sphere, rad, sl, st); //draw sphere 0.5,30,30 (rad,slice,stacks)
	gluDeleteQuadric(sphere);  //free up the memory to avoid crash
}
void drawCube(float sz) {
	glBegin(GL_QUADS);
	// Face 1 // bottom face
	if (isTexture) {
		glColor3f(1.0, 1.0, 1.0);  //white
	}
	else {
		glColor3f(1.0, 0.98, 0.98);   //snow	#FFFAFA	(255,250,250)
	}


	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, sz);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, 0.0f, sz);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// Face 2 … /Left
	//glColor3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, 0.0f);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sz, sz);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, sz);

	// Face 3 / Front face
	//glColor3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, sz);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sz, sz);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, sz, sz);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, 0.0f, sz);

	// Face 4 / Right face
	//glColor3f(0.0, 1.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, 0.0f, sz);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, sz, sz);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(sz, sz, 0.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, 0.0f, 0.0f);

	// Face 5 / Back face
	//glColor3f(1.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, 0.0f, 0.0f);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sz, 0.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz, sz, 0.0f);

	// Face 6 / Top face
	//glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sz, sz, 0.0f);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(sz, sz, sz);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sz, sz);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0f, sz, 0.0f);

	glEnd();
}
void drawCylinder(float br, float tr, float h, float csl, float cst) {
	//glPointSize(5.0);   //draw the point size
	GLUquadricObj* cylinder = NULL;  //create quadric obj pointer
	cylinder = gluNewQuadric(); //create quadric obj
	gluQuadricDrawStyle(cylinder, GLU_FILL); //set the draw style GLU_LINE,GLU_FILL,GLU_POINT GLU_SILHOUETTE

	if (isTexture) {
		glColor3f(1.0, 1.0, 1.0);  //white
	}
	else {
		glColor3f(1.0, 0.98, 0.98);   //snow	#FFFAFA	(255,250,250)
	}
	//add texture
	//gluQuadricTexture(GLUquadric* quad, GLboolean texture);
	gluQuadricTexture(cylinder, true);



	gluCylinder(cylinder, br, tr, h, csl, cst); //(GLUquadric obj *, baseRadius,topRadius, height, slices, stacks) gluCylinder(cylinder,0.4,0.0,0.5,10,10);
	gluDeleteQuadric(cylinder);  //free up the memory to avoid crash
}
void drawCylinder1(float br, float tr, float h, float csl, float cst) {
	//glPointSize(5.0);   //draw the point size
	GLUquadricObj* cylinder = NULL;  //create quadric obj pointer
	cylinder = gluNewQuadric(); //create quadric obj
	gluQuadricDrawStyle(cylinder, GLU_FILL); //set the draw style GLU_LINE,GLU_FILL,GLU_POINT GLU_SILHOUETTE

	if (isTexture) {
		glColor3f(1.0, 1.0, 1.0);  //white
	}
	else {
		glColor3f(0.0, 0.0, 0.0);  //black
	}
	//add texture
	//gluQuadricTexture(GLUquadric* quad, GLboolean texture);
	gluQuadricTexture(cylinder, true);



	gluCylinder(cylinder, br, tr, h, csl, cst); //(GLUquadric obj *, baseRadius,topRadius, height, slices, stacks) gluCylinder(cylinder,0.4,0.0,0.5,10,10);
	gluDeleteQuadric(cylinder);  //free up the memory to avoid crash
}
void drawCylinder2(float br, float tr, float h, float csl, float cst) {
	//glPointSize(5.0);   //draw the point size
	GLUquadricObj* cylinder = NULL;  //create quadric obj pointer
	cylinder = gluNewQuadric(); //create quadric obj
	gluQuadricDrawStyle(cylinder, GLU_FILL); //set the draw style GLU_LINE,GLU_FILL,GLU_POINT GLU_SILHOUETTE

	if (isTexture) {
		glColor3f(1.0, 1.0, 1.0);  //white
	}
	else {
		glColor3f(0.66, 0.66, 0.66);  //dark grey	#A9A9A9	(169,169,169)
	}
	//add texture
	//gluQuadricTexture(GLUquadric* quad, GLboolean texture);
	gluQuadricTexture(cylinder, true);



	gluCylinder(cylinder, br, tr, h, csl, cst); //(GLUquadric obj *, baseRadius,topRadius, height, slices, stacks) gluCylinder(cylinder,0.4,0.0,0.5,10,10);
	gluDeleteQuadric(cylinder);  //free up the memory to avoid crash
}
void circleWeapon() {

	glBegin(GL_TRIANGLE_FAN);  //change to GL_LINE_LOOP


	glColor3f(0.66, 0.66, 0.66);  //dark grey	#A9A9A9	(169,169,169)

	glVertex2f(xc, yc);  //draw the center of your circle

	for (anglec = 0; anglec < 2 * PI; anglec += 2 * PI / noOfSegmentc)
	{
		x2c = xc + radiusc * cos(anglec);
		y2c = yc + radiusc * sin(anglec);

		glVertex2f(x2c, y2c);
	}

	glEnd();
}
void circleWeapon1() {

	glBegin(GL_TRIANGLE_FAN);  //change to GL_LINE_LOOP
	glColor3f(0.0, 0.0, 0.0); //black
	glVertex2f(xc1, yc1);  //draw the center of your circle

	for (anglec1 = 0; anglec1 < 2 * PI; anglec1 += 2 * PI / noOfSegmentc1)
	{
		x2c1 = xc1 + radiusc1 * cos(anglec1);
		y2c1 = yc1 + radiusc1 * sin(anglec1);

		glVertex2f(x2c1, y2c1);
	}

	glEnd();
}
void pyramid(float szp) {
	glBegin(GL_POLYGON);

	if (isTexture) {
		glColor3f(1.0, 1.0, 1.0);  //white
	}
	else {
		glColor3f(0.86, 0.07, 0.23);  //crimson	#DC143C	(220,20,60)
	}



	// Face 1 // bottom face
	//glColor3f(1.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-szp, 0.0f, -szp); //a
	glTexCoord2f(1.0, 1.0);
	glVertex3f(szp, 0.0f, -szp); //b
	glTexCoord2f(1.0, 0.0);
	glVertex3f(szp, 0.0f, szp); //c
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-szp, 0.0f, szp); //d
	glEnd();


	//glBegin(GL_LINE_LOOP);
	// Face a // tri
	glBegin(GL_POLYGON);
	//glColor3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0, szp * 2, 0); //top point//glVertex3f(szp, 1.0f, szp);  //top point
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-szp, 0.0f, -szp); //a
	glTexCoord2f(0.0, 0.0);
	glVertex3f(szp, 0.0f, -szp); //b
	glEnd();

	//glBegin(GL_LINE_LOOP);
	// Face b // tri
	glBegin(GL_POLYGON);
	//glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0, szp * 2, 0); //top point
	glTexCoord2f(1.0, 0.0);
	glVertex3f(szp, 0.0f, -szp); //b
	glTexCoord2f(0.0, 0.0);
	glVertex3f(szp, 0.0f, szp); //c
	glEnd();

	//glBegin(GL_LINE_LOOP);
	// Face c // tri
	glBegin(GL_POLYGON);
	//glColor3f(1.0, 0.0, 1.0);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0, szp * 2, 0); //top point
	glTexCoord2f(1.0, 0.0);
	glVertex3f(szp, 0.0f, szp); //c
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-szp, 0.0f, szp); //d
	glEnd();

	//glBegin(GL_LINE_LOOP);
	// Face d // tri
	glBegin(GL_POLYGON);
	//glColor3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0, szp * 2, 0); //top point
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-szp, 0.0f, szp); //d
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-szp, 0.0f, -szp); //a
	glEnd();
}

void petBodyA() {
	glPushMatrix(); //scale shape
	glScalef(1.2, 0.8, 1.2);
	//A1
	drawSphere(0.2, 30, 30);

	//A2
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	drawCylinder(0.2, 0.2, 0.35, 50, 50);
	glPopMatrix();

	//A3
	glPushMatrix();
	glTranslatef(0.0, -0.35, 0.0);
	drawSphere(0.2, 30, 30);
	glPopMatrix();

	glPopMatrix(); //end scale shape
}
void petHand() {


	if (phAngle >= 90) {
		phAngle -= phSpeed;
	}
	else if (phAngle <= -90) {
		phAngle += phSpeed;
	}

	//able to move
	glPushMatrix();
	glTranslatef(phx, phy, 0.0);                 // 3. Translate back to original 
	glRotatef(phAngle, 1.0, 0.0, 0.0);   // 2. Rotate the object around angle 
	glTranslatef(-phm, -phn, 0.0);            // 1. Move to origin 



	//B1
	glPushMatrix();
	glTranslatef(0.29, -0.02, 0.0);
	drawSphere1(0.05, 50, 50);
	glPopMatrix();

	//B2
	glPushMatrix();
	glTranslatef(0.29, -0.02, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	drawCylinder1(0.05, 0.05, 0.35, 50, 50);
	glPopMatrix();


	//B3
	glPushMatrix();
	glTranslatef(0.29, -0.37, 0.0);
	drawSphere1(0.05, 50, 50);
	glPopMatrix();


	//stop move
	glPopMatrix();
}
void petHandModel() {

	//B1
	glPushMatrix();
	glTranslatef(0.29, -0.02, 0.0);
	drawSphere1(0.05, 50, 50);
	glPopMatrix();

	//B2
	glPushMatrix();
	glTranslatef(0.29, -0.02, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	drawCylinder1(0.05, 0.05, 0.35, 50, 50);
	glPopMatrix();


	//B3
	glPushMatrix();
	glTranslatef(0.29, -0.37, 0.0);
	drawSphere1(0.05, 50, 50);
	glPopMatrix();



}
void petHand2() {


	//step3
	if (phAngle2 >= 90) {
		phAngle2 -= phSpeed;
	}
	else if (phAngle2 <= -90) {
		phAngle2 += phSpeed;
	}

	//able to move
	glPushMatrix();
	glTranslatef(phx2, phy2, 0.0);                 // 3. Translate back to original 
	glRotatef(phAngle2, 1.0, 0.0, 0.0);   // 2. Rotate the object around angle 
	glTranslatef(-phm2, -phn2, 0.0);            // 1. Move to origin 


	glPushMatrix();
	glTranslatef(-0.58, 0.0, 0.0);
	petHandModel(); //right hand
	glPopMatrix();

	glPopMatrix();
}
void petHandModel1() {

	//B1
	glPushMatrix();
	glTranslatef(0.29, -0.02, 0.0);
	drawSphere1(0.05, 50, 50);
	glPopMatrix();

	//B2
	glPushMatrix();
	glTranslatef(0.29, -0.02, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	drawCylinder1(0.05, 0.05, 0.35, 50, 50);
	glPopMatrix();


	//B3
	glPushMatrix();
	glTranslatef(0.29, -0.37, 0.0);
	drawSphere1(0.05, 50, 50);
	glPopMatrix();

}
void petLeg() {

	if (plAngle >= 20) {
		plAngle -= phSpeed;
	}
	else if (plAngle <= -20) {
		plAngle += phSpeed;
	}

	/*if (heads >= 10)
		heads -= 0.5;
	if (heads <= -10)
		heads += 0.5; */


		//move leg
	glPushMatrix();
	glTranslatef(plx, ply, 0.0);                 // 3. Translate back to original 
	glRotatef(plAngle, 1.0, 0.0, 0.0);   // 2. Rotate the object around angle 
	glTranslatef(-plm, -pln, 0.0);            // 1. Move to origin 

	glPushMatrix();
	glTranslatef(-0.12, -0.40, 0.0);
	petHandModel1();
	glPopMatrix();

	glPopMatrix();
}
void petLegModel() {

	glPushMatrix();
	glTranslatef(-0.12, -0.40, 0.0);
	petHandModel1();
	glPopMatrix();
}
void petLeg2() {

	if (plAngle2 >= 20) {
		plAngle2 -= phSpeed;
	}
	else if (plAngle2 <= -20) {
		plAngle2 += phSpeed;
	}

	//move leg
	glPushMatrix();
	glTranslatef(plx2, ply2, 0.0);                 // 3. Translate back to original 
	glRotatef(plAngle2, 1.0, 0.0, 0.0);   // 2. Rotate the object around angle 
	glTranslatef(-plm2, -pln2, 0.0);            // 1. Move to origin 


	glPushMatrix();
	glTranslatef(-0.32, 0.0, 0.0);
	petLegModel();
	glPopMatrix();

	glPopMatrix();
}
void petRibbon() {

	//left pyramid
	glPushMatrix();
	glTranslatef(-0.7, -0.5, 0.0);
	glRotatef(270, 0.0, 0.0, 1.0);
	pyramid(0.05);
	glPopMatrix();

	//centre ball
	glPushMatrix();
	glTranslatef(-0.6, -0.5, 0.0);
	drawSphere2(0.03, 30, 30);
	glPopMatrix();

	//right pyramid
	glPushMatrix();
	glTranslatef(-0.5, -0.5, 0.0);
	glRotatef(450, 0.0, 0.0, 1.0);
	pyramid(0.05);
	glPopMatrix();
}
void petWeapon() {
	//---------------weapon hold
	//front
	glPushMatrix();
	glTranslatef(0.6, 0.02, 0.0);
	circleWeapon();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.6, 0.02, -0.01);
	circleWeapon1();
	glPopMatrix();

	//back
	glPushMatrix();
	glTranslatef(0.6, 0.02, 0.2);
	circleWeapon();
	glPopMatrix();

}
void ball() {
	glPushMatrix();
	glTranslatef(0.6, 0.02, 0);
	drawSphere3(0.05, 30, 30);
	glPopMatrix();
}

//-------------------------------------------------------------------------------------------
//------------------------------------MOVEMENT-----------------------------------------------
//-------------------------------------------------------------------------------------------
void movement() {
	//Lhangle += hspeed, Rhangle -= hspeed, Lx_spin = 1.0, Ly_spin = 0.0, Lz_spin = 0.0;
	//	lAngle += lSpeed, lAngle2 -= lSpeed;
	
	if (walkforward || walkbackward) {
		if (movecount == 0) {
			Lhangle = 32, Rhangle = -32, Lx_spin = 1.0, Ly_spin = 0.0, Lz_spin = 0.0;
			lAngle = 16, lAngle2 = -16;
		}
		else if (movecount == 5) {
			Lhangle = 0, Rhangle = 0, Lx_spin = 1.0, Ly_spin = 0.0, Lz_spin = 0.0;
			lAngle = 0, lAngle2 = 0;
		}
		else if (movecount == 10)
		{
			Lhangle = -32, Rhangle = 32, Lx_spin = 1.0, Ly_spin = 0.0, Lz_spin = 0.0;
			lAngle = -16, lAngle2 = 16;
		}
		else if (movecount == 15) {
			Lhangle = 0, Rhangle = 0, Lx_spin = 1.0, Ly_spin = 0.0, Lz_spin = 0.0;
			lAngle = 0, lAngle2 = 0;
		}
		else if (movecount == 20) {
			movecount = -1;
		}
		movecount += 1;
		if (walkforward) {
			movez += 0.1;

		}
		else if (walkbackward) {
			movez -= 0.1;

		}
	}
	else walkforward = false, walkbackward = false;
		


	if (runforward) {
		bowz = 10;
		if (movecount == 0) {
			lAngle = 40, lAngle2 = -70;
			lcAngle = 0, lcAngle2 = 10;
			Lhangle = 45, Rhangle = -45, Lx_spin = 1.0, Ly_spin = 0.0, Lz_spin = 0.0;
		}
		else if (movecount == 5) {
			lAngle = 0, lAngle2 = 0;
			lcAngle = 0, lcAngle2 = 0;
			Lhangle = 0, Rhangle = 0, Lx_spin = 1.0, Ly_spin = 0.0, Lz_spin = 0.0;
		}
		else if (movecount == 10)
		{
			lAngle = -70, lAngle2 = 40;
			lcAngle = 10, lcAngle2 = 0;
			Lhangle = -45, Rhangle = 45, Lx_spin = 1.0, Ly_spin = 0.0, Lz_spin = 0.0;
		}
		else if (movecount == 15) {
			lAngle = 0, lAngle2 = 0;
			lcAngle = 0, lcAngle2 = 0;
			Lhangle = 0, Rhangle = 0, Lx_spin = 1.0, Ly_spin = 0.0, Lz_spin = 0.0;
			movecount = 0;
		}
		movecount += 1;

		movez += 0.25;


	}
	else runforward = false;
		

	if (fly) {
		isFly = true;
		headx = 1.0, heady = 0.0, heads = 15;
		Lhangle = -160, Rhangle = -160, Lx_spin = 1.0, Ly_spin = 0.0, Lz_spin = 0.0;
		lwAngle = -20, lwAngle2 = 20;
		movey += 0.05;

	}
	else fly = false;
}
void headBody() {
	if (heads >= 25)
		heads -= 0.5;
	if (heads <= -25)
		heads += 0.5;

	if (bowz >= 20)
		bowz -= lSpeed;
	glPushMatrix();
	glRotatef(speed, Rx, Ry, 0.0);
	glScalef(0.9, 0.9, 1.0);
	glPushMatrix();
	glRotatef(heads, headx, heady, 0.0);
	glTranslatef(0, 0.58, 0.05);
	glPushMatrix();
	glScalef(0.6, 0.8, 1.0);
	if (eyeno == 1)
		eyes1();
	else if (eyeno == 2)
		eyes2();
	else if (eyeno == 3)
		eyes3();
	glPopMatrix();
	head();
	glPopMatrix();
	glPushMatrix();
	body();
	glPopMatrix();

	glPopMatrix();
}

//-------------------------------------------------------------------------------------------
//------------------------------------DISPLAY------------------------------------------------
//-------------------------------------------------------------------------------------------

void display()
{
	//texture
	GLuint textures[11];

	//Background
	displayBackground();
	glDisable(GL_DEPTH_TEST);
	if (sky) {
		textures[9] = loadTexture("sky.bmp");
	}
	else {
		textures[10] = loadTexture("skymountain.bmp");   //#cc
	}
	glPushMatrix();
	glScalef(10.0, 10.0, 10.0);
	drawSky();
	glPopMatrix();
	glDeleteTextures(1, &textures[9]);
	glDeleteTextures(1, &textures[10]);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	//Projection setting
	Projection();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();   //projection translate
	glTranslatef(0, 0, tz);

	//Lighting 
	glPushMatrix();   //projection translate
	glTranslatef(0, 0, tzL);
	lighting();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, movey, movez);
	glPushMatrix();
	glRotatef(bowz, 1.0, 0, 0);
	
	//head + body
	glPushMatrix();
	glTranslatef(0.0, 1.2, 0.0);
	glScalef(3.0, 3.0, 3.0);
	glRotatef(180, 0.0, 1.0, 0.0);
	headBody();
	glPopMatrix();
	if (!red) {
		textures[8] = loadTexture("pink2.bmp");
	}
	else {
		textures[0] = loadTexture("blue3.bmp");
	}
	//hand + weapon
	glPushMatrix();
	handWeapon();
	glPopMatrix();
	glDeleteTextures(1, &textures[0]);
	glDeleteTextures(1, &textures[8]);
	

	textures[1] = loadTexture("feather.bmp");
	//wing
	glPushMatrix();
	glTranslatef(-0.05, -0.1, 4.55);
	glScalef(10.0, 10.0, 10.0);
	glRotatef(180, 0.0, 1.0, 0.0);
	wholeWing();
	glPopMatrix();
	glDeleteTextures(1, &textures[1]);
	glPopMatrix();

	if (!red) {
		textures[8] = loadTexture("pink2.bmp");
	}
	else {
		textures[0] = loadTexture("blue3.bmp");
	}
	//leg
	glPushMatrix();
	glTranslatef(0.00, -0.25, -4.0);
	glScalef(8.0, 8.0, 8.0);
	wholeLeg();
	glPopMatrix();
	glDeleteTextures(1, &textures[0]);
	glDeleteTextures(1, &textures[8]);

	glPopMatrix();
	movement();

	//--------------pet section-----------------------------------------------------------------

	glPushMatrix();
	glTranslatef(4.0, -2.6, 0);
	glRotatef(180, 0, 1.0, 0);
	glScalef(2.0, 2.0, 2.0);
	//-----------head---------------------------
	if (pAngle >= 45) {
		pAngle -= phSpeed;
	}
	else if (pAngle <= -45) {
		pAngle += phSpeed;
	}

	//able to move
	glPushMatrix();
	glTranslatef(px, py, 0.0);                 // 3. Translate back to original 
	glRotatef(pAngle, 1.0, 0.0, 0.0);   // 2. Rotate the object around angle 
	glTranslatef(-pm, -pn, 0.0);            // 1. Move to origin 

	if (pethead) {
		textures[2] = loadTexture("newfur.bmp");
		glPushMatrix();
		glTranslatef(0.0, 0.45, 0.02);
		glScalef(1.5, 0.8, 1.5);
		petBodyA();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.15, 0.4, -0.4);
		glScalef(1.0, 1.2, 1.0);
		drawSphere(0.02, 50, 50);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.15, 0.4, -0.4);
		glScalef(1.0, 1.2, 1.0);
		drawSphere(0.02, 50, 50);
		glPopMatrix();


		glDeleteTextures(1, &textures[2]);

		//eye map

		textures[3] = loadTexture("newblackFur.bmp");
		//middle black----------------left eye
		glPushMatrix();
		glTranslatef(-0.15, 0.4, -0.35);
		glScalef(1.0, 1.5, 1.0);
		drawSphere(0.05, 50, 50);
		glPopMatrix();
		//bottom black
		glPushMatrix();
		glTranslatef(-0.15, 0.4, -0.35);
		glRotatef(180, 0.0, 0.0, 1.0);
		glScalef(1.0, 1.5, 1.0);
		drawSphere(0.06, 50, 50);
		glPopMatrix();


		//middle black--------------------right eye
		glPushMatrix();
		glTranslatef(0.15, 0.4, -0.35);
		glScalef(1.0, 1.5, 1.0);
		drawSphere(0.05, 50, 50);
		glPopMatrix();
		//bottom black
		glPushMatrix();
		glTranslatef(0.15, 0.4, -0.35);
		glRotatef(180, 0.0, 0.0, 1.0);
		glScalef(1.0, 1.5, 1.0);
		drawSphere(0.06, 50, 50);
		glPopMatrix();

		//nose
		glPushMatrix();
		glTranslatef(0.0, 0.3, -0.33);
		glScalef(1.5, 1.0, 1.5);
		drawSphere(0.02, 50, 50);
		glPopMatrix();

		//ear
		glPushMatrix();
		glTranslatef(0.19, 0.55, -0.10);
		drawSphere(0.09, 50, 50);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-0.19, 0.55, -0.10);
		drawSphere(0.09, 50, 50);
		glPopMatrix();

		glDeleteTextures(1, &textures[3]);



	}
	else {
		glPushMatrix();
		glTranslatef(0.0, 0.35, 0.38);
		pandahead();
		glPopMatrix();
	}

	glPopMatrix();
	//------------------end of head------------------------

	//-------------white body---------------------
	textures[2] = loadTexture("newfur.bmp");
	petBodyA();
	glDeleteTextures(1, &textures[2]);

	//----------------black------------------------
	textures[3] = loadTexture("newblackFur.bmp");

	//hand
	petHand();

	petHand2();

	//leg
	petLeg();

	petLeg2();

	glDeleteTextures(1, &textures[3]);


	//---------------red ribbon-----------------------
	textures[4] = loadTexture("red.bmp");

	glPushMatrix();
	glTranslatef(0.6, 0.55, -0.28);
	petRibbon();
	glPopMatrix();

	glDeleteTextures(1, &textures[4]);

	//---------------weapon model----------------------

	//fix boom to the body middle part----------------------------------------------------
	glPushMatrix();
	glTranslatef(-0.60, -0.2, -0.38);


	//---------------texture----------------------------
	textures[5] = loadTexture("silver.bmp");

	//middle of weapon
	glPushMatrix();
	glTranslatef(0.6, 0.02, 0.0);
	drawCylinder2(0.1, 0.1, 0.2, 50, 50);
	glPopMatrix();

	glDeleteTextures(1, &textures[5]);

	//---------------ICE  && FIRE BALL--------------------------
	if (petAttack == true) {
		petAtkCount = 45;
		petAttack = false;
	}
	else if (petAtkCount > 0) {
		petAtkCount -= 1;
		bom_z -= 1;
	}
	else {
		bom_z = 0;
	}
	glTranslatef(0, 0, bom_z);
	//ICE
	if (iceAttack) {
		textures[7] = loadTexture("ice.bmp");
		ball();
		glDeleteTextures(1, &textures[7]);
	}//FIRE BALL
	else {
		textures[6] = loadTexture("fire.bmp");
		ball();
		glDeleteTextures(1, &textures[6]);
	}
	glTranslatef(0, 0, -bom_z);
	petWeapon();
	
	//---fix middel end
	glPopMatrix();
	//--------------------end of weapon model-----------

	//--------------Pet Section End --------------------------------------------------------------------------------------



	//for projection translate
	glPopMatrix();


	//Step5: Remove texture info.
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();



	//--------------------background usage-----------
	if (bgcount > 2000) {
		bgcount = 0;
		bgspeed = 0;
		turnArround = true;
	}
	else {
		bgspeed += 0.01;
		bgcount++;
		turnArround = false;
	}
	glTranslatef(bgspeed, 0.0, 0);
	glScalef(1.0, 1.0, 1.0);
	airBaloon();
	glTranslatef(-bgspeed, 0.0, 0);

	if (bgcount1 > 4500) {
		bgcount1 = 0;
		bgspeed1 = 0;
		turnArround1 = true;
	}
	else {
		bgspeed1 += 0.007;
		bgcount1++;
		turnArround1 = false;
	}
	glTranslatef(bgspeed1, 0.0, 0);
	glScalef(1.0, 1.0, 1.0);
	cloudsPart1();
	glTranslatef(-bgspeed1, 0.0, 0);

	if (bgcount2 > 4500) {
		bgcount2 = 0;
		bgspeed2 = 0;
		turnArround2 = true;
	}
	else {
		bgspeed2 += 0.007;
		bgcount2++;
		turnArround2 = false;
	}
	glTranslatef(bgspeed2, 0.0, 0);
	glScalef(1.0, 1.0, 1.0);
	cloudsPart2();
	glTranslatef(-bgspeed2, 0.0, 0);

	if (bgcount3 > 4500) {
		bgcount3 = 0;
		bgspeed3 = 0;
		turnArround3 = true;
	}
	else {
		bgspeed3 += 0.007;
		bgcount3++;
		turnArround3 = false;
	}
	glTranslatef(bgspeed3, 0.0, 0);
	glScalef(1.0, 1.0, 1.0);
	cloudsPart3();
	glTranslatef(-bgspeed3, 0.0, 0);

	if (attack == true) {
		switch (weapon_choice) {
		case 1:				// normal laser
			Lhangle = 90, Lx_spin = -1, Ly_spin = 0, Lz_spin = 0;
			Rhangle = 90, Rx_spin = -1, Ry_spin = 0, Rz_spin = 0;
			attackCount = 120;
			break;
		case 2:				// blade swing
			Lhangle = 180, Lx_spin = -1.5, Ly_spin = -0.5, Lz_spin = 0;
			Rhangle = 180, Rx_spin = -1.5, Ry_spin = -0.5, Rz_spin = 0;
			attackCount = 120;
			break;
		case 3:				// cannon ball
			Lhangle = 90, Lx_spin = -1, Ly_spin = 0, Lz_spin = 0;
			Rhangle = 90, Rx_spin = -1, Ry_spin = 0, Rz_spin = 0;
			attackCount = 120;
			break;
		default:
			break;
		}
		attack = false;
	}

	if (attackCount > 90) {
		attackCount -= 1;
		if (weapon_choice == 2 && attackCount > 90 && attackCount < 115) {
			Lhangle = 90, Lx_spin = -1, Ly_spin = 1, Lz_spin = 0;
			Rhangle = 90, Rx_spin = -1, Ry_spin = 1, Rz_spin = 0;
		}
		else if (weapon_choice == 2 && attackCount >= 115) {
			Lhangle = 180, Lx_spin = -1.5, Ly_spin = -0.5, Lz_spin = 0;
			Rhangle = 180, Rx_spin = -1.5, Ry_spin = -0.5, Rz_spin = 0;
		}
		attackMove();
	}
	else if (attackCount > 0 && attackCount <= 90) {
		Lhangle -= 1;
		Rhangle -= 1;
		attackCount -= 1;
		effect_x = 0;
		effect_y = 0;
		effect_z = 0;
	}
	else {
	}
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------