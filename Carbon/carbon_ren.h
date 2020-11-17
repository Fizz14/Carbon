#pragma once

float width = 1440;
float height = 900;
float pi = 3.141592654;

float FetchHighest(float f1, float f2, float f3) {
	if (f1 > f2) {
		if (f1 > f3) {
			return f1;
		} else {
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
		}else {
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
	float not1 = FetchHighest(f1, f2, f3);
	float not2 = FetchLowest(f1, f2, f3);
	if (f1 != not1 && f1 != not2) {
		return f1;
	}
	else if (f2 != not1 && f2 != not2){
		return f2;
	}
	else if (f3 != not1 && f3 != not2) {
		return f3;
	}
}

Uint32 coloToUint(colo colori) {

	float srcr = colori.r;
	float srcg = colori.g;
	float srcb = colori.b;

	srcr /= 255;
	srcg /= 255;
	srcb /= 255;

	float alpha = colori.a;
	alpha = alpha / 255;
	float alphainv = 1 - alpha;
	srcr = ((alphainv * 0.121) + (alpha * srcr)) * 255;
	srcg = ((alphainv * 0.149) + (alpha * srcg)) * 255;
	srcb = ((alphainv * 0.164) + (alpha * srcb)) * 255;
	
	return RGB((int)srcr, (int)srcg, (int)srcb);
}

void SketchPixelAlpha(Uint32 * pixelsi, site s1, colo colori) {
	Uint32 ucolor = coloToUint(colori);
	int x = s1.u; int y = s1.v;
	if (int((y * width) + x) < width * height) {
		if (int((y * width) + x) > 0) {
			if (s1.u > 0 && s1.u < width) {
				pixelsi[int((y * width) + x)] = ucolor;
			}
		}
	}
}

void SketchSystemPixel(SDL_Renderer* rendi, site s1, colo colori) {
	SDL_SetRenderDrawColor(rendi, colori.r, colori.g, colori.b, colori.a);
	SDL_RenderDrawPoint(rendi, s1.u, s1.v);
}

void SketchSystemLine(SDL_Renderer* rendi, site s1, site s2, colo colori) {
	SDL_SetRenderDrawColor(rendi, colori.r, colori.g, colori.b, colori.a);
	SDL_RenderDrawLine(rendi, s1.u, s1.v, s2.u, s2.v);
}

void SketchText(SDL_Renderer* rendi, site s1, string text) {
	TTF_Font * font = TTF_OpenFont("MODERNE SANS.ttf", 14);
	SDL_Color color = { 207, 203, 203 };
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


void SketchRenderTriangle(SDL_Renderer* rendi, site s1, site s2, site s3, colo colori, bool fill) {
	if (fill) {
		site mys1;
		site mys2;
		site p1;
		site p2;
		site p3;
		//sort points in order of height
		
		//is 3 right?
		bool hko = (s1.v == s3.v && s2.u == s3.u && s2.v < s3.v && s1.u != s3.u);
		bool hkt = (s2.v == s3.v && s1.u == s3.u && s1.v < s3.v && s2.u != s3.u);

		//is 2 right?
		bool tko = (s2.v == s1.v && s3.u == s2.u && s3.v < s2.v && s1.u != s2.u);
		bool tkt = (s2.v == s3.v && s1.u == s2.u && s1.v < s2.v && s3.u != s2.u);
			
		//is 1 right?
		bool oko = (s1.v == s2.v && s3.u == s1.u && s3.v < s1.v && s1.u != s2.u);
		bool okt = (s1.v == s3.v && s2.u == s1.u && s2.v < s1.v && s1.u != s3.u);

		//for three:
		if (hko || hkt) {
			
			p1 = s1;
			p2 = s2;
			p3 = s3;

			float m12 = (p1.v - p2.v) / (p1.u - p2.u);
			float b12 = (p1.v) - (m12 * p1.u);

			for (float i = (p2.v + p1.v - p3.v); i < p3.v; i++) {
				mys2.u = (i - b12) / m12;

				mys1.u = p3.u;

				mys1.v = i;
				mys2.v = i;
				SketchSystemLine(rendi, mys1, mys2, colori);
			}
			
			
		} else { //for two:
			if (tko || tkt) {
				
				p1 = s1;
				p2 = s3;
				p3 = s2;

				float m12 = (p1.v - p2.v) / (p1.u - p2.u);
				float b12 = (p1.v) - (m12 * p1.u);

				for (float i = (p2.v + p1.v - p3.v); i < p3.v; i++) {
					mys2.u = (i - b12) / m12;

					mys1.u = p3.u;

					mys1.v = i;
					mys2.v = i;
					SketchSystemLine(rendi, mys1, mys2, colori);
				}
			} else {//for one:
				if (hko || hkt) {
					
					p1 = s3;
					p2 = s2;
					p3 = s1;

					float m12 = (p1.v - p2.v) / (p1.u - p2.u);
					float b12 = (p1.v) - (m12 * p1.u);

					for (float i = (p2.v + p1.v - p3.v); i < p3.v; i++) {
						mys2.u = (i - b12) / m12;

						mys1.u = p3.u;

						mys1.v = i;
						mys2.v = i;
						SketchSystemLine(rendi, mys1, mys2, colori);
					}
				
				
				}else {
				if (s1.v < s2.v && s1.v < s3.v) {
					p1 = s1;

					if (s2.v < s3.v) {
						p2 = s2;
						p3 = s3;
					}
					else if (s3.v < s2.v) {
						p2 = s3;
						p3 = s2;
					}
				}
				else {
					if (s2.v < s1.v && s2.v < s3.v) {
						p1 = s2;
						if (s1.v < s3.v) {
							p2 = s1;
							p3 = s3;
						}
						else if (s3.v < s1.v) {
							p2 = s3;
							p3 = s1;
						}
					}
					else {
						if (s3.v < s1.v && s3.v < s2.v) {
							p1 = s3;
							if (s1.v < s2.v) {
								p2 = s1;
								p3 = s2;
							}
							else if (s2.v < s1.v) {
								p2 = s2;
								p3 = s1;
							}
						}
					}
				}
				//if two are equal, make those two p1 and p2
				if (s1.v == s2.v) {
					p1 = s1;
					p2 = s2;
					p3 = s3;
				}
				else {
					if (s1.v == s3.v) {
						p1 = s1;
						p2 = s3;
						p3 = s2;
					}
					else {
						if (s3.v == s2.v) {
							p1 = s2;
							p2 = s3;
							p3 = s1;
						}
					}
				}

				float m31 = (p1.v - p3.v) / (p1.u - p3.u);
				float b31 = (p1.v) - (m31 * p1.u);

				float m12 = (p1.v - p2.v) / (p1.u - p2.u);
				float b12 = (p1.v) - (m12 * p1.u);

				float m23 = (p2.v - p3.v) / (p2.u - p3.u);
				float b23 = (p2.v) - (m23 * p2.u);

				//broad case
				if (s1.v != s2.v && s2.v != s3.v && s3.v != s1.v) {
					for (float i = p1.v; i < p2.v; i++) {
						if (p2.u == p1.u) {
							mys2.u = p1.u;
						}
						else {
							mys2.u = (i - b12) / m12;
						}
						if (p1.u == p3.u) {
							mys1.u = p1.u;
						}
						else {
							mys1.u = (i - b31) / m31;
						}
						mys1.v = i;
						mys2.v = i;
						SketchSystemLine(rendi, mys1, mys2, colori);
					}
					for (float i = p2.v; i < p3.v; i++) {
						if (p2.u == p3.u) {
							mys2.u = p3.u;
						}
						else {
							mys2.u = (i - b23) / m23;
						}
						if (p1.u == p3.u) {
							mys1.u = p1.u;
						}
						else {
							mys1.u = (i - b31) / m31;
						}
						mys1.v = i;
						mys2.v = i;
						SketchSystemLine(rendi, mys1, mys2, colori);
					}
				}
				else {
					if (p3.v > p1.v) {
						for (float i = p1.v; i < p3.v; i++) {
							if (p1.u == p3.u) {
								mys2.u = p3.u;
							}
							else {
								mys2.u = (i - b31) / m31;
							}
							if (p2.u == p3.u) {
								mys1.u = p2.u;
							}
							else {
								mys1.u = (i - b23) / m23;
							}
							mys1.v = i;
							mys2.v = i;
							SketchSystemLine(rendi, mys1, mys2, colori);
						}
					}
					else {
						if (p3.v < p1.v) {
							for (int i = p3.v; i < p1.v; i++) {
								if (p1.u == p3.u) {
									mys2.u = p3.u;
								}
								else {
									mys2.u = (i - b31) / m31;
								}
								if (p2.u == p3.u) {
									mys1.u = p1.u;
								}
								else {
									mys1.u = (i - b23) / m23;
								}
								mys1.v = i;
								mys2.v = i;
								SketchSystemLine(rendi, mys1, mys2, colori);
							}
						}
					}
				}
				}
			}
		}	
	} else {
	SketchSystemLine(rendi, s1, s2, colori);
	SketchSystemLine(rendi, s2, s3, colori);
	SketchSystemLine(rendi, s3, s1, colori);
	}
}


colo FetchInterp(float dist1, float dist2, float dist3, colo color1, colo color2, colo color3) {
	float tot = dist1 + dist2 + dist3;

	float t1; float t2; float t3;

	t1 = (dist2 + dist3) / tot;
	t2 = (dist1 + dist3) / tot;
	t3 = (dist1 + dist2) / tot;

	t1 = pow(t1, 1);
	t2 = pow(t2, 1);
	t3 = pow(t3, 1);


	colo colori;
	colori.r = (color1.r * (t1)) + (color2.r * (t2)) + (color3.r * (t3));
	colori.g = (color1.g * (t1)) + (color2.g * (t2)) + (color3.g * (t3));
	colori.b = (color1.b * (t1)) + (color2.b * (t2)) + (color3.b * (t3));

	return colori;
}

void SketchRenderBITriangle(SDL_Renderer* rendi, site s1, site s2, site s3, colo color1, colo color2, colo color3) {
	site mys1;
	site mys2;
	site p1;
	site p2;
	site p3;

	//is 3 right?
	bool hko = (s1.v == s3.v && s2.u == s3.u && s2.v < s3.v && s1.u != s3.u);
	bool hkt = (s2.v == s3.v && s1.u == s3.u && s1.v < s3.v && s2.u != s3.u);

	//is 2 right?
	bool tko = (s2.v == s1.v && s3.u == s2.u && s3.v < s2.v && s1.u != s2.u);
	bool tkt = (s2.v == s3.v && s1.u == s2.u && s1.v < s2.v && s3.u != s2.u);
	
	//is 1 right?
	bool oko = (s1.v == s2.v && s3.u == s1.u && s3.v < s1.v && s1.u != s2.u);
	bool okt = (s1.v == s3.v && s2.u == s1.u && s2.v < s1.v && s1.u != s3.u);

	//for three:
	if (hko || hkt) {

		p1 = s1;
		p2 = s2;
		p3 = s3;

		float m12 = (p1.v - p2.v) / (p1.u - p2.u);
		float b12 = (p1.v) - (m12 * p1.u);

			for (float i = (p2.v + p1.v - p3.v); i < p3.v; i++) {
				mys2.u = (i - b12) / m12;
				mys1.u = p3.u;

				if (mys2.u < mys1.u) {
					for (int j = mys2.u; j < mys1.u; j++) {
						site res; res.u = j; res.v = i;

						float dist1; float dist2; float dist3;
						dist1 = pow(pow(s1.u - j, 2) + pow(s1.v - i, 2), 0.5);
						dist2 = pow(pow(s2.u - j, 2) + pow(s2.v - i, 2), 0.5);
						dist3 = pow(pow(s3.u - j, 2) + pow(s3.v - i, 2), 0.5);

						colo colori = FetchInterp(dist1, dist2, dist3, color1, color2, color3);
						
						SketchSystemPixel(rendi, res, colori);
					}
				}
				else {
					for (int j = mys1.u; j < mys2.u; j++) {
						site res; res.u = j; res.v = i;
						float dist1; float dist2; float dist3;
						dist1 = pow(pow(s1.u - j, 2) + pow(s1.v - i, 2), 0.5);
						dist2 = pow(pow(s2.u - j, 2) + pow(s2.v - i, 2), 0.5);
						dist3 = pow(pow(s3.u - j, 2) + pow(s3.v - i, 2), 0.5);

						colo colori = FetchInterp(dist1, dist2, dist3, color1, color2, color3);

						SketchSystemPixel(rendi, res, colori);
					}
				}
			}
		}
		else { //for two:
			if (tko || tkt) {

				p1 = s1;
				p2 = s3;
				p3 = s2;

				float m12 = (p1.v - p2.v) / (p1.u - p2.u);
				float b12 = (p1.v) - (m12 * p1.u);

				for (float i = (p2.v + p1.v - p3.v); i < p3.v; i++) {
					mys2.u = (i - b12) / m12;

					mys1.u = p3.u;

					if (mys2.u < mys1.u) {
						for (int j = mys2.u; j < mys1.u; j++) {
							site res; res.u = j; res.v = i;
							float dist1; float dist2; float dist3;
							dist1 = pow(pow(s1.u - j, 2) + pow(s1.v - i, 2), 0.5);
							dist2 = pow(pow(s2.u - j, 2) + pow(s2.v - i, 2), 0.5);
							dist3 = pow(pow(s3.u - j, 2) + pow(s3.v - i, 2), 0.5);

							colo colori = FetchInterp(dist1, dist2, dist3, color1, color2, color3);

							SketchSystemPixel(rendi, res, colori);
						}
					}
					else {
						for (int j = mys1.u; j < mys2.u; j++) {
							site res; res.u = j; res.v = i;
							float dist1; float dist2; float dist3;
							dist1 = pow(pow(s1.u - j, 2) + pow(s1.v - i, 2), 0.5);
							dist2 = pow(pow(s2.u - j, 2) + pow(s2.v - i, 2), 0.5);
							dist3 = pow(pow(s3.u - j, 2) + pow(s3.v - i, 2), 0.5);

							colo colori = FetchInterp(dist1, dist2, dist3, color1, color2, color3);

							SketchSystemPixel(rendi, res, colori);
						}
					}
				}
			}
			else {//for one:
				if (hko || hkt) {

					p1 = s3;
					p2 = s2;
					p3 = s1;

					float m12 = (p1.v - p2.v) / (p1.u - p2.u);
					float b12 = (p1.v) - (m12 * p1.u);

					for (float i = (p2.v + p1.v - p3.v); i < p3.v; i++) {
						mys2.u = (i - b12) / m12;

						mys1.u = p3.u;

						if (mys2.u < mys1.u) {
							for (int j = mys2.u; j < mys1.u; j++) {
								site res; res.u = j; res.v = i;
								float dist1; float dist2; float dist3;
								dist1 = pow(pow(s1.u - j, 2) + pow(s1.v - i, 2), 0.5);
								dist2 = pow(pow(s2.u - j, 2) + pow(s2.v - i, 2), 0.5);
								dist3 = pow(pow(s3.u - j, 2) + pow(s3.v - i, 2), 0.5);

								colo colori = FetchInterp(dist1, dist2, dist3, color1, color2, color3);

								SketchSystemPixel(rendi, res, colori);
							}
						}
						else {
							for (int j = mys1.u; j < mys2.u; j++) {
								site res; res.u = j; res.v = i;
								float dist1; float dist2; float dist3;
								dist1 = pow(pow(s1.u - j, 2) + pow(s1.v - i, 2), 0.5);
								dist2 = pow(pow(s2.u - j, 2) + pow(s2.v - i, 2), 0.5);
								dist3 = pow(pow(s3.u - j, 2) + pow(s3.v - i, 2), 0.5);

								colo colori = FetchInterp(dist1, dist2, dist3, color1, color2, color3);

								SketchSystemPixel(rendi, res, colori);
							}
						}
					}


				}
				else {
					if (s1.v < s2.v && s1.v < s3.v) {
						p1 = s1;

						if (s2.v < s3.v) {
							p2 = s2;
							p3 = s3;
						}
						else if (s3.v < s2.v) {
							p2 = s3;
							p3 = s2;
						}
					}
					else {
						if (s2.v < s1.v && s2.v < s3.v) {
							p1 = s2;
							if (s1.v < s3.v) {
								p2 = s1;
								p3 = s3;
							}
							else if (s3.v < s1.v) {
								p2 = s3;
								p3 = s1;
							}
						}
						else {
							if (s3.v < s1.v && s3.v < s2.v) {
								p1 = s3;
								if (s1.v < s2.v) {
									p2 = s1;
									p3 = s2;
								}
								else if (s2.v < s1.v) {
									p2 = s2;
									p3 = s1;
								}
							}
						}
					}
					//if two are equal, make those two p1 and p2
					if (s1.v == s2.v) {
						p1 = s1;
						p2 = s2;
						p3 = s3;
					}
					else {
						if (s1.v == s3.v) {
							p1 = s1;
							p2 = s3;
							p3 = s2;
						}
						else {
							if (s3.v == s2.v) {
								p1 = s2;
								p2 = s3;
								p3 = s1;
							}
						}
					}

					float m31 = (p1.v - p3.v) / (p1.u - p3.u);
					float b31 = (p1.v) - (m31 * p1.u);

					float m12 = (p1.v - p2.v) / (p1.u - p2.u);
					float b12 = (p1.v) - (m12 * p1.u);

					float m23 = (p2.v - p3.v) / (p2.u - p3.u);
					float b23 = (p2.v) - (m23 * p2.u);

					//broad case
					if (s1.v != s2.v && s2.v != s3.v && s3.v != s1.v) {
						for (float i = p1.v; i < p2.v; i++) {
						if (p2.u == p1.u) {
							mys2.u = p1.u;
						}
						else {
							mys2.u = (i - b12) / m12;
						}
						if (p1.u == p3.u) {
							mys1.u = p1.u;
						}
						else {
							mys1.u = (i - b31) / m31;
						}
						if (mys2.u < mys1.u) {
							for (int j = mys2.u; j < mys1.u; j++) {
								site res; res.u = j; res.v = i;
								float dist1; float dist2; float dist3;
								dist1 = pow(pow(s1.u - j, 2) + pow(s1.v - i, 2), 0.5);
								dist2 = pow(pow(s2.u - j, 2) + pow(s2.v - i, 2), 0.5);
								dist3 = pow(pow(s3.u - j, 2) + pow(s3.v - i, 2), 0.5);

								colo colori = FetchInterp(dist1, dist2, dist3, color1, color2, color3);

								SketchSystemPixel(rendi, res, colori);
							}
						}
						else {
							for (int j = mys1.u; j < mys2.u; j++) {
								site res; res.u = j; res.v = i;
								float dist1; float dist2; float dist3;
								dist1 = pow(pow(s1.u - j, 2) + pow(s1.v - i, 2), 0.5);
								dist2 = pow(pow(s2.u - j, 2) + pow(s2.v - i, 2), 0.5);
								dist3 = pow(pow(s3.u - j, 2) + pow(s3.v - i, 2), 0.5);

								colo colori = FetchInterp(dist1, dist2, dist3, color1, color2, color3);

								SketchSystemPixel(rendi, res, colori);
							}
						}
					}
					for (float i = p2.v; i < p3.v; i++) {
						if (p2.u == p3.u) {
							mys2.u = p3.u;
						}
						else {
							mys2.u = (i - b23) / m23;
						}
						if (p1.u == p3.u) {
							mys1.u = p1.u;
						}
						else {
							mys1.u = (i - b31) / m31;
						}


						if (mys2.u < mys1.u) {
							for (int j = mys2.u; j < mys1.u; j++) {
								site res; res.u = j; res.v = i;
								float dist1; float dist2; float dist3;
								dist1 = pow(pow(s1.u - j, 2) + pow(s1.v - i, 2), 0.5);
								dist2 = pow(pow(s2.u - j, 2) + pow(s2.v - i, 2), 0.5);
								dist3 = pow(pow(s3.u - j, 2) + pow(s3.v - i, 2), 0.5);

								colo colori = FetchInterp(dist1, dist2, dist3, color1, color2, color3);

								SketchSystemPixel(rendi, res, colori);
							}
						}
						else {
							for (int j = mys1.u; j < mys2.u; j++) {
								site res; res.u = j; res.v = i;
								float dist1; float dist2; float dist3;
								dist1 = pow(pow(s1.u - j, 2) + pow(s1.v - i, 2), 0.5);
								dist2 = pow(pow(s2.u - j, 2) + pow(s2.v - i, 2), 0.5);
								dist3 = pow(pow(s3.u - j, 2) + pow(s3.v - i, 2), 0.5);

								colo colori = FetchInterp(dist1, dist2, dist3, color1, color2, color3);

								SketchSystemPixel(rendi, res, colori);
							}
						}
					}
				}
				else {
					if (p3.v > p1.v) {
						for (float i = p1.v; i < p3.v; i++) {
							if (p1.u == p3.u) {
								mys2.u = p3.u;
							}
							else {
								mys2.u = (i - b31) / m31;
							}
							if (p2.u == p3.u) {
								mys1.u = p2.u;
							}
							else {
								mys1.u = (i - b23) / m23;
							}


							if (mys2.u < mys1.u) {
								for (int j = mys2.u; j < mys1.u; j++) {
									site res; res.u = j; res.v = i;
									float dist1; float dist2; float dist3;
									dist1 = pow(pow(s1.u - j, 2) + pow(s1.v - i, 2), 0.5);
									dist2 = pow(pow(s2.u - j, 2) + pow(s2.v - i, 2), 0.5);
									dist3 = pow(pow(s3.u - j, 2) + pow(s3.v - i, 2), 0.5);

									colo colori = FetchInterp(dist1, dist2, dist3, color1, color2, color3);

									SketchSystemPixel(rendi, res, colori);
								}
							}
							else {
								for (int j = mys1.u; j < mys2.u; j++) {
									site res; res.u = j; res.v = i;
									float dist1; float dist2; float dist3;
									dist1 = pow(pow(s1.u - j, 2) + pow(s1.v - i, 2), 0.5);
									dist2 = pow(pow(s2.u - j, 2) + pow(s2.v - i, 2), 0.5);
									dist3 = pow(pow(s3.u - j, 2) + pow(s3.v - i, 2), 0.5);

									colo colori = FetchInterp(dist1, dist2, dist3, color1, color2, color3);

									SketchSystemPixel(rendi, res, colori);
								}
							}
						}
					}
					else {
						if (p3.v < p1.v) {
							for (int i = p3.v; i < p1.v; i++) {
								if (p1.u == p3.u) {
									mys2.u = p3.u;
								}
								else {
									mys2.u = (i - b31) / m31;
								}
								if (p2.u == p3.u) {
									mys1.u = p1.u;
								}
								else {
									mys1.u = (i - b23) / m23;
								}
								if (mys2.u < mys1.u) {
									for (int j = mys2.u; j < mys1.u; j ++) {
										site res; res.u = j; res.v = i;

										
										float dist1; float dist2; float dist3;
										dist1 = pow(pow(s1.u - j, 2) + pow(s1.v - i, 2), 0.5);
										dist2 = pow(pow(s2.u - j, 2) + pow(s2.v - i, 2), 0.5);
										dist3 = pow(pow(s3.u - j, 2) + pow(s3.v - i, 2), 0.5);
										
										colo colori = FetchInterp(dist1, dist2, dist3, color1, color2, color3);

										SketchSystemPixel(rendi, res, colori);
									}
								}
								else {
									for (int j = mys1.u; j < mys2.u; j++) {
										site res; res.u = j; res.v = i;
										float dist1; float dist2; float dist3;
										dist1 = pow(pow(s1.u - j, 2) + pow(s1.v - i, 2), 0.5);
										dist2 = pow(pow(s2.u - j, 2) + pow(s2.v - i, 2), 0.5);
										dist3 = pow(pow(s3.u - j, 2) + pow(s3.v - i, 2), 0.5);

										colo colori = FetchInterp(dist1, dist2, dist3, color1, color2, color3);

										SketchSystemPixel(rendi, res, colori);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void SketchTexturePixel(Uint32 * pixelsi, site s1, Uint32 ucolor) {
	int x = s1.u; int y = s1.v;
	if (int((y * width) + x) < width * height) {
		if (int((y * width) + x) > 0) {
			if (s1.u > 0 && s1.u < width) {
				pixelsi[int((y * width) + x)] = ucolor;
			}
		}
	}
}

void SketchTextureScanLine(Uint32 * pixelsi, site s1, int endu, Uint32 ucolor) {
	float sx = s1.u;
	
	if (endu < sx) {
		return;
	}
	
	for (float i = sx; i < endu; i++) {
		s1.u = i;
		SketchTexturePixel(pixelsi, s1, ucolor);
	}
}

void SketchTextureLine(Uint32 * pixelsi, site s1, site s2, Uint32 ucolor) {
	float m = (s1.v - s2.v) / (s1.u - s2.u);
	float b = s1.v - (m * s1.u);
	float p;
	float k;
	float dist = pow(double(pow((s1.u - s2.u), 2) + pow((s1.v - s2.v), 2)), 0.5);
	float step = abs((abs(s1.u - s2.u)) / dist);

	colo colori;

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
		SketchTexturePixel(pixelsi, s1, ucolor);
	}
	else {
		if (s1.u == s2.u) {
			for (float i = s1.v; i < s2.v; ++i) {
				site res; res.u = s1.u; res.v = i;
				SketchTexturePixel(pixelsi, res, ucolor);
			}
		}
		else {
			if (s1.v == s2.v) {
				for (float i = s1.u; i < s2.u; i += 1) {
					site res; res.u = i; res.v = s1.v;
					SketchTexturePixel(pixelsi, res, ucolor);
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

					colori.a = k;
					site res; res.u = i; res.v = (m * i) + b;

					SketchTexturePixel(pixelsi, res, ucolor);

					/*
					colori.a = p;
					res.u = i + xshift; res.v = (m * i) + b + yshift;
					SketchPixel(pixelsi, res, colori);
					*/
				}
			
			}
		}
	}
}
	
void SketchHeaderText(SDL_Renderer* rendi, site s1, string text) {
	TTF_Font * font = TTF_OpenFont("MODERNE SANS.ttf", 20);
	SDL_Color color = { 107, 103, 103 };
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
	s1.u = 1250; s2.u = 1250; s3.u = 1250; s4.u = 1250; s5.u = 1250; s6.u = 1250;
	s1.v = 40; s2.v = 70; s3.v = 100; s4.v = 130; s5.v = 160; s6.v = 190;
	SketchText(rendi, s1, "PX: " + to_string(vect.x));
	SketchText(rendi, s2, "PY: " + to_string(vect.y));
	SketchText(rendi, s3, "PZ: " + to_string(vect.z));
	SketchText(rendi, s4, "RX: " + to_string(vect.rx));
	SketchText(rendi, s5, "RY: " + to_string(vect.ry));
	SketchText(rendi, s6, "RZ: " + to_string(vect.rz));
}

site FetchVertex(vert a, tran mycam, int fov) {
	a.z = -a.z;
	float x = a.x - mycam.x;
	float y = a.y - mycam.y;
	float z = a.z - mycam.z;

	vect d;

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
	float e = 0.25;
	site res;

	if (d.z == 0) {
		d.z = 0.00001;
	}

	res.u = int(((e / d.z) * d.x + 0.5) * width * 100) / 100;
	res.v = int(((e / d.z) * d.y + 0.5) * width * 100) / 100;
	return res;
}

int perm[1000] = { 0 };
float res[1000] = { 0 };

int compare(const void * a, const void * b) {
	double diff = res[*(int*)a] - res[*(int*)b];
	return  (0 < diff) - (diff < 0);
}

void SketchSystemMesh(SDL_Renderer* rendi, mesh meshi, colo colori, byte $sh, light lighti, tran cami) {
	
	for (int i = 0; i < 1000; i++) {
		meshi.sarr[i] = FetchVertex(meshi.varr[i], cam, 103);
	}
	//calculate render order, based on distance from camera to first vertex
	
	for (int i = 0; i < 1000; i++) {
		meshi.distarr[i] = FetchDistanceToCamera(meshi.farr[i].c);
	}

	//create a permutation based off of distarr[] and apply to sarr[]
	perm[1000];
	res[1000];

	for (int i = 0; i < 1000; i++) {
		res[i] = meshi.distarr[i];
	}

	for (int i = 0; i < 1000; i++) {
		perm[i] = i;
	}
	qsort(perm, 1000, sizeof(int), compare);

	if ($sh == 0) {
		for (int i = 0; i < 1000; i++) {
			if (meshi.fnarr[i].v1.z < 0) {
				SketchSystemLine(rendi, meshi.sarr[meshi.farr[i].vr1], meshi.sarr[meshi.farr[i].vr2], colori);
				SketchSystemLine(rendi, meshi.sarr[meshi.farr[i].vr2], meshi.sarr[meshi.farr[i].vr3], colori);
				SketchSystemLine(rendi, meshi.sarr[meshi.farr[i].vr3], meshi.sarr[meshi.farr[i].vr1], colori);
			}
		}
	}
	else if ($sh == 1) {
		vect vcam; vcam.x = cami.rx; 
		vcam.y = cami.ry; vcam.z = cami.rz;
		for (int i = 0; i < 1000; i++) {
			//cull backfaces
			float cullf = FetchVectorAgreement(meshi.fnarr[perm[abs(999 - i)]].v4, vcam);
			if (cullf > 0) {
				//continue;
			} 
			
			//draw only first face
			//if (perm[abs(999-i)] != 0) { continue; }
			float temp;
			colo color1;
			color1.a = 255;
			temp = FetchLighting(meshi.fnarr[perm[abs(999 - i)]].v4, sun);
			color1.r = temp * colori.r;
			color1.g = temp * colori.g;
			color1.b = temp * colori.b;
			SketchRenderTriangle(rendi, meshi.sarr[meshi.farr[perm[abs(999-i)]].vr1], meshi.sarr[meshi.farr[perm[abs(999 - i)]].vr2], meshi.sarr[meshi.farr[perm[abs(999 - i)]].vr3], color1, true);
		}
	}
	else if ($sh = 2) {
		for (int i = 0; i < 1000; i++) {
			/*
			float temp1; float temp2; float temp3;
			
			
			temp1 = FetchLighting(meshi.fnarr[perm[abs(999 - i)]].v1, sun);
			temp2 = FetchLighting(meshi.fnarr[perm[abs(999 - i)]].v2, sun);
			temp3 = FetchLighting(meshi.fnarr[perm[abs(999 - i)]].v3, sun);
			*/

			vect temp1;
			vect temp2;
			vect temp3;

			temp1 = meshi.fnarr[perm[abs(999 - i)]].v1;
			temp2 = meshi.fnarr[perm[abs(999 - i)]].v2;
			temp3 = meshi.fnarr[perm[abs(999 - i)]].v3;


			colo color1;
			colo color2;
			colo color3;

			
			color1.r = temp1.x * 255;
			color1.g = temp1.y * 255;
			color1.b = temp1.z * 255;

			color2.r = temp2.x * 255;
			color2.g = temp2.y * 255;
			color2.b = temp2.z * 255;

			color3.r = temp3.x * 255;
			color3.g = temp3.y * 255;
			color3.b = temp3.z * 255;

			
			SketchRenderBITriangle(rendi, meshi.sarr[meshi.farr[perm[abs(999 - i)]].vr1], meshi.sarr[meshi.farr[perm[abs(999 - i)]].vr2], meshi.sarr[meshi.farr[perm[abs(999 - i)]].vr3], color1, color2, color3);
			//SketchRenderTriangle(rendi, meshi.sarr[meshi.farr[perm[abs(999 - i)]].vr1], meshi.sarr[meshi.farr[perm[abs(999 - i)]].vr2], meshi.sarr[meshi.farr[perm[abs(999 - i)]].vr3], color1, true);
		}
	}
	

}

int StringSearch(const std::string& referenceString, const std::string& subString) {

	const size_t step = subString.size();

	int count =0;
	size_t pos = 0;

	while ((pos = referenceString.find(subString, pos)) != std::string::npos) {
		pos += step;
		++count;
	}
	return count;
}

void SketchWindow(SDL_Renderer* rendi, site pos, string title, string text) {
	TTF_Font * font = TTF_OpenFont("MODERNE SANS.ttf", 14);
	int w; int h;
	byte $b = StringSearch(text, "&*");
	int maxlen = 0;
	int len;
	string text2 = text;
	for (int i = 0; i < $b; i++) {
		string temp;
		temp = text2.substr(0, text2.find_first_of("&*"));
		len = temp.length();
		text2.erase(0, text2.find_first_of("&*") + 2);
		if (len > maxlen) {
			maxlen = len;
		}
	}

	site bound;

	bound.u = (maxlen * 8.5) + 10;
	bound.v = ($b * 14) + 13;
	
	SDL_Rect main; main.h = 2; main.w = bound.u; main.x = pos.u; main.y = pos.v - 2;
	SDL_SetRenderDrawColor(rendi, 195, 195, 195, 255);
	SDL_RenderFillRect(rendi, &main);

	main.h = bound.v; main.w = bound.u; main.x = pos.u; main.y = pos.v;
	SDL_SetRenderDrawColor(rendi, 85, 85, 85, 255);
	SDL_RenderFillRect(rendi, &main);

	pos.u += 5; pos.v -= 18;

	SketchHeaderText(rendi, pos, title);

	pos.v += 10;

	

	for(int i = 0; i < $b; i++){
		pos.v += 14;
		string line;

		line = text.substr(0, text.find_first_of("&*"));
		
		SketchText(rendi, pos, line);

		text.erase(0, text.find_first_of("&*") + 2);
	}
}

//References:
//sh$:
//0 - wireframe
//1 - unlit shading
//2 - flat shading
//3 - gourand shading
//4 - phong shading
//5 - texture 
//6 - specular
//7 - phong, specular, texture