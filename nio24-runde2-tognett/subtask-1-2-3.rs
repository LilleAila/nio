use std::collections::HashSet;
use std::convert::TryInto;
use std::io;

struct DSU {
    parent: Vec<usize>,
    size: Vec<usize>,
}

impl DSU {
    fn new(n: usize) -> Self {
        DSU {
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
        let mut rx = self.find(x);
        let mut ry = self.find(y);
        if rx == ry {
            return false;
        }
        if self.size[rx] < self.size[ry] {
            std::mem::swap(&mut rx, &mut ry);
        }
        self.parent[ry] = rx;
        self.size[rx] += self.size[ry];
        true
    }
}

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

    let mut dsu = DSU::new(n);

    for &(a, b) in &trains {
        dsu.union(a, b);

        let mut removed = 0;
        for u in 0..n {
            let mut to_remove = Vec::new();
            for &v in &plane_graph[u] {
                if dsu.find(u) == dsu.find(v) {
                    to_remove.push(v);
                }
            }
            removed += to_remove.len();
            for v in to_remove {
                plane_graph[u].remove(&v);
            }
        }

        println!("{}", removed / 2);
    }
}
