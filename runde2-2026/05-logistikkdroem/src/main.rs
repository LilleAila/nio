// Solution specifically for subtask 5 (all belts point upwards)

use std::collections::VecDeque;
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

    let index = |x, y| n * x + y;
    let end = index(n - 1, n - 1);
    let mut belts: Vec<bool> = vec![false; n * n];

    for _ in 0..k {
        let l = lines.next().unwrap().unwrap();
        let mut l = l.trim().split_whitespace();
        let x: usize = l.next().unwrap().parse().unwrap();
        let y: usize = l.next().unwrap().parse().unwrap();
        l.next();
        belts[index(x, y)] = true;
    }

    let mut dp = vec![u16::MAX; n * n];
    dp[end] = 0;
    let mut stack: VecDeque<usize> = VecDeque::new();
    stack.push_back(end);

    while let Some(a) = stack.pop_front() {
        let c = dp[a];
        let new_cost = c + 1;
        let x = a % n;
        let y = a / n;

        if y + 1 < n {
            let b = a + n;
            if dp[b] > new_cost {
                dp[b] = new_cost;
                stack.push_back(b);
            }
        }

        if y >= 1 {
            let b = a - n;
            let cost = if belts[b] { 0 } else { 1 };
            let new_cost = c + cost;
            if dp[b] > new_cost {
                dp[b] = new_cost;
            }
            if c == 0 {
                stack.push_front(b);
            } else {
                stack.push_back(b);
            }
        }

        if x >= 1 {
            let b = a - 1;
            if dp[b] > new_cost {
                dp[b] = new_cost;
                stack.push_back(b);
            }
        }

        if x + 1 < n {
            let b = a + 1;
            if dp[b] > new_cost {
                dp[b] = new_cost;
                stack.push_back(b);
            }
        }
    }

    println!("{}", dp[0]);
}
