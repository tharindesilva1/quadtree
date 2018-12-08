#pragma once
template <typename T>
class Vec2 {
public:
	Vec2(T _x, T _y) : x{ _x }, y{ _y } {

	}
	Vec2() : x{ 0 }, y{ 0 } {

	}

	void set(T _x, T _y) {
		x = _x;
		y = _y;
	}
	T x, y;
};

