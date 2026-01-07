# python3 testing_tool.py cargo run < examples/1.txt

import random
import subprocess
from typing import IO

### Testverktøy for romfart
#
# Du bruker testverktøyet ved å kjøre det fra en terminal.
# Naviger først til mappen hvor løsningen din ligger, hvor denne testing_tool.py også bør ligge, sammen med
# en input-fil.
#
# Om du er på en Mac eller et Unix-system, bruker du kommandoene under i en terminal.
# Om du er på en windows-maskin, bruker du dem i kommandolinjen (cmd.exe, "command prompt"):
#
# Python: python3 ./testing_tool.py [--verbose] [--random] python ./løsning.py < eks.in
# C++:    python3 ./testing_tool.py [--verbose] [--random] ./a.out < in  (etter kompilering)
#
# hvor [] her indikerer en valgfri parameter, løsning.py er løsningen du vil teste og eks.in er en input-fil.
#
# Input-filen leses inn på følgende måte:
#
# Linje 1: antall runder (r)
# Linje 2 til og med 1 + r: En linje med tallene a, b, n, x, separert med mellomrom, hvor x representerer
# den gitte avstanden mellom jorden og Fremtid i dette tilfellet.
#
# Hvis --random er gitt, vil x bli ignorert. Da settes x til et tilfeldig tall mellom a og b.
#
#
# Eksempel:
# Om du i mappen har testing_tool.py, eks.in og en løsning mitt_program.py, kan du på windows kjøre
# python3 testing_tool.py --verbose python mitt_program.py < eks.in
# i kommandolinjen for å få grundig tilbakemelding på hvordan mitt_program.py gjør det på eksempel-inputet.
# Obs: Om du får feilmelding på at "python3" ikke finnes, prøv gjerne med python eller py i stedet.
#
# Merk at det gis ingen garantier for at programmet fungerer hvis din løsning krasjer / kommuniserer paa feil format.
# For øvrig vil vi også påpeke at testverktøyet kan ha feil/bugs, at det kun er til hjelp
# og til slutt at det ikke er det samme programmet som brukes på konkurranseserverene våre.


class ProgramDiedError(Exception):
    def __str__(self):
        return "Your program died"


def main():
    import argparse

    parser = argparse.ArgumentParser(
        prog="testing_tool",
        description="romfart testverktøy (les kommentar øverst i kildekoden for forklaring)",
    )

    parser.add_argument("--verbose", action="store_true")
    parser.add_argument("--random", action="store_true")
    parser.add_argument("program", nargs="+")

    args = parser.parse_args()

    proc = subprocess.Popen(
        args.program,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
    )

    stdin: IO[bytes] = proc.stdin
    stdout: IO[bytes] = proc.stdout

    def to_proc(*args):
        stdin.write(" ".join(map(str, [*args])).encode() + b"\n")
        stdin.flush()

    def from_proc():
        if proc.poll() is not None:
            raise ProgramDiedError()
        return stdout.readline().decode()[:-1]

    def round(a, b, n, x, i):
        if args.verbose:
            print(f"Round {i + 1}: Starting interaction with {a=} {b=} {n=} {x=}")

        used_fuel_this_round = 0

        to_proc(a, b, n)

        successes = 0

        while successes < n:
            cmd = from_proc().split()
            if len(cmd) == 2 and cmd[0] == "send":
                fuel = int(cmd[1])

                if fuel >= x:
                    if args.verbose:
                        print(
                            f"Round {i + 1}: Successfully sent rocket using {fuel} fuel ({x=})"
                        )
                    successes += 1

                    to_proc("landet")
                else:
                    if args.verbose:
                        print(
                            f"Round {i + 1}: Unsuccessfully sent rocket using {fuel} fuel ({x=})"
                        )
                    to_proc("forsvunnet")

                used_fuel_this_round += fuel
            else:
                print("invalid command:", *cmd)

        performance = used_fuel_this_round / (n * x) - 1
        print(
            f"Round {i + 1}: used={used_fuel_this_round}, needed={n * x}, this amounts to {performance * 100:.5f} percent more fuel than needed."
        )

        return performance

    performance = 0

    r = int(input())

    to_proc(r)

    for i in range(r):
        a, b, n, x = map(int, input().split())

        if args.random:
            x = random.randint(a, b)

        performance += round(a, b, n, x, i)

    avg_performance = performance / r
    p = 2 ** (-(avg_performance * 100) / 10)
    print(
        f"On average, you used {avg_performance * 100:.5f} percent more fuel than if you'd magically guessed correctly. On subtask 4 you would therefore get {p * 100:.5f} percent of the available points."
    )


main()
