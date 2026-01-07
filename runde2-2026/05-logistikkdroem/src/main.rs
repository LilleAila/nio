// Instead of treating it as changing or keeping a belt, i have treated it as a graph where
// traversing an edge where a belt is pointing in the same direction will cost 0, while traversing
// an edge without a belt pointing in that direction will cost 1.
// To save space and time and because the weights when not using the belts is equal to dx + dy, i
// only have to check the different combinations of paths.

use std::cmp;
use std::collections::{BinaryHeap, HashMap};
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

    // Turn individual belts into a map of full paths
    let mut paths: HashMap<(usize, usize), (usize, usize)> = HashMap::new();
    {
        // Inverse path map to speed up lookup
        // let mut paths_b: HashMap<(usize, usize), (usize, usize)> = HashMap::new();

        for _ in 0..k {
            let l = lines.next().unwrap().unwrap();
            let mut l = l.trim().split_whitespace();
            let x: usize = l.next().unwrap().parse().unwrap();
            let y: usize = l.next().unwrap().parse().unwrap();
            let c = (x - 1, y - 1);
            let d = l.next().unwrap();
            let d = match d {
                "o" => (0, 1),
                "n" => (0, -1),
                "h" => (1, 0),
                "v" => (-1, 0),
                _ => panic!(),
            };
            let t = add_coord(c, d);

            // if let Some(&n) = paths.get(&t) {
            //     paths.remove(&t);
            //     paths.insert(c, n);
            //
            //     paths_b.remove(&n);
            //     paths_b.insert(n, c);
            // } else if let Some(&n) = paths_b.get(&c) {
            //     paths_b.remove(&n);
            //     paths_b.insert(t, n);
            //
            //     paths.remove(&c);
            //     paths.insert(n, t);
            // } else {
            //     paths.insert(c, t);
            //     paths_b.insert(t, c);
            // }

            paths.insert(c, t);
        }
    }

    let mut nodes = vec![(0, 0), (n - 1, n - 1)];
    for (&a, &b) in paths.iter() {
        nodes.push(a);
        nodes.push(b);
    }
    nodes.sort();
    nodes.dedup();
    let n_nodes = nodes.len();

    let mut graph: Graph = vec![Vec::new(); n_nodes];
    for (i1, &(x1, y1)) in nodes.iter().enumerate() {
        for (i2, &(x2, y2)) in nodes.iter().enumerate() {
            if i1 == i2 || x2 < x1 || y2 < y1 {
                continue;
            }
            let cost = if paths.get(&(x1, y1)) == Some(&(x2, y2)) {
                0
            } else {
                (x2 as i32 - x1 as i32).abs() as usize + (y2 as i32 - y1 as i32).abs() as usize
            };
            graph[i1].push((i2, cost));
        }
    }

    let path = dijkstra(&graph, 0, nodes.len() - 1).unwrap();
    println!("{}", path);
}

fn add_coord((x, y): (usize, usize), (dx, dy): (i32, i32)) -> (usize, usize) {
    let nx = x as i32 + dx;
    let ny = y as i32 + dy;
    return (nx as usize, ny as usize);
}

fn dijkstra(graph: &Graph, start: usize, end: usize) -> Option<usize> {
    let n = graph.len();
    let mut dist = vec![usize::MAX; n];
    let mut heap = BinaryHeap::new();

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
