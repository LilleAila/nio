// This solution works but the time complexity is wayyy to high

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

    let s: Vec<u8> = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .chars()
        .map(|x| x as u8 - 'A' as u8)
        .collect();

    let mut ms: Vec<Vec<bool>> = vec![vec![true; 26]; 26];

    for _ in 0..m {
        let [o, u]: [u8; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.chars().next().unwrap() as u8 - 'A' as u8)
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        ms[u as usize][o as usize] = false;
    }

    let mut dp: Vec<usize> = vec![usize::MAX; n];
    dp[0] = 1;

    for i in 1..n {
        dp[i] = dp[i].min(dp[i - 1] + 1);

        for j in 0..=i {
            let group = &s[j..=i];
            let mut valid = false;

            for &o in group {
                let mut valid_o = true;
                for &u in group {
                    if !ms[u as usize][o as usize] {
                        valid_o = false;
                        break;
                    }
                }

                if valid_o {
                    valid = true;
                    break;
                }
            }

            if valid {
                if j > 0 {
                    dp[i] = dp[i].min(dp[j - 1] + 1);
                } else {
                    dp[i] = dp[i].min(1);
                }
            }
        }
    }

    println!("{:?}", dp[n - 1]);
}
