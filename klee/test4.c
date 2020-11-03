#include<stdio.h>
#include<stdint.h>


uintptr_t safe_addptr(int *of, uint64_t a, uint64_t b)
{
	uintptr_t r = a+b;
	if(r < a || r < b)
	{
	  *of=1;
	  klee_assert(0);
	 }  
	return r;
}
void main()
{
	uint64_t a,b;
	int var=500;
	int *of=&var;
	klee_make_symbolic(&a, sizeof(a), "a");
	klee_make_symbolic(&b, sizeof(b), "b");
	safe_addptr(of,a,b);
}


