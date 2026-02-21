use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [x, y]: [f32; 2] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let n: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();

    let mut nodes: Vec<(f32, f32)> = Vec::new();
    for _ in 0..n {
        let [x, y]: [f32; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();
        nodes.push((x, y));
    }
}
