#pragma once

tran cam;
light sun;
clock_t current_ticks, delta_ticks;
clock_t fps = 0;
clock_t deltaTime = 0;
float frames = 0;
float frameRate = 30;

float FetchHighest(float f1, float f2, float f3) {
	if (f1 > f2) {
		if (f1 > f3) {
			return f1;
		}
		else {
			return f3;
		}
	}
	else {
		if (f2 > f3) {
			return f2;
		}
		return f3;
	}
}

float FetchLowest(float f1, float f2, float f3) {
	if (f1 < f2) {
		if (f1 < f3) {
			return f1;
		}
		else {
			return f3;
		}
	}
	else {
		if (f2 < f3) {
			return f2;
		}
		return f3;
	}
}

float FetchNeither(float f1, float f2, float f3) {
	float not1 = FetchHighest(f1, f2, f3);		float not2 = FetchLowest(f1, f2, f3);
	if (f1 != not1 && f1 != not2) {
		return f1;
	}
	else if (f2 != not1 && f2 != not2) {
		return f2;
	}
	else if (f3 != not1 && f3 != not2) {
		return f3;
	}
}

float FetchDistance(vert v1, vert v2) {
	float ret;
	ret = pow(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2), 0.5);
	return ret;
}

float FetchCDistance(vect v1, vect v2) {
	float ret;
	ret = pow(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2), 0.5);
	return ret;
}

float FetchDistanceToCamera(vert v1) {
	float ret;
	ret = pow(pow(v1.x - cam.x, 2) + pow(v1.y - cam.y, 2) + pow(v1.z - cam.z, 2), 0.5);
	return ret;
}

float FetchVectorMagnitude(vect v1) {
	float ret;
	ret = pow(pow(v1.x, 2) + pow(v1.y, 2) + pow(v1.z, 2), 0.5);
	return ret;
}

float dot(vect v1, vect v2) {
	float ret;
	float theta;
	float a = FetchVectorMagnitude(v1);
	float b = FetchVectorMagnitude(v2);
	float c = FetchCDistance(v1, v2);
	ret = a * b * ((pow(c, 2) - pow(a, 2) - pow(b, 2)) / (2 * a*b));
	return ret;
}

float FetchVectorAngle(vect v1, vect v2) {
	float a = FetchVectorMagnitude(v1);
	float b = FetchVectorMagnitude(v2);
	return acos(dot(v1, v2) / (a * b));
}

float FetchVectorAgreement(vect v1, vect v2) {
	float a = FetchVectorMagnitude(v1);
	float b = FetchVectorMagnitude(v2);
	return dot(v1, v2) / (a * b);
}

float FetchLighting(vect v1, light sun) {
	float ret = FetchVectorAgreement(v1, sun.rad);
	float sizef = sun.size;
	sizef = (sizef / 64) - 2;
	//if size is 255, move -1 -> 1 to 0 -> 1; add 1, divide by 2
	ret = (ret + sizef) / (sizef + 1);
	sizef = sun.stren;
	ret *= sizef / 64;
	if (ret > 1) {
		ret = 1;
	}
	else {
		float lim = sun.ambstren;
		lim /= 255;
		if (ret < lim) {
			ret = lim;
		}
	}
	return ret;
}

vect NormalizeVector(vect v1) {
	float mag = FetchVectorMagnitude(v1);
	v1.x = v1.x / mag;
	v1.y = v1.y / mag;
	v1.z = v1.z / mag;
	return v1;
}

double c_ms(clock_t ticks) {
	return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;
}

float FetchFPS(clock_t bFramei) {
	clock_t eFrame = clock();
	deltaTime += eFrame - bFramei;
	frames++;
	if (c_ms(deltaTime) > 1000.0) {
		frameRate = (float)frames * 0.5 + frameRate * 0.5;
		frames = 0;
		deltaTime -= CLOCKS_PER_SEC;
		return frameRate;
	}
	else {
		return 9874555;
	}
}

float FetchDelta(clock_t bFramei) {
	clock_t eFrame = clock();
	deltaTime += eFrame - bFramei;
	if (c_ms(deltaTime) > 1000.0) {
		deltaTime -= CLOCKS_PER_SEC;
	}
	return deltaTime;
}

double FetchRandom(float min, float max) {
	double r;
	r = ((double)rand() / (RAND_MAX)) + 1;
	r = r * max;
	r = r + min;
	return r;

}

site FetchRotation(site c, float angle, site p)
{
	float sind = sin(angle);
	float cosd = cos(angle);

	// translate point back to origin:
	p.u -= c.u;
	p.v -= c.v;

	// rotate point
	float xnew = p.u * cosd - p.v * sind;
	float ynew = p.u * sind + p.v * cosd;

	// translate point back:
	p.u = xnew + c.u;
	p.v = ynew + c.v;
	return p;
}

int FetchRandomInt(int min, int max) {
	int r = (rand() % (max + 1 - min)) + min;
	return r;
}

float FetchLerp(float current, float start, float dest, int steps) {
	current += (dest - start) / steps;
	return current;
}

void memset32(void * dest, uint64_t value, uintptr_t size) {
	uintptr_t i;
	for (i = 0; i < (size & (~3)); i += 4) {
		memcpy(((char*)dest) + i, &value, 4);
	}
}