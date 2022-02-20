// #ifdef __APPLE__
// 	#include <GLUT/glut.h>
// #else 
// 	#include <glut.h> 
// 	//#include <GL/glut.h> 
// #endif
#include <GL/glut.h>
#include <math.h>
#include "othello.h"

#define WIDTH 800
#define HEIGHT 800

#define PI 3.1415926535

int pos_othello=0;

int cursorX=0;
int cursorY=0;

int windowWidth=800;
int windowHeight=800;

GameOthello* othello;


void drawCircle(double radius,double posx,double posy,double r,double g, double b){
	glColor3d(r,g,b);
	
	int resolution=90; //ポリゴンの頂点数
	glBegin(GL_POLYGON);
	for(int i=0;i<resolution;i++){
		glVertex2d(posx+radius*cos(2*PI*i/resolution),
		posy+radius*sin(2*PI*i/resolution));
	}
	glEnd();
}

void drawMarker(int x,int y,double r,double g,double b){
	glColor3d(r,g,b);

	int originX=80+x*80;
	int originY=80+y*80;
	glBegin(GL_QUADS);
		glVertex2i(originX,originY);
		glVertex2i(originX,originY+80);
		glVertex2i(originX+80,originY+80);
		glVertex2i(originX+80,originY);
	glEnd();
}

void display(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//カーソル
	drawMarker(cursorX,cursorY,1.0,1.0,0.0);

	//選択肢の表示

	//ラインを描く
	glColor3f(0,0,0);
	glLineWidth(3);//線幅の指定。省略可。指定しなければ1。
	glBegin(GL_LINES);
	for(int i=0;i<9;i++){
		glVertex2i(80+80*i,720);//縦線上端
		glVertex2i(80+80*i,80);//縦線下端
		glVertex2i(80,80+80*i);//横線左端
		glVertex2i(720,80+80*i);//横線右端
	}
	glEnd();

	//点を4箇所描く
	glColor3f(0,0,0);
	glPointSize(10);
	glBegin(GL_POINTS);
		glVertex2i(240,240);
		glVertex2i(240,560);
		glVertex2i(560,240);
		glVertex2i(560,560);
	glEnd();

	
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			int state=othello->board[i][j];
			switch(state){
				case 1:
					drawCircle(30,80+40+j*80,80+40+i*80,0,0,0);
					break;
				case 2:
					drawCircle(30,80+40+j*80,80+40+i*80,1,1,1);
					break;
				default:
					break;
			}
		}
	}

	glutSwapBuffers();
}

void Idle() {
	// glutPostRedisplay(); //これはGPU使用率がマズそう
}

void timer(int value) {
	pos_othello=(pos_othello+1)%8;
	glutTimerFunc(100 , timer , 0);
	glutPostRedisplay();
}

void mouseMotion(int x,int y){
	if((80<x && x<720) && (80<y && y<720)){
		cursorX=(x-80)/80;
		cursorY=(y-80)/80;
		glutPostRedisplay();
	}
}

// 面倒なのでウィンドウの大きさを固定
void fixedWindow(int width,int height){
	glutReshapeWindow(windowWidth,windowHeight);
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);	
	glutInitWindowSize(windowWidth,windowHeight);//ウィンドウの画面の幅と高さを指定
	// glutInitWindowSize(800,800);//ウィンドウの画面の幅と高さを指定
	glutInitWindowPosition(0, 0);//ウィンドウの場所を指定
	glutCreateWindow("Othello");//ウィンドウの名前
	glClearColor( 0 , 0.7, 0, 1);//オセロ盤の色
	// gluOrtho2D(0, 800, 800,0);//座標系の設定 ←使えない
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1); //代わり
	glutDisplayFunc(display);//描画関数を指定
	glutIdleFunc(Idle);
	glutTimerFunc(1000 , timer , 0);
	glutPassiveMotionFunc(mouseMotion); //マウスが動くと実行
	glutReshapeFunc(fixedWindow);

	othello = new GameOthello();

	glutMainLoop();
	return 0;
}