// use std::cmp;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let n: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();
    let teeth: Vec<bool> = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split(" ")
        .map(|x| x == "1")
        .collect();

    // println!("{} {:?}", n, teeth);

    let mut potential: i64 = 0;
    for (i, &t) in teeth.iter().enumerate() {
        if t || (i > 0 && teeth[i - 1]) || (i < n - 1 && teeth[i + 1]) {
            potential += 1;
        }
    }

    // Temporary code used before completely solving it to get partial points
    // Subtask 1 and 2
    // let min = if teeth.iter().any(|&x| x) { 1 } else { 0 };
    // Subtask 3
    // let min = teeth.iter().filter(|&&x| x).count();
    // Subtask 4
    // let min = (teeth.len() as f64 / 3.0).ceil() as i64;

    // A draft of a solution using DP. This might work in theory, but the actual solution turned
    // out to be much simpler. The DP solution works for some cases, but not always. I think there
    // is something wrong with the conditions set for checking whether to add an infection or not.
    // The most likely issue it that it does not properly check the {n-1, n, n+1} condition which
    // sometimes leads to results which are too big.
    // let mut dp: Vec<Vec<i64>> = vec![vec![i64::MAX; 2]; n + 1];
    // dp[0][0] = 0; // Initial DP state
    //
    // // Populate using tabulation
    // for i in 0..n {
    //     for s in 0..=1 {
    //         let state = dp[i][s];
    //         if state == i64::MAX {
    //             // This state is invalid
    //             continue;
    //         }
    //
    //         if i == 0 || !teeth[i - 1] || s == 1 {
    //             // Tooth is either not damaged or already covered by an infection.
    //             // This means that the tooth will not need to be infected
    //             dp[i + 1][0] = cmp::min(dp[i + 1][0], state);
    //         }
    //
    //         // Set the next state for the choice that the tooth will be covered.
    //         if (i > 0 && teeth[i - 1]) || teeth[i] || (i < n - 2 && teeth[i + 1]) {
    //             dp[i + 1][1] = cmp::min(dp[i + 1][1], state + 1);
    //         }
    //     }
    // }
    //
    // let min = cmp::min(dp[n][0], dp[n][1]);

    let mut min: i64 = 0;
    let mut i: usize = 0;
    while i < n {
        if teeth[i] {
            min += 1;
            i += if i + 1 < n { 3 } else { 1 };
        } else {
            i += 1;
        }
    }

    println!("{} {}", min, potential);
}
