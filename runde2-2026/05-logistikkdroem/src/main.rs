use std::convert::TryInto;
use std::io;

#[derive(Clone, Debug)]
enum Direction {
    Up,
    Down,
    Right,
    Left,
}

#[derive(Clone, Debug)]
enum Cell {
    Empty,
    Conveyor(Direction),
}

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

    let mut grid: Vec<Vec<Cell>> = vec![vec![Cell::Empty; n]; n];

    for _ in 0..k {
        let l = lines.next().unwrap().unwrap();
        let mut l = l.trim().split_whitespace();
        let x: usize = l.next().unwrap().parse().unwrap();
        let y: usize = l.next().unwrap().parse().unwrap();
        let d = l.next().unwrap();
        let d = match d {
            "o" => Direction::Up,
            "n" => Direction::Down,
            "h" => Direction::Right,
            "v" => Direction::Left,
            _ => panic!(),
        };
        grid[x][y] = Cell::Conveyor(d);
    }

    println!("{:?}", grid);
}
