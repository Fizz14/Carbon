#include "stdafx.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <carbon_calc.h>
#include <carbon_ren.h>

SDL_Window* carbonwind = 0;
SDL_Renderer* carbonrend = 0;

////////////////////////
//TEMP
////////////////////////
float increment = 0;
vert v1; vert v2; vert v3; vert v4; vert v5; vert v6; vert v7; vert v8;
float scale = 8;
////

///////////////////////
//PERM
///////////////////////
map<int, bool> keyboard;
float uvelo = 0;
float vvelo = 0;
float oldmouseX;
float oldmouseY;
float mouseX = 0;
float mouseY = 0;
float carbonfps;
float fps_accepted;
site fpssite;
Uint32 * pixels = new Uint32[width * height];
float camrspd = 0.0001;
float camspd = 0.1;
bool run = true;
bool drag = false;
////

int main(int argc, char* args[]) {

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	site mys1; site mys2; site mys3; site mys4; site mys5; site mys6; site mys7; site mys8;
	//Hard-coded Cube

	v1.x = scale, v1.y = -scale; v1.z = scale;
	v2.x = scale, v2.y = scale; v2.z = scale;
	v3.x = -scale, v3.y = scale; v3.z = scale;
	v4.x = -scale, v4.y = -scale; v4.z = scale;
	v5.x = scale, v5.y = -scale; v5.z = -scale;
	v6.x = scale, v6.y = scale; v6.z = -scale;
	v7.x = -scale, v7.y = scale; v7.z = -scale;
	v8.x = -scale, v8.y = -scale; v8.z = -scale;
	fpssite.u = 15; fpssite.v = 15;
	cam.z = -40;

	colo colorref; colorref.r = 180; colorref.g = 180; colorref.b = 180; colorref.a = 255;
	SDL_Event carbonevent;
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		carbonwind = SDL_CreateWindow("Carbon Renderer", 0, 0, width, height, 0);
		TTF_Init();
		if (carbonwind != 0) {
			carbonrend = SDL_CreateRenderer(carbonwind, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
		}
	}
	else {
		return 1;
	}
	SDL_Texture * memframe = SDL_CreateTexture(carbonrend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
	SDL_SetRenderDrawBlendMode(carbonrend, SDL_BLENDMODE_BLEND);

	while (run) {
		clock_t bframe = clock();

		//input

		SDL_PollEvent(&carbonevent);
		switch (carbonevent.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (drag == false) {
				oldmouseX = carbonevent.motion.x;
				oldmouseY = carbonevent.motion.y;
				drag = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			uvelo = 0;
			vvelo = 0;
			drag = false;
			break;
		case SDL_MOUSEMOTION:
			if (drag) {
				mouseX = carbonevent.motion.x;
				mouseY = carbonevent.motion.y;
				uvelo = mouseX - oldmouseX;
				vvelo = mouseY - oldmouseY;
			}
			break;
		case SDL_KEYDOWN:
			keyboard[carbonevent.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			keyboard[carbonevent.key.keysym.sym] = false;
			break;
		}
		if (keyboard[SDLK_ESCAPE]) {
			run = false;
		}
		if (keyboard[SDLK_w]) {
			cam.y -= camspd * sin(cam.rz + (pi / 2));
			cam.x -= camspd * cos(cam.rz + (pi / 2));
		}
		if (keyboard[SDLK_s]) {
			cam.y += camspd * sin(cam.rz + (pi / 2));
			cam.x += camspd * cos(cam.rz + (pi / 2));
		}
		if (keyboard[SDLK_a]) {
			cam.y += camspd * sin(cam.rz);
			cam.x += camspd * cos(cam.rz);
		}
		if (keyboard[SDLK_d]) {
			cam.y -= camspd * sin(cam.rz);
			cam.x -= camspd * cos(cam.rz);
		}

		if (keyboard[SDLK_UP]) {

		}
		if (keyboard[SDLK_DOWN]) {

		}
		if (keyboard[SDLK_LEFT]) {
			cam.ry += camrspd * sin(cam.rz) * vvelo;
			cam.rx += camrspd * cos(cam.rz) * vvelo;
		}
		if (keyboard[SDLK_RIGHT]) {
			cam.ry -= camrspd * sin(cam.rz) * vvelo;
			cam.rx -= camrspd * cos(cam.rz) * vvelo;
		}

		//Background
		cam.ry += camrspd * sin(cam.rz) * vvelo;
		cam.rx += camrspd * cos(cam.rz) * vvelo;
		//cam.rz += camrspd * uvelo;
		memset(pixels, 25, width* height * sizeof(Uint32));


		//Draw calls
		mys1 = FetchVertex(v1, cam, 103);
		mys2 = FetchVertex(v2, cam, 103);
		mys3 = FetchVertex(v3, cam, 103);
		mys4 = FetchVertex(v4, cam, 103);
		mys5 = FetchVertex(v5, cam, 103);
		mys6 = FetchVertex(v6, cam, 103);
		mys7 = FetchVertex(v7, cam, 103);
		mys8 = FetchVertex(v8, cam, 103);

		SketchLine(pixels, mys1, mys2, colorref);
		SketchLine(pixels, mys2, mys3, colorref);
		SketchLine(pixels, mys3, mys4, colorref);
		SketchLine(pixels, mys4, mys1, colorref);
		SketchLine(pixels, mys5, mys6, colorref);
		SketchLine(pixels, mys6, mys7, colorref);
		SketchLine(pixels, mys7, mys8, colorref);
		SketchLine(pixels, mys8, mys5, colorref);
		SketchLine(pixels, mys1, mys5, colorref);
		SketchLine(pixels, mys2, mys6, colorref);
		SketchLine(pixels, mys3, mys7, colorref);
		SketchLine(pixels, mys4, mys8, colorref);

		SDL_RenderCopy(carbonrend, memframe, NULL, NULL);

		//Text Calls
		SketchText(carbonrend, fpssite, "FPS: " + to_string(int(fps_accepted)));
		if (carbonfps != 9874555) {
			fps_accepted = carbonfps;
		}
		SketchVectorDebug(carbonrend, cam);

		//Draw
		SDL_UpdateTexture(memframe, NULL, pixels, width * sizeof(Uint32));
		SDL_RenderPresent(carbonrend);

		//frame updates
		carbonfps = FetchFPS(bframe);
	}
	delete[] pixels;
	SDL_DestroyTexture(memframe);
	SDL_DestroyRenderer(carbonrend);
	SDL_DestroyWindow(carbonwind);
	TTF_Quit();
	SDL_Quit();
	return 0;
}