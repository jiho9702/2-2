#include <iostream>
using namespace std;
/*
class Dog {
private:
	string name;
	int age;
	int weight;
public:
	Dog(string s, int a, int w) {
		name = s;
		age = a;
		weight = w;
	}
	void display() {
		cout << name << age << weight << endl;
	}
	void bark() {
		cout << "港港" << endl;
	}
};

class Cat {
private:
	string name;
	int age; 
	int weight;
public:
	Cat(string s, int a, int w) {
		name = s;
		age = a;
		weight = w;
	}
	void display() {
		cout << name << age << weight << endl;
	}
	void meow() {
		cout << "具克" << endl;
	}
};
*/

class Animal {
	string name;
	int age, weight;

public:
	Animal(string n, int a, int w)
		:name(n), age(a), weight(w) {}

	void display() const {
		cout << name << age << weight;
	}
};

class Dog : public Animal {
public:
	Dog(string n, int a, int w) :Animal(n, a, w) {}

	void bark() {
		cout << "港港" << endl;
	}
};

class Cat : public Animal {
public:
	Cat(string n, int a, int w) :Animal(n, a, w) {}

	void meow() {
		cout << "具克" << endl;
	}
};


int main() {

	Dog dol("滦", 8, 20);
	Cat nabi("唱厚", 4, 15);

	dol.display();
	dol.bark();

	nabi.display();
	nabi.meow();

}