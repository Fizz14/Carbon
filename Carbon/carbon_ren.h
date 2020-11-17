#pragma once

struct colo {
	byte r = 0;
	byte g = 0;
	byte b = 0;
	byte a = 255;
};

struct site {
	float u = 0;
	float v = 0;
};

struct vert {
	float x = 0;
	float y = 0;
	float z = 0;
};

struct vect {
	float x = 0;
	float y = 0;
	float z = 0;
};

struct tran {
	float x = 0;
	float y = 0;
	float z = 0;
	float rx = 0;
	float ry = 0;
	float rz = 0;
	float xs = 1;
	float ys = 1;
	float zs = 1;
};

tran cam;
float width = 1440;
float height = 900;
float pi = 3.141592654;

void SketchPixel(Uint32 * pixelsi, site s1, colo colori) {
	int x = s1.u; int y = s1.v;
	Uint32 ucolor = RGB(colori.b * colori.a, colori.g * colori.a, colori.r * colori.a);
	if (int((y * width) + x) < width * height) {
		if (int((y * width) + x) > 0) {
			if (s1.u > 0 && s1.u < width) {
				pixelsi[int((y * width) + x)] = ucolor;
			}
		}
	}
}

void SketchLine(Uint32 * pixelsi, site s1, site s2, colo colori) {
	float m = (s1.v - s2.v) / (s1.u - s2.u);
	float b = s1.v - (m * s1.u);
	float p;
	float k;
	float a = colori.a / 255;
	float dist = pow(double(pow((s1.u - s2.u), 2) + pow((s1.v - s2.v), 2)), 0.5);
	float step = abs((abs(s1.u - s2.u)) / dist);

	int xshift = 1;
	int yshift = 0;
	if (abs(s1.u - s2.u) > abs(s1.v - s2.v)) {
		xshift = 0;
		yshift = 1;
	}
	if (s1.u > s2.u) {
		float temp = s1.u;
		s1.u = s2.u;
		s2.u = temp;
	}
	if (s1.v > s2.v) {
		float temp = s1.v;
		s1.v = s2.v;
		s2.v = temp;
	}
	if (s1.u == s2.u && s1.v == s2.v) {
		SketchPixel(pixelsi, s1, colori);
	}
	else {
		if (s1.u == s2.u) {
			for (float i = s1.v; i < s2.v; ++i) {
				site res; res.u = s1.u; res.v = i;
				SketchPixel(pixelsi, res, colori);
			}
		}
		else {
			if (s1.v == s2.v) {
				for (float i = s1.u; i < s2.u; i += 1) {
					site res; res.u = i; res.v = s1.v;
					SketchPixel(pixelsi, res, colori);
				}
			}
			else {
				for (float i = s1.u; i < s2.u; i += step) {
					if (xshift == 1) {
						p = i - trunc(i);
					}
					else {
						p = (m*i + (s1.v - m * s1.u)) - (trunc(m*i + (s1.v - m * s1.u)));
					}
					p = p * 255;
					k = 255 - p;

					//colori.a = p;
					site res; res.u = i; res.v = (m * i) + b;
					SketchPixel(pixelsi, res, colori);
					//colori.a = k;
					//res.u = i + xshift; res.v = (m * i) + b + yshift;
					//SketchPixel(pixelsi, res, colori);
				}
			}
		}
	}
}


void SketchTriangle(Uint32 * pixelsi, site s1, site s2, site s3, colo colori, bool fill) {
	SketchLine(pixelsi, s1, s2, colori);
	SketchLine(pixelsi, s2, s3, colori);
	SketchLine(pixelsi, s3, s1, colori);
}

void SketchText(SDL_Renderer* rendi, site s1, string text) {
	TTF_Font * font = TTF_OpenFont("MODERNE SANS.ttf", 20);
	SDL_Color color = { 180, 180, 180 };
	SDL_Surface * surface;
	const char * ctext = text.c_str();
	surface = TTF_RenderText_Blended(font, ctext, color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(rendi, surface);
	SDL_Rect Message_rect;
	Message_rect.x = s1.u;
	Message_rect.y = s1.v;
	int w; int h;
	TTF_SizeText(font, ctext, &w, &h);
	Message_rect.w = w;
	Message_rect.h = h;
	SDL_RenderCopy(rendi, texture, NULL, &Message_rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void SketchHeaderText(SDL_Renderer* rendi, site s1, string text) {
	TTF_Font * font = TTF_OpenFont("MODERNE SANS.ttf", 60);
	SDL_Color color = { 200, 200, 200 };
	SDL_Surface * surface;
	const char * ctext = text.c_str();
	surface = TTF_RenderText_Blended(font, ctext, color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(rendi, surface);
	SDL_Rect Message_rect;
	Message_rect.x = s1.u;
	Message_rect.y = s1.v;
	int w; int h;
	TTF_SizeText(font, ctext, &w, &h);
	Message_rect.w = w;
	Message_rect.h = h;
	SDL_RenderCopy(rendi, texture, NULL, &Message_rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void SketchVectorDebug(SDL_Renderer* rendi, tran vect) {
	site s1; site s2; site s3; site s4; site s5; site s6;
	s1.u = 15; s2.u = 15; s3.u = 15; s4.u = 15; s5.u = 15; s6.u = 15;
	s1.v = 40; s2.v = 70; s3.v = 100; s4.v = 130; s5.v = 160; s6.v = 190;
	SketchText(rendi, s1, "SX: " + to_string(vect.x));
	SketchText(rendi, s2, "SY: " + to_string(vect.y));
	SketchText(rendi, s3, "SZ: " + to_string(vect.z));
	SketchText(rendi, s4, "RX: " + to_string(vect.rx));
	SketchText(rendi, s5, "RY: " + to_string(vect.ry));
	SketchText(rendi, s6, "RZ: " + to_string(vect.rz));
}

//sh$ shading types: 
//
//0- wireframe
//1- texture
//2- gorand
//3- phong
//4- normal + phong + texture
//5- normal + phong + texture + shadow

site FetchVertex(vert a, tran mycam, int fov) {
	float x = a.x - mycam.x;
	float y = a.y - mycam.y;
	float z = a.z - mycam.z;

	vect d;

	mycam.rx = pi;

	float cx = cos(mycam.rx);
	float cy = cos(mycam.ry);
	float cz = cos(mycam.rz);

	float sx = sin(mycam.rx);
	float sy = sin(mycam.ry);
	float sz = sin(mycam.rz);

	d.x = (cy * ((sz * y) + (cz * x))) - (sy * z);
	d.y = (sx * ((cy * z) + (sy * ((sz * y) + (cz * x))))) + (cx * ((cz * y) - (sz * x)));
	d.z = (cx * ((cy * z) + (sy * ((sz * y) + (cz * x))))) - (sx * ((cz * y) - (sz * x)));

	//float e = 1 / (tan(fov / 2));
	float e = 0.7;
	site res;

	if (d.z == 0) {
		d.z = 0.00001;
	}

	res.u = int(((e / d.z) * d.x + 0.5) * 144000) / 100;
	res.v = int(((e / d.z) * d.y + 0.5) * 144000) / 100;
	return res;
}

void SketchPoly(Uint32 * pixelsi, vert a, vert b, vert c, tran mycam, int fov) {
	site sa = FetchVertex(a, mycam, fov);
	site sb = FetchVertex(b, mycam, fov);
	site sc = FetchVertex(c, mycam, fov);
	colo colorref; colorref.a = 255; colorref.r = 255;
	SketchTriangle(pixelsi, sa, sb, sc, colorref, true);
}


