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

    let mut grid: Vec<Vec<usize>> = vec![vec![0; n]; n];

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
        grid[x][y] = d;
    }

    let directions: [(usize, usize); 5] =
        [(0, 0), (0, 1), (0, usize::MAX), (1, 0), (usize::MAX, 0)];

    let mut dp: Vec<Vec<usize>> = vec![vec![usize::MAX; n]; n];
    dp[n - 1][n - 1] = 0;

    let mut stack: Vec<(usize, usize)> = vec![(n - 1, n - 1)];

    while let Some((x, y)) = stack.pop() {
        for (nx, ny) in neighbors((x, y), n) {
            // Find the number of changes required to go from each neighbor
            let direction = directions[grid[nx][ny]];
            let cost = if add_coord((nx, ny), direction) == (x, y) {
                0
            } else {
                1
            };

            // Add the this square to the stack if a better path was found
            if dp[nx][ny] > dp[x][y] + cost {
                dp[nx][ny] = dp[x][y] + cost;
                stack.push((nx, ny));
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
