from z3 import *
s=Solver()
x=Int('x')
y=Int('y')

s.add(28*x+34*y == 844)
s.add(x>=0, y>=0)

ctr=1
while s.check() == sat:
    mdl=s.model()
    print("Solution:"+str(ctr))
    print("x="+str(mdl[x])+"y="+str(mdl[y]))
    s.add(x != mdl[x])
    s.add(y != mdl[y])
    ctr+=1
