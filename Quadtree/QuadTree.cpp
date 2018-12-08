#include "QuadTree.h"



QuadTree::QuadTree(Rect _boundary) :
	boundary{ _boundary } {
}


QuadTree::~QuadTree() {
}

void QuadTree::Insert(Rect& r) {
	if(boundary.Intersects(r)) {
		if(rectsWithin.size() < MAX_RECTS) {
			rectsWithin.emplace_back((std::ref(r)));
		} else {
			if(!isSubdivide) subdivide();
			TL->Insert(r);
			TR->Insert(r);
			BL->Insert(r);
			BR->Insert(r);

		}
	}
}

void QuadTree::Query(const Rect& r, std::vector<std::reference_wrapper<Rect>>& outRects) {
	if(this->boundary.Intersects(r)) {
		std::copy_if(rectsWithin.begin(), rectsWithin.end(),
					 std::back_inserter(outRects),
					 [&r](const std::reference_wrapper<Rect>& i) {
			return (std::addressof(i.get()) != std::addressof(r)); });
	}
	
	if(TL)TL->Query(r, outRects);
	if(TR)TR->Query(r, outRects);
	if(BL)BL->Query(r, outRects);
	if(BR)BR->Query(r, outRects);

}

void QuadTree::subdivide() {
	TL = std::make_unique< QuadTree >(Rect{ boundary.pos.x - (boundary.dimensions.x / 4),
										boundary.pos.y - (boundary.dimensions.y / 4),
													(boundary.dimensions.x / 2),
											  (boundary.dimensions.y / 2) });

	TR = std::make_unique< QuadTree >(Rect{ boundary.pos.x + (boundary.dimensions.x / 4),
									boundary.pos.y - (boundary.dimensions.y / 4),
												(boundary.dimensions.x / 2),
										  (boundary.dimensions.y / 2) });

	BL = std::make_unique< QuadTree >(Rect{ boundary.pos.x - (boundary.dimensions.x / 4),
									boundary.pos.y + (boundary.dimensions.y / 4),
												(boundary.dimensions.x / 2),
										  (boundary.dimensions.y / 2) });

	BR = std::make_unique< QuadTree >(Rect{ boundary.pos.x + (boundary.dimensions.x / 4),
									boundary.pos.y + (boundary.dimensions.y / 4),
												(boundary.dimensions.x / 2),
										  (boundary.dimensions.y / 2) });

	isSubdivide = true;
}

void QuadTree::Reset() {
	isSubdivide = false;
	rectsWithin.clear();
}

void QuadTree::Draw(SDL_Renderer* gRenderer) {
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_Rect outlineRect = { boundary.pos.x - (boundary.dimensions.x) / 2, boundary.pos.y - (boundary.dimensions.y) / 2, boundary.dimensions.x, boundary.dimensions.y };
	SDL_RenderDrawRect(gRenderer, &outlineRect);

	if(TL)TL->Draw(gRenderer);
	if(TR)TR->Draw(gRenderer);;
	if(BL)BL->Draw(gRenderer);;
	if(BR)BR->Draw(gRenderer);;

}


