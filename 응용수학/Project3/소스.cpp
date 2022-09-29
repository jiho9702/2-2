#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
public:
	double x, y, z;
	Point(double xx = 0, double yy = 0, double zz = 0)  //생성자
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

	double DotP(Point vec) {  //내적하는 멤버함수
		return (x * vec.x) + (y * vec.y) + (z * vec.z);
	}

	Point crossProduct(Point vec) //외적
	{
		return Point((y * vec.z) - (z * vec.y), (z * vec.x) - (x * vec.z), (x * vec.y) - (y * vec.x));
	}

	Point scalarMultiple(double a) //스칼라배 (실수 a)
	{
		/*
		if (a > 0) return Point(a * abs(x), a * abs(y), a * abs(z));
		else if (a < 0) return Point(-a * abs(x), -a * abs(y), -a * abs(z));
		else if ((a && (x || y || z)) == 0) return Point(0, 0, 0);
		*/

		return Point(a * x, a * y, a * z);
	}
};


void ToXY(Point& a)
{
	if (a.x == 0)
	{
		a.x = a.y;
	}
	a.y = a.z;
	a.z = 0;
}
void XYtoXZ(Point& a)
{
	a.z = a.y;
	a.y = 0;
}
void XYtoYZ(Point& a)
{
	a.z = a.y;
	a.y = a.x;
	a.x = 0;
}


Point Line(Point& p1, Point& p2, double t)
{
	// Line(p1,p2,t) -> p1 + t*(p2-p1)
	Point temp = p2.Minus(p1);
	temp.x *= t;
	temp.y *= t;
	temp.z *= t;
	return p1.Plus(temp);
}

// 평면과 직선의 교점 구하는 함수
Point intersection(Point p1, Point p2, double a, double b, double c, double d) {
	double tmp1 = a * p1.x + b * p1.y + c * p1.z + d;
	double tmp2 = a * (p1.x - p2.x) + b * (p1.y - p2.y) + c * (p1.z - p2.z);

	// 직선의 방정식(Point Line() 함수로 가정) -> L(t) = p1 + t * (p2 - p1)
	double t = tmp1 / tmp2;

	// Line() 함수의 매개변수에 변수 t를 대입한 후, 반환되는 Point 좌표가 교점
	return Line(p1, p2, t);
}

int triinout(Point a, Point b, Point c, Point p)
{
	Point pp[4] = { a,b,c,a };
	if ((pp[0].x == 0 && pp[1].x == 0 && pp[2].x == 0 && pp[3].x == 0 && p.x == 0) || (pp[0].y == 0 && pp[1].y == 0 && pp[2].y == 0 && pp[3].y == 0 && p.x == 0))
	{
		for (int i = 0; i < 4; i++)
		{
			ToXY(pp[i]);
		}
	}
	int count[3] = { 0, };
	for (int i = 0; i < 3; i++)
	{
		Point x = pp[i + 1].Minus(pp[i]);
		Point y = p.Minus(pp[i]);
		Point sum = y.crossProduct(x);

		if (sum.z > 0)
			count[i] = 1;
		else if (sum.z == 0)
			count[i] = 0;
		else
			count[i] = -1;
	}

	if (count[0] == 1 && count[1] == 1 && count[2] == 1)
		return 1;//
	else if (count[0] == 0 || count[1] == 0 || count[2] == 0)
		return 0;//
	else
		return -1;//
}

double tt(Point A, Point B, Point C, Point* n) {    // 7. 평면의 방정식 함수

	double a = A.y * (B.z - C.z) + B.y * (C.z - A.z) + C.y * (A.z - B.z);
	double b = A.z * (B.x - C.x) + B.z * (C.x - A.x) + C.z * (A.x - B.x);
	double c = A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y);

	n->x = a;
	n->y = b;
	n->z = c;

	double d = A.x * (B.y * C.z - C.y * B.z) + B.x * (C.y * A.z - A.y * C.z) + C.x * (A.y * B.z - B.y * A.z);

	return -d;
}

bool IsInEdge(Point& triA, Point& triB, Point& p)
{
	// 직선 내부의 점에 대하여 그점과 양끝 점 사이의 거리 합이 양끝 점 사이의 거리와 같음을 이용한 직선 위 점 존재 여부 확인 
	return sqrt(triB.Minus(triA).DotP(triB.Minus(triA))) == sqrt(p.Minus(triA).DotP(p.Minus(triA))) + sqrt(p.Minus(triB).DotP(p.Minus(triB)));
}

Point FindContact(Point& p1, Point& p2, Point& triA, Point& triB, Point& triC)
{
	double check1, check2, check3;
	double t1, t2, t3; // 직선의 방정식에서 t값을 임의로 저장할 변수
	int validCount = 0; // 유효한 점들의 갯수를 저장하는 변수 
	Point validPoints[3]; // 유효한 점들을 저장하는 변수 
	Point contact; // 충돌점 : 유효한 점들 중에서 p1과 가장 가까운 점 
	int zeroPlane = 0; // 1 -> y = 0, 2 -> x = 0; 

	// xz, yz 평면에 삼각형과 직선이 존재하는 경우
	if (p1.x == 0 && p2.x == 0 && triA.x == 0 && triB.x == 0 && triC.x == 0)
	{
		zeroPlane = 1;
	}
	else if (p1.y == 0 && p2.y == 0 && triA.y == 0 && triB.y == 0 && triC.y == 0)
	{
		zeroPlane = 2;
	}
	if (zeroPlane == 1 || zeroPlane == 2)
	{
		//  xz,yz 평면의 점을 xy 평면으로 내려 주기
		ToXY(p1);
		ToXY(p2);
		ToXY(triA);
		ToXY(triB);
		ToXY(triC);
	}

	check1 = (triA.x - triC.x) * (p2.y - p1.y) - (triA.y - triC.y) * (p2.x - p1.x);
	check2 = (triB.x - triA.x) * (p2.y - p1.y) - (triB.y - triA.y) * (p2.x - p1.x);
	check3 = (triB.x - triC.x) * (p2.y - p1.y) - (triB.y - triC.y) * (p2.x - p1.x);

	// check 값이 0이 되어버리면 t가 존재하지 않으므로 건너뛰기
	if (check1 != 0)
	{
		t1 = ((triA.y - triC.y) * (p1.x - triC.x) - (triA.x - triC.x) * (p1.y - triC.y)) / check1;
		// 구한 t 값으로 교점 후보 구하기
		Point temp = Line(p1, p2, t1);
		// 교점 후보가 삼각형의 모서리 위에 있는지 확인하고 후보에 추가
		if (IsInEdge(triA, triC, temp))
		{
			validPoints[validCount++] = temp;
		}
	}
	if (check2 != 0)
	{
		t2 = ((triB.y - triA.y) * (p1.x - triA.x) - (triB.x - triA.x) * (p1.y - triA.y)) / check2;
		// 구한 t 값으로 교점 후보 구하기
		Point temp = Line(p1, p2, t2);
		// 교점 후보가 삼각형의 모서리 위에 있는지 확인하고 후보에 추가
		if (IsInEdge(triB, triA, temp))
		{
			validPoints[validCount++] = temp;
		}
	}
	if (check3 != 0)
	{
		t3 = ((triB.y - triC.y) * (p1.x - triC.x) - (triB.x - triC.x) * (p1.y - triC.y)) / check3;
		// 구한 t 값으로 교점 후보 구하기
		Point temp = Line(p1, p2, t3);
		// 교점 후보가 삼각형의 모서리 위에 있는지 확인하고 후보에 추가
		if (IsInEdge(triB, triC, temp))
		{
			validPoints[validCount++] = temp;
		}
	}
	// 첫번째 후보를 충돌점이라고 하고 만약에 점 p1과 거리가 더 짦은 후보가 있을 때 바꾸기
	contact = validPoints[0];
	for (int i = 1; i < validCount; i++)
	{
		double minDistance = p1.Minus(contact).DotP(p1.Minus(contact));
		if (p1.Minus(validPoints[i]).DotP(p1.Minus(validPoints[i])) < minDistance)
		{
			contact = validPoints[i];
		}
	}
	// 유효한 점이 하나도 없을 경우 p1과 가장 가까운 삼각형의 점을 반환
	if (validCount == 0)
	{
		Point closest = triA;
		cout << "직선이 삼각형을 지나지 않으므로 p1과 가장 가까운 삼각형의 점을 반환합니다." << endl;
		// p1 와 tri의 거리의 제곱 == (p1 - tri) 내적 (p1 - tri)   
		double minDistance = p1.Minus(closest).DotP(p1.Minus(closest));
		if (p1.Minus(triB).DotP(p1.Minus(triB)) < minDistance)
		{
			closest = triB;
			minDistance = p1.Minus(triB).DotP(p1.Minus(triB));
		}
		if (p1.Minus(triC).DotP(p1.Minus(triC)) < minDistance)
		{
			closest = triC;
			minDistance = p1.Minus(triB).DotP(p1.Minus(triB));
		}
		contact = closest;
	}
	// 점을 내려서 계산 했으므로 다시 원래 있던 평면으로 올려주기
	if (zeroPlane == 1)
	{
		XYtoYZ(contact);
	}
	else if (zeroPlane == 2)
	{
		XYtoXZ(contact);
	}
	return contact;
}

void showVector(Point vec) {  //세 점을 출력하는 함수
	cout << "( " << vec.x << ", " << vec.y << ", " << vec.z << " )" << endl;
}


int main() {

	Point a, b, c, p1, p2;

	cout << "=> 삼각형 점 A 입력 : ";
	cin >> a.x >> a.y >> a.z;

	cout << "=> 삼각형 점 B 입력 : ";
	cin >> b.x >> b.y >> b.z;

	cout << "=> 삼각형 점 C 입력 : ";
	cin >> c.x >> c.y >> c.z;

	cout << "=> 직선 점 p1 입력 : ";
	cin >> p1.x >> p1.y >> p1.z;

	cout << "=> 직선 점 p2 입력 : ";
	cin >> p2.x >> p2.y >> p2.z;

	/*
	<test case>
	Point a(0, 0, 0); // 삼각형 점 A
	Point b(0, 1, 0); // 삼각형 점 B
	Point c(1, 0, 0); // 삼각형 점 C

	Point p1(0.1, 0.1, -1);
	Point p2(0.1, 0.1, 2);
	*/

	cout << "\n";

	Point v = p2.Minus(p1); // 직선벡터

	cout << "직선 벡터 p1p2 : ( " << v.x << ", " << v.y << ", " << v.z << " )\n";

	Point n; // 평면의 법선벡터
	double d = tt(a, b, c, &n); // ax + by + cz + d = 0 일때, d의 값

	cout << "평면의 법선 벡터 n : ( " << n.x << ", " << n.y << ", " << n.z << " )\n";

	Point p = intersection(p1, p2, n.x, n.y, n.z, d); // 평면과 직선의 교점

	

	if (n.DotP(v) != 0) {
		cout << "삼각형과 직선이 평행하지 않을 때, ";
		if (triinout(a, b, c, p) == 1) {
			cout << "삼각형과 직선의 교점 : ";
			showVector(p); // 교점 출력
			cout << "점이 삼각형 내부에 있다";
		}
		else if (triinout(a, b, c, p) == 0) {
			cout << "삼각형의 변과 직선의 교점 : ";
			showVector(p); // 교점 출력
			cout << "점이 삼각형 선분위에 있다";
		}
		else {
			cout << "평면과 직선의 교점 : ";
			showVector(p); // 교점 출력
			cout << "점이 삼각형 외부에 있다";
		}
	}
	else if (n.x * p1.x + n.y * p1.y + n.z * p1.z + d == 0 && n.x * p2.x + n.y * p2.y + n.z * p2.z + d == 0) {
		cout << "직선의 두 점이 삼각형을 포함한 평면위에 있을 때, ";
		showVector(FindContact(p1, p2, a, b, c));
	}
	else {
		cout << "사선은 평면위에 있지않고 평면과 평행하다." << endl << "교차점이 없다.";
	}

}

