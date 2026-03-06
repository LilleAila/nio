// Binary search which removes all edges lower than the selected value, then checks if the graph is
// still fully connected. This should be much faster than the others. Something like
// Time: DFS * binary search = O((V + E) logN)) which is much faster than the others at O(n^3)
// Space: O(V)

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

    let mut graph: Graph = vec![Vec::new(); n];

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

    let mut min: i32 = 0;
    let mut max: i32 = *graph
        .iter()
        .flat_map(|xs| xs.iter().map(|(_, w)| w).max())
        .max()
        .unwrap();

    let mut result: i32 = -1;

    while min <= max {
        let mid = (min + max) / 2;

        let mut visited = vec![false; n];
        let mut stack = vec![0];
        visited[0] = true;

        // DFS to check if the graph is still connected with the limited edge weight
        while let Some(x) = stack.pop() {
            for &(n, w) in &graph[x] {
                if !visited[n] && w <= mid {
                    visited[n] = true;
                    stack.push(n);
                }
            }
        }

        if visited.iter().all(|&x| x) {
            result = mid;
            max = mid - 1;
        } else {
            min = mid + 1;
        }
    }

    println!("{}", result);
}
