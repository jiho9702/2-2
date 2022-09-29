#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
public:
	double x, y, z;
	Point(double xx = 0, double yy = 0, double zz = 0)  //������
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

	double DotP(Point vec) {  //�����ϴ� ����Լ�
		return (x * vec.x) + (y * vec.y) + (z * vec.z);
	}

	Point crossProduct(Point vec) //����
	{
		return Point((y * vec.z) - (z * vec.y), (z * vec.x) - (x * vec.z), (x * vec.y) - (y * vec.x));
	}

	Point scalarMultiple(double a) //��Į��� (�Ǽ� a)
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

// ���� ������ ���� ���ϴ� �Լ�
Point intersection(Point p1, Point p2, double a, double b, double c, double d) {
	double tmp1 = a * p1.x + b * p1.y + c * p1.z + d;
	double tmp2 = a * (p1.x - p2.x) + b * (p1.y - p2.y) + c * (p1.z - p2.z);

	// ������ ������(Point Line() �Լ��� ����) -> L(t) = p1 + t * (p2 - p1)
	double t = tmp1 / tmp2;

	// Line() �Լ��� �Ű������� ���� t�� ������ ��, ��ȯ�Ǵ� Point ��ǥ�� ����
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

double tt(Point A, Point B, Point C, Point* n) {    // 7. ����� ������ �Լ�

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
	// ���� ������ ���� ���Ͽ� ������ �糡 �� ������ �Ÿ� ���� �糡 �� ������ �Ÿ��� ������ �̿��� ���� �� �� ���� ���� Ȯ�� 
	return sqrt(triB.Minus(triA).DotP(triB.Minus(triA))) == sqrt(p.Minus(triA).DotP(p.Minus(triA))) + sqrt(p.Minus(triB).DotP(p.Minus(triB)));
}

Point FindContact(Point& p1, Point& p2, Point& triA, Point& triB, Point& triC)
{
	double check1, check2, check3;
	double t1, t2, t3; // ������ �����Ŀ��� t���� ���Ƿ� ������ ����
	int validCount = 0; // ��ȿ�� ������ ������ �����ϴ� ���� 
	Point validPoints[3]; // ��ȿ�� ������ �����ϴ� ���� 
	Point contact; // �浹�� : ��ȿ�� ���� �߿��� p1�� ���� ����� �� 
	int zeroPlane = 0; // 1 -> y = 0, 2 -> x = 0; 

	// xz, yz ��鿡 �ﰢ���� ������ �����ϴ� ���
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
		//  xz,yz ����� ���� xy ������� ���� �ֱ�
		ToXY(p1);
		ToXY(p2);
		ToXY(triA);
		ToXY(triB);
		ToXY(triC);
	}

	check1 = (triA.x - triC.x) * (p2.y - p1.y) - (triA.y - triC.y) * (p2.x - p1.x);
	check2 = (triB.x - triA.x) * (p2.y - p1.y) - (triB.y - triA.y) * (p2.x - p1.x);
	check3 = (triB.x - triC.x) * (p2.y - p1.y) - (triB.y - triC.y) * (p2.x - p1.x);

	// check ���� 0�� �Ǿ������ t�� �������� �����Ƿ� �ǳʶٱ�
	if (check1 != 0)
	{
		t1 = ((triA.y - triC.y) * (p1.x - triC.x) - (triA.x - triC.x) * (p1.y - triC.y)) / check1;
		// ���� t ������ ���� �ĺ� ���ϱ�
		Point temp = Line(p1, p2, t1);
		// ���� �ĺ��� �ﰢ���� �𼭸� ���� �ִ��� Ȯ���ϰ� �ĺ��� �߰�
		if (IsInEdge(triA, triC, temp))
		{
			validPoints[validCount++] = temp;
		}
	}
	if (check2 != 0)
	{
		t2 = ((triB.y - triA.y) * (p1.x - triA.x) - (triB.x - triA.x) * (p1.y - triA.y)) / check2;
		// ���� t ������ ���� �ĺ� ���ϱ�
		Point temp = Line(p1, p2, t2);
		// ���� �ĺ��� �ﰢ���� �𼭸� ���� �ִ��� Ȯ���ϰ� �ĺ��� �߰�
		if (IsInEdge(triB, triA, temp))
		{
			validPoints[validCount++] = temp;
		}
	}
	if (check3 != 0)
	{
		t3 = ((triB.y - triC.y) * (p1.x - triC.x) - (triB.x - triC.x) * (p1.y - triC.y)) / check3;
		// ���� t ������ ���� �ĺ� ���ϱ�
		Point temp = Line(p1, p2, t3);
		// ���� �ĺ��� �ﰢ���� �𼭸� ���� �ִ��� Ȯ���ϰ� �ĺ��� �߰�
		if (IsInEdge(triB, triC, temp))
		{
			validPoints[validCount++] = temp;
		}
	}
	// ù��° �ĺ��� �浹���̶�� �ϰ� ���࿡ �� p1�� �Ÿ��� �� �F�� �ĺ��� ���� �� �ٲٱ�
	contact = validPoints[0];
	for (int i = 1; i < validCount; i++)
	{
		double minDistance = p1.Minus(contact).DotP(p1.Minus(contact));
		if (p1.Minus(validPoints[i]).DotP(p1.Minus(validPoints[i])) < minDistance)
		{
			contact = validPoints[i];
		}
	}
	// ��ȿ�� ���� �ϳ��� ���� ��� p1�� ���� ����� �ﰢ���� ���� ��ȯ
	if (validCount == 0)
	{
		Point closest = triA;
		cout << "������ �ﰢ���� ������ �����Ƿ� p1�� ���� ����� �ﰢ���� ���� ��ȯ�մϴ�." << endl;
		// p1 �� tri�� �Ÿ��� ���� == (p1 - tri) ���� (p1 - tri)   
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
	// ���� ������ ��� �����Ƿ� �ٽ� ���� �ִ� ������� �÷��ֱ�
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

void showVector(Point vec) {  //�� ���� ����ϴ� �Լ�
	cout << "( " << vec.x << ", " << vec.y << ", " << vec.z << " )" << endl;
}


int main() {

	Point a, b, c, p1, p2;

	cout << "=> �ﰢ�� �� A �Է� : ";
	cin >> a.x >> a.y >> a.z;

	cout << "=> �ﰢ�� �� B �Է� : ";
	cin >> b.x >> b.y >> b.z;

	cout << "=> �ﰢ�� �� C �Է� : ";
	cin >> c.x >> c.y >> c.z;

	cout << "=> ���� �� p1 �Է� : ";
	cin >> p1.x >> p1.y >> p1.z;

	cout << "=> ���� �� p2 �Է� : ";
	cin >> p2.x >> p2.y >> p2.z;

	/*
	<test case>
	Point a(0, 0, 0); // �ﰢ�� �� A
	Point b(0, 1, 0); // �ﰢ�� �� B
	Point c(1, 0, 0); // �ﰢ�� �� C

	Point p1(0.1, 0.1, -1);
	Point p2(0.1, 0.1, 2);
	*/

	cout << "\n";

	Point v = p2.Minus(p1); // ��������

	cout << "���� ���� p1p2 : ( " << v.x << ", " << v.y << ", " << v.z << " )\n";

	Point n; // ����� ��������
	double d = tt(a, b, c, &n); // ax + by + cz + d = 0 �϶�, d�� ��

	cout << "����� ���� ���� n : ( " << n.x << ", " << n.y << ", " << n.z << " )\n";

	Point p = intersection(p1, p2, n.x, n.y, n.z, d); // ���� ������ ����

	

	if (n.DotP(v) != 0) {
		cout << "�ﰢ���� ������ �������� ���� ��, ";
		if (triinout(a, b, c, p) == 1) {
			cout << "�ﰢ���� ������ ���� : ";
			showVector(p); // ���� ���
			cout << "���� �ﰢ�� ���ο� �ִ�";
		}
		else if (triinout(a, b, c, p) == 0) {
			cout << "�ﰢ���� ���� ������ ���� : ";
			showVector(p); // ���� ���
			cout << "���� �ﰢ�� �������� �ִ�";
		}
		else {
			cout << "���� ������ ���� : ";
			showVector(p); // ���� ���
			cout << "���� �ﰢ�� �ܺο� �ִ�";
		}
	}
	else if (n.x * p1.x + n.y * p1.y + n.z * p1.z + d == 0 && n.x * p2.x + n.y * p2.y + n.z * p2.z + d == 0) {
		cout << "������ �� ���� �ﰢ���� ������ ������� ���� ��, ";
		showVector(FindContact(p1, p2, a, b, c));
	}
	else {
		cout << "�缱�� ������� �����ʰ� ���� �����ϴ�." << endl << "�������� ����.";
	}

}

