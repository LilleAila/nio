use std::collections::{HashSet, VecDeque};
use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, m, q]: [usize; 3] = lines
        .next()
        .unwrap()
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut graph: Vec<Vec<(usize, bool)>> = vec![Vec::new(); n];
    // for i in 0..n {
    //     graph[i].push((i, true));
    // }
    for _ in 0..m {
        let [l, a, b]: [isize; 3] = lines
            .next()
            .unwrap()
            .unwrap()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();
        graph[a as usize].push((b as usize, l > 0));
    }

    for _ in 0..q {
        let [a, b]: [usize; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        let mut queue: VecDeque<(usize, bool)> = VecDeque::new();
        let mut visited: HashSet<usize> = HashSet::new();

        // Start at self, and we know that any node likes itself
        queue.push_back((a, true));
        let mut found = false;

        while let Some((n, likes)) = queue.pop_front() {
            if visited.contains(&n) {
                continue;
            }
            visited.insert(n);

            if n == b {
                if likes {
                    println!("1");
                } else {
                    println!("-1");
                }
                found = true;
                break;
            }

            for &(neighbor, n_likes) in &graph[n] {
                let l = if likes { n_likes } else { !n_likes };
                queue.push_back((neighbor, l));
            }
        }

        if !found {
            println!("0");
        }
    }
}
