// Solution specifically for subtask 5 (all belts point upwards)
// This uses a DP over the belts, indexed by the belt index and whether or not it has been used
// This is now only proportional to k^2 and not to n^2 as the previous onees
// While also having a smaller space complexity of just O(k)

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

    let mut belts: Vec<(usize, usize)> = Vec::new();

    for _ in 0..k {
        let l = lines.next().unwrap().unwrap();
        let mut l = l.trim().split_whitespace();
        let x: usize = l.next().unwrap().parse().unwrap();
        let y: usize = l.next().unwrap().parse().unwrap();
        l.next();
        belts.push((x - 1, y - 1));
    }
    belts.sort_unstable();

    let mut dp = vec![[u16::MAX; 2]; belts.len()];
    let start: (usize, usize) = (0, 0);
    let end: (usize, usize) = (n - 1, n - 1);

    for i in 0..k {
        let d = manhattan_distance(start, belts[i]) as u16;
        dp[i][0] = d;
        dp[i][1] = d.saturating_sub(1);
    }

    for i in 0..k {
        for j in 0..i {
            let ba = belts[i];
            let bb = belts[j];
            if ba.1 < bb.1 {
                continue;
            }
            let d = manhattan_distance(bb, ba) as u16;
            for used in 0..=1 {
                let c = dp[j][used];
                if c == u16::MAX {
                    continue;
                }
                dp[i][0] = dp[i][0].min(c + d);
                dp[i][1] = dp[i][1].min(c + d - 1);
            }
        }
    }

    let mut result = 2 * (n - 1) as u16;
    for i in 0..k {
        let rest = manhattan_distance(belts[i], end) as u16;
        result = result.min(dp[i][0] + rest).min(dp[i][1] + rest);
    }

    println!("{}", result);
}

fn manhattan_distance((x1, y1): (usize, usize), (x2, y2): (usize, usize)) -> usize {
    (x2 as i32 - x1 as i32).abs() as usize + (y2 as i32 - y1 as i32).abs() as usize
}
