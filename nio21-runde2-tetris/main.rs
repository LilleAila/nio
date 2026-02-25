use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, v]: [usize; 2] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut pieces: Vec<(usize, usize)> = Vec::new();
    for _ in 0..n {
        let [x, b]: [usize; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();
        pieces.push((x, b));
    }

    let mut game: Vec<usize> = Vec::new();

    for (x, w) in pieces {
        let p = ((1 << w) - 1) << (v - x - w);

        let mut j = game.len();
        for (i, r) in game.iter().enumerate().rev() {
            if r & p == 0 {
                j = i;
            } else {
                break;
            }
        }

        if j == game.len() {
            game.push(p);
        } else {
            game[j] |= p;
        }

        if game[j] == (1 << v) - 1 {
            game.remove(j);
        }

        println!("{}", game.len());
    }
}
