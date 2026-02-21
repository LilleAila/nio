// Solution using a modified dijkstra's algorithm with max instead of +
// I don't know if the following is correct but
// Time: O(n^3)
// Space: O(n^2)
// Both are too much :(

use std::cmp;
use std::collections;
use std::convert::TryInto; // 2021 edition compatibility (try_into) - it seems nio uses 2015
use std::io;

type Graph = Vec<Vec<(usize, i32)>>;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, k]: [i32; 2] = lines
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

    let pairs: Vec<(usize, usize)> = (0..n)
        .flat_map(|a| ((a + 1)..n).map(move |b| (a as usize, b as usize)))
        .collect();

    let mut weight = 0;
    for (a, b) in pairs {
        match dijkstra(&graph, a, b) {
            Some(w) => {
                weight = cmp::max(w, weight);
            }
            None => {
                println!("-1");
                return;
            }
        }
    }
    println!("{}", weight);
}

fn dijkstra(graph: &Graph, start: usize, end: usize) -> Option<i32> {
    let n = graph.len();
    let mut dist = vec![i32::MAX; n];
    let mut heap = collections::BinaryHeap::new();

    dist[start] = 0;
    heap.push(cmp::Reverse((0, start)));

    while let Some(cmp::Reverse((cost, node))) = heap.pop() {
        if node == end {
            return Some(cost);
        }

        if cost > dist[node] {
            continue;
        }

        for &(neighbor, weight) in &graph[node] {
            // NOTE: The following line differs from standard dijkstra.
            // It would have been `cost + weight` instead of `cmp::max(cost, weight)`
            // But here we want the highest weight and not the total weight.
            let next_cost = cmp::max(cost, weight);
            if next_cost < dist[neighbor] {
                dist[neighbor] = next_cost;
                heap.push(cmp::Reverse((next_cost, neighbor)));
            }
        }
    }

    None
}
