use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let r: i32 = lines.next().unwrap().unwrap().trim().parse().unwrap();

    for _ in 0..r {
        let [a, b, n]: [i32; 3] = lines
            .next()
            .unwrap()
            .unwrap()
            .trim()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect::<Vec<_>>()[..]
            .try_into()
            .unwrap();

        let mut a = a;
        let mut b = b;
        let mut k: i32;
        let mut success: i32 = 0;
        while success < n {
            k = (b + a) / 2;
            println!("send {}", k);
            let result = lines.next().unwrap().unwrap().trim() == "landet";
            if result {
                b = k;
                success += 1;
            } else {
                a = k + 1;
            }
        }
    }
}
