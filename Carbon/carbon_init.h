#pragma once
////////////////////////
//CONST
////////////////////////
colo RED;
colo BLU;
colo GRE;
//

///////////////////////
//PERM
///////////////////////
map<int, bool> keyboard;
float carbonfps;
float fps_accepted = 30;
site fpssite;
site versionsite;
string info;
string temp;
bool run = true;
colo DWCOLO;
colo DWCOLO2;
colo DWCOLO3;
colo DWCOLO4;
POINT m;
POINT minit;
POINT m2init;
bool m1 = 0;
bool m2 = 0;
float delta;
float tbucket;
////

///////////////////////
//Tetris
///////////////////////
tetrisgame mtetrisgame;
site msite1;
site msite2;
int score;
site scoresite;
bool play = true;
bool newpiece = true;
int currentpiece;
int canfall = 0;
int canmove = 0;
float timescale = 40000;
int upcheck;
bool ureset;
bool rreset;
bool lreset;
bool rotreset;
site pivot;
int newposu[3];
int newposv[3];
int minocounter;
////

////////////////////////
//TEMP
////////////////////////




////

void SketchInit() {
	RED.r = 255;	BLU.b = 255;	GRE.g = 255;
	fpssite.u = 15; fpssite.v = 60;
	DWCOLO4.r = 215; DWCOLO4.b = 215; DWCOLO4.g = 215;
	DWCOLO3.r = 185; DWCOLO3.g = 185; DWCOLO3.b = 185;
	DWCOLO2.r = 29; DWCOLO2.b = 29; DWCOLO2.g = 26;
	DWCOLO.r = 20; DWCOLO.b = 20; DWCOLO.g = 18;

	mtetrisgame.pos.u = 520;
	mtetrisgame.bound.u = 920;
	mtetrisgame.boardlength = abs(mtetrisgame.pos.u - mtetrisgame.bound.u);
	mtetrisgame.pos.v = (height / 2) - mtetrisgame.boardlength;
	mtetrisgame.bound.v = (height / 2) + mtetrisgame.boardlength;
	mtetrisgame.boardheight = abs(mtetrisgame.pos.v - mtetrisgame.bound.v);
	mtetrisgame.minolength = mtetrisgame.boardlength / 10;
	mtetrisgame.minoheight = mtetrisgame.boardheight / 20;

	scoresite.u = 1020;
	scoresite.v = 50;
}