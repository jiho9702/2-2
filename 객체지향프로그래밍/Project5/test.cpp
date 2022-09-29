#include <iostream>
using namespace std;

class Shape {
protected:
	int x, y;

public:
	Shape(int xx, int yy) {
		x = xx;
		y = yy;
	}

	 void draw() {
		cout << "shape draw";
	}

	void setOrigin(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

class Rectangle : public Shape {
private:
	int width, height;

public:
	Rectangle(int x, int y, int w, int h) : Shape(x,y) {
		width = w;
		height = h;
	}

	void setWidth(int w) {
		width = w;
	}

	void setHeight(int h) {
		height = h;
	}

	void draw() {
		cout << "Rectangle draw";
	}
};


int main() {

	Shape* s = new Rectangle(1, 1, 10, 10);

	s->draw();

}