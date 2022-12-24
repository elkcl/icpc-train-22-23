from random import randint

n = randint(1, 20)
q = randint(100, 200)
print(n, q)
for _ in range(n):
    print(randint(1, n), end=' ')
print()
for _ in range(q):
    l = randint(1, n)
    r = randint(l, n)
    k = randint(2, 5)
    print(l, r, k)