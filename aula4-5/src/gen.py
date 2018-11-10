import random as rd

n = rd.randint(10000, 200000)

for i in range(n):
    print(rd.randint(-n, n))
