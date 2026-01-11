// Only focused on group 3 in which
// b ≤ 50
// n ≤ 15
// Works by using DP to fund the best value of k with a given set of inputs
// I think it would also work quite well for subtask 5, but it runs into memory constraints

use std::convert::TryInto;
use std::io::{self, Lines, StdinLock, Write};

const B_MAX: usize = 50;
const N_MAX: usize = 15;

fn main() {
    let mut lines = io::stdin().lines();

    let mut dp: Vec<Vec<Vec<f64>>> = vec![vec![vec![0.0; N_MAX + 1]; B_MAX + 2]; B_MAX + 2];
    let mut best: Vec<Vec<Vec<usize>>> = vec![vec![vec![0; N_MAX + 1]; B_MAX + 2]; B_MAX + 2];

    for a in 1..=B_MAX {
        for b in a..=B_MAX {
            dp[a][b][0] = 0.0;
        }
    }

    for n in 1..=N_MAX {
        for d in 1..=B_MAX {
            for a in 1..=B_MAX - d + 1 {
                let b = a + d - 1;
                let mut best_e = f64::INFINITY;
                let mut best_k = a;

                for k in a..=b {
                    // Trying to find the probability of success to find the best value of k
                    // with a given value of a, b and n.
                    let p = (k - a + 1) as f64 / (b - a + 1) as f64;
                    let cost_success = dp[a][k][n - 1];
                    let cost_failure = if k + 1 <= b { dp[k + 1][b][n] } else { 0.0 };
                    let expected = k as f64 + p * cost_success + (1.0 - p) * cost_failure;

                    if expected < best_e {
                        best_e = expected;
                        best_k = k;
                    }
                }

                dp[a][b][n] = best_e;
                best[a][b][n] = best_k;
            }
        }
    }

    let r: i32 = lines.next().unwrap().unwrap().trim().parse().unwrap();

    for _ in 0..r {
        let [mut a, mut b, mut n]: [usize; 3] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()[..]
            .try_into()
            .unwrap();

        while n > 0 {
            let k = best[a][b][n];
            if send(k, &mut lines) {
                b = k;
                n -= 1;
            } else {
                a = k + 1;
            }
        }
    }
}

fn send(k: usize, lines: &mut Lines<StdinLock>) -> bool {
    println!("send {}", k);
    io::stdout().flush().unwrap();
    return lines.next().unwrap().unwrap().trim() == "landet";
}
