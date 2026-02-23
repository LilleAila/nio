use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, k]: [usize; 2] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut houses: Vec<bool> = vec![false; n];

    for _ in 0..k {
        let [a, b]: [usize; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        houses[a] = !houses[a];
        if b + 1 < n {
            houses[b + 1] = !houses[b + 1];
        }
    }

    let mut flip = false;
    let mut result = 0;

    for h in houses {
        flip ^= h;

        result += !flip as usize;
    }

    println!("{}", result);
}
