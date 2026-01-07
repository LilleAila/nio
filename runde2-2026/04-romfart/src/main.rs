use std::cmp;
use std::convert::TryInto;
use std::io::{self, Lines, StdinLock, Write};

fn main() {
    let mut lines = io::stdin().lines();

    let r: i32 = lines.next().unwrap().unwrap().trim().parse().unwrap();

    for _ in 0..r {
        let [a, b, n]: [i32; 3] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()[..]
            .try_into()
            .unwrap();

        let mut success: i32 = 0;

        if n == 1 || b - a <= 1 {
            // Subtask 1 and 2 (full score)
            let mut k = a;
            while success < n {
                let result = send(k, &mut lines);
                if result {
                    success += 1;
                } else if a < b {
                    k += 1;
                }
            }
        } else if n <= 15 {
            // Subtask 3
            let mut k = a;
            let mut i = 1;
            let max = (2.0 * n as f32).sqrt() as i32;
            while success < n {
                k = (i / max) ^ 2;
                let result = send(k, &mut lines);
                if result {
                    success += 1;
                } else {
                    k = cmp::min(cmp::max(k * 2, 1), b);
                    i += 1;
                }
            }
        } else {
            // Binary search would be optimal if we didn't take cost into perspective
            // This algorithm becomes more optimal as the limit of N approaches infinity.
            // Due to this, it is likely the best for subtask 4 where N >= 30, but worse
            // for the earlier ones where N has an upper bound, but this only applier to worst-case
            // Due to the different grading algorithm for subtask 4, i assume this is optimal though
            // it does not get a full score, because here it is compared to guessing correctly
            let mut a = a;
            let mut b = b;
            let mut k: i32;
            while success < n {
                k = (b + a) / 2;
                let result = send(k, &mut lines);
                if result {
                    b = k;
                    success += 1;
                } else {
                    a = k + 1;
                }
            }
        }
    }
}

fn send(k: i32, lines: &mut Lines<StdinLock>) -> bool {
    println!("send {}", k);
    io::stdout().flush().unwrap();
    return lines.next().unwrap().unwrap().trim() == "landet";
}
