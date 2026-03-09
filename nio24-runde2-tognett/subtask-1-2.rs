use std::collections::{HashSet, VecDeque};
use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, m, k]: [usize; 3] = lines
        .next()
        .unwrap()
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut plane_graph: Vec<HashSet<usize>> = vec![HashSet::new(); n];
    for _ in 0..m {
        let [a, b]: [usize; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        plane_graph[a].insert(b);
        plane_graph[b].insert(a);
    }

    let mut train_graph: Vec<HashSet<usize>> = vec![HashSet::new(); n];
    let mut trains: Vec<(usize, usize)> = Vec::new();
    for _ in 0..k {
        let [a, b]: [usize; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();
        trains.push((a, b));
    }

    for &(a, b) in &trains {
        train_graph[a].insert(b);
        train_graph[b].insert(a);

        let mut reachable: HashSet<usize> = HashSet::new();

        let mut visited: Vec<bool> = vec![false; n];
        let mut queue: VecDeque<usize> = VecDeque::new();

        // It doesn't really matter where we start, we just want to find all reachable nodes
        queue.push_back(a);
        visited[a] = false;
        while let Some(u) = queue.pop_front() {
            reachable.insert(u);

            for &v in &train_graph[u] {
                if !visited[v] {
                    queue.push_back(v);
                    visited[v] = true;
                }
            }
        }

        let mut removed = 0;
        for &n in &reachable {
            let len_a = plane_graph[n].len();
            plane_graph[n].retain(|x| !reachable.contains(x));
            let len_b = plane_graph[n].len();
            removed += len_a - len_b;
        }
        // This is an undirected graph, so all edges are defined twice
        removed /= 2;

        println!("{}", removed);
    }
}
