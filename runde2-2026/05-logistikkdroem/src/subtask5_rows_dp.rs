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

    let mut rows_with_belt: HashSet<usize> = HashSet::new();
    for (i, r) in belts.iter().enumerate() {
        if r.iter().any(|&x| x) {
            rows_with_belt.insert(i);
        }
    }

    // Traverse the grid one row at a time.
    // We will not need to access the previous results.
    // As such, it is only required to store the last DP instead of everything.
    let mut dp0: Vec<usize> = vec![usize::MAX; n + 2];
    let mut dp1: Vec<usize> = vec![usize::MAX; n + 2];
    dp0[1] = 0;

    for y in 1..=n {
        if rows_with_belt.contains(&y) {
            for x in 2..=n {
                dp0[x] = dp0[x].min(dp0[x - 1] + 1);
            }
            for x in (1..n).rev() {
                dp0[x] = dp0[x].min(dp0[x + 1] + 1);
            }

            if y < n {
                for x in 1..=n {
                    dp1[x] = dp0[x] + if belts[x][y] { 0 } else { 1 };
                }
                std::mem::swap(&mut dp0, &mut dp1);
            }
        } else {
            if y < n {
                for x in 1..=n {
                    dp1[x] = dp0[x] + 1;
                }
                std::mem::swap(&mut dp0, &mut dp1);
            }
        }
    }

    println!("{}", dp0[n]);
}
