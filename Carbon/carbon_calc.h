#pragma once


clock_t current_ticks, delta_ticks;
clock_t fps = 0;
clock_t deltaTime = 0;
float frames = 0;
float frameRate = 30;

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

double FetchRandom(float minimum, float maximum) {
	double r;
	r = ((double)rand() / (RAND_MAX)) + 1;
	r = r * maximum;
	r = r + minimum;
	return r;
}