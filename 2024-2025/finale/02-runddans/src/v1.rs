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

        people.insert(man, (woman1, woman2));
    }

    let mut stack: Vec<(String, Vec<String>)> = Vec::new();
    let mut visited: HashSet<String> = HashSet::new();
    let start = people.keys().min().unwrap().clone();
    stack.push((people[&start].0.clone(), vec![start.clone()]));

    while let Some((woman, path)) = stack.pop() {
        let (m, (w1, _)) = people
            .iter()
            .find(|(_, (_, w2))| w2 == &woman)
            .map(|(x, y)| (x.clone(), y.clone()))
            .unwrap();

        if m == start {
            for p in path {
                println!("{}", p);
            }
            break;
        }

        if !visited.contains(&m) {
            let mut path = path.clone();
            path.push(m.clone());
            stack.push((w1, path));
            visited.insert(m);
        }
    }
}
