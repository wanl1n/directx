#pragma once

#include <cmath>
namespace Math {
	class Vector2 {
	public:
		float x = 0, y = 0;

		Vector2() : x(0), y(0) {}
		Vector2(float x) : x(x), y(x) {}
		Vector2(float x, float y) : x(x), y(y) {}
		Vector2(const Vector2& point) : x(point.x), y(point.y) {}
		~Vector2() {}

		static Vector2 lerp(const Vector2& start, const Vector2& end, float delta) {
			Vector2 v;

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
				x = x / length;
				y = y / length;
			}
		}

		Vector2 operator-(const Vector2& other) const
		{
			return Vector2(x - other.x, y - other.y);
		}

		void operator +=(const Vector2& other) {
			this->x += other.x;
			this->y += other.y;
		}

		void operator -=(const Vector2& other) {
			this->x -= other.x;
			this->y -= other.y;
		}

		void operator +=(float addend) {
			this->x += addend;
			this->y += addend;
		}

		Vector2 operator +(const Vector2& other) {
			Vector2 result;

			result.x = x + other.x;
			result.y = y + other.y;

			return result;
		}

		Vector2 operator *(const Vector2& other) {
			Vector2 result;

			result.x = x * other.x;
			result.y = y * other.y;

			return result;
		}

		Vector2 operator *(float mult) {
			Vector2 result;

			result.x = x * mult;
			result.y = y * mult;

			return result;
		}

		bool operator !=(const Vector2& other) {
			if (other.x != this->x ||
				other.y != this->y)
				return true;
			else
				return false;
		}
	};
}