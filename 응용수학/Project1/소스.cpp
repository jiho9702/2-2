#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
public:
	float x, y, z;
	Point(float xx = 0, float yy = 0, float zz = 0)  //생성자
	{ 
		x = xx;	
		y = yy;
		z = zz;
	}
	Point Plus(Point vec)     //합
	{ 
		return Point(x + vec.x, y + vec.y, z + vec.z); 
	}
	Point Minus(Point vec)    //차
	{ 
		return Point(x - vec.x, y - vec.y, z - vec.z); 
	}
	
	float DotP(Point vec){  //내적하는 멤버함수
		return (x * vec.x) + (y * vec.y) + (z * vec.z);
	}
};

void showVector(Point vec) {  //세 점을 출력하는 함수
	cout << "( " << vec.x << ", " << vec.y << ", " << vec.z << " )" << endl;
}


int main() {

	Point A(0,0,0);
	Point B(-1,1,1);
	Point C(1,1,1);

	Point P1(0, 1, 0);
	Point P2(0, 0, 1);

	Point E = A.Minus(B);
	showVector(E);

	float BdC = B.DotP(C);
	cout << BdC;

}