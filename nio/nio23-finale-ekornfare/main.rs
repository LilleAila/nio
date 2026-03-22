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

    let trees: Vec<usize> = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut squirrel: Vec<bool> = vec![true; n];

    let mut queue: Vec<usize> = (0..n).collect();

    // println!("Trees {:?}", trees);
    for _ in 0..k {
        // println!("Squirrels {} {:?}", i, squirrel);
        let mut new_queue: Vec<usize> = Vec::new();
        let mut new_squirrel: Vec<bool> = squirrel.clone();
        while let Some(t) = queue.pop() {
            let ta = if t > 0 { trees[t - 1] } else { 0 };
            let tb = trees[t];
            let tc = if t < n - 1 { trees[t + 1] } else { 0 };

            let sa = if t > 0 { squirrel[t - 1] } else { false };
            let sc = if t < n - 1 { squirrel[t + 1] } else { false };

            let from_left = ta < tb && sa;
            let from_right = tc < tb && sc;

            // dbg!(t, ta, tb, tc, sa, sc, from_left, from_right);
            // println!();

            let to_left = ta > tb;
            let to_right = tc > tb;

            if to_left && !(from_left || from_right) {
                new_squirrel[t] = false;
                new_queue.push(t - 1);
            }

            if to_right && !(from_left || from_right) {
                new_squirrel[t] = false;
                new_queue.push(t + 1);
            }
        }
        queue = new_queue;
        squirrel = new_squirrel;
    }

    println!(
        "{}",
        squirrel
            .iter()
            .map(|&s| if s { "E" } else { "O" })
            .collect::<Vec<_>>()
            .join(" ")
    )
}
