#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
public:
	float x, y, z;
	Point(float xx = 0, float yy = 0, float zz = 0)  //������
	{ 
		x = xx;	
		y = yy;
		z = zz;
	}
	Point Plus(Point vec)     //��
	{ 
		return Point(x + vec.x, y + vec.y, z + vec.z); 
	}
	Point Minus(Point vec)    //��
	{ 
		return Point(x - vec.x, y - vec.y, z - vec.z); 
	}
	
	float DotP(Point vec){  //�����ϴ� ����Լ�
		return (x * vec.x) + (y * vec.y) + (z * vec.z);
	}
};

void showVector(Point vec) {  //�� ���� ����ϴ� �Լ�
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