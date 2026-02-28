// Not quite O(n), but still much more efficient than the previous version
// Instead of checking for duplicate items and testing every interval,
// it builds up an interval, and when it encounters a pre existing value,
// it shifts the start of that interval to where this value last occured

use std::collections::HashMap;
use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let [n, _m, k]: [usize; 3] = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let tastes: Vec<usize> = lines
        .next()
        .unwrap()
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut c: HashMap<usize, usize> = HashMap::new();
    let mut a: usize = 0;
    let mut i = 0;
    let mut result = 0;
    while a <= n - k {
        let x = tastes[i];
        if let Some(&j) = c.get(&x) {
            for &l in &tastes[a..=j] {
                c.remove(&l);
            }
            c.insert(x, i);
            a = j + 1;
        }
        c.insert(x, i);
        i += 1;

        if c.len() == k {
            result += 1;
            c = HashMap::new();
            a = i;
        }
    }

    println!("{}", result);
}
