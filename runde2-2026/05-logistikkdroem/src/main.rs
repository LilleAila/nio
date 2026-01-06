use std::cmp;
use std::collections::{self, HashSet};
use std::convert::TryInto;
use std::io;

type Graph = Vec<Vec<(usize, usize)>>;

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

    let mut graph: Graph = vec![vec![]; n * n];
    let mut belts: HashSet<(usize, usize)> = HashSet::new();

    for _ in 0..k {
        let l = lines.next().unwrap().unwrap();
        let mut l = l.trim().split_whitespace();
        let x: usize = l.next().unwrap().parse().unwrap();
        let y: usize = l.next().unwrap().parse().unwrap();
        let d = l.next().unwrap();
        let d = match d {
            "o" => (0, 1),
            "n" => (0, usize::MAX),
            "h" => (1, 0),
            "v" => (usize::MAX, 0),
            _ => panic!(),
        };
        let (tx, ty) = add_coord((x, y), d);
        belts.insert((index(x, y, n), index(tx, ty, n)));
        // for (nx, ny) in neighbors((x, y), n) {
        //     if nx == tx && ny == ty {
        //         continue;
        //     }
        //     belts.insert(index(x, y, n), (index(tx, ty, n), 1));
        // }
    }

    for x in 0..n {
        for y in 0..n {
            let i = index(x, y, n);
            for (nx, ny) in neighbors((x, y), n) {
                let ni = index(nx, ny, n);
                if belts.contains(&(i, ni)) {
                    graph[i].push((ni, 0));
                } else {
                    graph[i].push((ni, 1));
                }
            }
        }
    }

    let path = dijkstra(&graph, 0, index(n - 1, n - 1, n)).unwrap();
    println!("{}", path);
}

fn add_coord((x, y): (usize, usize), (dx, dy): (usize, usize)) -> (usize, usize) {
    return (x.wrapping_add(dx), y.wrapping_add(dy));
}

fn neighbors((x, y): (usize, usize), n: usize) -> Vec<(usize, usize)> {
    return [(0, 1), (0, usize::MAX), (1, 0), (usize::MAX, 0)]
        .iter()
        .filter_map(|&(dx, dy)| {
            let nx = x.wrapping_add(dx);
            let ny = y.wrapping_add(dy);
            if nx < n && ny < n {
                Some((nx, ny))
            } else {
                None
            }
        })
        .collect();
}

fn index(x: usize, y: usize, n: usize) -> usize {
    x * n + y
}

fn dijkstra(graph: &Graph, start: usize, end: usize) -> Option<usize> {
    let n = graph.len();
    let mut dist = vec![usize::MAX; n];
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
            let next_cost = cost + weight;
            if next_cost < dist[neighbor] {
                dist[neighbor] = next_cost;
                heap.push(cmp::Reverse((next_cost, neighbor)));
            }
        }
    }

    None
}
