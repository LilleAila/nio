// This greedy bitmask solution is pretty close to being correct, but i think the problem lies in
// that if i for example have AB incompatible with each other, it will stop at `ABC` and split
// this at `A` suth chat i have `A` and `B` but if there was more values, the entire group
// `ABABABC` would be valid, but my code makes it split into A B A B A BC

use std::collections::HashSet;
use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, m]: [usize; 2] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let s: Vec<usize> = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .chars()
        .map(|x| x as usize - 'A' as usize)
        .collect();

    let mut ms: Vec<usize> = vec![0x3FFFFFF; 26];

    for _ in 0..m {
        let [o, u]: [usize; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.chars().next().unwrap() as usize - 'A' as usize)
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        // ms[u] ^= 1 << o;
        ms[u] &= !(1 << o);
    }

    let mut groups = 0;

    let mut valid_leaders = 0x3FFFFFF;
    let mut group = 0;

    for x in s {
        group |= 1 << x;
        valid_leaders &= ms[x];

        let leaders = valid_leaders & group;
        if leaders == 0 {
            groups += 1;
            group = 1 << x;
            valid_leaders = ms[x];
        }
    }
    groups += 1;

    println!("{}", groups);
}
