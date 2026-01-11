use std::collections::HashSet;
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
        .collect::<Vec<_>>()[..]
        .try_into()
        .unwrap();

    let mut belts: Vec<Vec<bool>> = vec![vec![false; n + 2]; n + 2];

    for _ in 0..k {
        let l = lines.next().unwrap().unwrap();
        let mut l = l.trim().split_whitespace();
        let x: usize = l.next().unwrap().parse().unwrap();
        let y: usize = l.next().unwrap().parse().unwrap();
        l.next();
        belts[x][y] = true;
    }
}
