use std::cmp::Reverse;
use std::collections::{BinaryHeap, HashMap};
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

    let mut belts: Vec<Vec<usize>> = vec![Vec::new(); n + 1];

    for _ in 0..k {
        let l = lines.next().unwrap().unwrap();
        let mut l = l.trim().split_whitespace();
        let x: usize = l.next().unwrap().parse().unwrap();
        let y: usize = l.next().unwrap().parse().unwrap();
        l.next();
        belts[y].push(x);
    }

    for r in &mut belts {
        r.sort_unstable();
    }

    let mut rows: Vec<usize> = Vec::new();
    rows.push(1);
    for y in 2..n {
        if !belts[y].is_empty() {
            rows.push(y);
        }
    }
    rows.push(n);

    let mut dp: HashMap<usize, usize> = HashMap::new();
    dp.insert(1, 0);

    for i in 0..rows.len() - 1 {
        let y = rows[i];
        let ny = rows[i + 1];
        let dy = ny - y;
        let mut dp1: HashMap<usize, usize> = HashMap::new();

        for (&x, &cost) in dp.iter() {
            let c = cost + dy
                - if belts[y].binary_search(&x).is_ok() {
                    1
                } else {
                    0
                };
            dp1.insert(x, c);
        }

        // 1D djikstra

        let mut heap: BinaryHeap<(Reverse<usize>, usize)> = BinaryHeap::new();
        let mut best = usize::MAX;

        for (&x, &c) in dp1.iter() {
            heap.push((Reverse(c), x));
            best = best.min(c);
        }

        let l = best + n;
        while let Some((Reverse(cost), x)) = heap.pop() {
            if cost > *dp1.get(&x).unwrap() {
                continue;
            }
            if cost > l {
                break;
            }

            if x > 1 {
                let nc = cost + 1;
                if nc < *dp1.get(&(x - 1)).unwrap_or(&usize::MAX) {
                    dp1.insert(x - 1, nc);
                    heap.push((Reverse(nc), x - 1));
                }
            }
            if x < n {
                let nc = cost + 1;
                if nc < *dp1.get(&(x + 1)).unwrap_or(&usize::MAX) {
                    dp1.insert(x + 1, nc);
                    heap.push((Reverse(nc), x + 1));
                }
            }
        }

        dp = dp1;
    }

    let result = dp.get(&n).unwrap();
    println!("{}", result - 1);
}
