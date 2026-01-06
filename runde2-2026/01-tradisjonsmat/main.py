# This is a python version written just for fun after submitting the rust one because why not

n = int(input())
halves = [int(x) for x in input().split()]

if sum(halves) % n != 0:
    print(-1)
else:
    hs = list(enumerate(halves))
    hs.sort(key=lambda x: x[1])

    a = hs[:n]
    b = hs[n:][::-1]

    for i in range(n):
        print(a[i][0], b[i][0])
