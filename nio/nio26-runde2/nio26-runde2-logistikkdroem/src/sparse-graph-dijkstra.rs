// Instead of treating it as changing or keeping a belt, i have treated it as a graph where
// traversing an edge where a belt is pointing in the same direction will cost 0, while traversing
// an edge without a belt pointing in that direction will cost 1.
// To save space and time and because the weights when not using the belts is equal to dx + dy, i
// only have to check the different combinations of paths.
// This is much better than the others in terms of space complexity
// Yet it still falls short in terms of time complexity, so this is better for subtasks with low
// values for K while the others are faster for low values of N. Combined they can solve the first
// 4 subtasks, but the first one runs into memory issues and this one into time issues.

use std::cmp;
use std::collections::{BinaryHeap, HashMap, HashSet, VecDeque};
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

    let mut paths: HashMap<(usize, usize), (usize, usize)> = HashMap::new();

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
        paths.insert(c, t);
    }

    // let mut nodes = vec![(0, 0), (n - 1, n - 1)];
    // for (&a, &b) in paths.iter() {
    //     nodes.push(a);
    //     nodes.push(b);
    // }
    // nodes.sort();
    // nodes.dedup();
    // let n_nodes = nodes.len();

    let mut nodes: HashSet<(usize, usize)> = HashSet::new();
    nodes.insert((0, 0));
    nodes.insert((n - 1, n - 1));
    for (&a, &b) in paths.iter() {
        nodes.insert(a);
        nodes.insert(b);
    }
    let mut nodes: Vec<(usize, usize)> = nodes.into_iter().collect();
    nodes.sort();
    let n_nodes = nodes.len();

    let mut index: HashMap<(usize, usize), usize> = HashMap::new();
    for (i, &pos) in nodes.iter().enumerate() {
        index.insert(pos, i);
    }

    let mut graph: Graph = vec![Vec::new(); n_nodes];
    for (i1, &(x1, y1)) in nodes.iter().enumerate() {
        for (i2, &(x2, y2)) in nodes.iter().enumerate() {
            if i1 == i2 || x2 < x1 || y2 < y1 {
                continue;
            }
            let cost = if paths.get(&(x1, y1)) == Some(&(x2, y2)) {
                0
            } else {
                manhattan_distance((x1, y1), (x2, y2))
            };
            graph[i1].push((i2, cost));
        }
    }
    // let heuristic: &dyn Fn(usize, usize) -> usize =
    //     &|a: usize, b: usize| manhattan_distance(nodes[a], nodes[b]);
    // let path = a_star(&graph, 0, n_nodes - 1, heuristic).unwrap();
    let path = dijkstra(&graph, 0, n_nodes - 1).unwrap();
    println!("{}", path);

    // let mut dp = vec![usize::MAX; n_nodes];
    // dp[n_nodes - 1] = 0;
    // let mut stack = VecDeque::new();
    // stack.push_back(n_nodes - 1);
    //
    // while let Some(i) = stack.pop_front() {
    //     let (x, y) = nodes[i];
    //
    //     if let Some(&(nx, ny)) = paths_b.get(&(x, y)) {
    //         let n = index[&(nx, ny)];
    //         if dp[i] < dp[n] {
    //             dp[n] = dp[i];
    //             stack.push_front(n);
    //         }
    //     }
    //
    //     for &(nx, ny) in nodes.iter() {
    //         let n = index[&(nx, ny)];
    //         let cost =
    //             (nx as i32 - x as i32).abs() as usize + (ny as i32 - y as i32).abs() as usize;
    //         if dp[i] + cost < dp[n] {
    //             dp[n] = dp[i] + cost;
    //             stack.push_back(n);
    //         }
    //     }
    // }
    //
    // println!("{:?}", dp[0]);
}

fn add_coord((x, y): (usize, usize), (dx, dy): (i32, i32)) -> (usize, usize) {
    let nx = x as i32 + dx;
    let ny = y as i32 + dy;
    return (nx as usize, ny as usize);
}

fn manhattan_distance((x1, y1): (usize, usize), (x2, y2): (usize, usize)) -> usize {
    (x2 as i32 - x1 as i32).abs() as usize + (y2 as i32 - y1 as i32).abs() as usize
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

fn a_star(
    graph: &Graph,
    start: usize,
    end: usize,
    heuristic: &dyn (Fn(usize, usize) -> usize),
) -> Option<usize> {
    let n = graph.len();
    let mut dist = vec![usize::MAX; n];
    let mut heap = BinaryHeap::new();

    dist[start] = 0;
    heap.push(cmp::Reverse((heuristic(start, end), start)));

    while let Some(cmp::Reverse((_, node))) = heap.pop() {
        if node == end {
            return Some(dist[node]);
        }

        for &(neighbor, weight) in &graph[node] {
            let next_cost = dist[node] + weight;
            if next_cost < dist[neighbor] {
                dist[neighbor] = next_cost;
                let priority = next_cost + heuristic(neighbor, end);
                heap.push(cmp::Reverse((priority, neighbor)));
            }
        }
    }

    None
}
