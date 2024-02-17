#include <stdio.h>

struct A;
struct B;

struct TypeInfo {
	const char* name;
	const char* parent;
};
struct AVTBL {
	struct TypeInfo* type;
	void (*f1)(struct A* this);
	void (*f2)(struct A* this);
};
struct BVTBL {
	struct TypeInfo* type;
	void (*f1)(struct B* this);
	void (*f2)(struct A* this);
	void (*f3)(struct B* this);
};


struct A {
	struct AVTBL* vptr;
	int m;
};

struct B {
	struct A subobject;
	int x;
};

void A_foo(struct A* this) { printf("Hi from A::foo()\n");}
void A_bar(struct A* this) { printf("Hi from A::bar()\n");}
void A_simple(struct A* this) { printf("Hi from A::simple()\n");}

void B_foo(struct B* this) { printf("Hi from B::foo()\n");}
void B_simple(struct B* this) { printf("Hi from B::simple()\n");}
void B_other(struct B* this) { printf("Hi from B::other()\n");}

int main() {
	struct A ob;
	struct B obj;

	struct TypeInfo A_type;
	A_type.name = "A";
	A_type.parent = NULL;

	struct TypeInfo B_type;
	B_type.name = "B";
	B_type.parent = "A";

	struct AVTBL at;
	at.type = &A_type;
	at.f1 = &A_foo;
	at.f2 = &A_bar;

	struct BVTBL bt;
	bt.type = &B_type;
	bt.f1 = &B_foo;
	bt.f2 = &A_bar;
	bt.f3 = &B_other;

	ob.vptr = &at;
	obj.subobject.vptr = (struct AVTBL*)&bt;
/*
	A_foo(&ob);
	A_bar(&ob);
	A_simple(&ob);

	B_foo(&obj);
	B_simple(&obj);
	B_other(&obj);
	A_bar(&obj.subobject);
*/
	struct A* ptr = &ob;
	
	(ptr->vptr)->f1(ptr);
	A_bar(ptr);
	A_simple(ptr);
	/*
	printf("INFO\n");
	printf("%s\n",ptr->vptr->type->name);	
	//printf("%s\n",ptr->vptr->type->parent);//segmentation fault, because it is NULL	
	*/

	ptr = (struct A*)&obj;
	
	//((((struct B*)ptr)->subobject).vptr)->f1(ptr);
	((((struct B*)ptr)->subobject).vptr)->f1((struct B*)ptr);
	A_simple(ptr); 
	A_bar(ptr);
	/*
	printf("INFO\n");
	printf("%s\n",ptr->vptr->type->name);	
	printf("%s\n",ptr->vptr->type->parent);	
	*/

	return 0;
}
