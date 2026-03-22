use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [_n, q]: [usize; 2] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let s: Vec<bool> = lines
        .next()
        .unwrap()
        .unwrap()
        .chars()
        .map(|x| x == 'A')
        .collect();

    for _ in 0..q {
        let [k, m]: [usize; 2] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        let mut total_p = 0;

        let mut pa = 0;
        let mut pb = 0;

        let mut sa = 0;
        let mut sb = 0;

        for &p in &s {
            match p {
                true => pa += 1,
                false => pb += 1,
            }
            total_p += 1;

            if pa >= k && pa >= pb + 2 {
                sa += 1;
                pa = 0;
                pb = 0;
            }
            if pb >= k && pb >= pa + 2 {
                sb += 1;
                pa = 0;
                pb = 0;
            }

            if sa >= m {
                println!("A {}", total_p);
                break;
            }
            if sb >= m {
                println!("B {}", total_p);
                break;
            }
        }

        if sa < m && sb < m {
            println!("X");
        }
    }
}
