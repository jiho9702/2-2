#include <iostream>
#include <math.h>
using namespace std;
#define e = 2.71828;

int main() {

	double x; //e�� ������
	double count; // ���Ϸ� �޼� Ƚ��;

	cin >> x >> count;

	double fact = 0, power = 0;
	double tailor = 1;

	for (int i = 1; i <= count; i++) {
		int num = 1;
		power = pow(x, i);
		for (int j = 1; j <= i; j++) {
			num = num * j;
			fact = num;
		}
		tailor += power * (1/fact);
	}

	cout << tailor;
}