/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <vector>

#include <random>     /* srand, rand */
#include "Rect.h"
#include "QuadTree.h"
#include "Timer.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

std::random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> moveDis(-1, 1);

std::vector<Rect> rects;

QuadTree qt{ Rect{SCREEN_WIDTH/2,SCREEN_HEIGHT/2,SCREEN_WIDTH,SCREEN_HEIGHT } };

Timer t{ true };
float elapsedTime = 0;


bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		//Set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Quadtree Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}

	std::uniform_int_distribution<> xPosDis(20, 1260);
	std::uniform_int_distribution<> yPosDis(20, 700);
	std::uniform_int_distribution<> size(0, 100);

	
	for(int i = 0; i < 100; i++) {
		rects.emplace_back(xPosDis(gen), yPosDis(gen), size(gen), size(gen));
	}

	return success;
}



void close() {
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}



int main(int argc, char* args[]) {
	//Start up SDL and create window
	if(!init()) {
		printf("Failed to initialize!\n");
	} else {
		//Load media
	
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while(!quit) {
			//Handle events on queue
			while(SDL_PollEvent(&e) != 0) {
				//User requests quit
				if(e.type == SDL_QUIT) {
					quit = true;
				} 
			}

			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
			SDL_RenderClear(gRenderer);


			qt.Reset();
			for(auto& rect : rects) qt.Insert(rect);

			for(auto& rectA : rects) {
				
				rectA.resetCollisionFlag();
				rectA.Update(moveDis(gen), moveDis(gen));
				std::vector<std::reference_wrapper<Rect >> outQueryRects;
				qt.Query(rectA, outQueryRects);
				for(auto& rectB : outQueryRects) {
					rectA.CheckCollision(rectB);
				}

			}


		for(auto& rect : rects) {
			rect.Draw(gRenderer);
		}
		qt.Draw(gRenderer);
			//Update screen
			SDL_RenderPresent(gRenderer);
		}
		
	}

	//Free resources and close SDL
	close();

	return 0;
}


//Render red filled quad
//SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
//SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
//SDL_RenderFillRect(gRenderer, &fillRect);


//elapsedTime += t.GetDeltaTime();
//
//if(elapsedTime > 0.1) {
//	for(auto& rectA : rects) {
//
//		rectA.resetCollisionFlag();
//
//		rectA.Update(moveDis(gen), moveDis(gen));
//		for(auto& rectB : rects) {
//			if(&rectA != &rectB) rectA.CheckCollision(rectB);
//		}
//	}
//	elapsedTime = 0;
//}
//
//
//for(auto& rect : rects) {
//	rect.Draw(gRenderer);
//}
//
//for(auto& rectA : tarr) {
//	for(auto& rectB : tarr) {
//		if(&rectA != &rectB) rectA.CheckCollision(rectB);
//
//	}
//}
//
//for(auto& rect : tarr) {
//	rect.Draw(gRenderer);
//	rect.resetCollisionFlag();
//}