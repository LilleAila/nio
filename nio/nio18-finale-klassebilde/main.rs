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
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut photos: Vec<Vec<usize>> = Vec::new();
    for _ in 0..k {
        let photo: Vec<usize> = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>();
        photos.push(photo);
    }

    let mut d = 0;
    let mut a = 0;
    let mut b = 0;

    for m in (1 << 1)..(1 << k) {
        let mut indexes = vec![0; n];

        for i in 0..k {
            let photo = if m & (1 << i) != 0 {
                let mut p = photos[i].clone();
                p.reverse();
                p
            } else {
                photos[i].clone()
            };

            for (i, &person) in photo.iter().enumerate() {
                indexes[person] += i;
            }
        }

        let new_d = indexes.iter().max().unwrap() - indexes.iter().min().unwrap();
        if new_d > d {
            d = new_d;
            a = indexes
                .iter()
                .enumerate()
                .min_by_key(|&(_, v)| v)
                .unwrap()
                .0;
            b = indexes
                .iter()
                .enumerate()
                .max_by_key(|&(_, v)| v)
                .unwrap()
                .0;
        }
    }

    if a > b {
        println!("{} {}", b, a);
    } else {
        println!("{} {}", a, b);
    }
}
