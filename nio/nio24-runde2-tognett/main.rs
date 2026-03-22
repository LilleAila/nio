use std::collections::{HashMap, HashSet};
use std::convert::TryInto;
use std::io::{self, BufRead};

struct DSU {
    parent: Vec<usize>,
    size: Vec<usize>,
}

impl DSU {
    fn new(n: usize) -> Self {
        Self {
            parent: (0..n).collect(),
            size: vec![1; n],
        }
    }

    fn find(&mut self, x: usize) -> usize {
        if self.parent[x] != x {
            self.parent[x] = self.find(self.parent[x]);
        }
        self.parent[x]
    }

    fn union(&mut self, x: usize, y: usize) -> bool {
        let mut px = self.find(x);
        let mut py = self.find(y);
        if px == py {
            return false;
        }
        if self.size[px] < self.size[py] {
            // Add the smaller set to the larger
            std::mem::swap(&mut px, &mut py);
        }
        self.parent[py] = px;
        self.size[px] += self.size[py];
        true
    }
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let [n, m, k]: [usize; 3] = lines
        .next()
        .unwrap()
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut plane_edges: HashSet<(usize, usize)> = HashSet::new();
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
        let edge = if a < b { (a, b) } else { (b, a) };
        plane_edges.insert(edge);
    }

    let mut train_edges: Vec<(usize, usize)> = Vec::new();
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
        train_edges.push((a, b));
    }

    let mut dsu = DSU::new(n);

    let mut edge_count: Vec<HashMap<usize, usize>> = vec![HashMap::new(); n];
    let mut plane_adj: Vec<Vec<usize>> = vec![Vec::new(); n];

    for &(u, v) in &plane_edges {
        edge_count[u].entry(v).or_insert(0);
        edge_count[v].entry(u).or_insert(0);

        plane_adj[u].push(v);
        plane_adj[v].push(u);
    }

    for i in 0..n {
        for &v in &plane_adj[i] {
            edge_count[i].insert(v, 1);
        }
    }

    for &(u, v) in &train_edges {
        let ru = dsu.find(u);
        let rv = dsu.find(v);
        if ru == rv {
            println!("0");
            continue;
        }

        let (small_root, large_root) = if edge_count[ru].len() < edge_count[rv].len() {
            (ru, rv)
        } else {
            (rv, ru)
        };

        let mut removed = 0;
        let mut to_merge = Vec::new();
        for (&node, neighbors) in &edge_count[small_root] {
            let node_root = dsu.find(node);
            if node_root == large_root {
                removed += neighbors;
            } else {
                to_merge.push((node, neighbors));
            }
        }

        println!("{}", removed);

        dsu.union(ru, rv);

        let (first_root, second_root) = if ru < rv { (ru, rv) } else { (rv, ru) };
        let (left, right) = edge_count.split_at_mut(second_root);

        let (map_a, map_b) = if first_root < second_root {
            (&mut left[first_root], &mut right[0])
        } else {
            (&mut right[0], &mut left[second_root])
        };

        for (node, cnt) in map_b.drain() {
            *map_a.entry(node).or_insert(0) += cnt;
        }
    }
}
