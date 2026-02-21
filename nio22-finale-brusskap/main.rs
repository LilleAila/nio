use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [k, n]: [i32; 2] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()[..]
        .try_into()
        .unwrap();

    let mut transactions: Vec<i32> = Vec::new();
    for _ in 0..n {
        let l = lines.next().unwrap().unwrap();
        let d: i32 = l[1..].parse::<i32>().unwrap() * if &l[0..1] == "+" { 1 } else { -1 };
        transactions.push(d);
    }
    let transactions = transactions;

    let mut a = 0;
    let mut b = 0;
    let mut resets = 0;

    for t in transactions {
        a += t;
        b += t;

        if b < 0 || a > k {
            a = 0.max(t);
            b = k.min(k + t);
            resets += 1;
        } else {
            b = b.min(k);
            a = a.max(0);
        }
    }

    println!("{}", resets);
}
