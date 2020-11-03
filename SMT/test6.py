from z3 import *
import math

s=Solver()
x=Real('x')
y=Real('y')

s.add(math.exp(x+y) != (math.exp(x)+math.exp(y)))


print(s.check())
print(s.model())
