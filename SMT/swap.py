from z3 import *

s=Solver()
x=BitVec('x',32)
y=BitVec('y',32)

init_x=x
init_y=y

x=x^y
y=y^x
x=x^y

s.add(And(init_x != y, init_y != x))

print(s.check())
print(s.model())
