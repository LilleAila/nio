// Subtask 5 with 0-1 BFS (again)

use std::collections::VecDeque;
use std::convert::TryInto;
use std::io;

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

    let index = |x: usize, y: usize| (x - 1) * n + (y - 1);

    let mut belt: Vec<bool> = vec![false; n * n];

    for _ in 0..k {
        let l = lines.next().unwrap().unwrap();
        let mut l = l.trim().split_whitespace();
        let x: usize = l.next().unwrap().parse().unwrap();
        let y: usize = l.next().unwrap().parse().unwrap();
        l.next();
        belt[index(x, y)] = true;
    }

    let mut d: Vec<usize> = vec![usize::MAX; n * n];
    let mut stack: VecDeque<(usize, usize)> = VecDeque::new();

    d[index(1, 1)] = 0;
    stack.push_front((1, 1));

    let directions: [(isize, isize); 3] = [(0, 1), (-1, 0), (1, 0)];

    while let Some((x, y)) = stack.pop_front() {
        let cost = d[index(x, y)];

        for &(dx, dy) in &directions {
            let nx = (x as isize + dx) as usize;
            let ny = (y as isize + dy) as usize;

            // NOTE: the coordinates are 1-indexed
            if nx < 1 || nx > n || ny < 1 || ny > n {
                continue;
            }

            let c = if dy == 1 && belt[index(x, y)] { 0 } else { 1 };

            let new_cost = cost + c;

            if new_cost < d[index(nx, ny)] {
                d[index(nx, ny)] = new_cost;
                if c == 0 {
                    stack.push_front((nx, ny));
                } else {
                    stack.push_back((nx, ny));
                }
            }
        }
    }

    println!("{}", d[index(n, n)]);
}
