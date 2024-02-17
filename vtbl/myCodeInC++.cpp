#include <iostream>

class A {
public:
	virtual void foo() { std::cout << "Hi from A::foo()" << std::endl;}
	virtual void bar() { std::cout << "Hi from A::bar()" << std::endl;}
	void simple() { std::cout << "Hi from A::simple()" << std::endl;}
private:
	int m;
};

class B : public A {
public:
	void foo() override { std::cout << "Hi from B::foo()" << std::endl;}
	void simple() { std::cout << "Hi from B::simple()" << std::endl;}
	virtual void other() { std::cout << "Hi from B::other()" << std::endl;}
private:
	int x;
};

int main() {
	A ob;
	B obj;
	
	ob.foo();
	ob.bar();
	ob.simple();
	
	obj.foo();
	obj.simple();
	obj.other();
	obj.bar();

	A* ptr = &ob;
	ptr->foo();
	ptr->bar();
	ptr->simple();

	ptr = &obj;
	ptr->foo();
	ptr->simple();
	//ptr->other();
	ptr->bar();
	
	return 0;
}
