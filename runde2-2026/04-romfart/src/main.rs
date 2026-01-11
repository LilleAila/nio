use std::cmp;
use std::convert::TryInto;
use std::io::{self, Lines, StdinLock, Write};

fn main() {
    let mut lines = io::stdin().lines();

    // Based on the optimal solution from 2024/25 finale
    // https://nio.no/oppgaver/2024-2025/NIO2025-finale-fasit.pdf
    // This gives different threshold values to use based on n
    // idk if this even works
    let mut e: Vec<f64> = vec![0.0; 1001];
    e[1] = 0.5;
    for i in 2..=1000 {
        e[i] = (1.0 + e[i - 1] * e[i - 1]) / 2.0;
    }

    let r: i32 = lines.next().unwrap().unwrap().trim().parse().unwrap();

    for _ in 0..r {
        let [mut a, mut b, n]: [i32; 3] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()[..]
            .try_into()
            .unwrap();

        let mut n = n as usize;

        while n > 0 {
            let d = (b - a) as f64;
            let k = ((a as f64 + d * e[n]).floor() as i32).max(a).min(b);
            if send(k, &mut lines) {
                b = k;
                n -= 1;
            } else {
                a = k + 1;
            }
        }
    }
}

fn send(k: i32, lines: &mut Lines<StdinLock>) -> bool {
    println!("send {}", k);
    io::stdout().flush().unwrap();
    return lines.next().unwrap().unwrap().trim() == "landet";
}
