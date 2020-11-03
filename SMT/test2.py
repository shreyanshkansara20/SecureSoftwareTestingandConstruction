from z3 import *

s=Solver()
t=BitVec('t',4)

s.add(Not(Or(t > 0, (t-1) < 0)))

print(s.check())
print(s.model())
