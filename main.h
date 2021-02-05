#ifndef MAIN_H
#define MAIN_H

#include "pch.h"

#undef main

SDL_Window*		window   = NULL;
SDL_Renderer*	renderer = NULL;

SDL_Texture*	solidTexture;
SDL_Texture*	text;
SDL_Rect			solidRect;
TTF_Font*		gFont = NULL;

SDL_Event e;

LTexture image1[4];

bool running = true;
					
#endif // MAIN_H
