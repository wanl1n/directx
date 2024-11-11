#pragma once

#include <cmath>

class Point {
	public:
		int x = 0, y = 0; 

		Point() : x(0), y(0) {}
		Point(int x, int y) : x(x), y(y) {}
		Point(const Point& point) : x(point.x), y(point.y) {}
		~Point() {}
		
		static Point lerp(const Point& start, const Point& end, float delta) {
			Point v;

			v.x = start.x * (1.0f - delta) + end.x * delta;
			v.y = start.y * (1.0f - delta) + end.y * delta;

			return v;
		}

		float magnitude() {
			return (float)sqrt(pow(this->x, 2) + pow(this->y, 2));
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

		Point operator-(const Point& other) const
		{
			return Point(x - other.x, y - other.y);
		}
		
		void operator +=(const Point& other) {
			this->x += other.x;
			this->y += other.y;
		}

		void operator -=(const Point& other) {
			this->x -= other.x;
			this->y -= other.y;
		}

		void operator +=(float addend) {
			this->x += addend;
			this->y += addend;
		}

		Point operator +(const Point& other) {
			Point result;

			result.x = x + other.x;
			result.y = y + other.y;

			return result;
		}

		Point operator *(const Point& other) {
			Point result;

			result.x = x * other.x;
			result.y = y * other.y;

			return result;
		}

		Point operator *(float mult) {
			Point result;

			result.x = x * mult;
			result.y = y * mult;

			return result;
		}

		bool operator !=(const Point& other) {
			if (other.x != this->x ||
				other.y != this->y)
				return true;
			else
				return false;
		}
};