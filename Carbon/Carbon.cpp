//Carbon 1.1 Update
//Copyright Joseph Buskmiller

#include "stdafx.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "structs.h"
#include <carbon_calc.h>
#include <carbon_ren.h>
#include <carbon_phys.h>
#include <carbon_sou.h>
#include <carbon_load.h>
#include <carbon_init.h>

int main(int argc, char* args[]) {
	SketchInit();
	SDL_Window* carbonwind = 0;
	SDL_Renderer* carbonrend = 0;
	SDL_Event carbonevent;
	srand(time(NULL));
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		carbonwind = SDL_CreateWindow("Carbon Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_FULLSCREEN);
		TTF_Init();
		if (carbonwind != 0) {
			carbonrend = SDL_CreateRenderer(carbonwind, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
		}
	}
	else {
		return 1;
	}
	SDL_Surface *cursorbmp = SDL_LoadBMP("textures/cursor.bmp");
	SDL_Cursor *cursor = SDL_CreateColorCursor(cursorbmp, 0, 0);
	SDL_SetCursor(cursor);
	SDL_Surface * image = SDL_LoadBMP("textures/background.bmp");
	SDL_Texture * texture = SDL_CreateTextureFromSurface(carbonrend, image);
	SDL_Rect rect;
	while (run) {
		clock_t bframe = clock();
		delta = FetchDelta(bframe);

		//
		//INPUT
		SDL_PollEvent(&carbonevent);
		GetCursorPos(&m);

		switch (carbonevent.type) {
		case SDL_KEYDOWN:
			keyboard[carbonevent.key.keysym.sym] = 1;
			break;
		case SDL_KEYUP:
			keyboard[carbonevent.key.keysym.sym] = 0;
			break;
		}
		if (carbonevent.type == SDL_MOUSEBUTTONDOWN) {
			if (carbonevent.button.button == SDL_BUTTON_LEFT) {
				m1 = true;
				GetCursorPos(&minit);
			}
			if (carbonevent.button.button == SDL_BUTTON_RIGHT) {
				m2 = true;
				GetCursorPos(&m2init);
			}
		}
		if (carbonevent.type == SDL_MOUSEBUTTONUP) {
			if (carbonevent.button.button == SDL_BUTTON_LEFT) {
				m1 = false;
			}
			if (carbonevent.button.button == SDL_BUTTON_RIGHT) {
				m2 = false;
			}
		}

		if (keyboard[SDLK_ESCAPE]) {
			run = false;
		}

		if (!keyboard[SDLK_UP]) {
			ureset = 1;
		}

		if (keyboard[SDLK_UP] && ureset) {
			ureset = 0;
			do {
				canfall = 0;
				for (int i = 0; i < 10; i++) {
					for (int j = 18; j > -1; j--) {
						if ((mtetrisgame.mino[i][j]) > 1 && (mtetrisgame.mino[i][j + 1] != 1)) {
							canfall++;
						}
					}
				}
				if (canfall == 4) {	//move block down
					for (int i = 0; i < 10; i++) {
						for (int j = 18; j > -1; j--) {
							if (mtetrisgame.mino[i][j] > 1) {
								mtetrisgame.mino[i][j + 1] = mtetrisgame.mino[i][j];
								mtetrisgame.mino[i][j] = 0;
							}
						}
					}
				}
				else {
					for (int i = 0; i < 10; i++) {
						for (int j = 19; j > -1; j--) {
							if (mtetrisgame.mino[i][j] > 1) {
								mtetrisgame.mino[i][j] = 1;
							}
						}
					}
					newpiece = 1;
				}
				upcheck = canfall;
			} while (upcheck == 4);
		}

		if (keyboard[SDLK_DOWN]) {
			timescale = 10000;
		}
		if (!keyboard[SDLK_DOWN] && !keyboard[SDLK_UP]) {
			timescale = 40000;
		}
		 
		if (!keyboard[SDLK_LEFT]) {
			lreset = 1;
		}

		if (keyboard[SDLK_LEFT] && lreset) {
			lreset = 0;
			canmove = 0;
			for (int i = 1; i < 10; i++) {
				for (int j = 19; j > 0; j--) {
					if ((mtetrisgame.mino[i][j]) > 1 && (mtetrisgame.mino[i-1][j] != 1)) {
						canmove++;
					}
				}
			}
			if (canmove == 4) {
				for (int i = 0; i < 10; i++) {
					for (int j = 19; j > 0; j--) {
						if (mtetrisgame.mino[i][j] > 1) {
							mtetrisgame.mino[i-1][j] = mtetrisgame.mino[i][j];
							mtetrisgame.mino[i][j] = 0;
						}
					}
				}
			}
		}

		if (!keyboard[SDLK_RIGHT]) {
			rreset = 1;
		}

		if (keyboard[SDLK_RIGHT] && rreset) {
			rreset = 0;
			canmove = 0;
			for (int i = 8; i > -1; i--) {
				for (int j = 19; j > 0; j--) {
					if ((mtetrisgame.mino[i][j]) > 1 && (mtetrisgame.mino[i + 1][j] != 1)) {
						canmove++;
					}
				}
			}
			if (canmove == 4) {
				for (int i = 8; i > -1; i--) {
					for (int j = 19; j > 0; j--) {
						if (mtetrisgame.mino[i][j] > 1) {
							mtetrisgame.mino[i + 1][j] = mtetrisgame.mino[i][j];
							mtetrisgame.mino[i][j] = 0;
						}
					}
				}
			}
		}

		if (!keyboard[SDLK_SPACE]) {
			rotreset = 1;
		}

		if (keyboard[SDLK_SPACE] && rotreset) {
			rotreset = 0;
			canmove = 0;
			minocounter = 0;

			if (currentpiece == 0) {

			} else {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 20; j++) {
						if (mtetrisgame.mino[i][j] == 3) {
							//found pivot point!
							pivot.u = i;
							pivot.v = j;
						}
					}
				}
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 20; j++) {
						if (mtetrisgame.mino[i][j] == 2) {
							site newpos; newpos.u = i; newpos.v = j;
							newpos = FetchRotation(pivot, pi / 2, newpos);
							newposu[minocounter] = newpos.u;
							newposv[minocounter] = newpos.v;
							if (newposu[minocounter] >= 0 && newposu[minocounter] < 10 && newposv[minocounter] >= 0 && newposv[minocounter] < 20) {
								if (mtetrisgame.mino[newposu[minocounter]][newposv[minocounter]] != 1) {
									canmove++;
								}
							}
							minocounter++;
						}				
					}
				}
				if (canmove == 3) {
					for (int i = 0; i < 10; i++) { //clear all twos
						for (int j = 0; j < 20; j++) {
							if (mtetrisgame.mino[i][j] == 2) {
								mtetrisgame.mino[i][j] = 0;
							}
						}
					}
					for (int i = 0; i < 3; i++) {
						mtetrisgame.mino[newposu[i]][newposv[i]] = 2;
					}
				}
			}
		}
		

		//
		//LOGIC
		tbucket += delta;
		if (tbucket > timescale && play) {
			//tetris clear
			for (int j = 0; j < 20; j++) {
				if ((mtetrisgame.mino[0][j] == 1) && (mtetrisgame.mino[1][j] == 1) && (mtetrisgame.mino[2][j] == 1) && (mtetrisgame.mino[3][j] == 1) && (mtetrisgame.mino[4][j] == 1) && (mtetrisgame.mino[5][j] == 1) && (mtetrisgame.mino[6][j] == 1) && (mtetrisgame.mino[7][j] == 1) && (mtetrisgame.mino[8][j] == 1) && (mtetrisgame.mino[9][j]) == 1) {
					mtetrisgame.mino[0][j] = 0;
					mtetrisgame.mino[1][j] = 0;
					mtetrisgame.mino[2][j] = 0;
					mtetrisgame.mino[3][j] = 0;
					mtetrisgame.mino[4][j] = 0;
					mtetrisgame.mino[5][j] = 0;
					mtetrisgame.mino[6][j] = 0;
					mtetrisgame.mino[7][j] = 0;
					mtetrisgame.mino[8][j] = 0;
					mtetrisgame.mino[9][j] = 0;
					score++;
					//move everything down
					
					for (int m = j; m > 0; m--) {
						for (int i = 0; i < 10; i++) {
							if (mtetrisgame.mino[i][m - 1] == 1) {
								mtetrisgame.mino[i][m] = 1;
							}
							else {
								if (mtetrisgame.mino[i][m - 1] == 0 && mtetrisgame.mino[i][m] == 1) {
									mtetrisgame.mino[i][m] = 0;
								}
							}
						}
					}
				}
			}
			
			//gravity for current piece
			canfall = 0;
			for (int i = 0; i < 10; i++) {
				for (int j = 18; j > -1; j--) {
					if ((mtetrisgame.mino[i][j]) > 1 && (mtetrisgame.mino[i][j+1] != 1)) {
						canfall++;
					}
				}
			}
			if (canfall == 4) {	//move block down
				for (int i = 0; i < 10; i++) {
					for (int j = 18; j > -1; j--) {
						if (mtetrisgame.mino[i][j] > 1) {
							mtetrisgame.mino[i][j + 1] = mtetrisgame.mino[i][j];
							mtetrisgame.mino[i][j] = 0;
							
						}
					}
				}
			}
			else {
				for (int i = 0; i < 10; i++) {
					for (int j = 19; j > -1; j--) {
						if (mtetrisgame.mino[i][j] > 1) {
							mtetrisgame.mino[i][j] = 1;
						}
					}
				}
				newpiece = 1;
			}
			
			//lose?
			for (int i = 0; i < 10; i++) {
				if (mtetrisgame.mino[i][0] == 1) {
					//play = false;
					//run = false;
				}
			}

			tbucket = 0;
		}


		
		if (newpiece) {
			currentpiece = floor(FetchRandomInt(0, 6));
			if (currentpiece == 0) {
				//spawn o
				mtetrisgame.mino[4][0] = 3;
				mtetrisgame.mino[5][0] = 2;
				mtetrisgame.mino[4][1] = 2;
				mtetrisgame.mino[5][1] = 2;
				newpiece = 0;
			}
			if (currentpiece == 1) {
				//spawn i
				mtetrisgame.mino[3][0] = 2;
				mtetrisgame.mino[4][0] = 2;
				mtetrisgame.mino[5][0] = 3;
				mtetrisgame.mino[6][0] = 2;
				newpiece = 0;
			}
			if (currentpiece == 2) {
				//spawn l
				mtetrisgame.mino[5][0] = 2;
				mtetrisgame.mino[5][1] = 2;
				mtetrisgame.mino[5][2] = 3;
				mtetrisgame.mino[6][2] = 2;
				newpiece = 0;
			}
			if (currentpiece == 3) {
				//spawn j
				mtetrisgame.mino[5][0] = 2;
				mtetrisgame.mino[5][1] = 2;
				mtetrisgame.mino[5][2] = 3;
				mtetrisgame.mino[4][2] = 2;
				newpiece = 0;
			}
			if (currentpiece == 4) {
				//spawn s
				mtetrisgame.mino[4][0] = 2;
				mtetrisgame.mino[5][0] = 3;
				mtetrisgame.mino[5][1] = 2;
				mtetrisgame.mino[6][1] = 2;
				newpiece = 0;
			}
			if (currentpiece == 5) {
				//spawn z
				mtetrisgame.mino[6][0] = 2;
				mtetrisgame.mino[5][0] = 2;
				mtetrisgame.mino[5][1] = 3;
				mtetrisgame.mino[4][1] = 2;
				newpiece = 0;
			}
			if (currentpiece == 6) {
				//spawn t
				mtetrisgame.mino[4][0] = 2;
				mtetrisgame.mino[5][0] = 3;
				mtetrisgame.mino[6][0] = 2;
				mtetrisgame.mino[5][1] = 2;
				newpiece = 0;
			}
		}




		//
		//CLEAR FRAME
		SDL_RenderCopy(carbonrend, texture, NULL, NULL);

		//
		//RENDER

		//draw the board
		SketchRenderRectangle(carbonrend, mtetrisgame.pos, mtetrisgame.bound, DWCOLO2);

		//go through each mino and draw it or don't
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 20; j++) {
				if (mtetrisgame.mino[i][j] == 1) {
					msite1.u = mtetrisgame.pos.u;
					msite1.v = mtetrisgame.pos.v;
					msite1.u += (i * mtetrisgame.minolength);
					msite1.v += (j * mtetrisgame.minoheight);
					msite2.u = msite1.u + mtetrisgame.minolength;
					msite2.v = msite1.v + mtetrisgame.minoheight;
					SketchRenderRectangle(carbonrend, msite1, msite2, DWCOLO3);
				}
				else if (mtetrisgame.mino[i][j] == 2) {
					msite1.u = mtetrisgame.pos.u;
					msite1.v = mtetrisgame.pos.v;
					msite1.u += (i * mtetrisgame.minolength);
					msite1.v += (j * mtetrisgame.minoheight);
					msite2.u = msite1.u + mtetrisgame.minolength;
					msite2.v = msite1.v + mtetrisgame.minoheight;
					SketchRenderRectangle(carbonrend, msite1, msite2, DWCOLO4);
				}
				else {
					if (mtetrisgame.mino[i][j] == 3) {
						msite1.u = mtetrisgame.pos.u;
						msite1.v = mtetrisgame.pos.v;
						msite1.u += (i * mtetrisgame.minolength);
						msite1.v += (j * mtetrisgame.minoheight);
						msite2.u = msite1.u + mtetrisgame.minolength;
						msite2.v = msite1.v + mtetrisgame.minoheight;
						SketchRenderRectangle(carbonrend, msite1, msite2, DWCOLO4);
					}
				}
			}
		}
		

		//
		//WINDOWS
		info = "FPS: " + to_string(int(fps_accepted));
		info += "&*";
		temp = to_string(trunc((1 / fps_accepted) * 10000) / 10);
		temp.erase(temp.find_first_of(".") + 2, 12);
		info += "RT: " + temp + " MS";
		info += "&*";
		SketchWindow(carbonrend, fpssite, "STATS", info);
		
		info = to_string(score);
		info += "&*";
		SketchWindow(carbonrend, scoresite, "SCORE", info);
		
		SDL_RenderPresent(carbonrend);
		carbonfps = FetchFPS(bframe);
		if (carbonfps != 9874555) {
			fps_accepted = carbonfps;
		}


		
		
	}
	SDL_DestroyRenderer(carbonrend);
	SDL_DestroyWindow(carbonwind);
	TTF_Quit();
	SDL_Quit();
	return 0;
}