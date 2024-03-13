#include <iostream>

class Shape {
public:
        virtual void draw() const {
                std::cout << "Drawing nothing " << std::endl;
        }
};

class Circle : public Shape {
public:
        Circle(double radius) : radius(radius) {}

        void draw() const override {
                std::cout << "Drawing Circle with radius " << radius << std::endl;
        }
private:
        double radius;
};

int main() {
	Circle obj{5.0};
        Shape* shape1 = &obj;

        // Use dynamic_cast to safely downcast
        Circle* circle = dynamic_cast<Circle*>(shape1);
        if (circle) {
                circle->draw();
        } else {
                std::cout << "Failed to cast to Circle." << std::endl;
        }

        return 0;
}
