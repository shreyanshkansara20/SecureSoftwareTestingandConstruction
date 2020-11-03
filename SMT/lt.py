from z3 import *

import math



x = Real('x')

y = Real('y')

z = Real('z')

s = Solver()

# z = x+y

exp1 = math.e ** (x+y)

exp2 = (math.e**x) * (math.e**y)



s.add(exp1 != exp2)

state = s.check()

if state == unsat:

    print("The Theorem is valid for all Real a and b")

else:

    print("The Theorem is NOT valid for all Real a and b")
