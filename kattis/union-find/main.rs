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

    let [n, q]: [usize; 2] = lines
        .next()
        .unwrap()
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut dsu = DSU::new(n);

    for _ in 0..q {
        let line = lines.next().unwrap().unwrap();
        let mut iter = line.trim().split_whitespace();
        let join: bool = iter.next().unwrap() == "=";
        let a: usize = iter.next().unwrap().parse().unwrap();
        let b: usize = iter.next().unwrap().parse().unwrap();

        if join {
            dsu.union(a, b);
        } else {
            if dsu.find(a) == dsu.find(b) {
                println!("yes");
            } else {
                println!("no");
            }
        }
    }
}
