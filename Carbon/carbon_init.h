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
colo DWCOLO5;
colo DWCOLO6;
POINT m;
POINT minit;
POINT m2init;
bool m1 = 0;
bool m2 = 0;
float delta;
float tbucket;
////

///////////////////////
//Sort
///////////////////////
int MX = 200;
int value[200];
int used[200];
site lstart;
site lend;
int padding;
int r_refw;
int r_refh;
float perx;
float pery;
float gap;
int tempi;

//gnome
int cart = 0;
int limit = MX - 2;

//qsort
int pivot = 0;
float pivoted = 0;
int scope = MX - 1 / 2;
site t1;
site t2;
site t3;
float sorted = 0;
site ssorted;
site sSORT;
////

////////////////////////
//TEMP
////////////////////////




////

void SketchInit() {
	RED.r = 255;	BLU.b = 255;	GRE.g = 255;
	fpssite.u = 15; fpssite.v = 60;

	DWCOLO.r = 20; DWCOLO.b = 20; DWCOLO.g = 18;
	DWCOLO2.r = 29; DWCOLO2.b = 29; DWCOLO2.g = 26;
	DWCOLO3.r = 185; DWCOLO3.g = 185; DWCOLO3.b = 185;
	DWCOLO4.r = 215; DWCOLO4.b = 215; DWCOLO4.g = 215;
	DWCOLO5.r = 255; DWCOLO5.b = 0; DWCOLO5.g = 0;
	DWCOLO6.r = 255; DWCOLO6.b = 0; DWCOLO6.g = 255;

	ssorted.u = width * 3 / 5;
	ssorted.v = height * 1 / 11;
	
	padding = 120;
	r_refw = width - (padding * 2);
	r_refh = height - (padding * 2);

	for (int i = 0; i < MX; i++) {
		value[i] = i + 1;
	}


	std::random_shuffle(&value[0], &value[MX]);

}