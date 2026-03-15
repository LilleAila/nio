use std::collections::HashMap;
use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, m, a, b]: [usize; 4] = lines
        .next()
        .unwrap()
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut edges = Vec::new();
    let mut adj: Vec<Vec<usize>> = vec![Vec::new(); n];
    for i in 0..m {
        let [u, v]: [usize; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        edges.push((u, v));
        adj[u].push(i);
        adj[v].push(i);
    }

    let mut graph: Vec<Vec<usize>> = vec![Vec::new(); 2 * m];
    for (i, &(u, v)) in edges.iter().enumerate() {
        let a = 2 * i;
        let b = 2 * i + 1;

        for &e in &adj[v] {
            if e == i {
                continue;
            }

            let (x, y) = edges[e];

            if x == v {
                graph[a].push(2 * e);
            } else {
                graph[a].push(2 * e + 1);
            }
        }

        for &e in &adj[u] {
            if e == i {
                continue;
            }

            let (x, y) = edges[e];

            if x == u {
                graph[b].push(2 * e);
            } else {
                graph[b].push(2 * e + 1);
            }
        }
    }

    let mut rg = vec![Vec::new(); 2 * m];
    for v in 0..2 * m {
        for &to in &graph[v] {
            rg[to].push(v);
        }
    }

    let mut visited = vec![false; 2 * m];
    let mut order = vec![];
    let mut stack = vec![];
    for i in 0..2 * m {
        if visited[i] {
            continue;
        }
        stack.push((i, 0));
        while let Some((v, state)) = stack.pop() {
            if state == 0 {
                if visited[v] {
                    continue;
                }
                visited[v] = true;
                stack.push((v, 1));
                for &to in &graph[v] {
                    if !visited[to] {
                        stack.push((to, 0));
                    }
                }
            } else {
                order.push(v);
            }
        }
    }

    let mut component = vec![usize::MAX; 2 * m];
    let mut id = 0;
    for &v in order.iter().rev() {
        if component[v] != usize::MAX {
            continue;
        }
        let mut stack = vec![v];
        component[v] = id;
        while let Some(x) = stack.pop() {
            for &to in &rg[x] {
                if component[to] == usize::MAX {
                    component[to] = id;
                    stack.push(to);
                }
            }
        }

        id += 1;
    }

    dbg!(&id, &component);
}
