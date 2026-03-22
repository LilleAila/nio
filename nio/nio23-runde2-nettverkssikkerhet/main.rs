use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, m, _k, p]: [usize; 4] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut graph: Vec<Vec<usize>> = vec![Vec::new(); n];

    for _ in 0..m {
        let [u, v]: [usize; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        graph[u].push(v);
        graph[v].push(u);
    }

    for _ in 0..p {
        let [u, v]: [usize; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        graph[u].push(v);
        graph[v].push(u);
    }

    println!("{:?}", graph);
}
