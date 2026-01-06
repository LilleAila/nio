use std::convert::TryInto;
use std::io::{self, Write};

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

        // Binary search would be optimal if we didn't take cost into perspective
        // This algorithm becomes more optimal as the limit of N approaches infinity.
        // Due to this, it is likely the best for subtask 4 where N >= 30, but worse
        // for the earlier ones where N has an upper bound.
        let mut a = a;
        let mut b = b;
        let mut k: i32;
        let mut success: i32 = 0;
        while success < n {
            k = (b + a) / 2;
            println!("send {}", a);
            io::stdout().flush().unwrap();
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
