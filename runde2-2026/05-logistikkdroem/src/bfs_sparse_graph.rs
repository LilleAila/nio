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

    let mut dp: Vec<Vec<u16>> = vec![vec![u16::MAX; n]; n];
    dp[n - 1][n - 1] = 0;

    let mut stack: VecDeque<(usize, usize)> = VecDeque::with_capacity(n * n);
    stack.push_back((n - 1, n - 1));

    while let Some((x, y)) = stack.pop_front() {
        if x == 0 && y == 0 {
            break;
        }

        let c = dp[x][y];

        // Up (d = 1)
        if y > 0 {
            let nx = x;
            let ny = y - 1;
            let cost = if belts[nx][ny] == 1 { 0 } else { 1 };

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

        // Down (d = 2)
        if y < n - 1 {
            let nx = x;
            let ny = y + 1;
            let cost = if belts[nx][ny] == 2 { 0 } else { 1 };

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

        // Right (d = 3)
        if x > 0 {
            let nx = x - 1;
            let ny = y;
            let cost = if belts[nx][ny] == 3 { 0 } else { 1 };

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

        // Left (d = 4)
        if x < n - 1 {
            let nx = x + 1;
            let ny = y;
            let cost = if belts[nx][ny] == 4 { 0 } else { 1 };

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
