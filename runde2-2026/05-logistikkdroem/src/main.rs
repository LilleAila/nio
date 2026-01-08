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

    let mut belts: Vec<Vec<i8>> = vec![vec![0; n]; n];

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
        belts[x - 1][y - 1] = d;
    }

    let directions: [(i32, i32); 5] = [(0, 0), (0, 1), (0, -1), (1, 0), (-1, 0)];

    let mut dp: Vec<Vec<u16>> = vec![vec![u16::MAX; n]; n];
    dp[n - 1][n - 1] = 0;

    let mut stack: VecDeque<(usize, usize)> = VecDeque::new();
    stack.push_back((n - 1, n - 1));

    while let Some((x, y)) = stack.pop_front() {
        if x == 0 && y == 0 {
            break;
        }

        let c = dp[x][y];

        for (nx, ny) in neighbors((x, y), n) {
            let (dx, dy) = directions[belts[nx][ny] as usize];
            let cost = if add_coord((nx, ny), (dx, dy)) == (x, y) {
                0
            } else {
                1
            };

            let next_cost = c + cost;

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

    println!("{:?}", dp[0][0]);
}

fn add_coord((x, y): (usize, usize), (dx, dy): (i32, i32)) -> (usize, usize) {
    let nx = x as i32 + dx;
    let ny = y as i32 + dy;
    return (nx as usize, ny as usize);
}

fn neighbors(a: (usize, usize), n: usize) -> Vec<(usize, usize)> {
    let directions: [(i32, i32); 4] = [(0, 1), (0, -1), (1, 0), (-1, 0)];
    return directions
        .iter()
        .filter_map(|&d| {
            let (nx, ny) = add_coord(a, d);
            if nx < n && ny < n {
                Some((nx, ny))
            } else {
                None
            }
        })
        .collect();
}
