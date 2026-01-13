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

    // let mut belts: HashSet<((usize, usize), (usize, usize))> = HashSet::new();
    let mut belts: Vec<Vec<usize>> = vec![vec![0; n]; n];

    for _ in 0..k {
        let l = lines.next().unwrap().unwrap();
        let mut l = l.trim().split_whitespace();
        let x: usize = l.next().unwrap().parse().unwrap();
        let y: usize = l.next().unwrap().parse().unwrap();
        let d = l.next().unwrap();
        let d = match d {
            "o" => 1,
            "n" => 2,
            "h" => 3,
            "v" => 4,
            _ => panic!(),
        };
        belts[x][y] = d;
    }

    let mut dp: Vec<Vec<usize>> = vec![vec![usize::MAX; n]; n];
    dp[n - 1][n - 1] = 0;

    let directions: [(usize, usize); 5] =
        [(0, 0), (0, 1), (0, usize::MAX), (1, 0), (usize::MAX, 0)];

    let mut stack: VecDeque<(usize, usize)> = VecDeque::new();
    stack.push_back((n - 1, n - 1));

    while let Some((x, y)) = stack.pop_front() {
        let current_cost = dp[x][y];
        for (nx, ny) in neighbors((x, y), n) {
            // Find the number of changes required to go from each neighbor
            let dir = directions[belts[nx][ny]];
            let cost = if add_coord((nx, ny), dir) == (x, y) {
                0
            } else {
                1
            };
            let next_cost = current_cost + cost;

            // Add the this square to the stack if a better path was found
            if next_cost < dp[nx][ny] {
                dp[nx][ny] = next_cost;

                if cost == 0 {
                    stack.push_front((nx, ny));
                } else {
                    stack.push_back((nx, ny));
                }
            }
        }
    }

    println!("{}", dp[0][0]);
}

fn add_coord((x, y): (usize, usize), (dx, dy): (usize, usize)) -> (usize, usize) {
    return (x.wrapping_add(dx), y.wrapping_add(dy));
}

fn neighbors((x, y): (usize, usize), n: usize) -> Vec<(usize, usize)> {
    return [(0, 1), (0, usize::MAX), (1, 0), (usize::MAX, 0)]
        .iter()
        .filter_map(|&(dx, dy)| {
            let nx = x.wrapping_add(dx);
            let ny = y.wrapping_add(dy);
            if nx < n && ny < n {
                Some((nx, ny))
            } else {
                None
            }
        })
        .collect();
}
