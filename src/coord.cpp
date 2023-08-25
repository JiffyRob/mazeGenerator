#include "coord.h"
using namespace std;



Coord::Coord(float x_value, float y_value) {
        x = x_value;
        y = y_value;
    }
Coord::Coord() {
        x = 0;
        y = 0;
    }
Coord::Coord(float scalar)  {
        x = scalar;
        y = scalar;
    }

Coord Coord::operator+(Coord other) {
        return Coord(this->x + other.x, this->y + other.y);
    }
Coord Coord::operator-(Coord other) {
        return Coord(this->x - other.x, this->y - other.y);
    }
Coord Coord::operator*(Coord other) {
        return Coord(this->x * other.x, this->y * other.y);
    }
Coord Coord::operator/(Coord other) {
        return Coord(this->x / other.x, this->y / other.y);
    }