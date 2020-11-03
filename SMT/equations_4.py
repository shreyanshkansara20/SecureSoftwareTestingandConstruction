from z3 import *

import math


x = Real('x')

y = Real('y')

s = Solver()



s.add(math.e ** (x+y) != ((math.e ** x)*(math.e ** y)))





print(s.check())
print(s.model())
