use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, _k, t]: [usize; 3] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut socks = Vec::new();
    for _ in 0..n {
        let x: usize = lines.next().unwrap().unwrap().parse().unwrap();
        socks.push(x);
    }
    socks.sort_unstable();
    let socks = socks;

    let mut prev: Option<usize> = None;
    let mut pairs = 0;

    for &s in &socks {
        if let Some(p) = prev {
            if s - p <= t {
                pairs += 1;
                prev = None;
                continue;
            }
        }
        prev = Some(s);
    }

    println!("{}", pairs);
}
