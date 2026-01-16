use std::cmp::{self, Reverse};
use std::collections::BinaryHeap;
use std::convert::TryInto;
use std::io;

type Graph = Vec<Vec<(usize, usize)>>;

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

    let mut db: Vec<usize> = vec![usize::MAX; n];
    let mut heap: BinaryHeap<Reverse<(usize, usize)>> = BinaryHeap::new();
    db[b] = 0;
    heap.push(Reverse((0, b)));

    while let Some(Reverse((d, u))) = heap.pop() {
        if d > db[u] {
            continue;
        }
        for &(v, w) in &graph[u] {
            if wormhole[v] {
                continue;
            }
            let nd = d + w;
            if nd < db[v] {
                db[v] = nd;
                heap.push(cmp::Reverse((nd, v)));
            }
        }
    }

    let mut x = usize::MAX;
    for u in 0..n {
        if !wormhole[u] {
            continue;
        }

        for &(v, w) in &graph[u] {
            if !wormhole[v] && db[v] < usize::MAX {
                x = x.min(w + db[v]);
            }
        }
    }

    if x == usize::MAX {
        println!("-1");
        return;
    }

    let mut dist: Vec<usize> = vec![usize::MAX; n];
    let mut heap: BinaryHeap<Reverse<(usize, usize)>> = BinaryHeap::new();
    dist[a] = 0;
    heap.push(Reverse((0, a)));

    while let Some(Reverse((d, u))) = heap.pop() {
        if d > dist[u] {
            continue;
        }
        if u == b {
            break;
        }
        for &(v, w) in &graph[u] {
            if wormhole[v] {
                let nd = d + w + x;
                for wh in 0..n {
                    if wormhole[wh] && nd < dist[wh] {
                        dist[wh] = nd;
                        heap.push(Reverse((nd, wh)));
                    }
                }
            } else {
                let nd = d + w;
                if nd < dist[v] {
                    dist[v] = nd;
                    heap.push(cmp::Reverse((nd, v)));
                }
            }
        }
    }

    if dist[b] == usize::MAX {
        println!("-1");
        return;
    }
    println!("{:.15}", dist[b]);
}
