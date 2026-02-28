// Failed attempt at creating an overly optimized version lol
// Probably ended up being even worse optimized
use std::collections::BTreeSet;
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

    let mut socks = BTreeSet::new();

    for _ in 0..n {
        let x: usize = lines.next().unwrap().unwrap().parse().unwrap();
        socks.insert(x);
    }

    let mut prev: Option<usize> = None;
    let mut pairs = 0;

    for &s in socks.iter() {
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
