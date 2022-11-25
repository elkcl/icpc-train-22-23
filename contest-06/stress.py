from random import randint

n = randint(1, 5)
q = randint(1, 10)
print(n, q)
for _ in range(n):
    for _ in range(4):
        for _ in range(4):
            print(randint(0, 10**3), end=' ')
        print()
for _ in range(q):
    l = randint(1, n)
    r = randint(l, n)
    print(l, r)