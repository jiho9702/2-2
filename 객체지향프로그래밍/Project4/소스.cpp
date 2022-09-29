#include <iostream>
using namespace std;

class Point {
private:
	int x;
	int y;
public:
	Point(int xx = 0, int yy = 0) {
		x = xx;
		y = yy;
	}
	void Draw() {
		cout << "(" << x << ",";
		cout << y << ") ";
	}
};

class CShape {
private:
	Point p1,  p2;

public:
	CShape(int x1, int y1, int x2, int y2) {
		p1 = Point(x1, y1);
		p2 = Point(x2, y2);
	}
	virtual void Draw() {

		cout << "ÁÂ»ó´Ü ÁÂÇ¥ : ";
		p1.Draw();
		cout << "¿ìÇÏ´Ü ÁÂÇ¥ : ";
		p2.Draw();
		cout << endl;
	}

};

class CCircle : public CShape {
private:
	Point p1, p2;
public:
	CCircle(int x1, int y1, int x2, int y2) :CShape(x1, y1, x2, y2) {
		p1 = Point(x1, y1);
		p2 = Point(x2, y2);
	}
	void Draw() {
		cout << "¿ø ±×¸°´Ù." << endl;
		cout << "ÁÂ»ó´Ü ÁÂÇ¥ : ";
		p1.Draw();
		cout << "¿ìÇÏ´Ü ÁÂÇ¥ : ";
		p2.Draw();
		cout << endl;
	}
};

class CLine : public CShape {
private:
	Point* p1, * p2;
public:
	CLine(int x1, int y1, int x2, int y2) :CShape(x1, y1, x2, y2) {
		p1 = new Point(x1, y1);
		p2 = new Point(x2, y2);
	}
	void Draw() {
		cout << "Á÷¼± ±×¸°´Ù." << endl;
		cout << "ÁÂ»ó´Ü ÁÂÇ¥ : ";
		p1->Draw();
		cout << "¿ìÇÏ´Ü ÁÂÇ¥ : ";
		p2->Draw();
		cout << endl;
	}
	
};

void main() {

	CCircle a(1, 1, 5, 5); // ÁÂ»ó´ÜÁ¡, ¿ìÇÏ´ÜÁ¡ ÁÂÇ¥
	CLine b(5, 5, 9, 9); // ÁÂ»ó´ÜÁ¡, ¿ìÇÏ´ÜÁ¡ ÁÂÇ¥
	CShape* p;
	a.Draw(); // ¡°¿ø ±×¸°´Ù¡± ÁÂ»ó´Ü/¿ìÇÏ´ÜÁ¡ ÁÂÇ¥ Ãâ·Â
	b.Draw(); // ¡°Á÷¼± ±×¸°´Ù¡± ÁÂ»ó´Ü/¿ìÇÏ´ÜÁ¡ ÁÂÇ¥ Ãâ·Â
	p = new CLine(10, 10, 100, 100);
	p->Draw(); // ¡°Á÷¼± ±×¸°´Ù¡± Ãâ·Â, ÁÂ»ó´Ü/¿ìÇÏ´ÜÁ¡ ÁÂÇ¥ Ãâ·Â
	p = new CCircle(100, 100, 200, 200);
	p->Draw(); // ¡°¿ø ±×¸°´Ù¡± Ãâ·Â, ÁÂ»ó´Ü/¿ìÇÏ´ÜÁ¡ ÁÂÇ¥ Ãâ·Â
	
	delete p;
}