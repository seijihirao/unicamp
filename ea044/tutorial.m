f=[
  -5; 
  -2
  ]
A=[
  10 12;
  2 1
  ]
b=[
  60; 
  6
  ]
Aeq=[]
beq=[]
lb=[
  0; 
  0
  ]
ub=[]

[x,z]=linprog(f, A, b, Aeq, beq, lb, ub)