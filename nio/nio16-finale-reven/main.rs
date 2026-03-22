use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [ox, oy]: [f64; 2] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let n: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();

    let mut nodes: Vec<(f64, f64)> = Vec::new();
    for _ in 0..n {
        let [x, y]: [f64; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();
        nodes.push((x, y));
    }

    let mut dp = vec![f64::MAX; 1 << n];
    dp[0] = 0.0;

    let dist = |(x1, y1): (f64, f64), (x2, y2): (f64, f64)| {
        pythagoras(ox, oy, x1, y1) + pythagoras(x1, y1, x2, y2) + pythagoras(x2, y2, ox, oy)
    };

    let mut dists = vec![vec![f64::MAX; n]; n];
    for i in 0..n {
        for j in 0..n {
            dists[i][j] = dist(nodes[i], nodes[j]);
        }
    }

    for mask in 0..(1 << n) {
        if dp[mask] == f64::MAX {
            continue;
        }

        // First unburied hen
        let mut i = 0;
        while i < n && mask & (1 << i) != 0 {
            i += 1;
        }

        if i == n {
            continue;
        }

        let remaining = (1 << n) - 1 - mask;

        // Doing i..n also has the case of (i, i) which is the same as only taking a single hen.
        // The result will be the same, but this avoids manually handling that extra case.
        for j in i..n {
            if mask & (1 << j) == 0 {
                let new_mask = mask | (1 << i) | (1 << j);
                if remaining == ((1 << i) | (1 << j)) {
                    dp[new_mask] = dp[new_mask].min(
                        dp[mask]
                            + pythagoras(ox, oy, nodes[i].0, nodes[i].1)
                            + pythagoras(nodes[i].0, nodes[i].1, nodes[j].0, nodes[j].1),
                    );
                } else {
                    dp[new_mask] = dp[new_mask].min(dp[mask] + dists[i][j]);
                }
            }
        }
    }

    // for (i, &x) in dp.iter().enumerate() {
    //     println!("{:04b} {:?}", i, x);
    // }

    println!("{}", dp[(1 << n) - 1]);
}

fn pythagoras(x1: f64, y1: f64, x2: f64, y2: f64) -> f64 {
    let dx = x2 - x1;
    let dy = y2 - y1;
    (dx * dx + dy * dy).sqrt()
}
