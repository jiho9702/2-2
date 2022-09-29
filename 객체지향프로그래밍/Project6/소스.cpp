#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class Vector {
	int a, b;
	static int count;
	friend Vector operator+ (const Vector& v1, const Vector& v2);
	friend Vector operator- (const Vector& v1, const Vector& v2);
	friend bool operator== (const Vector& v1, const Vector& v2);
public:
	Vector(int x, int y) : a(x), b(y){
		count++;
		cout << "기본생성자" << endl;
		cout << count << endl;
	}
	/*Vector operator+ (const Vector &v) {
		Vector v3(0, 0);
		v3.a = this->a + v.a;
		v3.b = this->b + v.b;
		return v3;
	}*/

	Vector(const Vector& v) {
		this->a = v.a;
		this->b = v.b;
		cout << "복사생성자" << endl;
		count++;
		cout << count << endl;
	}

	~Vector() {
		cout << "소멸자" << endl;
		count--;
		cout << count << endl;
	}

	Vector operator=(Vector v) {
		a = v.a;
		b = v.b;
		return *this;
	}

	void display() {
		cout << a << "," << b << endl;
	}
};

int Vector :: count = 0;

Vector operator+ (const Vector& v1, const Vector& v2) {
	Vector v(0, 0);
	v.a = v1.a + v2.a;
	v.b = v1.b + v2.b;
	return v;
}

Vector operator- (const Vector& v1, const Vector& v2) {
	Vector v(0, 0);
	v.a = v1.a - v2.a;
	v.b = v1.b - v2.b;
	return v;
}

bool operator== (const Vector& v1, const Vector& v2) {
	if (v1.a == v2.a && v1.b == v2.b) {
		return 1;
	}
	else {
		return 0;
	}
}

bool operator!= (const Vector& v1, const Vector& v2) {
	return !(v1 == v2);
}

template<typename T>
void FindAbs(T a) {
	
	cout << sqrt(pow(a,2)) << endl;
}

template<typename T1, typename T2>
int add(T1 a, T2 b) {
	return a + b;
}

template<typename T>
void display(T &a) {
	int len = sizeof(a) / sizeof(int);
	for (int i = 0; i < len; i++) {
		cout << a[i];
	}
	cout << endl;
}

void display(char* s) {
	int len;
	len = strlen(s);
	for (int i = 0; i <len; i++) {
		cout << s[i];
	}
}

void swap(int *a, int *b) {
	int *temp;
	temp = a;
	a = b;
	b = temp;
}

class A {
	int a;
public:
	A(int n) : a(n) { cout << "생성자호출" << endl; }
	A(const A &n){ cout << "복사생성자호출" << endl; }
	~A() { cout << "소멸자 호출" << endl; }
	void display(A &b) {
		cout << b.a;
	}
};

int main() {

	/*Vector v1(2, 3);
	Vector v2(3, 4);
	Vector v3(5, 6);
	v1 = v2 = v3;*/
	/*Vector v3 = v1 + v2;
	v3.display();
	Vector v4 = v1 - v2;
	v3.display();*/

	//cout << (v1 == v2) << " , " << (v1 != v2);

	/*int x = -26;
	FindAbs(x);

	int a = 10;
	int b = 8;
	cout << add(a, b) << endl;

	int z[10] = { 1,2,3,4,5,6,7,8,9,10 };
	char c[100] = "This is me!";

	display(z);
	display(c);*/

	//vector<int> score(3);
	//cout << score.size() << endl;

	//for (int i = 0; i < 5; i++) {
	//	score.push_back(i);
	//}
	//cout << score.size() << endl;

	//vector<int> scores[3];
	//for (int i = 0; i < 3; i++) {
	//	for (int j = 0; j < 5; j++) {
	//		scores[i].push_back(j);
	//	}
	//}
	//for (int i = 0; i < 3; i++) {
	//	for (int j = 0; j < 5; j++) {
	//		cout << scores[i][j];
	//	}
	//	cout << endl;
	//}
	//vector<int> v[10];
	//for (int i = 0; i < 10; i++) {
	//	for (int j = 0; j < 10; j++) {
	//		v[i].push_back(j);
	//	}
	//}
	//vector<int> :: iterator it;
	//for (int i = 0; i < 10; i++) {
	//	for (it = v[i].begin(); it != v[i].end(); it++) {
	//		cout << *it;
	//	}
	//	cout << endl;
	//}

	/*int a = 5;
	int b = 6;

	swap(a, b);

	cout << a << " " << b << endl;*/

}