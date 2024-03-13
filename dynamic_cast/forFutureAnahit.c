#include <stdio.h>

void A(int* a) { printf("A\n"); }
void B(double* b) { printf("B\n"); }

int main() {
	int i;
	double d;
	
	void (*f1)(int*) = &A;
	void (*f2)(int*) = (void (*)(int*))&B;
	
	int* ptr = (int*)&d;
        f2(ptr);
}

/*
The output is "B" because f2 is assigned to point to function B through casting. 
The type of cast doesn't change which function f2 points to; it still points to B. 
Therefore, when f2 is called, it calls B regardless of the cast. 
Technically, this leads to undefined behavior because of the mismatch in expected argument types (function B expects a double*, but an int* is passed). 
However, in this specific case, it simply prints "B". 
The casting and type mismatch do not affect the function call's outcome due to the nature of the code.
*/



/*
#include <stdio.h>

struct Something {
	int s;
};

struct Something2 {
	double s1;
	char s2;
};

void A(struct Something* a) { printf("%d\n",a->s); }
void B(struct Something2* a) { printf("%lf %c\n",a->s1, a->s2); }

int main() {
	struct Something ob = {4};
	struct Something2 obj = {3.14, 'a'};
	
	void (*f1)(struct Something* this) = &A;
	void (*f2)(struct Something* this) = (void (*)(struct Something*))&B;
	
	struct Something* ptr = (struct Something*)&obj;
        f2(ptr);
        
        //struct Something* ptr2 = (struct Something*)&ob; //undefined behaviour
        //f2(ptr2);
        
}

The program demonstrates casting and function pointer manipulation leading to undefined behavior. 
f2 is explicitly cast to point to function B, which expects a struct Something2*. 
However, when calling f2(ptr) with ptr cast to struct Something* but actually pointing to obj of type struct Something2, B is executed with obj as its argument. 
This results in printing "3.140000 a", which corresponds to the double and char values in obj.

The commented-out section with f2(ptr2) hints at further undefined behavior. 
If executed, it would attempt to treat ob (of type struct Something) as if it were a struct Something2, likely leading to nonsensical output or a crash, as the memory layout and size of ob do not match what B expects.

The initial output line "3.140000 a" occurs because the memory layout of obj aligns with the parameters expected by B, allowing the function to print the values correctly. 
However, the commented-out potential output "//56920145920.000031 m" suggests accessing and interpreting memory in a manner inconsistent with its intended structure, underlining the unpredictability of undefined behavior in such casting scenarios.
*/












