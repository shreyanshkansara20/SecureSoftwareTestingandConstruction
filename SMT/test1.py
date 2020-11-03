from z3 import *

s=Solver()
t=BitVec('t',32)
s.add(And(t>0 , t*t <0))

print(s.check())
print(s.model())


