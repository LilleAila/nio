use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let n: usize = lines.next().unwrap().unwrap().parse().unwrap();

    // NOTE: making everything 1-indexed to make DP easier
    let mut c: Vec<Vec<usize>> = vec![vec![usize::MAX; 2]; n + 1]; // x, y
    for i in 1..=n {
        let [f, b]: [usize; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();
        c[i][0] = 1000 - f;
        c[i][1] = 1000 - b;
    }
    let c = c;

    // Each person has 3 states: dark, light, torch (torch implies light)
    let max = usize::MAX / 2;
    let mut dp: Vec<[[usize; 3]; 3]> = vec![[[max; 3]; 3]; n + 1];
    dp[0][1][1] = 0;

    for i in 1..=n {
        dp[i][0][0] = dp[i - 1][1][1];
        dp[i][1][0] = dp[i - 1][2][1];
        dp[i][0][1] = dp[i - 1][1][2];
        dp[i][1][1] = dp[i - 1][2][2];

        dp[i][2][1] = dp[i][2][1]
            .min(dp[i - 1][0][1] + c[i][0])
            .min(dp[i - 1][1][1] + c[i][0])
            .min(dp[i - 1][2][1] + c[i][0])
            .min(dp[i - 1][1][2] + c[i][0])
            .min(dp[i - 1][2][2] + c[i][0]);

        dp[i][1][2] = dp[i][1][2]
            .min(dp[i - 1][1][0] + c[i][1])
            .min(dp[i - 1][1][1] + c[i][1])
            .min(dp[i - 1][2][1] + c[i][1])
            .min(dp[i - 1][1][2] + c[i][1])
            .min(dp[i - 1][2][2] + c[i][1]);

        dp[i][2][2] = dp[i][2][2]
            .min(dp[i - 1][0][0] + c[i][0] + c[i][1])
            .min(dp[i - 1][1][0] + c[i][0] + c[i][1])
            .min(dp[i - 1][0][1] + c[i][0] + c[i][1])
            .min(dp[i - 1][1][1] + c[i][0] + c[i][1])
            .min(dp[i - 1][2][1] + c[i][0] + c[i][1])
            .min(dp[i - 1][1][2] + c[i][0] + c[i][1])
            .min(dp[i - 1][2][2] + c[i][0] + c[i][1]);
    }

    let result = dp[n][1][1]
        .min(dp[n][2][1])
        .min(dp[n][1][2])
        .min(dp[n][2][2]);

    println!("{}", result);
}
