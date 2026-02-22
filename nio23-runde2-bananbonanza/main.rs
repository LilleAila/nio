use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let n: usize = lines.next().unwrap().unwrap().parse().unwrap();

    let mut prices_b: Vec<usize> = Vec::new();
    let mut prices_o: Vec<usize> = Vec::new();

    for _ in 0..n {
        let [b, o]: [usize; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        prices_b.push(b);
        prices_o.push(o);
    }
    let prices_b = prices_b;
    let prices_o = prices_o;

    let mut dp: Vec<usize> = vec![0; n + 3];

    for i in 0..n {
        // Wait
        dp[i + 1] = dp[i + 1].max(dp[i]);

        // Sell in Oslo.
        // This action does not affect dp[i], but dp[i+2]
        // as that is when the car arrives back to the warehouse
        if i >= 2 {
            dp[i + 2] = dp[i + 2].max(dp[i - 2] + prices_o[i]);
        }

        // Sell in Bergen. Same logic as above
        if i >= 3 {
            dp[i + 3] = dp[i + 3].max(dp[i - 3] + prices_b[i]);
        }
    }

    println!("{}", dp.iter().max().unwrap());
}
