use std::collections::{HashMap, HashSet};
use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let n: usize = lines.next().unwrap().unwrap().parse().unwrap();

    let mut next: HashMap<String, String> = HashMap::with_capacity(n);
    let mut men: HashMap<String, String> = HashMap::with_capacity(n);

    let mut start: Option<String> = None;

    for _ in 0..n {
        let [m, w1, w2]: [String; 3] = lines
            .next()
            .unwrap()
            .unwrap()
            .split_whitespace()
            .map(|x| x.to_string())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        next.insert(w2.clone(), w1);
        men.insert(w2.clone(), m.clone());

        match &start {
            None => start = Some(w2.clone()),
            Some(s) if m < men[s] => start = Some(w2.clone()),
            _ => {}
        }
    }

    let mut c = start.unwrap();

    for _ in 0..n {
        println!("{}", men[&c]);
        c = next[&c].clone();
    }
}
