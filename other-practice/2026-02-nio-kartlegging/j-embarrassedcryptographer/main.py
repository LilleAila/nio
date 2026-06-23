import math

limit = 1_000_000
prime = [True for _ in range(limit+1)]
prime[0], prime[1] = False, False

for p in range(2, int(math.sqrt(limit)) + 1):
    if prime[p]:
        for i in range(p * p, limit+1, p):
            prime[i] = False

primes = [i for i, p in enumerate(prime) if p]

while True:
    line = input().strip()
    k, l = map(int, line.split()) # noqa: E741
    if k == 0:
        break

    good = True
    for p in primes:
        if p >= l:
            break
        if k % p == 0:
            print(f"BAD {p}")
            good = False
            break
    if good:
        print("GOOD")
