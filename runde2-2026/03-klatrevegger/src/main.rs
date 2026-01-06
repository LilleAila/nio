use std::convert::TryInto; // 2021 edition compatibility (try_into) - it seems nio uses 2015
use std::io;

type Graph = Vec<Vec<(usize, i32)>>;

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

    let mut graph: Graph = vec![Vec::new(); n as usize];

    for _ in 0..k {
        let [a, b, f]: [usize; 3] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()[..]
            .try_into()
            .unwrap();
        graph[a].push((b, f as i32));
        graph[b].push((a, f as i32));
    }

    let mut dp: Vec<Vec<i32>> = vec![vec![i32::MAX; n]; n];

    for u in 0..n {
        dp[u][u] = 0;
        for &(v, w) in &graph[u] {
            dp[u][v] = w;
            dp[v][u] = w;
        }
    }

    for k in 0..n {
        for i in 0..n {
            for j in 0..n {
                let through_k = dp[i][k].max(dp[k][j]);
                if through_k < dp[i][j] {
                    dp[i][j] = through_k;
                }
            }
        }
    }

    let max: i32 = *dp.iter().flat_map(|xs| xs.iter().max()).max().unwrap();

    if max == i32::MAX {
        println!("-1");
    } else {
        println!("{}", max);
    }
}
