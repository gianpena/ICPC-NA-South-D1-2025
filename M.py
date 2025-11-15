from math import ceil,floor
r,c = map(int,input().split())
if c == 1:
    print(1)
elif r > 2:
    print(-1)
elif r == 1:
    print(int(ceil(c/3)))
elif r == 2:
    print(int(floor(c/2))+1)
