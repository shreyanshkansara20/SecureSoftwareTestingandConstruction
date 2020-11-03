from z3 import *

s=Solver()
p=Bool('p')
q=Real('q')

s.add(Or(q < 5, q > 10))
s.add(Or(p, q**2 == 2))
s.add(Not(p))

print(s.check())
print(s.model())
