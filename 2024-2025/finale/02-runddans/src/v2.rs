use std::collections::{HashMap, HashSet};
use std::convert::TryInto;
use std::io;

fn main() {
    let mut lines = io::stdin().lines();

    let n: usize = lines.next().unwrap().unwrap().parse().unwrap();

    let mut people: HashMap<String, (String, String)> = HashMap::new();

    for _ in 0..n {
        let [man, woman1, woman2]: [String; 3] = lines
            .next()
            .unwrap()
            .unwrap()
            .split_whitespace()
            .map(|x| x.to_string())
            .collect::<Vec<_>>()
            .try_into()
            .unwrap();

        people.insert(woman2, (man, woman1));
    }

    let mut stack: Vec<(String, Vec<String>)> = Vec::new();
    let mut visited: HashSet<String> = HashSet::new();
    let start = people.iter().min_by_key(|(_, (m, _))| m).unwrap().0.clone();
    stack.push((start, vec![]));

    while let Some((w, path)) = stack.pop() {
        if visited.contains(&w) {
            for p in path {
                println!("{}", p);
            }
            break;
        }

        let (m, next_w) = people[&w].clone();
        let mut path = path.clone();
        path.push(m);
        visited.insert(w);
        stack.push((next_w, path));
    }
}
