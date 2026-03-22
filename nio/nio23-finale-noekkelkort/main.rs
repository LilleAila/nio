use std::collections::{HashSet, VecDeque};
use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, m, k, t]: [usize; 4] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let all_permissions: u32 = (1 << k) - 1;

    let mut graph: Vec<Vec<(usize, u32)>> = vec![Vec::new(); n];
    let mut pairs: Vec<(usize, usize, u32)> = Vec::new();

    for i in 0..m {
        let line = lines.next().unwrap().unwrap();
        let mut iter = line.split_whitespace();
        let u: usize = iter.next().unwrap().parse().unwrap();
        let v: usize = iter.next().unwrap().parse().unwrap();
        let a: u32 = u32::from_str_radix(iter.next().unwrap(), 2).unwrap();

        graph[u].push((v, a));
        graph[v].push((u, a));

        if i < t {
            pairs.push((u, v, a));
        }
    }

    for &(u, v, p) in &pairs {
        let mut queue: VecDeque<usize> = VecDeque::new();
        let mut visited: HashSet<usize> = HashSet::new();
        let permissions = !p & all_permissions;
        queue.push_back(u);

        let mut result = true;

        while let Some(a) = queue.pop_front() {
            if visited.contains(&a) {
                continue;
            }
            visited.insert(a);

            if a == v {
                result = false;
                break;
            }

            for &(n, ps) in &graph[a] {
                if permissions & ps != 0 {
                    queue.push_back(n);
                }
            }
        }

        println!("{}", result as u8);
    }
}
