#pragma once



struct mbyte {
	bool bit[8] = { 0 };
};

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

struct plot {
	site sarr[128] = {10};
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

struct edge {
	int vr1;
	int vr2;
};

struct face {
	int vr1;
	int vr2;
	int vr3;
	vert c;
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

struct tricord {
	site s1;
	site s2;
	site s3;
};

struct quadvect {
	vect v1;
	vect v2;
	vect v3;
	vect v4;
};

struct mesh {
	string ref;
	byte sh$;
	vert varr[1000] = { 0 };
	site sarr[1000] = { 0 };
	face farr[1000] = { 0 };
	vect vnarr[1000] = { 0 };
	quadvect fnarr[1000] = { 0 };
	site tcarr[1000] = { 0 };
	tricord carr[1000] = { 0 };
	float distarr[1000] = { 0 };
};

struct light {
	vect rad;
	byte stren;
	byte size;
	byte ambstren;
};