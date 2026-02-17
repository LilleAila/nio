use std::cmp::Reverse;
use std::collections::BinaryHeap;
use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, m, v]: [usize; 3] = lines
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
        let [a, b, k]: [usize; 3] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();
        graph[a].push((b, k));
    }

    let start = 0;
    let target = 1;

    let mut heap = BinaryHeap::new();
    heap.push(Reverse((0, v, start))); // (cost, tickets, node)
    let mut dist = vec![vec![usize::MAX; v + 1]; n];
    dist[start][v] = 0;

    let mut result = None;

    while let Some(Reverse((cost, tickets, node))) = heap.pop() {
        if cost > dist[node][tickets] {
            continue;
        }

        if node == target {
            result = Some(cost);
            break;
        }

        for &(n, c) in &graph[node] {
            let new_cost = cost + c;
            if new_cost < dist[n][tickets] {
                dist[n][tickets] = new_cost;
                heap.push(Reverse((new_cost, tickets, n)));
            }

            if tickets > 0 && cost < dist[n][tickets - 1] {
                dist[n][tickets - 1] = cost;
                heap.push(Reverse((cost, tickets - 1, n)));
            }
        }
    }

    println!("{}", result.unwrap());
}
