### Testverktøy for Skattekartet
#
# Bruk:
#   python3 testing_tool.py <kjøring av programmet>
#
# Testverktøyet tar kun en linje som input, med tre heltall: N X Y R
# Verktøyet vil først kjøre programmet i kartleggmodus med et NxN koordinatsystem og skatt i posisjon (X, Y).
# Deretter vil verktøyet kjøre programmet i letemodus, hvor koordinatsystemet er rotert R grader med klokka.
# Gyldige verdier for R er 0, 90, 180 og 270.

# Her er noen eksempler på å kjøre verktøyet med ulike språk. Parametrene er her definert
# i en egen fil kalt 1.in. Filen skal kun inneholde én linje med N, X, Y og R.
#
# C++:
#   g++ solution.cpp
#   python3 testing_tool.py ./a.out < 1.in
#
# Python:
#   python3 testing_tool.py python3 ./solution.py < 1.in
#
# Rust:
#   cargo build
#   python3 testing_tool.py ./target/debug/solution < 1.in

# Selv om programmet blir godtatt av testverktøyet, er det ingen garanti for at det er
# korrekt og vil fungerere når du sender inn programmet i konkurransesystemet.

import subprocess
import argparse

def write_to_proc(p, s):
    print(f"< {s}")
    p.stdin.write((s + "\n").encode())
    p.stdin.flush()

def read_line_from_proc(p):
    line = p.stdout.readline().decode()[:-1]
    print(f"> {line}")
    return line

def rotate_clockwise(n, x, y):
    return n + 1 - y, x

parser = argparse.ArgumentParser(
    prog="testing_tool",
    description="testverktøy for binærkoding (les kommentar øverst i kildekoden for forklaring)",
)
parser.add_argument("program", nargs="+")
args = parser.parse_args()

n, x, y, r = map(int, input().split())

if x <= 0 or x > n:
    print(f"Ugyldig x-koordinat: {x}")
    exit()
if y <= 0 or y > n:
    print(f"Ugyldig y-koordinat: {y}")
    exit()

rotations = [0, 90, 180, 270]
if not r in rotations:
    print(f"Ugyldig rotasjon: {r}")
    exit()

print(f"\n---------- Kjøring 1 ----------\n")

coins = []
with subprocess.Popen(
        args.program,
        stdout=subprocess.PIPE,
        stdin=subprocess.PIPE,
    ) as p:
    write_to_proc(p, "kartlegg")
    write_to_proc(p, f"{n} {x} {y}")

    while True:
        line = read_line_from_proc(p)
        if line == "avslutt":
            break
        splitted = line.split()
        if splitted[0] != "marker":
            print(f"Ugyldig linje: {line}")
            exit()
        coin_x = int(splitted[1])
        coin_y = int(splitted[2])
        if coin_x <= 0 or coin_x > n:
            print(f"Ugyldig x-koordinat: {coin_x}")
            exit(0)
        if coin_y <= 0 or coin_y > n:
            print(f"Ugyldig y-koordinat: {coin_y}")
            exit(0)

        coins.append((coin_x, coin_y))

print()
print(f"Mynter: {coins}")

num_clockwise = rotations.index(r)
for i in range(num_clockwise):
    for j in range(len(coins)):
        coins[j] = rotate_clockwise(n, coins[j][0], coins[j][1])
    x, y = rotate_clockwise(n, x, y)

print()
print(f"Etter rotasjon er skatten på ({x}, {y})")
print(f"og myntene har posisjoner: {coins}")

print(f"\n---------- Kjøring 2 ----------\n")

num_queries = 0
with subprocess.Popen(
        args.program,
        stdout=subprocess.PIPE,
        stdin=subprocess.PIPE,
    ) as p:
    write_to_proc(p, "let")
    write_to_proc(p, f"{n}")

    while True:
        line = read_line_from_proc(p)
        splitted = line.split()

        if splitted[0] == "skatt":
            guess_x = int(splitted[1])
            guess_y = int(splitted[2])
            if (guess_x, guess_y) == (x, y):
                print("Programmet fant skatten på riktig koordinat")
            else:
                print("Programmet skrev feil koordinat for skatten")
            break

        if splitted[0] != "sjekk":
            print(f"Ugyldig linje: {line}")
            exit()

        check_x = int(splitted[1])
        check_y = int(splitted[2])
        if check_x <= 0 or check_x > n:
            print(f"Ugyldig x-koordinat: {check_x}")
            exit(0)
        if check_y <= 0 or check_y > n:
            print(f"Ugyldig y-koordinat: {check_y}")
            exit(0)

        if (check_x, check_y) in coins:
            write_to_proc(p, "mynt")
        else:
            write_to_proc(p, "ingenting")
        num_queries += 1

print()
print(f"Programmet brukte {num_queries} spørringer")
