from z3 import *

s=Solver()
x=BitVec('x',32)
y=BitVec('y',32)
val=BitVec('val',32)

s.add(And(x<-3,y>x))
s.add(val==x+y)

print(s.check())
print(s.model())
