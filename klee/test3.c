#include<stdio.h>

unsigned mod_opt(unsigned x, unsigned y)
{
	if((y & -y) == y)
	  return x & (y-1);
	else
	  return x % y;
}
unsigned mod(unsigned x, unsigned y)
{
	return x % y;
}
int main()
{
	unsigned x,y;
	klee_make_symbolic(&x, sizeof(x), "x");
	klee_make_symbolic(&y, sizeof(y), "y");
	assert(mod(x,y) == mod_opt(x,y));
	return 0;
}
