use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let n: usize = lines.next().unwrap().unwrap().parse().unwrap();

    // NOTE: making everything 1-indexed to make DP easier
    let mut calories: Vec<Vec<usize>> = vec![vec![usize::MAX; 2]; n]; // x, y
    for i in 0..n {
        let [f, b]: [usize; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();
        calories[i][0] = 1000 - f;
        calories[i][1] = 1000 - b;
    }
    let calories = calories;

    // Generate costs for all 4 combinations of carrying torches.
    let mut cost: Vec<[usize; 4]> = vec![[0; 4]; n];
    for i in 0..n {
        for m in 0..4 {
            let mut c = 0;
            // front
            if m & 0b01 != 0 {
                c += calories[i][0];
            }
            // back
            if m & 0b10 != 0 {
                c += calories[i][1];
            }
            cost[i][m] = c;
        }
    }

    let mut dp: Vec<[usize; 4]> = vec![[usize::MAX / 2; 4]; n];

    for m in 1..4 {
        dp[0][m] = cost[0][m];
    }

    for i in 1..n {
        for m in 0..4 {
            for n in 0..4 {
                // test all combinations of masks for the two columns
                let prev_front_lit = n & 0b01 != 0 || n & 0b10 != 0 || m & 0b01 != 0;
                let prev_back_lit = n & 0b01 != 0 || n & 0b10 != 0 || m & 0b10 != 0;
                if prev_front_lit && prev_back_lit {
                    // Mask is valid; there are at least 2 torches in the 2x2 area
                    dp[i][m] = dp[i][m].min(dp[i - 1][n] + cost[i][m]);
                }
            }
        }
    }

    println!("{}", dp[n - 1].iter().min().unwrap());
}
