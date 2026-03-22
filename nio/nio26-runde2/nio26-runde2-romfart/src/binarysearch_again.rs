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

        let mut success = 0;

        while success < n {
            let k = (a + b) / 2;
            if send(k, &mut lines) {
                success += 1;
                b = k;
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
