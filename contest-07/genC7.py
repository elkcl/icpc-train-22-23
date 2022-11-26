from random import randint

n = randint(1, 10)
k = randint(1, 20)
print(n, k)
for _ in range(n + 1):
    print(randint(-10, 10), randint(-10, 10))