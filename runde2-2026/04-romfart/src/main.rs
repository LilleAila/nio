use std::cmp;
use std::convert::TryInto;
use std::io::{self, Lines, StdinLock, Write};

fn main() {
    let mut lines = io::stdin().lines();

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

        let mut success = false;
        let mut k = a + (b - a) / 3;
        while n > 0 {
            if !success {
                k = a + (b - a) / 3;
            }
            if send(k, &mut lines) {
                b = k;
                success = truer
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
