#include "Rect.h"



Rect::Rect(int xPos, int yPos, int w, int h) {
	pos.set(xPos, yPos);
	dimensions.set(w, h);

	right = pos.x + dimensions.x / 2;
	left = pos.x - dimensions.x / 2;
	top = pos.y - dimensions.y / 2;
	bot = pos.y + dimensions.y / 2;
}

void Rect::resetCollisionFlag() {
	intersected = false;
}

void Rect::set(int xPos, int yPos) {
	pos.set(xPos, yPos);
	dimensions.set(dimensions.x, dimensions.y);

	right = pos.x + dimensions.x / 2;
	left = pos.x - dimensions.x / 2;
	top = pos.y - dimensions.y / 2;
	bot = pos.y + dimensions.y / 2;
}


Rect::~Rect() {
}

void Rect::Draw(SDL_Renderer* gRenderer) {

	//Render green outlined quad
	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
	if(!intersected) SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);


	SDL_Rect outlineRect = { pos.x - (dimensions.x)/2, pos.y - (dimensions.y) / 2, dimensions.x, dimensions.y };
	SDL_RenderDrawRect(gRenderer, &outlineRect);

	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);

	SDL_RenderDrawPoint(gRenderer, left, top);
	SDL_RenderDrawPoint(gRenderer, left, bot);

	SDL_RenderDrawPoint(gRenderer, right, top);
	SDL_RenderDrawPoint(gRenderer, right, bot);
}

void Rect::Update(int xdisplace, int ydisplace) {
	if ((pos.x + xdisplace > 0)  && (pos.x + xdisplace < 1280))	pos.x += xdisplace;
	if((pos.y + ydisplace > 0) && (pos.y + ydisplace < 720)) pos.y += ydisplace;

	right = pos.x + dimensions.x / 2;
	left = pos.x - dimensions.x / 2;
	top = pos.y - dimensions.y / 2;
	bot = pos.y + dimensions.y / 2;
}


//

bool Rect::Intersects(const Rect& other) {

	auto AwithB = [=](const Rect& a, const Rect& b) {
		bool horizontallyIntersects = ((a.right >= b.left) && (a.right <= b.right)) || ((a.left >= b.left) && (a.left <= b.right));
		bool verticallyIntersects = ((a.top <= b.bot) && (a.top >= b.top)) || ((a.bot <= b.bot) && (a.bot >= b.top));
		return horizontallyIntersects && verticallyIntersects;
	};

	return AwithB(*this, other) || AwithB(other, *this);
}


void Rect::CheckCollision(Rect & other) {
	
		auto AwithB = [=](const Rect& a, const Rect& b) {
			bool horizontallyIntersects = ((a.right >= b.left) && (a.right <= b.right)) || ((a.left >= b.left) && (a.left <= b.right));
			bool verticallyIntersects = ((a.top <= b.bot) && (a.top >= b.top)) || ((a.bot <= b.bot) && (a.bot >= b.top));
			return horizontallyIntersects && verticallyIntersects;
		};
	
		bool currentIntersect = AwithB(*this, other) || AwithB(other, *this);
	
		if(!intersected) intersected = currentIntersect;
		if(!other.intersected) other.intersected = currentIntersect;
	
	}