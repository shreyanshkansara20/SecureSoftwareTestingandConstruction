from z3 import *

s=Solver()
a=Bool('a')
b=Bool('b')

s.add(And(a,b) != Not(Or(Not(a),Not(b))))

print(s.check())
print(s.model())
