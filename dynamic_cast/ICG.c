#include <stdio.h>
#include <string.h>

struct Shape;
struct Circle;

struct TypeInfo {
	const char* name;
	const struct TypeInfo* parent;
};

struct ShapeVTBL {
	struct TypeInfo* type;
	void (*f1)(const struct Shape* this);
};

struct CircleVTBL {
	struct ShapeVTBL base;
};

struct Shape {
	struct ShapeVTBL* vptr;
};

struct Circle {
	struct Shape subobject;
	double radius;
};

void Circle_ctor(struct Circle* this, double r) { this->radius = r; }
void draw_Shape(const struct Shape* this) { printf("Drawing nothing\n"); }
void draw_Circle(const struct Circle* this) { printf("Drawing Circle with radius %f\n",this->radius); }

struct TypeInfo Shape_type = {"Shape", NULL};
struct TypeInfo Circle_type = {"Circle", &Shape_type};

struct ShapeVTBL shape_vtbl = {&Shape_type, &draw_Shape};
struct CircleVTBL circle_vtbl = {&Circle_type, (void (*)(const struct Shape*))&draw_Circle};

void* dynamic_cast(const struct TypeInfo* current, const struct TypeInfo* target, void* obj) {
	while (current) {
        	if (strcmp(current->name, target->name) == 0) {
			return obj;
		}
		current = (const struct TypeInfo*)current->parent;
	}
	return NULL;
}

int main() {
	struct Circle obj;
	Circle_ctor(&obj,5.0);
	obj.subobject.vptr = (struct ShapeVTBL*)&circle_vtbl;
	
	struct Shape* shape = (struct Shape*)&obj;

   	struct Circle* circle = (struct Circle*)dynamic_cast(shape->vptr->type, &Circle_type, shape);
    	if (circle) {
        	circle->subobject.vptr->f1((struct Shape*)circle);
    	} else {
        	printf("Failed to cast to Circle.\n");
    	}

	return 0;	
}
