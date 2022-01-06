#include<Windows.h>
#include<GL/glew.h>
#include<GL/freeglut.h>
#include<stdio.h>
#include <time.h>   /* 時間相關函數 */
#include<string.h>
#include"classDef.h"

#include"Imagx.h"
#include "glm.h"
#include "ObjectLoader.h"

extern Player p1;
Building b1(5, 10, 5);
extern Timer myTimer;
extern Ground myGround;
extern ProgressBar myProgressBar;
extern RandomGenObStacles myRandGenObstacles;

//status flag
GLboolean isFullScreen=GL_FALSE;
GLboolean isInExitMenu=GL_FALSE;
extern GLboolean listExchange=GL_FALSE;

//圖片素材
//external variable需要初始化一個實體
extern Imagx helpMenu=Imagx();
extern Imagx mainMenu=Imagx();
extern Imagx exitMenu=Imagx();
extern Imagx coverRGL=Imagx();
extern Imagx aboutMenu=Imagx();
extern Imagx restartMenu=Imagx();

//客戶
extern Imagx callingMan=Imagx();
extern Imagx callingWoman=Imagx();
extern Imagx callingOldMan=Imagx();
extern Imagx callingOldWoman=Imagx();
//對話框
extern Imagx textInit_normal=Imagx();

//馬路貼圖
extern Imagx zebraStripe=Imagx();
extern Imagx laneStripe=Imagx();

//成就
extern Imagx archiv_ad_board=Imagx();
extern Imagx archiv_fire=Imagx();
extern Imagx archiv_intersection_car=Imagx();
extern Imagx archiv_old_woman=Imagx();
extern Imagx archiv_reverse_car=Imagx();
extern Imagx archiv_road_hole=Imagx();


//3D素材
extern ObjectLoader stev=ObjectLoader();
extern ObjectLoader building_test=ObjectLoader();
extern ObjectLoader board_small_cup=ObjectLoader();
extern ObjectLoader board_pawnshop=ObjectLoader();

//list
extern ImagxList imlist=ImagxList();
extern ObjList objlist=ObjList();

void init(){
	glClearColor(0.5,0.5,0.5,1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//texture
	//若某模型不須貼圖或透明，要關掉功能
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_RESCALE_NORMAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//載入圖片素材
	mainMenu=Imagx("assets/img/menu/menu_main.png",2.5,GL_TRUE);
	coverRGL=Imagx("assets/img/cover/cover_RGL_normal.png",2.8,GL_TRUE);coverRGL.cirleRotateAnim(GL_TRUE);
	exitMenu=Imagx("assets/img/menu/menu_exit.png",0,GL_TRUE);exitMenu.setMaxScale(3.5);exitMenu.setEndTick(50);
	helpMenu=Imagx("assets/img/menu/menu_help.png",0,GL_TRUE);helpMenu.setMaxScale(4);
	aboutMenu=Imagx("assets/img/menu/menu_about.png",0,GL_TRUE);aboutMenu.setMaxScale(4);
	restartMenu=Imagx("assets/img/menu/menu_restart.png",2,GL_TRUE);
	imlist.push(mainMenu.getDpIndex());
	imlist.push(coverRGL.getDpIndex());
	imlist.push(exitMenu.getDpIndex());
	imlist.push(helpMenu.getDpIndex());
	imlist.push(aboutMenu.getDpIndex());
	imlist.push(restartMenu.getDpIndex());

	//人物
	callingMan=Imagx("assets/img/phone_call/talking_man.png",1,GL_TRUE);
	callingWoman=Imagx("assets/img/phone_call/talking_woman.png",1,GL_TRUE);
	callingOldMan=Imagx("assets/img/phone_call/talking_ojiisan.png",1,GL_TRUE);
	callingOldWoman=Imagx("assets/img/phone_call/talking_obaasan.png",1,GL_TRUE);
	textInit_normal=Imagx("assets/img/text_init/text_init_normal.png",4,GL_TRUE);
	imlist.push(callingMan.getDpIndex());
	imlist.push(callingWoman.getDpIndex());
	imlist.push(callingOldMan.getDpIndex());
	imlist.push(callingOldWoman.getDpIndex());
	imlist.push(textInit_normal.getDpIndex());

	//道路素材貼圖
	zebraStripe=Imagx("assets/img/traffic/zebraStripe.png",1,GL_TRUE);
	laneStripe=Imagx("assets/img/traffic/lane.png",1,GL_TRUE);
	imlist.push(zebraStripe.getDpIndex());
	imlist.push(laneStripe.getDpIndex());

	//成就
	archiv_fire=Imagx("assets/img/archiv/archiv_fire.png",1,GL_TRUE);
	archiv_ad_board=Imagx("assets/img/archiv/archiv_ad_board.png",1,GL_TRUE);
	archiv_old_woman=Imagx("assets/img/archiv/archiv_old_woman.png",1,GL_TRUE);
	archiv_road_hole=Imagx("assets/img/archiv/archiv_road_hole.png",1,GL_TRUE);
	archiv_reverse_car=Imagx("assets/img/archiv/archiv_reverse_car.png",1,GL_TRUE);
	archiv_intersection_car=Imagx("assets/img/archiv/archiv_intersection_car.png",1,GL_TRUE);
	imlist.push(archiv_fire.getDpIndex());
	imlist.push(archiv_ad_board.getDpIndex());
	imlist.push(archiv_old_woman.getDpIndex());
	imlist.push(archiv_road_hole.getDpIndex());
	imlist.push(archiv_reverse_car.getDpIndex());
	imlist.push(archiv_intersection_car.getDpIndex());


	//載入3D素材
	stev=ObjectLoader(	
		"assets/obj/stev/stev.obj",
		"assets/obj/stev/stev.jpg",
		GL_FALSE,
		GLM_SMOOTH|GLM_MATERIAL|GLM_TEXTURE
	);
	building_test=ObjectLoader(
		"assets/obj/building_test/building_test.obj",
		"assets/obj/building_test/building_tex01.png",
		GL_FALSE,
		GLM_SMOOTH|GLM_MATERIAL|GLM_TEXTURE
	);

	//招牌
	board_small_cup=ObjectLoader(
		"assets/obj/board/small_cup/board_small_cup.obj",
		"assets/obj/board/small_cup/board_small_cup.png",
		GL_FALSE,
		GLM_SMOOTH|GLM_MATERIAL|GLM_TEXTURE
	);
	board_pawnshop=ObjectLoader(
		"assets/obj/board/pawnshop/board_pawnshop.obj",
		"assets/obj/board/pawnshop/board_pawnshop.png",
		GL_FALSE,
		GLM_SMOOTH|GLM_MATERIAL|GLM_TEXTURE
	);

	objlist.push(stev.getDpIndex());
	objlist.push(building_test.getDpIndex());
	objlist.push(board_small_cup.getDpIndex());
	objlist.push(board_pawnshop.getDpIndex());

	/* 對隨機產生障礙物設定亂數種子 */
	srand(time(NULL));
}

void idle(){	
	glutPostRedisplay();
}

void initGame() {
	myTimer.nowTime = myTimer.time;
	memset(p1.pos, 0, sizeof(p1.pos));
	p1.v = 0.01;
	p1.shift = 0;
	//停止播放音樂
	PlaySound(NULL, NULL, SND_FILENAME);
	/* 設定亂數種子 */
	srand(time(NULL));

	myRandGenObstacles.init();

	//音樂
	PlaySound(TEXT("assets/music/game-bgm.wav"), NULL, SND_ASYNC | SND_LOOP);
	//mciSendString(TEXT("play \"assets/music/逆向車.mp3 repeat\" "), NULL, 0, NULL);
}

void keyboard(unsigned char key,int x,int y){
	//大寫全轉小寫
	if(65<=key && key<=90) key+=32;

	//與離開遊戲相關
	if(key==27){
		if(isInExitMenu)exitMenu.scaleSmall();
		else			exitMenu.scaleBig();
		isInExitMenu = ~isInExitMenu;
	}
	if(key=='y'){
		if(isInExitMenu){
			exit(0);
		}
	}
	if(key=='n'){
		if(isInExitMenu && exitMenu.getScale()==exitMenu.getMaxScale()){
			exitMenu.scaleSmall();
			isInExitMenu=GL_FALSE;
		}
	}

	//主要控制鍵
	if (key == 32 ) {//space
		if (p1.status == START) {
			//START跳轉頁面function
			//使用空白鍵可開始遊戲
			
			//if(頁面為最後一頁)
			//增加skip跳過故事的功能
			p1.status = GAME;
			initGame();
		}
		if (p1.status == TIMEUP ||
			p1.status == DEAD   ||
			p1.status == END) {
			//TIMEUP跳轉頁面function
			p1.status = GAME;
			initGame();
		}
		if (p1.status == MAIN_MENU){
			p1.status = START;
		}
	}
	if (p1.status == GAME) {
		p1.kb(key,x,y);
	}
	if (key=='r'){
		if (p1.status == TIMEUP ||
			p1.status == DEAD   ||
			p1.status == END    ){
			//回到主選單
			memset(p1.pos, 0, sizeof(p1.pos));
			p1.status = MAIN_MENU;
		}
	}
	if(key=='h'){
		//幫助/遊戲說明
		if(p1.status==MAIN_MENU){
			//動畫播放完之後，才能進行下一個動畫
			if(helpMenu.getScale() == 0)helpMenu.scaleBig();
			else if(helpMenu.getScale() == helpMenu.getMaxScale())helpMenu.scaleSmall();
		}
	}
	if(key=='v'){
		//關於遊戲資訊
		if(p1.status==MAIN_MENU){
			//動畫播放完之後，才能進行下一個動畫
			if(aboutMenu.getScale() == 0)aboutMenu.scaleBig();
			else if(aboutMenu.getScale() == aboutMenu.getMaxScale())aboutMenu.scaleSmall();
		}
	}
	if(key=='f'){
		//全螢幕
		if(isFullScreen){
			glutPositionWindow(500,200);
			glutReshapeWindow(700, 700);
		}
		else{
			glutFullScreen();
		}
		isFullScreen = ~isFullScreen;
	}
	if(key=='b'){
		if(p1.status==MAIN_MENU){
			p1.status = DEBUG;
			glClearColor(0.5,0.5,0.8,1);
		}
		else if(p1.status==DEBUG){
			p1.status = MAIN_MENU;
			glClearColor(0.5,0.5,0.5,1);
		}
	}

	if (key == 'c') { //無敵模式
		p1.cheat = !p1.cheat;
	}

	glutPostRedisplay();
}

void specialKb(int key,int x,int y){
	if(listExchange){
		imlist.specialKb(key,x,y);
	}
	else{
		objlist.specialKb(key,x,y);
	}

	if(key==101 || key==103) listExchange = ~listExchange;

}

void timer1000() {
	if (p1.status == GAME) {
		--myTimer.nowTime;
		if (myTimer.nowTime <= 0) {
			p1.status = TIMEUP;
			//關掉音樂
			PlaySound(NULL, NULL, NULL);
		}
	}
	
}
void timer20() {
	//player的速度會因摩擦力慢慢減少
	if (p1.v - 0.01 > p1.maxV) p1.v -= 0.01;
	if (p1.shift - 0.05 > 0) p1.shift -= 0.05;
	else p1.shift = 0;
}

void timer5() {
	//圖片素材
	helpMenu.progress();
	exitMenu.progress();
	coverRGL.progress();
	aboutMenu.progress();

	//player 自動移動
	if (p1.status == GAME) {
		p1.Progress();
		//printf("\rpos.z = %f, pos.x=%f, STATUS:%d \t",p1.pos[2], p1.pos[0], p1.status);
	}

	//如果遊戲結束，停止移動
	if (p1.status == END) {
		p1.playerStop(myProgressBar.pathLen);
	}
}
void timer(int id) {
	switch (id)
	{
	case 0:
		timer1000();
		glutTimerFunc(1000, timer, 0);
		break;
	case 1:
		timer20();
		glutTimerFunc(20, timer, 1);
		break;

	case 2:
		timer5();
		glutTimerFunc(5, timer, 2);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void reshape(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,(GLfloat)w/(GLfloat)h,1,80);
	glMatrixMode(GL_MODELVIEW);
}

//====================================draw====================================
void drawGround(int w, int h) {
	myGround.draw(laneStripe);
}

void drawObstacles() {
	myRandGenObstacles.drawObstacle(&p1,myProgressBar.pathLen);
}

void drawBuildings() {
	b1.setPos(10, 1, -70);
	b1.drawBuilding();
}

void drawPlayer() {
	p1.drawPlayer();
}

void drawProgressBar() {
	myProgressBar.draw(&p1);
}

void drawTimer() {
	myTimer.drawTimer(&p1);
}

void drawstr(GLfloat x, GLfloat y, char* format, ...)
{
	GLvoid* font_style = GLUT_BITMAP_HELVETICA_18;
	va_list args;
	char buffer[255], * s;

	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	glRasterPos2f(x, y);
	for (s = buffer; *s; s++)
		glutBitmapCharacter(font_style, *s);
}