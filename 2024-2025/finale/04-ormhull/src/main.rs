use std::cmp;
use std::collections::BinaryHeap;
use std::convert::TryInto;
use std::io;

type Graph = Vec<Vec<(usize, usize, bool)>>;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, m, k, a, b]: [usize; 5] = lines
        .next()
        .unwrap()
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut graph: Graph = vec![Vec::new(); n];

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

        graph[v].push((u, t, false));
        graph[u].push((v, t, false));
    }

    let wormholes: Vec<usize> = lines
        .next()
        .unwrap()
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    for &a in &wormholes {
        for &b in &wormholes {
            graph[a].push((b, 0, true));
        }
    }

    let length = dijkstra(&graph, a, b);
    println!("{:?}", length);
}

fn dijkstra(graph: &Graph, start: usize, end: usize) -> Option<usize> {
    let n = graph.len();
    let mut dist = vec![usize::MAX; n];
    let mut heap = BinaryHeap::new();

    dist[start] = 0;
    heap.push(cmp::Reverse((0, start)));

    while let Some(cmp::Reverse((cost, node))) = heap.pop() {
        if node == end {
            return Some(cost);
        }

        if cost > dist[node] {
            continue;
        }

        for &(neighbor, weight, _wormhole) in &graph[node] {
            let next_cost = cost + weight;
            if next_cost < dist[neighbor] {
                dist[neighbor] = next_cost;
                heap.push(cmp::Reverse((next_cost, neighbor)));
            }
        }
    }

    None
}
