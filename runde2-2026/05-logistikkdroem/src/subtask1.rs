// This solution only works for subtask 1.

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

    let mut positive_belts: i32 = 0;

    for _ in 0..k {
        let l = lines.next().unwrap().unwrap();
        let mut l = l.trim().split_whitespace();
        l.next();
        l.next();
        let d = l.next().unwrap();
        if d == "o" || d == "h" {
            positive_belts += 1;
        }
    }

    let weight = 2 * (n - 1) - positive_belts as usize;
    println!("{}", weight);
}

fn add_coord((x, y): (i32, i32), (dx, dy): (i32, i32)) -> (i32, i32) {
    return (x + dx, y + dy);
}
