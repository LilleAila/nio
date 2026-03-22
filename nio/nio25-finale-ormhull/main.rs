use std::cmp::Reverse;
use std::collections::BinaryHeap;
use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, m, k, a, b]: [usize; 5] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut graph: Vec<Vec<(usize, usize)>> = vec![Vec::new(); n];

    for _ in 0..m {
        let [v, u, t]: [usize; 3] = lines
            .next()
            .unwrap()
            .unwrap()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        graph[v].push((u, t));
        graph[u].push((v, t));
    }

    let mut wormhole: Vec<bool> = vec![false; n];
    for i in lines
        .next()
        .unwrap()
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse::<usize>().unwrap())
    {
        wormhole[i] = true;
    }

    let mut dist: Vec<usize> = vec![usize::MAX; n];
    let mut heap = BinaryHeap::new();
    heap.push(Reverse((0, a)));
    dist[a] = 0;

    let mut result = None;

    while let Some(Reverse((cost, node))) = heap.pop() {
        if cost > dist[node] {
            continue;
        }

        if node == b {
            result = Some(cost);
            break;
        }

        for &(neighbor, c) in &graph[node] {
            let new_cost = cost + c;
            if new_cost < dist[neighbor] {
                dist[neighbor] = new_cost;
                heap.push(Reverse((new_cost, neighbor)));
            }
        }
    }

    match result {
        None => println!("-1"),
        Some(r) => println!("{}", r),
    }
}
