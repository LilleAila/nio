// I want to try using a type of DFS to check whether or not the graph is still connected
// After removing certain edges or nodes.

use std::collections::HashSet;
use std::convert::TryInto;
use std::io;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Instruction {
    Build,
    Query,
}

fn main() {
    let mut lines = io::stdin().lines();

    let [n, m, q]: [usize; 3] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut years: Vec<usize> = Vec::new();
    for _ in 0..n {
        let y = lines.next().unwrap().unwrap().parse().unwrap();
        years.push(y);
    }
    let years = years;
    let max_year = *years.iter().max().unwrap();

    // dbg!(max_year);

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
    let graph = graph;

    let mut instructions: Vec<(Instruction, usize)> = Vec::new();
    for _ in 0..q {
        let line = lines.next().unwrap().unwrap();
        let [i, n]: [&str; 2] = line
            .trim()
            .split_whitespace()
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        let i = if i == "!" {
            Instruction::Build
        } else {
            Instruction::Query
        };
        let n: usize = n.parse().unwrap();

        instructions.push((i, n));
    }
    let instructions = instructions;

    let mut water: HashSet<usize> = HashSet::new();

    for (i, node) in instructions {
        if i == Instruction::Build {
            water.insert(node);
        } else {
            let mut min = 0;
            let mut max = max_year;

            while min <= max {
                let mid = (min + max) / 2;

                let mut success = false;
                let mut stack: Vec<usize> = Vec::new();
                let mut visited: Vec<bool> = vec![false; n];

                if years[node] > mid {
                    stack.push(node);
                }

                while let Some(a) = stack.pop() {
                    if visited[a] {
                        continue;
                    }
                    visited[a] = true;

                    if water.contains(&a) {
                        success = true;
                        break;
                    }

                    for &b in &graph[a] {
                        if !visited[b] && years[b] > mid {
                            stack.push(b);
                        }
                    }
                }

                // Note that this is really an inverted binary search
                // instead of being something like 11110000
                // , the results here are 00001111
                // which is why we need to invert these
                // and also check if mid == 0 to avoid underflow
                if success {
                    min = mid + 1;
                } else {
                    if mid == 0 {
                        break;
                    }
                    max = mid - 1;
                }
            }

            if min == 0 {
                println!("-1");
            } else {
                println!("{}", min);
            }
        }
    }
}
