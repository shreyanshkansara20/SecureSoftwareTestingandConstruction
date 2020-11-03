from z3 import *

s=Solver()
t=BitVec('t',32)

s.add(Not(Or((t&7) != 7, (t<<29) < 0)))

print(s.check())
print(s.model())
