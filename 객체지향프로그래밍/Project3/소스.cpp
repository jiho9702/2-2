#include <iostream>
using namespace std;

class Point {
private:
	int x;
	int y;
public:
	Point(int xx, int yy) {
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
	Point* p1, * p2;
	string s;

public:
	CShape(int x1, int y1, int x2, int y2) {
		p1 = new Point(x1, y1);
		p2 = new Point(x2, y2);
		cout << s;
	}
	virtual void Draw() {

		cout << "�»�� ��ǥ : ";
		p1->Draw();
		cout << "���ϴ� ��ǥ : ";
		p2->Draw();
		cout << endl;
	}

};

class CCircle : public CShape {
private:
	Point *p1, *p2;
public:
	CCircle(int x1, int y1, int x2, int y2):CShape(x1, y1, x2, y2) {
		p1 = new Point(x1, y1);
		p2 = new Point(x2, y2);
	}
	void Draw() {
		cout << "�� �׸���." << endl;
		cout << "�»�� ��ǥ : ";
		p1->Draw();
		cout << "���ϴ� ��ǥ : ";
		p2->Draw();
		cout << endl;
	}
};

class CLine : public CShape{
private:
	Point* p1, * p2;
public:
	CLine(int x1, int y1, int x2, int y2):CShape(x1, y1, x2, y2) {
		p1 = new Point(x1, y1);
		p2 = new Point(x2, y2);
	}
	void Draw() {
		cout << "���� �׸���." << endl;
		cout << "�»�� ��ǥ : ";
		p1->Draw();
		cout << "���ϴ� ��ǥ : ";
		p2->Draw();
		cout << endl;
	}
};

void main() {

	CCircle a(1, 1, 5, 5); // �»����, ���ϴ��� ��ǥ
	CLine b(5, 5, 9, 9); // �»����, ���ϴ��� ��ǥ
	CShape* p;
	a.Draw(); // ���� �׸��١� �»��/���ϴ��� ��ǥ ���
	b.Draw(); // ������ �׸��١� �»��/���ϴ��� ��ǥ ���
	p = new CLine(10, 10, 100, 100);
	p->Draw(); // ������ �׸��١� ���, �»��/���ϴ��� ��ǥ ���
	p = new CCircle(100, 100, 200, 200);
	p->Draw(); // ���� �׸��١� ���, �»��/���ϴ��� ��ǥ ���
	delete p;
}