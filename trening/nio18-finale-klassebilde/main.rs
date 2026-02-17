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

    let mut permutations = vec![vec![photos[0].clone()]];
    for i in 1..k {
        let photo = &photos[i];
        permutations = permutations
            .iter()
            .flat_map(|p| {
                let mut a = p.clone();
                a.push(photo.clone());

                let mut b = p.clone();
                let mut photo_reversed = photo.clone();
                photo_reversed.reverse();
                b.push(photo_reversed);

                vec![a, b]
            })
            .collect();
    }

    let mut d = 0;
    let mut a = 0;
    let mut b = 0;

    for ps in &permutations {
        let mut indexes = vec![0; n];
        for p in ps {
            for i in 0..n {
                indexes[p[i]] += i;
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

    println!(
        "{} {}",
        if a > b { b } else { a },
        if a > b { a } else { b }
    );
}
