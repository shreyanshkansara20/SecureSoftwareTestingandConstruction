from z3 import *
s=Solver()
x=BitVec('x',32)
y=BitVec('y',32)

s.add(~(x)+~(y)+1 != ~(x+y))

print(s.check())
print(s.model())
