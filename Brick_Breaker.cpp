#include <stdlib.h>    
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;


// Initialise Score, Level, Lives and Block_state
int score = 0, level = 0;
int lives = 3;
int if_draw_blocks = 0;
int screen_state = 0;

int game_level[] = {40,30,20};
float rate = game_level[level];

GLfloat brick_color_array[3] = {1,0,0};
GLfloat paddle_color_array[3] = {1,0,0};
GLfloat text_color_array[4] = {0.39,0,0.79,1};
GLfloat home_text_color_array[4] ={1,1,0,1};
GLfloat paddle_size[3] = {9, 6, 3};


//The grid parameters for the bricks
int rows = 6;
int columns = 10;


// Structure to store the coordinates of each brick
struct brick_coords{
	GLfloat x;
	GLfloat y;
};


//Array to store the bricks
brick_coords brick_array[50][50];
GLfloat px,bx = 0,by = -12.94 ,speed = 0,dirx=0,diry=0,start = 0;



// Function to draw the paddle
void draw_paddle(){
	glDisable(GL_LIGHTING);
	glColor3fv(paddle_color_array);
	glBegin(GL_POLYGON);
	glVertex3f(-paddle_size[level]+px,0-15,0);
	glVertex3f(paddle_size[level]+px,0-15,0);
	glVertex3f(paddle_size[level]+px,1-15,0);
	glVertex3f(-paddle_size[level]+px,1-15,0);
	glEnd();
	glEnable(GL_LIGHTING);
}



//Function to draw a single brick
void brick(GLfloat x,GLfloat y, GLfloat z){	
	glDisable(GL_LIGHTING);
	glColor3fv(brick_color_array);
	glBegin(GL_QUADS);
	glVertex3f(x,y,z);
	glVertex3f(x+3,y,z);
	glVertex3f(x+3,y+1,z);
	glVertex3f(x,y+1,z);       
	glEnd();
	glEnable(GL_LIGHTING);
}



// Function to draw the grid of bricks
void draw_bricks(){
	int i,j;
	if(if_draw_blocks == 0)
	{
		for(i = 1;i<=rows;i++)
		{
			for(j = 1;j<=columns;j++)
			{   
				
				brick_array[i][j].x = (GLfloat)(j*4*0.84);
				brick_array[i][j].y = (GLfloat)(i*2*0.6) ;
			}
		}
	}
	
	
	glPushMatrix();
	glTranslatef(-19.5,5,0);

	for(i = 1;i<=rows;i+=1)
	{
		for(j = 1;j<=columns;j+=1)
		{
			
			if(brick_array[i][j].x==0 || brick_array[i][j].y ==0)
			{
				continue;
			}
			brick(brick_array[i][j].x,brick_array[i][j].y,0);
		}
	}
	glPopMatrix();
}



//Function to draw the spherical ball
void draw_ball(){
	GLfloat ambient1[] = {1,1,1};
	GLfloat diffuse1[] = {0.4,0.4,0.4};
	GLfloat specular1[] = {1,1,1};
	
	GLfloat position[] = {0,0,-50,1};
	GLfloat ambient2[] = {0,0,0};
	GLfloat diffuse2[] = {1,1,1};
	GLfloat specular2[] = {0,1,1};
	
	GLfloat materialColours[] = {0.39,0,0.39};
	GLfloat matAmbient1[] = {1,1,1};
	GLfloat matDiffuse1[] = {1,1,1};
	GLfloat matSpecular1[] = {1,1,1};
	GLfloat shininess[] = {1000};
	
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular1);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient1);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse1);
	
	glLightfv(GL_LIGHT1,GL_POSITION,position);
	glLightfv(GL_LIGHT1,GL_SPECULAR,specular2);
	glLightfv(GL_LIGHT1,GL_AMBIENT,ambient2);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,diffuse2);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,materialColours);
	
	glPushMatrix();
	glTranslatef(bx,by,0);
	glScalef(0.5, 0.5, 0.25);
	glutSolidSphere(1.0, 52, 52);
	glPopMatrix();
}


// Mouse Function to choose difficulty
void mouse_click(int button, int mouse_state, int x, int y){
	if(screen_state == 0 && button == GLUT_LEFT_BUTTON && mouse_state == GLUT_DOWN) {
        // Check if the click is in the specified region
        if (x >= 400 && x <= 600 && y >= 300 && y <= 400) {
			level = 0;
			screen_state = 1;
            glutPostRedisplay();
        }
        else if(x >= 700 && x <= 900 && y >= 300 && y <= 400){
			level = 1;
			screen_state = 1;
            glutPostRedisplay();
		}
		else if(x >= 1000 && x <= 1200 && y >= 300 && y <= 400){
			level = 2;
			screen_state = 1;
            glutPostRedisplay();
		}
    }
    
    else if(screen_state == 2 && button == GLUT_LEFT_BUTTON && mouse_state == GLUT_DOWN){
    	if (x >= 400 && x <= 600 && y >= 300 && y <= 400) {
    		level = 0;
			lives = 3;
			if_draw_blocks = 0;
			screen_state = 0;
			score=0;
			px=0,bx = 0,by = -12.8 ,speed = 0,dirx=0,diry=0,start = 0;
			glutPostRedisplay();
        }
        else if(x >= 700 && x <= 900 && y >= 300 && y <= 400){
			exit(0);
		}
	}
}


// Mouse function for moving paddle
void mousemotion(int x,int y){  
  	if(start == 1){
		px=(x-glutGet(GLUT_WINDOW_WIDTH)/2)/20;
		if(px>15){
			px=15;
		}
		if(px<-15){
			px=-15;
		}
    }
    else glutSetCursor(GLUT_CURSOR_INHERIT);
}



//Function to print the score on the screen
void text(int sc, int lives){
	glDisable(GL_LIGHTING);
	char text[40];
	char difficulty[10];

	if(level == 0)		sprintf(difficulty,"Easy");

	else if(level == 1)	sprintf(difficulty,"Medium");
	
	else if(level == 2)	sprintf(difficulty,"Hard");
	
	if(sc < rows * columns){
		sprintf(text,"Difficulty: %s    Your Score: %d      Lives: %d",difficulty, sc, lives);
	}
	else{
		level = 0;
		lives = 3;
		if_draw_blocks = 0;
		px=0,bx = 0,by = -12.8 ,speed = 0,dirx=0,diry=0,start = 0;
		screen_state = 2;
		glutPostRedisplay();
	}
	
	// The color of text
	glColor4fv(text_color_array);
	
	// Position of the text to be printer
	glPushMatrix();
	glTranslatef(-1,0,0);
	glRasterPos3f(0, 0, 20);
	for(int i = 0; text[i] != '\0'; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}
	glEnable(GL_LIGHTING);
	glPopMatrix();
}



//Function to print homepage
void home_text(int x, int y, string s)
{
	glDisable(GL_LIGHTING);
	string text = s;
	
	// The color
	glColor4fv(home_text_color_array);
	
	// Position of the text to be printer
	glPushMatrix();
	glTranslatef(-1,0,0);
	glRasterPos3f(x, y, 20);
	for(int i = 0; text[i] != '\0'; i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
	glEnable(GL_LIGHTING);
	glPopMatrix();
}



// To print exit Page
void close_text(int x, int y, int sc)
{
	glDisable(GL_LIGHTING);
	char text[40];
	sprintf(text,"Final Score = %d",sc);
	// The color
	glColor4fv(home_text_color_array);
	
	// Position of the text to be printed
	glPushMatrix();
	glTranslatef(-1,0,0);
	glRasterPos3f(x, y, 20);
	for(int i = 0; text[i] != '\0'; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}
	glEnable(GL_LIGHTING);
	glPopMatrix();
}



//The main display function
void display (void) {
	if(screen_state == 0){
		glClearColor (0.18,0.24,0.49,1.0);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(0,0,0,0,0,-25,0,1,0);
		glTranslatef(0,0,-25);
		home_text(0, 2, "Welcome to Brick Breaker");
		home_text(0, 1.5, "Choose Your Difficulty");
		home_text(-1, 0, "Easy");
		home_text(1, 0, "Medium");
		home_text(3, 0, "Hard");
		glutSwapBuffers();
	}
	else if(screen_state == 1){
		glClearColor (0.79,0.99,0.59,1.0);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(0,0,0,0,0,-25,0,1,0);
		glTranslatef(0,0,-25);

		// Draw Bricks and Wall
		draw_paddle();
		draw_bricks();
		draw_ball();
		text(score, lives);
		glutSwapBuffers();
	}
	else{
		glClearColor (0.18,0.24,0.49,1.0);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(0,0,0,0,0,-25,0,1,0);
		glTranslatef(0,0,-25);
		home_text(0, 2, "Game Over!!!!");
		close_text(0, 1, score);
		home_text(-1, 0, "Homepage");
		home_text(1, 0, "Exit");
		glutSwapBuffers();
	}
}



//function to turn on lights
void lightsOn(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}



//Reshape Function
void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
	glMatrixMode (GL_MODELVIEW);
}



//function to take in keyboard entries
void keyboard (unsigned char key, int x, int y){
	switch(key){
		case 'd': px+=3; break;
		case 'a': px-=3; break;
		case 'q': exit(0); break;
		case 's':
		if(!start){
			dirx = diry= 1;
			rate = game_level[level];
			start = 1;
			if_draw_blocks = 1;
			
			if(lives == 3){
				score = 0;
			}
			glutSetCursor(GLUT_CURSOR_NONE);	
		}
		break;
	}
	if(px>15)		px=15;

	if(px<-15)		px=-15;
	
	if(start== 0)	px=0;
	
	glutPostRedisplay();
}



//Function to handle the case when the ball strikes the bricks
void hit(){
	int i,j;
	for(i = 1;i<=rows;i++){
		for(j=1;j<=columns;j++){
			if((bx>=brick_array[i][j].x-19.5-0.1)&&( bx<=brick_array[i][j].x + 3-19.5+ 0.1)){
				if(by >=brick_array[i][j].y+5-0.1 && by <=brick_array[i][j].y+5 +1.2 +0.1){
					brick_array[i][j].x = 0;
					brick_array[i][j].y = 0;
					diry= diry*-1;
					score++;
				}
			}
		}
	}
}



//The idle function. Handles the motion of the ball along with rebounding from various surfaces
void idle(){
	hit();
	if(bx<-16 || bx>16 && start == 1)
	{
		dirx = dirx*-1;
	}
	if(by<-15 || by>14 && start == 1)
	{
		diry = diry*-1;
	}
	
	bx+=dirx/(rate);
	by+=diry/(rate);
	
	// Rate at which the speed of ball increases
	rate-=1e-30;
	
	float x = paddle_size[level];
	
	//Make changes here for the different position of ball after rebounded by paddle
	if( by<=-12.8 && bx<(px+x*2/3) && bx>(px+x/3)&& start == 1 ){
		dirx = 1;
		diry = 1;
	}
	else if(by <=-12.8 && bx<(px-x/3) && bx>(px-x*2/3) && start == 1 ){
		dirx = -1;
		diry = 1;
	}
	else if( by<=-12.8 && bx<(px+x/3) &&bx>(px-x/3) && start == 1){
		dirx = dirx;
		diry = 1;
	}
	else if(by <=-12.8 && bx<(px-(x*2/3)) && bx>(px-(x+0.3)) && start == 1 ){
		dirx = -1.5;
		diry = 0.8;
	}
	else if(by<=-12.8 && bx<(px+(x+0.3)) && bx>(px+x/3)&& start == 1 ){
		dirx = 1.5;
		diry = 0.8;
	}
	else if(by<-13){
		// Decrease the number of lives
        lives--;
        if (lives > 0){
            // Reset ball position and stop the game
            start = 0;
            if_draw_blocks = 1;
            by = -12.8;
            bx = 0;
            dirx = 0;
            diry = 0;
            px = 0;

            // Print the updated number of lives
            text(score, lives);
        }
        else{
			level = 0;
			lives = 3;
			if_draw_blocks = 0;
			px=0,bx = 0,by = -12.8 ,speed = 0,dirx=0,diry=0,start = 0;
			screen_state = 2;
			glutPostRedisplay();
        }
	}
	glutPostRedisplay();
}



// Main Function
int main (int argc,char **argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (900, 900);
	glutInitWindowPosition (300,50);
	glutCreateWindow ("Brick Breaker");
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	glEnable(GL_DEPTH_TEST);
	glutIdleFunc (idle);
	glutPassiveMotionFunc(mousemotion);
	glutMouseFunc(mouse_click);
	glutKeyboardFunc(keyboard);
	lightsOn();
	glutMainLoop ();
	return 0;
}

