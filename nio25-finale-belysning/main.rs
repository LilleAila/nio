use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, q]: [usize; 2] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut ys: Vec<usize> = Vec::new();
    for _ in 0..n {
        let y: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();
        ys.push(y);
    }

    let mut prices: Vec<(usize, usize)> = Vec::new();
    for _ in 0..q {
        let [a, b]: [usize; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();
        prices.push((a, b));
    }

    // Precompute the optimal y-value for a lamp in a given interval
    // this ignores the actual cost completely as even though the cost matters,
    // if we have the optimal configuration of lamps for all intervals we will end up with
    // the same total cost just using a different combination of intervals as we still only
    // check the optimal lamp positions for a given combination of intervals
    let mut lys: Vec<Vec<usize>> = vec![vec![usize::MAX; n]; n];
    for i in 0..n {
        for j in 0..=i {
            let p = (j..=i)
                .map(|lx| (lx, (j..=i).map(|x| ys[x] + lx.abs_diff(x)).max().unwrap()))
                .map(|(lx, ly)| ly - ys[lx])
                .min()
                .unwrap();
            lys[j][i] = p;
        }
    }

    for (a, b) in prices {
        let mut dp = vec![usize::MAX; n];

        for i in 0..n {
            for j in 0..=i {
                let mut min_cost = usize::MAX;
                for lx in j..=i {
                    let cost = a + b * lys[j][i];
                    min_cost = min_cost.min(cost);
                }
                let prev = if j == 0 { 0 } else { dp[j - 1] };
                dp[i] = dp[i].min(prev + min_cost);
            }
        }

        println!("{:?}", dp[n - 1]);
    }
}
