from z3 import *
s=Solver()
a=BitVec('a',32)
b=BitVec('b',32)

s.add(a>b)

print(s.check())
print(s.model())
