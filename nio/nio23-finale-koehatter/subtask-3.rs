use std::collections::VecDeque;
use std::io;

const MOD: usize = 1_000_000_007;

fn main() {
    let mut lines = io::stdin().lines();
    let _n: usize = lines.next().unwrap().unwrap().parse().unwrap();

    let actions: Vec<u8> = lines
        .next()
        .unwrap()
        .unwrap()
        .chars()
        .map(|x| x.to_digit(10).unwrap() as u8)
        .collect();

    let mut subsequences: usize = 1;
    let mut last: [usize; 2] = [0, 0];
    for &x in &actions {
        let new_subsequences = (subsequences * 2 - last[x as usize] + MOD) % MOD;
        last[x as usize] = subsequences;
        subsequences = new_subsequences;

        println!("{}", subsequences - 1);
    }
}
