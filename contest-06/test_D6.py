from random import randint

n = randint(1, 5)
print(n)
for _ in range(n):
    print(randint(0, 100), end=' ')
print()