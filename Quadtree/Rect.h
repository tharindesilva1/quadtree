#pragma once
#include "Vec2.h"
#include <SDL.h>

class Rect {
public:
	Rect(int xPos, int yPos, int w, int h);

	~Rect();

	void Draw(SDL_Renderer* gRenderer);
	void Update(int xdisplace, int ydisplace);
	void CheckCollision(Rect& other);
	
	bool Intersects(const Rect& other);

	void resetCollisionFlag();
	void set(int xPos, int yPos);
	Vec2<int> pos;
	Vec2<int> dimensions;

	int top;
	int bot;
	int left;
	int right;

	bool intersected = false;

};

