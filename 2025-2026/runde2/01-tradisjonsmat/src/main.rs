// use std::collections::HashMap;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let n: i64 = lines.next().unwrap().unwrap().trim().parse().unwrap();
    let halves: Vec<i64> = lines
        .next()
        .unwrap()
        .unwrap()
        .trim()
        .split(" ")
        .map(|x| x.parse().unwrap())
        .collect();

    let sum: i64 = halves.iter().sum();
    if sum % n != 0 {
        println!("-1");
        return;
    }

    let mut halves: Vec<(usize, i64)> = halves.iter().enumerate().map(|(i, &v)| (i, v)).collect();
    halves.sort_by_key(|&(_, v)| v);
    let (a, b) = halves.split_at_mut(n as usize);
    b.reverse();

    for ((i1, _), (i2, _)) in a.iter().zip(b.iter()) {
        println!("{} {}", i1, i2);
    }

    // let target_weight: i64 = sum / n;
    // let mut halves: HashMap<usize, i64> = halves.iter().enumerate().map(|(i, &v)| (i, v)).collect();
    // let mut results: Vec<(usize, usize)> = vec![];
    // while !halves.is_empty() {
    //     let i1 = *halves.keys().next().unwrap();
    //     let w1 = halves.remove(&i1).unwrap();
    //     let target = target_weight - w1;
    //     if let Some((&i2, _)) = halves.iter().find(|&(_, &v)| v == target) {
    //         halves.remove(&i2);
    //         results.push((i1, i2));
    //     } else {
    //         println!("-1");
    //         return;
    //     }
    // }
    //
    // for (i1, i2) in results {
    //     println!("{} {}", i1, i2);
    // }
}
