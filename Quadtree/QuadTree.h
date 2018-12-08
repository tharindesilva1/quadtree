#pragma once
#include<memory>
#include "Rect.h"
#include <vector>
#include <algorithm>
#include <memory>

class QuadTree {
public:
	QuadTree(Rect _boundary);
	~QuadTree();

	

	void Insert(Rect& r);
	void Query(const Rect& r, std::vector<std::reference_wrapper<Rect>>& outRects);
	void subdivide();
	void Reset();
	void Draw(SDL_Renderer* gRenderer);

private:

	bool isSubdivide = false;

	Rect boundary;

	static const int MAX_RECTS = 4;
	std::vector<std::reference_wrapper<Rect>> rectsWithin;
	// Children
	std::unique_ptr<QuadTree> TL;
	std::unique_ptr<QuadTree> TR;
	std::unique_ptr<QuadTree> BL;
	std::unique_ptr<QuadTree> BR;

};

