// Uses a BTreeMap instead of a combination of BTreeSet and HashMap
// A BTreeMap is like a HashMap but again sorted just like with BTreeSet

use std::collections::BTreeMap;
use std::io;

#[derive(Debug)]
struct Node<T> {
    value: T,
    left: Option<Box<Node<T>>>,
    right: Option<Box<Node<T>>>,
}

impl<T> Node<T> {
    fn new(value: T) -> Self {
        Node {
            value,
            left: None,
            right: None,
        }
    }
}

fn main() {
    let mut lines = io::stdin().lines();

    let n: usize = lines.next().unwrap().unwrap().parse().unwrap();

    let xs: Vec<usize> = lines
        .next()
        .unwrap()
        .unwrap()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut tree: BTreeMap<usize, usize> = BTreeMap::new();

    tree.insert(xs[0], 0);
    println!("0");

    for &x in &xs[1..] {
        let l = tree.range(..x).next_back().map(|(_, &d)| d);
        let r = tree.range(x + 1..).next().map(|(_, &d)| d);

        let d = l.unwrap_or(0).max(r.unwrap_or(0)) + 1;
        tree.insert(x, d);

        println!("{}", d);
    }
}
