// Too slow - this is O(n * k) which can be up to 1e5 * 2e5 = 2e10 (way too much)

use std::collections::{HashSet, VecDeque};
use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [_n, _m, k]: [usize; 3] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let tastes: Vec<usize> = lines
        .next()
        .unwrap()
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut c: VecDeque<usize> = VecDeque::with_capacity(k);
    let mut result = 0;
    for t in tastes {
        if c.len() == k {
            c.pop_front();
        }
        c.push_back(t);

        if c.len() == k && c.len() == c.iter().collect::<HashSet<_>>().len() {
            result += 1;
            c = VecDeque::with_capacity(k);
        };
    }

    println!("{}", result);
}
