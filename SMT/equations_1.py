from z3 import *

s=Solver()

a=Real('a')
b=Real('b')

s.add((a+b)**2 != (a**2+2*a*b+b**2))

print(s.check())
print(s.model())
