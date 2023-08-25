using namespace std;

class Coord {
public:
    float x;
    float y;

    Coord(float x_value, float y_value);
    Coord();
    Coord(float scalar);

    Coord operator+(Coord other);
    Coord operator-(Coord other);
    Coord operator*(Coord other);
    Coord operator/(Coord other);
};