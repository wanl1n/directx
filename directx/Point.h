#pragma once

#include <cmath>

class Point {
	public:
		int x = 0, y = 0; 

		Point() : x(0), y(0) {}
		Point(int x, int y) : x(x), y(y) {}
		Point(const Point& point) : x(point.x), y(point.y) {}
		~Point() {}

		Point operator-(const Point& other) const
		{
			return Point(x - other.x, y - other.y);
		}

		void normalize()
		{
			float length = std::sqrt(x * x + y * y);
			if (length == 0) {
				x = 0;
				y = 0;
			}
			else {
				x = static_cast<int>(x / length);
				y = static_cast<int>(y / length);
			}
		}
};