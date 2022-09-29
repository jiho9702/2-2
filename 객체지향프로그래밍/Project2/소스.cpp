#include <iostream>
using namespace std;

class CBox {
public:
	int a, b;
	CBox(int x = 10, int y = 20) :a(x), b(y) {
		cout << "Box持失切" << endl;
	}
	CBox(const CBox& tt) {
		a = tt.a;
		b = tt.b;
		cout << "Box差紫持失切" << endl;
	}
};

class CCandyBox :public CBox {
public:
	int c, d;
	CCandyBox(int a, int b, int x = 30, int y = 40)
		:CBox(a, b), c(x), d(y) \
	{
		cout << "CandyBox 持失切" << endl;
	}

	CCandyBox(const CCandyBox& tt)
		:CBox(tt)
	{
		c = tt.c;
		d = tt.d;
		cout << "CandyBox差紫持失切" << endl;
	}
};


int main() {
	CBox aa(1, 2);
	CBox bb(aa);
	CCandyBox cc(3, 4, 5, 6);
	CCandyBox dd(cc);
}